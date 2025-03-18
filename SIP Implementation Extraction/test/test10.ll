; ModuleID = 'test10.c'
source_filename = "test10.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(ptr noundef %0, i32 noundef %1) #0 !dbg !10 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  call void @llvm.dbg.declare(metadata ptr %3, metadata !17, metadata !DIExpression()), !dbg !18
  store i32 %1, ptr %4, align 4
  call void @llvm.dbg.declare(metadata ptr %4, metadata !19, metadata !DIExpression()), !dbg !20
  %5 = load i32, ptr %4, align 4, !dbg !21
  %6 = load ptr, ptr %3, align 8, !dbg !22
  %7 = load ptr, ptr %6, align 8, !dbg !23
  store i32 %5, ptr %7, align 4, !dbg !24
  %8 = load i32, ptr %4, align 4, !dbg !25
  ret i32 %8, !dbg !26
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !27 {
  %1 = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %1, metadata !30, metadata !DIExpression()), !dbg !31
  %2 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !32
  store ptr %2, ptr %1, align 8, !dbg !31
  %3 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !33
  %4 = load ptr, ptr %1, align 8, !dbg !34
  store ptr %3, ptr %4, align 8, !dbg !35
  %5 = load ptr, ptr %1, align 8, !dbg !36
  %6 = call i32 @foo(ptr noundef %5, i32 noundef 2), !dbg !37
  ret i32 0, !dbg !38
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
!1 = !DIFile(filename: "test10.c", directory: "/home/lkl/SoftwareIP/SIP/test", checksumkind: CSK_MD5, checksum: "ae7a8cccf2a59c9bdf79c2004043574f")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 8, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 2}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)"}
!10 = distinct !DISubprogram(name: "foo", scope: !1, file: !1, line: 4, type: !11, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !16)
!11 = !DISubroutineType(types: !12)
!12 = !{!13, !14, !13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64)
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64)
!16 = !{}
!17 = !DILocalVariable(name: "p", arg: 1, scope: !10, file: !1, line: 4, type: !14)
!18 = !DILocation(line: 4, column: 15, scope: !10)
!19 = !DILocalVariable(name: "a", arg: 2, scope: !10, file: !1, line: 4, type: !13)
!20 = !DILocation(line: 4, column: 22, scope: !10)
!21 = !DILocation(line: 5, column: 11, scope: !10)
!22 = !DILocation(line: 5, column: 7, scope: !10)
!23 = !DILocation(line: 5, column: 6, scope: !10)
!24 = !DILocation(line: 5, column: 9, scope: !10)
!25 = !DILocation(line: 6, column: 12, scope: !10)
!26 = !DILocation(line: 6, column: 5, scope: !10)
!27 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 8, type: !28, scopeLine: 8, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !16)
!28 = !DISubroutineType(types: !29)
!29 = !{!13}
!30 = !DILocalVariable(name: "p", scope: !27, file: !1, line: 9, type: !14)
!31 = !DILocation(line: 9, column: 11, scope: !27)
!32 = !DILocation(line: 9, column: 15, scope: !27)
!33 = !DILocation(line: 10, column: 10, scope: !27)
!34 = !DILocation(line: 10, column: 6, scope: !27)
!35 = !DILocation(line: 10, column: 8, scope: !27)
!36 = !DILocation(line: 11, column: 9, scope: !27)
!37 = !DILocation(line: 11, column: 5, scope: !27)
!38 = !DILocation(line: 12, column: 1, scope: !27)
