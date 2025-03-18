//
// Created by lkl on 24-8-31.
//
#include "SVF-LLVM/LLVMUtil.h"
#include "Graphs/SVFG.h"
#include "WPA/Andersen.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include "Util/Options.h"
#include "MemoryModel/PointerAnalysis.h"
#include "Graphs/PTACallGraph.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Constants.h"
#include <string>

using namespace llvm;
using namespace std;
using namespace SVF;
typedef FIFOWorkList<NodeID> WorkList;
typedef SCCDetection<PTACallGraph*> CallGraphSCC;
typedef std::set<SVFValue *> SVFValueBS;
typedef Map<const SVFFunction *, SVFValueBS>FunToParaMap;

FunToParaMap funToInputParaMap;
FunToParaMap funToOutputParaMap;
FunToParaMap funToInputGlobalMap;
FunToParaMap funToOutputGlobalMap;
Map<llvm::Value *, DILocalVariable *> IRToSouceVaribale;
Map<llvm::Value *, set<StoreInst *>> PointerOperandToStoreInst;
PointerAnalysis *pta;
Map<llvm::Function *, set<StoreInst *>> funToStrongUpdateInst;
Map<llvm::Function *, DominatorTree *>funToDomTree;
Map<const SVFFunction *, std::set<Argument *>> funToParametersMap;

// add by dyd
std::vector<llvm::Function *> FunTotal;
FunToParaMap funStateVarMap;
FunToParaMap funArgVarMap;
Map<SVFValue *, string> varToTypeMap;

// std::string parseType(DIType *Type) {
//     if (auto *DerivedType = dyn_cast<DIDerivedType>(Type)) {
//         std::string basicType = parseType(DerivedType->getBaseType());
//         if (DerivedType->getTag() == llvm::dwarf::DW_TAG_pointer_type) {
//             return basicType + "*";
//         }
//         // 其他派生类型处理...
//     } else if (auto *BasicType = dyn_cast<DIBasicType>(Type)) {
//         return BasicType->getName().str();
//     } else if (auto *CompositeType = dyn_cast<DICompositeType>(Type)) {
//         if (CompositeType->getTag() == llvm::dwarf::DW_TAG_array_type) {
//             DIType *baseType = CompositeType->getBaseType();
//             std::string baseTypeName = parseType(baseType);
//             unsigned arraySize = 0;
//             DINodeArray elements = CompositeType->getElements();
//             if (!elements.empty()) {
//                 if (auto Count = dyn_cast<ConstantInt>(Subrange->getCount())) {
//                     arraySize = Count->getZExtValue();
//                 }
//             }
//             return baseTypeName + " array [" + std::to_string(arraySize) + "]";
//         }
//         // 其他复合类型处理...
//     } else {
//         return "Unknown type";
//     }
// }

std::string parseType(DIType *Type) {
    if (!Type) {
        return "Unknown type";
    }
    // 处理派生类型（如指针、引用等）
    if (auto *DerivedType = dyn_cast<DIDerivedType>(Type)) {
        std::string basicType = parseType(DerivedType->getBaseType());
        switch (DerivedType->getTag()) {
            case llvm::dwarf::DW_TAG_pointer_type:
                return basicType + "*";
            case llvm::dwarf::DW_TAG_const_type:
                return "const " + basicType;
            case llvm::dwarf::DW_TAG_volatile_type:
                return "volatile " + basicType;
            case llvm::dwarf::DW_TAG_restrict_type:
                return "restrict " + basicType;
            case llvm::dwarf::DW_TAG_reference_type: {
                // 尝试通过名称或其他属性区分左值引用和右值引用
                if (DerivedType->getName().str() == "lvalue reference") {
                    return basicType + "&";
                } else if (DerivedType->getName().str() == "rvalue reference") {
                    return basicType + "&&";
                }
                // 如果无法区分，默认处理为左值引用
                return basicType + "&";
            }
            case llvm::dwarf::DW_TAG_typedef: {
                // 处理 typedef 类型
                return DerivedType->getName().str();
            }
            case llvm::dwarf::DW_TAG_subroutine_type: {
                // 处理函数类型
                // 这里可以进一步解析函数的参数和返回类型
                return "function(" + basicType + ")";
            }
            default: {
                // 对于其他未识别的派生类型，递归解析基类型
                outs() << "Warning: Unhandled derived type tag: " << DerivedType->getTag() << "\n";
                return basicType;
            }
        }
    }

    // 处理基本类型
    else if (auto *BasicType = dyn_cast<DIBasicType>(Type)) {
        return BasicType->getName().str();
    }

    // 处理复合类型（如数组、结构体、联合体等）
    else if (auto *CompositeType = dyn_cast<DICompositeType>(Type)) {
        switch (CompositeType->getTag()) {
            case llvm::dwarf::DW_TAG_structure_type:
                return "struct " + CompositeType->getName().str();
            case llvm::dwarf::DW_TAG_union_type:
                return "union " + CompositeType->getName().str();
            case llvm::dwarf::DW_TAG_class_type:
                return "class " + CompositeType->getName().str();
            case llvm::dwarf::DW_TAG_array_type: {
                DIType *baseType = CompositeType->getBaseType();
                std::string baseTypeName = parseType(baseType);

                // 获取数组的维度信息
                DINodeArray elements = CompositeType->getElements();
                std::vector<unsigned> dimensions;

                for (const auto &element : elements) {
                    if (auto *Subrange = dyn_cast<DISubrange>(element)) {
                        // 使用 dyn_cast 从 PointerUnion 中提取 ConstantInt*
                        if (llvm::ConstantInt *Count = Subrange->getCount().dyn_cast<llvm::ConstantInt*>()) {
                            dimensions.push_back(Count->getZExtValue());
                        } else {
                            // 如果 getCount() 返回的不是 ConstantInt*，打印警告
                            outs() << "Warning: getCount() did not return a ConstantInt\n";
                        }
                    }
                }

                // 构建数组类型的字符串表示
                std::string arrayType = baseTypeName;
                for (unsigned dim : dimensions) {
                    arrayType += " [" + std::to_string(dim) + "]";
                }

                return arrayType;
            }
            // 可以根据需要添加更多复合类型的处理
            default:
                return "Unknown composite type";
        }
    }

    // 处理枚举类型
    else if (auto *EnumType = dyn_cast<DIEnumerator>(Type)) {
        return "enum " + EnumType->getName().str();
    }

    // 处理其他未识别的类型
    else {
        return "Unknown type";
    }
}
    //

