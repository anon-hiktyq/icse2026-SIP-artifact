; ModuleID = 'test12.c'
source_filename = "test12.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@b = dso_local constant i32 1, align 4, !dbg !0
@a = dso_local global i32 0, align 4, !dbg !5

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(ptr noundef %0) #0 !dbg !17 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  call void @llvm.dbg.declare(metadata ptr %2, metadata !22, metadata !DIExpression()), !dbg !23
  %4 = load i32, ptr @a, align 4, !dbg !24
  %5 = load ptr, ptr %2, align 8, !dbg !25
  store i32 %4, ptr %5, align 4, !dbg !26
  store i32 1, ptr @a, align 4, !dbg !27
  call void @llvm.dbg.declare(metadata ptr %3, metadata !28, metadata !DIExpression()), !dbg !29
  %6 = load ptr, ptr %2, align 8, !dbg !30
  %7 = load i32, ptr %6, align 4, !dbg !31
  store i32 %7, ptr %3, align 4, !dbg !29
  %8 = load i32, ptr %3, align 4, !dbg !32
  ret i32 %8, !dbg !33
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!9, !10, !11, !12, !13, !14, !15}
!llvm.ident = !{!16}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 4, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C11, file: !3, producer: "clang version 16.0.0", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !4, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "test12.c", directory: "/home/dyd/project/SIP/test", checksumkind: CSK_MD5, checksum: "fd0b3f61904886db2b8f7088838f6363")
!4 = !{!0, !5}
!5 = !DIGlobalVariableExpression(var: !6, expr: !DIExpression())
!6 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 3, type: !7, isLocal: false, isDefinition: true)
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !7)
!9 = !{i32 7, !"Dwarf Version", i32 5}
!10 = !{i32 2, !"Debug Info Version", i32 3}
!11 = !{i32 1, !"wchar_size", i32 4}
!12 = !{i32 8, !"PIC Level", i32 2}
!13 = !{i32 7, !"PIE Level", i32 2}
!14 = !{i32 7, !"uwtable", i32 2}
!15 = !{i32 7, !"frame-pointer", i32 2}
!16 = !{!"clang version 16.0.0"}
!17 = distinct !DISubprogram(name: "foo", scope: !3, file: !3, line: 6, type: !18, scopeLine: 6, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !21)
!18 = !DISubroutineType(types: !19)
!19 = !{!7, !20}
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!21 = !{}
!22 = !DILocalVariable(name: "p", arg: 1, scope: !17, file: !3, line: 6, type: !20)
!23 = !DILocation(line: 6, column: 14, scope: !17)
!24 = !DILocation(line: 7, column: 8, scope: !17)
!25 = !DILocation(line: 7, column: 4, scope: !17)
!26 = !DILocation(line: 7, column: 6, scope: !17)
!27 = !DILocation(line: 8, column: 4, scope: !17)
!28 = !DILocalVariable(name: "c", scope: !17, file: !3, line: 9, type: !7)
!29 = !DILocation(line: 9, column: 7, scope: !17)
!30 = !DILocation(line: 9, column: 10, scope: !17)
!31 = !DILocation(line: 9, column: 9, scope: !17)
!32 = !DILocation(line: 10, column: 10, scope: !17)
!33 = !DILocation(line: 10, column: 3, scope: !17)
