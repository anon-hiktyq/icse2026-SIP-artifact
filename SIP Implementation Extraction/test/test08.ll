; ModuleID = 'test08.c'
source_filename = "test08.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(ptr noundef %0, i32 noundef %1) #0 !dbg !10 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  call void @llvm.dbg.declare(metadata ptr %3, metadata !16, metadata !DIExpression()), !dbg !17
  store i32 %1, ptr %4, align 4
  call void @llvm.dbg.declare(metadata ptr %4, metadata !18, metadata !DIExpression()), !dbg !19
  %6 = load i32, ptr %4, align 4, !dbg !20
  %7 = load ptr, ptr %3, align 8, !dbg !21
  store i32 %6, ptr %7, align 4, !dbg !22
  call void @llvm.dbg.declare(metadata ptr %5, metadata !23, metadata !DIExpression()), !dbg !24
  %8 = load ptr, ptr %3, align 8, !dbg !25
  %9 = load i32, ptr %8, align 4, !dbg !26
  store i32 %9, ptr %5, align 4, !dbg !24
  %10 = load i32, ptr %5, align 4, !dbg !27
  ret i32 %10, !dbg !28
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !29 {
  %1 = alloca ptr, align 8
  %2 = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %1, metadata !32, metadata !DIExpression()), !dbg !33
  %3 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !34
  store ptr %3, ptr %1, align 8, !dbg !33
  %4 = load ptr, ptr %1, align 8, !dbg !35
  %5 = call i32 @foo(ptr noundef %4, i32 noundef 2), !dbg !36
  call void @llvm.dbg.declare(metadata ptr %2, metadata !37, metadata !DIExpression()), !dbg !38
  %6 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !39
  store ptr %6, ptr %2, align 8, !dbg !38
  %7 = load ptr, ptr %2, align 8, !dbg !40
  %8 = call i32 @foo(ptr noundef %7, i32 noundef 3), !dbg !41
  ret i32 0, !dbg !42
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
!1 = !DIFile(filename: "test08.c", directory: "/home/lkl/SoftwareIP/SIP/test", checksumkind: CSK_MD5, checksum: "a80f8454d483b401442f1a2f6c56d63f")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 8, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 2}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)"}
!10 = distinct !DISubprogram(name: "foo", scope: !1, file: !1, line: 3, type: !11, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DISubroutineType(types: !12)
!12 = !{!13, !14, !13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64)
!15 = !{}
!16 = !DILocalVariable(name: "p", arg: 1, scope: !10, file: !1, line: 3, type: !14)
!17 = !DILocation(line: 3, column: 14, scope: !10)
!18 = !DILocalVariable(name: "a", arg: 2, scope: !10, file: !1, line: 3, type: !13)
!19 = !DILocation(line: 3, column: 21, scope: !10)
!20 = !DILocation(line: 4, column: 10, scope: !10)
!21 = !DILocation(line: 4, column: 6, scope: !10)
!22 = !DILocation(line: 4, column: 8, scope: !10)
!23 = !DILocalVariable(name: "c", scope: !10, file: !1, line: 5, type: !13)
!24 = !DILocation(line: 5, column: 9, scope: !10)
!25 = !DILocation(line: 5, column: 14, scope: !10)
!26 = !DILocation(line: 5, column: 13, scope: !10)
!27 = !DILocation(line: 6, column: 12, scope: !10)
!28 = !DILocation(line: 6, column: 5, scope: !10)
!29 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 9, type: !30, scopeLine: 9, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!30 = !DISubroutineType(types: !31)
!31 = !{!13}
!32 = !DILocalVariable(name: "p", scope: !29, file: !1, line: 10, type: !14)
!33 = !DILocation(line: 10, column: 10, scope: !29)
!34 = !DILocation(line: 10, column: 14, scope: !29)
!35 = !DILocation(line: 11, column: 9, scope: !29)
!36 = !DILocation(line: 11, column: 5, scope: !29)
!37 = !DILocalVariable(name: "q", scope: !29, file: !1, line: 12, type: !14)
!38 = !DILocation(line: 12, column: 10, scope: !29)
!39 = !DILocation(line: 12, column: 14, scope: !29)
!40 = !DILocation(line: 13, column: 9, scope: !29)
!41 = !DILocation(line: 13, column: 5, scope: !29)
!42 = !DILocation(line: 14, column: 1, scope: !29)