// 获取全局变量的类型信息
DIType *getDITypeFromGlobalVariable(GlobalVariable *GV) {
    if (!GV) {
        return nullptr;
    }

    // 获取与全局变量关联的调试信息节点
    MDNode *MD = GV->getMetadata("dbg");
    if (!MD) {
        // outs()<<"没有调试信息"<<"\n";
        return nullptr; // 没有调试信息
    }

    // 提取 DIGlobalVariable 节点
    DIGlobalVariableExpression *DIGVE = dyn_cast<DIGlobalVariableExpression>(MD);
    if (!DIGVE) {
        // outs()<<"节点类型不匹配"<<"\n";
        return nullptr; // 节点类型不匹配
    }

    // 获取 DIGlobalVariable 节点
    DIGlobalVariable *DIGV = DIGVE->getVariable();
    if (!DIGV) {
        return nullptr; // 节点类型不匹配
    }

    // 获取类型信息
    DIType *VarType = DIGV->getType();
    return VarType;
}


/*!
 * An example to query alias results of two LLVM values
 */
SVF::AliasResult aliasQuery(Value* v1, Value* v2)
{
    SVFValue* val1 = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(v1);
    SVFValue* val2 = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(v2);

    return pta->alias(val1,val2);
}

/*!
 * An example to print points-to set of an LLVM value
 */
std::string printPts(PointerAnalysis* pta, Value* val)
{

    std::string str;
    raw_string_ostream rawstr(str);
    SVFValue* svfval = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(val);

    NodeID pNodeId = pta->getPAG()->getValueNode(svfval);
    const PointsTo& pts = pta->getPts(pNodeId);
    for (PointsTo::iterator ii = pts.begin(), ie = pts.end();
         ii != ie; ii++)
    {
        rawstr << " " << *ii << " ";
        PAGNode* targetObj = pta->getPAG()->getGNode(*ii);
        if(targetObj->hasValue())
        {
            rawstr << "(" << targetObj->getValue()->toString() << ")\t ";
        }
    }

    return rawstr.str();

}


/*!
 * An example to query/collect all successor nodes from a ICFGNode (iNode) along control-flow graph (ICFG)
 */
void traverseOnICFG(ICFG* icfg, const Instruction* inst)
{
    SVFInstruction* svfinst = LLVMModuleSet::getLLVMModuleSet()->getSVFInstruction(inst);

    ICFGNode* iNode = icfg->getICFGNode(svfinst);
    FIFOWorkList<const ICFGNode*> worklist;
    Set<const ICFGNode*> visited;
    worklist.push(iNode);

    /// Traverse along VFG
    while (!worklist.empty())
    {
        const ICFGNode* iNode = worklist.pop();
        for (ICFGNode::const_iterator it = iNode->OutEdgeBegin(), eit =
                iNode->OutEdgeEnd(); it != eit; ++it)
        {
            ICFGEdge* edge = *it;
            ICFGNode* succNode = edge->getDstNode();
            if (visited.find(succNode) == visited.end())
            {
                visited.insert(succNode);
                worklist.push(succNode);
            }
        }
    }
}

/*!
 * An example to query/collect all the uses of a definition of a value along value-flow graph (VFG)
 */
void traverseOnVFG(const SVFG* vfg, Value* val)
{
    SVFIR* pag = SVFIR::getPAG();
    SVFValue* svfval = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(val);

    PAGNode* pNode = pag->getGNode(pag->getValueNode(svfval));
    const VFGNode* vNode = vfg->getDefSVFGNode(pNode);
    FIFOWorkList<const VFGNode*> worklist;
    Set<const VFGNode*> visited;
    worklist.push(vNode);

    /// Traverse along VFG
    while (!worklist.empty())
    {
        const VFGNode* vNode = worklist.pop();
        for (VFGNode::const_iterator it = vNode->OutEdgeBegin(), eit =
                vNode->OutEdgeEnd(); it != eit; ++it)
        {
            VFGEdge* edge = *it;
            VFGNode* succNode = edge->getDstNode();
            if (visited.find(succNode) == visited.end())
            {
                visited.insert(succNode);
                worklist.push(succNode);
            }
        }
    }

    /// Collect all LLVM Values
    for(Set<const VFGNode*>::const_iterator it = visited.begin(), eit = visited.end(); it!=eit; ++it)
    {
        const VFGNode* node = *it;
        /// can only query VFGNode involving top-level pointers (starting with % or @ in LLVM IR)
        /// PAGNode* pNode = vfg->getLHSTopLevPtr(node);
        /// Value* val = pNode->getValue();
    }
}

