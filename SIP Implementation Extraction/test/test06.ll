; ModuleID = 'test06.c'
source_filename = "test06.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@a = dso_local global i32 0, align 4, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(ptr noundef %0) #0 !dbg !14 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  call void @llvm.dbg.declare(metadata ptr %2, metadata !19, metadata !DIExpression()), !dbg !20
  %4 = load ptr, ptr %2, align 8, !dbg !21
  %5 = load i32, ptr %4, align 4, !dbg !22
  store i32 %5, ptr @a, align 4, !dbg !23
  call void @llvm.dbg.declare(metadata ptr %3, metadata !24, metadata !DIExpression()), !dbg !25
  %6 = load i32, ptr @a, align 4, !dbg !26
  store i32 %6, ptr %3, align 4, !dbg !25
  %7 = load i32, ptr %3, align 4, !dbg !27
  ret i32 %7, !dbg !28
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !29 {
  %1 = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %1, metadata !32, metadata !DIExpression()), !dbg !33
  %2 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !34
  store ptr %2, ptr %1, align 8, !dbg !33
  %3 = load ptr, ptr %1, align 8, !dbg !35
  %4 = call i32 @foo(ptr noundef %3), !dbg !36
  ret i32 0, !dbg !37
}

; Function Attrs: nounwind allocsize(0)
declare noalias ptr @malloc(i64 noundef) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { nounwind allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind allocsize(0) }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!6, !7, !8, !9, !10, !11, !12}
!llvm.ident = !{!13}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 3, type: !5, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C11, file: !3, producer: "clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !4, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "test06.c", directory: "/home/lkl/SoftwareIP/SIP/test", checksumkind: CSK_MD5, checksum: "8c0952e744ac7601ef1404d200d4e5b9")
!4 = !{!0}
!5 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!6 = !{i32 7, !"Dwarf Version", i32 5}
!7 = !{i32 2, !"Debug Info Version", i32 3}
!8 = !{i32 1, !"wchar_size", i32 4}
!9 = !{i32 8, !"PIC Level", i32 2}
!10 = !{i32 7, !"PIE Level", i32 2}
!11 = !{i32 7, !"uwtable", i32 2}
!12 = !{i32 7, !"frame-pointer", i32 2}
!13 = !{!"clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)"}
!14 = distinct !DISubprogram(name: "foo", scope: !3, file: !3, line: 4, type: !15, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !18)
!15 = !DISubroutineType(types: !16)
!16 = !{!5, !17}
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64)
!18 = !{}
!19 = !DILocalVariable(name: "p", arg: 1, scope: !14, file: !3, line: 4, type: !17)
!20 = !DILocation(line: 4, column: 14, scope: !14)
!21 = !DILocation(line: 5, column: 10, scope: !14)
!22 = !DILocation(line: 5, column: 9, scope: !14)
!23 = !DILocation(line: 5, column: 7, scope: !14)
!24 = !DILocalVariable(name: "c", scope: !14, file: !3, line: 6, type: !5)
!25 = !DILocation(line: 6, column: 9, scope: !14)
!26 = !DILocation(line: 6, column: 13, scope: !14)
!27 = !DILocation(line: 7, column: 12, scope: !14)
!28 = !DILocation(line: 7, column: 5, scope: !14)
!29 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 10, type: !30, scopeLine: 10, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !18)
!30 = !DISubroutineType(types: !31)
!31 = !{!5}
!32 = !DILocalVariable(name: "p", scope: !29, file: !3, line: 11, type: !17)
!33 = !DILocation(line: 11, column: 10, scope: !29)
!34 = !DILocation(line: 11, column: 14, scope: !29)
!35 = !DILocation(line: 12, column: 9, scope: !29)
!36 = !DILocation(line: 12, column: 5, scope: !29)
!37 = !DILocation(line: 13, column: 1, scope: !29)
