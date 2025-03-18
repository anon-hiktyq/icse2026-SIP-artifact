; ModuleID = 'test/loop01.c'
source_filename = "test/loop01.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @bar(i32 noundef %a) #0 !dbg !10 {
entry:
  %a.addr = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  call void @llvm.dbg.declare(metadata ptr %a.addr, metadata !15, metadata !DIExpression()), !dbg !16
  %0 = load i32, ptr %a.addr, align 4, !dbg !17
  %1 = load i32, ptr %a.addr, align 4, !dbg !18
  %mul = mul nsw i32 %0, %1, !dbg !19
  ret i32 %mul, !dbg !20
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(ptr noundef %p, i32 noundef %a) #0 !dbg !21 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca ptr, align 8
  %a.addr = alloca i32, align 4
  %e = alloca i32, align 4
  store ptr %p, ptr %p.addr, align 8
  call void @llvm.dbg.declare(metadata ptr %p.addr, metadata !25, metadata !DIExpression()), !dbg !26
  store i32 %a, ptr %a.addr, align 4
  call void @llvm.dbg.declare(metadata ptr %a.addr, metadata !27, metadata !DIExpression()), !dbg !28
  call void @llvm.dbg.declare(metadata ptr %e, metadata !29, metadata !DIExpression()), !dbg !30
  %0 = load ptr, ptr %p.addr, align 8, !dbg !31
  %1 = load i32, ptr %0, align 4, !dbg !32
  store i32 %1, ptr %e, align 4, !dbg !30
  %2 = load i32, ptr %e, align 4, !dbg !33
  %3 = load i32, ptr %a.addr, align 4, !dbg !35
  %cmp = icmp sgt i32 %2, %3, !dbg !36
  br i1 %cmp, label %if.then, label %if.else, !dbg !37

if.then:                                          ; preds = %entry
  %4 = load ptr, ptr %p.addr, align 8, !dbg !38
  %5 = load i32, ptr %e, align 4, !dbg !40
  %sub = sub nsw i32 %5, 1, !dbg !41
  %call = call i32 @foo(ptr noundef %4, i32 noundef %sub), !dbg !42
  store i32 %call, ptr %retval, align 4, !dbg !43
  br label %return, !dbg !43

if.else:                                          ; preds = %entry
  %6 = load i32, ptr %a.addr, align 4, !dbg !44
  %call1 = call i32 @bar(i32 noundef %6), !dbg !46
  %7 = load ptr, ptr %p.addr, align 8, !dbg !47
  store i32 %call1, ptr %7, align 4, !dbg !48
  %8 = load i32, ptr %a.addr, align 4, !dbg !49
  store i32 %8, ptr %retval, align 4, !dbg !50
  br label %return, !dbg !50

return:                                           ; preds = %if.else, %if.then
  %9 = load i32, ptr %retval, align 4, !dbg !51
  ret i32 %9, !dbg !51
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !52 {
entry:
  %p = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %p, metadata !55, metadata !DIExpression()), !dbg !56
  %call = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !57
  store ptr %call, ptr %p, align 8, !dbg !56
  %0 = load ptr, ptr %p, align 8, !dbg !58
  store i32 5, ptr %0, align 4, !dbg !59
  %1 = load ptr, ptr %p, align 8, !dbg !60
  %call1 = call i32 @foo(ptr noundef %1, i32 noundef 5), !dbg !61
  ret i32 0, !dbg !62
}

; Function Attrs: nounwind allocsize(0)
declare noalias ptr @malloc(i64 noundef) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { nounwind allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind allocsize(0) }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "test/loop01.c", directory: "/home/lkl/SoftwareIP/SIP", checksumkind: CSK_MD5, checksum: "7436cf3b388477f51935504431c8dab6")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 8, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 2}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)"}
!10 = distinct !DISubprogram(name: "bar", scope: !1, file: !1, line: 2, type: !11, scopeLine: 2, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!11 = !DISubroutineType(types: !12)
!12 = !{!13, !13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !{}
!15 = !DILocalVariable(name: "a", arg: 1, scope: !10, file: !1, line: 2, type: !13)
!16 = !DILocation(line: 2, column: 13, scope: !10)
!17 = !DILocation(line: 3, column: 12, scope: !10)
!18 = !DILocation(line: 3, column: 16, scope: !10)
!19 = !DILocation(line: 3, column: 14, scope: !10)
!20 = !DILocation(line: 3, column: 5, scope: !10)
!21 = distinct !DISubprogram(name: "foo", scope: !1, file: !1, line: 6, type: !22, scopeLine: 6, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!22 = !DISubroutineType(types: !23)
!23 = !{!13, !24, !13}
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64)
!25 = !DILocalVariable(name: "p", arg: 1, scope: !21, file: !1, line: 6, type: !24)
!26 = !DILocation(line: 6, column: 14, scope: !21)
!27 = !DILocalVariable(name: "a", arg: 2, scope: !21, file: !1, line: 6, type: !13)
!28 = !DILocation(line: 6, column: 21, scope: !21)
!29 = !DILocalVariable(name: "e", scope: !21, file: !1, line: 7, type: !13)
!30 = !DILocation(line: 7, column: 9, scope: !21)
!31 = !DILocation(line: 7, column: 14, scope: !21)
!32 = !DILocation(line: 7, column: 13, scope: !21)
!33 = !DILocation(line: 8, column: 8, scope: !34)
!34 = distinct !DILexicalBlock(scope: !21, file: !1, line: 8, column: 8)
!35 = !DILocation(line: 8, column: 12, scope: !34)
!36 = !DILocation(line: 8, column: 10, scope: !34)
!37 = !DILocation(line: 8, column: 8, scope: !21)
!38 = !DILocation(line: 9, column: 20, scope: !39)
!39 = distinct !DILexicalBlock(scope: !34, file: !1, line: 8, column: 14)
!40 = !DILocation(line: 9, column: 23, scope: !39)
!41 = !DILocation(line: 9, column: 25, scope: !39)
!42 = !DILocation(line: 9, column: 16, scope: !39)
!43 = !DILocation(line: 9, column: 9, scope: !39)
!44 = !DILocation(line: 13, column: 18, scope: !45)
!45 = distinct !DILexicalBlock(scope: !34, file: !1, line: 12, column: 9)
!46 = !DILocation(line: 13, column: 14, scope: !45)
!47 = !DILocation(line: 13, column: 10, scope: !45)
!48 = !DILocation(line: 13, column: 12, scope: !45)
!49 = !DILocation(line: 14, column: 16, scope: !45)
!50 = !DILocation(line: 14, column: 9, scope: !45)
!51 = !DILocation(line: 16, column: 1, scope: !21)
!52 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 18, type: !53, scopeLine: 18, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!53 = !DISubroutineType(types: !54)
!54 = !{!13}
!55 = !DILocalVariable(name: "p", scope: !52, file: !1, line: 19, type: !24)
!56 = !DILocation(line: 19, column: 10, scope: !52)
!57 = !DILocation(line: 19, column: 14, scope: !52)
!58 = !DILocation(line: 20, column: 6, scope: !52)
!59 = !DILocation(line: 20, column: 8, scope: !52)
!60 = !DILocation(line: 21, column: 9, scope: !52)
!61 = !DILocation(line: 21, column: 5, scope: !52)
!62 = !DILocation(line: 22, column: 1, scope: !52)