bool aliasWithParaAndItsPointsTO(Function *llvmFun, SVFValue *arg, SVFValue *storedValue){

    auto svfFunction = LLVMModuleSet::getLLVMModuleSet()->getSVFFunction(llvmFun);
    NodeID argNodeId = pta->getPAG()->getValueNode(arg);

    std::set<NodeID> pointToNode;
    std::queue<NodeID> worklist;
    worklist.push(argNodeId);
    while(!worklist.empty()){

        auto currentNodeID = worklist.front();
        worklist.pop();

        if(pointToNode.find(currentNodeID) != pointToNode.end()){
            continue;
        }
        pointToNode.insert(currentNodeID);

        PAGNode* targetObj = pta->getPAG()->getGNode(currentNodeID);
        if(targetObj->hasValue())
        {
            auto value = targetObj->getValue();
            if (pta->alias(value, storedValue) == AliasResult::MayAlias) {
                funToOutputParaMap[svfFunction].insert(arg);
                return true;
            }

            auto argPts = pta->getPts(currentNodeID);
            for (PointsTo::iterator ii = argPts.begin(), ie = argPts.end();
                 ii != ie; ii++)
            {
                worklist.push(*ii);
            }
        }
    }

    return false;

}

void getCallGraphSCCRevTopoOrder(WorkList& worklist, CallGraphSCC* callGraphSCC)
{

    NodeStack& topoOrder = callGraphSCC->topoNodeStack();
    while(!topoOrder.empty())
    {
        NodeID callgraphNodeID = topoOrder.top();
        topoOrder.pop();
        worklist.push(callgraphNodeID);
    }
}

static bool isBuiltinGlobal(StringRef GlobalName) {
    return GlobalName.find("llvm") == 0;
}

void getArgPointTo(SVFValue *svfArg, std::set<NodeID> &pointToNode){


    NodeID argNodeId = pta->getPAG()->getValueNode(svfArg);

    std::queue<NodeID> worklist;
    worklist.push(argNodeId);
    while(!worklist.empty()){

        auto currentNodeID = worklist.front();
        worklist.pop();

        if(pointToNode.find(currentNodeID) != pointToNode.end()){
            continue;
        }
        pointToNode.insert(currentNodeID);

        PAGNode* targetObj = pta->getPAG()->getGNode(currentNodeID);
        if(targetObj->hasValue())
        {
            auto argPts = pta->getPts(currentNodeID);
            for (PointsTo::iterator ii = argPts.begin(), ie = argPts.end();
                 ii != ie; ii++)
            {
                if(pointToNode.find((*ii)) != pointToNode.end()){
                    continue;
                }
                worklist.push(*ii);
            }
        }
    }


}



bool aliasWithParaAndItsPointsTO(std::map<SVFValue *, std::set<NodeID>> &argPointTo, SVFValue *arg, SVFValue *storedValue){
    for(auto valueID : argPointTo[arg]){
        auto targetNode = pta->getPAG()->getGNode(valueID);
        if(targetNode->hasValue()){
            auto value = pta->getPAG()->getGNode(valueID)->getValue();

            if (pta->alias(value, storedValue) == AliasResult::MayAlias) {

                return true;
            }
        }
    }
    return false;

}

