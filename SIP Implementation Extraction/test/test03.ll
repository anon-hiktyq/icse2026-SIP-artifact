; ModuleID = 'test03.c'
source_filename = "test03.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local ptr @foo(i32 noundef %0) #0 !dbg !10 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  store i32 %0, ptr %3, align 4
  call void @llvm.dbg.declare(metadata ptr %3, metadata !16, metadata !DIExpression()), !dbg !17
  call void @llvm.dbg.declare(metadata ptr %4, metadata !18, metadata !DIExpression()), !dbg !19
  %6 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !20
  store ptr %6, ptr %4, align 8, !dbg !19
  call void @llvm.dbg.declare(metadata ptr %5, metadata !21, metadata !DIExpression()), !dbg !22
  %7 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !23
  store ptr %7, ptr %5, align 8, !dbg !22
  %8 = load i32, ptr %3, align 4, !dbg !24
  %9 = icmp ne i32 %8, 0, !dbg !24
  br i1 %9, label %10, label %12, !dbg !26

10:                                               ; preds = %1
  %11 = load ptr, ptr %4, align 8, !dbg !27
  store ptr %11, ptr %2, align 8, !dbg !28
  br label %14, !dbg !28

12:                                               ; preds = %1
  %13 = load ptr, ptr %5, align 8, !dbg !29
  store ptr %13, ptr %2, align 8, !dbg !30
  br label %14, !dbg !30

14:                                               ; preds = %12, %10
  %15 = load ptr, ptr %2, align 8, !dbg !31
  ret ptr %15, !dbg !31
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

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
!1 = !DIFile(filename: "test03.c", directory: "/home/lkl/SoftwareIP/SIP/test", checksumkind: CSK_MD5, checksum: "8c18f7c5927a9a00ae40e4ec7046bcaa")
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
!12 = !{!13, !14}
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64)
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "c", arg: 1, scope: !10, file: !1, line: 3, type: !14)
!17 = !DILocation(line: 3, column: 14, scope: !10)
!18 = !DILocalVariable(name: "a", scope: !10, file: !1, line: 4, type: !13)
!19 = !DILocation(line: 4, column: 10, scope: !10)
!20 = !DILocation(line: 4, column: 14, scope: !10)
!21 = !DILocalVariable(name: "b", scope: !10, file: !1, line: 5, type: !13)
!22 = !DILocation(line: 5, column: 10, scope: !10)
!23 = !DILocation(line: 5, column: 14, scope: !10)
!24 = !DILocation(line: 6, column: 8, scope: !25)
!25 = distinct !DILexicalBlock(scope: !10, file: !1, line: 6, column: 8)
!26 = !DILocation(line: 6, column: 8, scope: !10)
!27 = !DILocation(line: 7, column: 16, scope: !25)
!28 = !DILocation(line: 7, column: 9, scope: !25)
!29 = !DILocation(line: 9, column: 16, scope: !25)
!30 = !DILocation(line: 9, column: 9, scope: !25)
!31 = !DILocation(line: 10, column: 1, scope: !10)