void handleFunctionSeparately(std::vector<GlobalVariable *> &globals, Function *llvmFun){

    if(llvmFun->isDeclaration() || llvmFun->getName().startswith("llvm")){
        return ;
    }
    std::set<GlobalVariable *>usedGlobals;

    /// find globalVariables used in llvmFun
    for (auto GV : globals) {

        if (GV->isConstant() || isBuiltinGlobal(GV->getName()))
            continue;
        std::queue<User *>worklist;
        worklist.push(GV);
        std::set<User *> visitedUser;
        while(!worklist.empty()){
            User *u = worklist.front();
            visitedUser.insert(u);
            worklist.pop();
            for (auto ui = u->use_begin(); ui != u->use_end(); ui++) {
                auto *user = ui->getUser();

                // avoid to search in infinite loop
                if (visitedUser.find(user) != visitedUser.end())
                    continue;

                if (Instruction *useInst = dyn_cast<Instruction>(user)) {
                    Function *caller = useInst->getParent()->getParent();
                    if(caller == llvmFun)
                        usedGlobals.insert(GV);
                }else
                    worklist.push(user);
            }
        }
    }
    std::map<SVFValue *, std::set<NodeID>> argWithItsPointTo;
    std::map<SVFValue *, std::set<NodeID>> globalWithItsPointTo;

    auto svfFunction = LLVMModuleSet::getLLVMModuleSet()->getSVFFunction(llvmFun);

    auto domTree = new DominatorTree(*llvmFun);
    funToDomTree[llvmFun] = domTree;
    std::vector<Value *> args;
    llvm::outs()<<"compute pointTo set start\n";
    for(auto &arg : llvmFun->args()){
        funToParametersMap[svfFunction].insert(&arg);
//        funToInputParaMap[svfFunction].insert(LLVMModuleSet::getLLVMModuleSet()->getSVFValue(&arg));
        SVFValue* svfArg = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(&arg);
        std::set<NodeID> PointToNodes;
        getArgPointTo(svfArg,PointToNodes);
        argWithItsPointTo[svfArg] = PointToNodes;
        args.push_back(&arg);
    }

    for (auto global: usedGlobals) {
        SVFValue* svfGlobal = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(global);
        std::set<NodeID> PointToNodes;
        getArgPointTo(svfGlobal,PointToNodes);
        globalWithItsPointTo[svfGlobal] = PointToNodes;
    }
    llvm::outs()<<"compute pointTo set end\n";

//    auto subprogram = llvmFun->getSubprogram();
//    if(subprogram == nullptr){
//        llvm::errs()<<"not compile with -g\n";
//        exit(0);
//    }


    for(auto &bb : *llvmFun){
        for(auto &inst : bb){
            if(auto storeInst = dyn_cast<StoreInst>(&inst)) {
                /// both name of parameter and global variable are equal to name in source code
                SVFValue* svfval = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(storeInst->getPointerOperand());
                NodeID pNodeId = pta->getPAG()->getValueNode(svfval);
                const PointsTo& pts = pta->getPts(pNodeId);
                bool strongUpdate = false;
                if(pts.count() == 1) {
                    strongUpdate = true;
                }
                /// avoid store para to the address of para and use the strong update to eliminate the use of para
                if(strongUpdate && IRToSouceVaribale.find(storeInst->getPointerOperand()) != IRToSouceVaribale.end()){
                    funToStrongUpdateInst[llvmFun].insert(storeInst);
                }
                for (auto argPair: argWithItsPointTo) {

                    bool result = aliasWithParaAndItsPointsTO(argWithItsPointTo, argPair.first, svfval);
                    if(result)
                        funToOutputParaMap[svfFunction].insert(argPair.first);
                    if(result && strongUpdate)
                        /// strong update. TODO: replace with must alias
                        funToStrongUpdateInst[llvmFun].insert(storeInst);
                }
                for (auto globalPair: globalWithItsPointTo) {

                    bool result = aliasWithParaAndItsPointsTO(globalWithItsPointTo, globalPair.first, svfval);
                    if(result)
                        funToOutputGlobalMap[svfFunction].insert(globalPair.first);
                    if(result && strongUpdate)
                        /// strong update. TODO: replace with must alias
                        funToStrongUpdateInst[llvmFun].insert(storeInst);
                }
                PointerOperandToStoreInst[storeInst->getPointerOperand()].insert(storeInst);
            }else if(auto loadInst = dyn_cast<LoadInst>(&inst)){
//                llvm::outs()<<*loadInst<<"\n";
                for (auto arg: args) {
                    bool loadFlag = true;
                    if (aliasQuery(loadInst->getPointerOperand(),arg) == AliasResult::MayAlias) {
                        for(auto storeInst : funToStrongUpdateInst[llvmFun]){
                            if(aliasQuery(storeInst->getPointerOperand(), arg) == AliasResult::MayAlias && domTree->dominates(storeInst->getParent(), &bb))
                                loadFlag = false;
                        }
                        if(loadFlag)
                            funToInputParaMap[svfFunction].insert(LLVMModuleSet::getLLVMModuleSet()->getSVFValue(arg));
                    }
                }

                for(auto dbgArgAddress : IRToSouceVaribale){
                    bool loadFlag = true;
                    if(loadInst->getPointerOperand() == dbgArgAddress.first && dbgArgAddress.second->isParameter()){
                        for(auto storeInst : funToStrongUpdateInst[llvmFun]){
                            if(storeInst->getPointerOperand() == dbgArgAddress.first && domTree->dominates(storeInst->getParent(), &bb)){
                                loadFlag = false;
                            }
                        }
                        if(loadFlag) {
                            funToInputParaMap[svfFunction].insert(LLVMModuleSet::getLLVMModuleSet()->getSVFValue(
                                    llvmFun->getArg(dbgArgAddress.second->getArg() - 1)));
                        }
                    }
                }
                for (auto global: usedGlobals) {

                    funToInputGlobalMap[svfFunction].insert(LLVMModuleSet::getLLVMModuleSet()->getSVFValue(global));

                    bool loadFlag = true;
                    if (aliasQuery(loadInst->getPointerOperand(),global) == AliasResult::MayAlias) {
                        for(auto storeInst : funToStrongUpdateInst[llvmFun]){
                            if(aliasQuery(storeInst->getPointerOperand(), global) == AliasResult::MayAlias && domTree->dominates(storeInst->getParent(), &bb))
                                loadFlag = false;
                        }
                        if(!loadFlag)
                        {
                            funToInputGlobalMap[svfFunction].erase(LLVMModuleSet::getLLVMModuleSet()->getSVFValue(global));

                        }
                        if(loadFlag)
                        {
                            funToInputGlobalMap[svfFunction].insert(LLVMModuleSet::getLLVMModuleSet()->getSVFValue(global));
                        }

                    }
                }
            }else if(auto retInst = dyn_cast<ReturnInst>(&inst)){
                if(!llvmFun->getReturnType()->isVoidTy()){
                    auto retValue = retInst->getReturnValue();
                    auto svfRetValue = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(retValue);

                    if(isa<Constant>(retValue)){
                        continue;
                    }

                    funToOutputParaMap[svfFunction].insert(svfRetValue);

                    if(auto loadRetValue = dyn_cast<LoadInst>(retValue)){
                        auto loadedOperand = loadRetValue->getPointerOperand();
                        auto it = IRToSouceVaribale.find(loadedOperand);
                        if(it != IRToSouceVaribale.end()){
                            /// store load(one level)
                            svfRetValue->setName(it->second->getName().str());
                            DIType *VarType = it->second->getType();
                            if (VarType) {
                                std::string sourceType = parseType(VarType);
                                varToTypeMap[svfRetValue] = sourceType;
                            }
                            continue;
                        }else{
                            auto storeIt = PointerOperandToStoreInst.find(loadedOperand);
                            /// store load store load( two levels)
                            if(storeIt != PointerOperandToStoreInst.end()){
                                string name = "";
                                for(auto storeInst : storeIt->second){
                                    auto localVarIt = IRToSouceVaribale.find(getLoadStorePointerOperand(storeInst->getValueOperand()));
                                    if(localVarIt != IRToSouceVaribale.end()){
                                        name += localVarIt->second->getName().str() + " ";
                                    }
                                }
                                svfRetValue->setName(name);

                            }
                        }
                    }
                }
            }else if(const DbgDeclareInst *dbgDelcare = dyn_cast<DbgDeclareInst>(&inst)){
                auto localVariable = dbgDelcare->getVariable();
                IRToSouceVaribale[dbgDelcare->getAddress()] = dbgDelcare->getVariable();
                DIType *VarType = localVariable->getType();

                if(localVariable->isParameter()) {
                    LLVMModuleSet::getLLVMModuleSet()->getSVFValue(
                            llvmFun->getArg(localVariable->getArg() - 1))->setName(localVariable->getName().str());

                    if (VarType) {
                        if (localVariable->getName().str() == "item")
                        {
                            outs() << "lalala" << "\n";
                        }
                        std::string sourceType = parseType(VarType);
                        SVFValue* svfValue = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(llvmFun->getArg(localVariable->getArg() - 1));
                        varToTypeMap[svfValue] = sourceType;
                    }
                }

            }
        }
    }

}

inline SVFValueBS& getModSideEffectOfFunction(const SVFFunction* fun)
{
    return funToOutputParaMap[fun];
}

inline const SVFValueBS& getRefSideEffectOfFunction(const SVFFunction* fun)
{
    return funToInputParaMap[fun];
}

//bool addRefSideEffectOfCallSite(const CallICFGNode* cs, const NodeBS& refs)
//{
//    if(!refs.empty())
//    {
//        NodeBS refset = refs;
//        refset &= getCallSiteArgsPts(cs);
//        getEscapObjviaGlobals(refset,refs);
//        addRefSideEffectOfFunction(cs->getCaller(),refset);
//        return csToRefsMap[cs] |= refset;
//    }
//    return false;
//}
//
//bool addModSideEffectOfCallSite(const CallICFGNode* cs, const NodeBS& mods)
//{
//    if(!mods.empty())
//    {
//        NodeBS modset = mods;
//        modset &= (getCallSiteArgsPts(cs) | getCallSiteRetPts(cs));
//        getEscapObjviaGlobals(modset,mods);
//        addModSideEffectOfFunction(cs->getCaller(),modset);
//        return csToModsMap[cs] |= modset;
//    }
//    return false;
//}

/// add callee's modref to caller, returns true if changed
bool handleCallsiteModRef(std::set<SVFValue *>& mod, std::set<SVFValue *>& ref, const CallICFGNode* cs, const SVFFunction* callee)
{
    /// if a callee is a heap allocator function, then its mod set of this callsite is the heap object.
//    if(isHeapAllocExtCall(cs->getCallSite()))
//    {
//        SVFStmtList& pagEdgeList = getPAGEdgesFromInst(cs->getCallSite());
//        for (SVFStmtList::const_iterator bit = pagEdgeList.begin(),
//                     ebit = pagEdgeList.end(); bit != ebit; ++bit)
//        {
//            const PAGEdge* edge = *bit;
//            if (const AddrStmt* addr = SVFUtil::dyn_cast<AddrStmt>(edge))
//                mod.set(addr->getRHSVarID());
//        }
//    }
        /// otherwise, we find the mod/ref sets from the callee function, who has definition and been processed
//    else
//    {
//        mod = getModSideEffectOfFunction(callee);
//        ref = getRefSideEffectOfFunction(callee);
//    }
    bool change = false;

    /// add modified global variables from callee
    auto modGlobals = funToOutputGlobalMap[callee];
    for(auto modGlobal : modGlobals){
        auto callerOutputGloabls = funToOutputGlobalMap[cs->getCaller()];
        auto it = callerOutputGloabls.find(modGlobal);
        if(it == callerOutputGloabls.end()){
            funToOutputGlobalMap[cs->getCaller()].insert(modGlobal);
            change = true;
        }
    }

    /// add referenced global variables from callee
    auto refGlobals = funToInputGlobalMap[callee];
    for(auto refGlobal : refGlobals){
        auto callerInputGloabls = funToInputGlobalMap[cs->getCaller()];
        auto it = callerInputGloabls.find(refGlobal);
        if(it == callerInputGloabls.end()){
            funToInputGlobalMap[cs->getCaller()].insert(refGlobal);
            change = true;
        }
    }

    /// add modified parameters from callee
    auto modParas = funToOutputParaMap[callee];
    for(auto modPara : modParas){
        for(auto para : funToParametersMap[cs->getCaller()]){
            auto svfPara = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(para);
            if(pta->alias(modPara, svfPara)){
                auto callerOutputParas = funToOutputParaMap[cs->getCaller()];
                auto it = callerOutputParas.find(svfPara);
                if(it == callerOutputParas.end()){
                    funToOutputParaMap[cs->getCaller()].insert(svfPara);
                    change = true;
                }

            }

        }
    }

    /// add referenced parameters from callee
//    auto refParas = funToInputParaMap[callee];
//    for(auto para : funToParametersMap[cs->getCaller()]){
//        auto svfPara = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(para);
//        for(auto refPara : refParas){
//            if(pta->alias(refPara, svfPara)){
//                auto callerInputParas = funToInputParaMap[cs->getCaller()];
//                auto it = callerInputParas.find(svfPara);
//                if(it == callerInputParas.end()){
//                    funToInputParaMap[cs->getCaller()].insert(svfPara);
//                    change = true;
//                }
//
//            }
//        }
//    }



    // add ref set
//    bool refchanged = addRefSideEffectOfCallSite(cs, ref);
    // add mod set
//    bool modchanged = addModSideEffectOfCallSite(cs, mod);

    return change;
}

void handleFunctionIterately(PTACallGraphNode*callGraphNode, WorkList& worklist){
    for(PTACallGraphNode::iterator it = callGraphNode->InEdgeBegin(), eit = callGraphNode->InEdgeEnd();
        it!=eit; ++it)
    {
        PTACallGraphEdge* edge = *it;

        /// handle direct callsites
        for(PTACallGraphEdge::CallInstSet::iterator cit = edge->getDirectCalls().begin(),
                    ecit = edge->getDirectCalls().end(); cit!=ecit; ++cit)
        {
            std::set<SVFValue *> mod, ref;
            const CallICFGNode* cs = (*cit);
            bool modrefchanged = handleCallsiteModRef(mod, ref, cs, callGraphNode->getFunction());
            ///TODO: what function?
            if(modrefchanged)
                worklist.push(edge->getSrcID());
        }
        /// handle indirect callsites
        for(PTACallGraphEdge::CallInstSet::iterator cit = edge->getIndirectCalls().begin(),
                    ecit = edge->getIndirectCalls().end(); cit!=ecit; ++cit)
        {
            std::set<SVFValue *> mod, ref;
            const CallICFGNode* cs = (*cit);
            bool modrefchanged = handleCallsiteModRef(mod, ref, cs, callGraphNode->getFunction());
            if(modrefchanged)
                worklist.push(edge->getSrcID());
        }
    }
}

int main(int argc, char ** argv)
{

    std::vector<std::string> moduleNameVec;
    moduleNameVec = OptionBase::parseOptions(
            argc, argv, "Whole Program Points-to Analysis", "[options] <input-bitcode...>"
    );

    if (Options::WriteAnder() == "ir_annotator")
    {
        LLVMModuleSet::preProcessBCs(moduleNameVec);
    }

    SVFModule* svfModule = LLVMModuleSet::buildSVFModule(moduleNameVec);

    /// Build Program Assignment Graph (SVFIR)
    SVFIRBuilder builder(svfModule);
    SVFIR* pag = builder.build();

    /// Create Andersen's pointer analysis
    Andersen* ander = AndersenWaveDiff::createAndersenWaveDiff(pag);

    pta = ander;
    /// Query aliases
    /// aliasQuery(ander,value1,value2);

    /// Print points-to information
    /// printPts(ander, value1);

    /// Call Graph
    PTACallGraph* callgraph = ander->getPTACallGraph();

    auto _callGraphScc = ander->getCallGraphSCC();
    std::vector<GlobalVariable *> globalVariables;
    for (size_t i = 0; i < LLVMModuleSet::getLLVMModuleSet()->getModuleNum(); ++i) {
        Module &module = LLVMModuleSet::getLLVMModuleSet()->getModuleRef(i);
        for(auto &globalVariable : module.globals()){
            globalVariables.push_back(&globalVariable);
        }
    }

    /// compute input & output for each function separately
    for (size_t i = 0; i < LLVMModuleSet::getLLVMModuleSet()->getModuleNum(); ++i)
    {
        Module& module = LLVMModuleSet::getLLVMModuleSet()->getModuleRef(i);
        auto size = module.getFunctionList().size();
        unsigned counter = 0;
        for(auto &func : module){
            FunTotal.push_back(&func);
            llvm::outs()<<func.getName()<<":start"<<counter++<<"|"<<size<<"\n";
            handleFunctionSeparately(globalVariables,&func);
            llvm::outs()<<func.getName()<<":finish\n";
        }
    }

    /// bottom up compute input & output iteratively
    Set<const SVFFunction*> _recursiveFuns;
    for(auto it = callgraph->begin(); it != callgraph->end(); it++){
        auto nodeID = it->second;
        if(_callGraphScc->isInCycle(it->second->getId()))
            _recursiveFuns.insert(it->second->getFunction());
    }

    _callGraphScc->find();
    auto topoNodes = _callGraphScc->topoNodeStack();
    WorkList worklist;
    getCallGraphSCCRevTopoOrder(worklist, _callGraphScc);
    while(!worklist.empty())
    {
        NodeID callGraphNodeID = worklist.pop();
        /// handle all sub scc nodes of this rep node
        const NodeBS& subNodes = _callGraphScc->subNodes(callGraphNodeID);

        for(NodeBS::iterator it = subNodes.begin(), eit = subNodes.end(); it!=eit; ++it)
        {
            PTACallGraphNode* subCallGraphNode = callgraph->getCallGraphNode(*it);
            /// Get mod-ref of all callsites calling callGraphNode
            handleFunctionIterately(subCallGraphNode,worklist);
        }
    }

    // for (size_t i = 0; i < LLVMModuleSet::getLLVMModuleSet()->getModuleNum(); ++i)
    // {
    //     Module& module = LLVMModuleSet::getLLVMModuleSet()->getModuleRef(i);
    //     for(auto &fun : module) {
    //         auto svfFun = LLVMModuleSet::getLLVMModuleSet()->getSVFFunction(&fun);
    //
    //         llvm::outs() << "##### Function: " << svfFun->getName() << "\n";
    //         llvm::outs() << "input: ";
    //         auto inputIt = funToInputParaMap.find(svfFun);
    //         if(inputIt != funToInputParaMap.end()){
    //             for (auto inputPara: inputIt->second) {
    //                 llvm::outs() << inputPara->getName() << " ";
    //             }
    //         }
    //
    //         auto it = funToInputGlobalMap.find(svfFun);
    //         if (it != funToInputGlobalMap.end()) {
    //             for (auto inputGlobal: it->second) {
    //                 llvm::outs() << inputGlobal->getName() << " ";
    //             }
    //         }
    //
    //         llvm::outs() << "\noutput: ";
    //         auto outputIt = funToOutputParaMap.find(svfFun);
    //         if (outputIt != funToOutputParaMap.end()) {
    //             for (auto outputPara: outputIt->second) {
    //                 llvm::outs() << outputPara->getName() << " ";
    //             }
    //         }
    //
    //         auto outputGlobalIt = funToOutputGlobalMap.find(svfFun);
    //         if (outputGlobalIt != funToOutputGlobalMap.end()) {
    //             for (auto outputGlobal: outputGlobalIt->second) {
    //                 llvm::outs() << outputGlobal->getName() << " ";
    //             }
    //         }
    //         llvm::outs() << "\n";
    //     }
    // }

    // add by dyd
    llvm::outs() << "========================================== SIP print ====================================\n";

    map<SVFValue*,std::set<SVFFunction*>> variableInputMap;
    map<SVFValue*,std::set<SVFFunction*>> variableOutputMap;
    map<SVFValue*,std::set<SVFFunction*>> variableBothMap;

    for(auto llvmFun : FunTotal)
    {
        auto svfFunction = LLVMModuleSet::getLLVMModuleSet()->getSVFFunction(llvmFun);
        auto inputGlobal = funToInputGlobalMap.find(svfFunction);
        auto outputGlobal = funToOutputGlobalMap.find(svfFunction);


        if(inputGlobal != funToInputGlobalMap.end())
        {
            for(auto inputG: inputGlobal->second)
                {
                    if(outputGlobal != funToOutputGlobalMap.end())
                    {
                         if (outputGlobal->second.find(inputG) != outputGlobal->second.end())
                         {
                             variableBothMap[inputG].insert(svfFunction);
                         }else
                         {
                             variableInputMap[inputG].insert(svfFunction);
                         }
                    }

                }
        }

        if(outputGlobal != funToOutputGlobalMap.end())
        {
            for(auto outputG: outputGlobal->second)
                {
                    if(inputGlobal != funToInputGlobalMap.end())
                    {
                        if (inputGlobal->second.find(outputG) == inputGlobal->second.end())
                        {
                            variableOutputMap[outputG].insert(svfFunction);
                        }
                    }

                }
        }

    }

    // FunToParaMap funStateVarMap;
    // FunToParaMap funArgVarMap;

    for(auto globalVar:globalVariables)
    {
        // outs()<<"globalVar name:"<<globalVar->getName()<<"\n";
        DIType *VarType = getDITypeFromGlobalVariable(globalVar);
        if (VarType) {
            llvm::outs()<<"start Type\n";
            std::string sourceType = parseType(VarType);
            llvm::outs()<<"end Type\n";
            SVFValue* svfValue = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(globalVar);
            varToTypeMap[svfValue] = sourceType;
        }

        // Collect which functions use global variables as input or output variables.
        SVFValue* svfVal = LLVMModuleSet::getLLVMModuleSet()->getSVFValue(globalVar);
        std::set<SVFFunction*> InOutFun;
        std::set<SVFFunction*> InFun;
        std::set<SVFFunction*> OutFun;
        auto BothSet = variableBothMap.find(svfVal);
        if(BothSet != variableBothMap.end())
        {
            InOutFun = BothSet->second;
        }
        auto InputSet = variableInputMap.find(svfVal);
        if(InputSet != variableInputMap.end())
        {
            InFun = InputSet->second;
        }
        auto OutputSet = variableOutputMap.find(svfVal);
        if(OutputSet != variableOutputMap.end())
        {
            OutFun = OutputSet->second;
        }

        if (InOutFun.size() == 1 && OutFun.size() == 0)
        {
            auto it = InOutFun.begin();
            funStateVarMap[*it].insert(svfVal);
        }

        if (InFun.size()!=0 && OutFun.size()==0 && InOutFun.size()==0)
        {
            for(auto it: InFun)
            {
                funArgVarMap[it].insert(svfVal);
            }
        }
    }

    //printf inputVar, outputVar, stateVar, argVar

    for (auto fun:FunTotal)
    {
        llvm::outs() << "##### Function: " << fun->getName() << " ##### \n";
        auto svfFunction = LLVMModuleSet::getLLVMModuleSet()->getSVFFunction(fun);

        llvm::outs() << "input:";
        auto inputIt = funToInputParaMap.find(svfFunction);
        if(inputIt != funToInputParaMap.end()){
            for (auto inputPara: inputIt->second) {
                llvm::outs() << "\n   varName:" << inputPara->getName() << " ";
                auto it = varToTypeMap.find(inputPara);
                if (it != varToTypeMap.end()) {
                    llvm::outs() << "   varType:" << it->second << " ";
                } else {
                    llvm::outs() << "   No type information found." << "\n";
                }
            }
        }

        auto it = funToInputGlobalMap.find(svfFunction);
        if (it != funToInputGlobalMap.end()) {
            for (auto inputGlobal: it->second) {
                llvm::outs() << "\n   varName:"<< inputGlobal->getName() << " ";
                auto it = varToTypeMap.find(inputGlobal);
                if (it != varToTypeMap.end()) {
                    llvm::outs() << "   varType:" << it->second << " ";
                } else {
                    llvm::outs() << "   No type information found for: " << inputGlobal->getName();
                }
            }
        }

        llvm::outs() << "\noutput: ";
        auto outputIt = funToOutputParaMap.find(svfFunction);
        if (outputIt != funToOutputParaMap.end()) {
            for (auto outputPara: outputIt->second) {
                llvm::outs() << "\n   varName:" << outputPara->getName() << " ";
                auto it = varToTypeMap.find(outputPara);
                if (it != varToTypeMap.end()) {
                    llvm::outs() << "   varType:" << it->second << " ";
                } else {
                    llvm::outs() << "    No type information found for: " << outputPara->getName();
                }
            }
        }

        auto outputGlobalIt = funToOutputGlobalMap.find(svfFunction);
        if (outputGlobalIt != funToOutputGlobalMap.end()) {
            for (auto outputGlobal: outputGlobalIt->second) {
                llvm::outs() << "\n   varName:" << outputGlobal->getName() << " ";
                auto it = varToTypeMap.find(outputGlobal);
                if (it != varToTypeMap.end()) {
                    llvm::outs() << "   varType:" << it->second << " ";
                } else {
                    llvm::outs() << "No type information found for: " << outputGlobal->getName();
                }
            }
        }
        llvm::outs() << "\n";

        llvm::outs() << "stateVar: ";
        for (auto stateVar:funStateVarMap[svfFunction])
        {
            llvm::outs() << "\n   varName:" << stateVar->getName() << " ";
            auto it = varToTypeMap.find(stateVar);
            if (it != varToTypeMap.end()) {
                llvm::outs() << "   varType:" << it->second << " ";
            } else {
                llvm::outs() << "No type information found for: " << stateVar->getName();
            }
        }
        llvm::outs() << "\n";

        llvm::outs() << "argVar: ";
        for (auto argVar:funArgVarMap[svfFunction])
        {
            llvm::outs() << "\n   varName:" << argVar->getName() << " ";
            auto it = varToTypeMap.find(argVar);
            if (it != varToTypeMap.end()) {
                llvm::outs() << "   varType:" << it->second << " ";
            } else {
                llvm::outs() << "No type information found." << argVar->getName();
            }
        }
        llvm::outs() << "\n";
    }

    // add by dyd



    /// ICFG
//    ICFG* icfg = pag->getICFG();

    /// Value-Flow Graph (VFG)
//    VFG* vfg = new VFG(callgraph);

    /// Sparse value-flow graph (SVFG)
//    SVFGBuilder svfBuilder;
//    SVFG* svfg = svfBuilder.buildFullSVFG(ander);

    /// Collect uses of an LLVM Value
    /// traverseOnVFG(svfg, value);

    /// Collect all successor nodes on ICFG
    /// traverseOnICFG(icfg, value);

    // clean up memory
//    delete vfg;
    AndersenWaveDiff::releaseAndersenWaveDiff();
    SVFIR::releaseSVFIR();

//    LLVMModuleSet::getLLVMModuleSet()->dumpModulesToFile(".svf.bc");
    SVF::LLVMModuleSet::releaseLLVMModuleSet();

    llvm::llvm_shutdown();
    return 0;
}
