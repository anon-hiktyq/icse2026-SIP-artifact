; ModuleID = 'test01.c'
source_filename = "test01.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@a = dso_local global i32 2, align 4, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(ptr noundef %0, i32 noundef %1) #0 !dbg !14 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  call void @llvm.dbg.declare(metadata ptr %3, metadata !19, metadata !DIExpression()), !dbg !20
  store i32 %1, ptr %4, align 4
  call void @llvm.dbg.declare(metadata ptr %4, metadata !21, metadata !DIExpression()), !dbg !22
  call void @llvm.dbg.declare(metadata ptr %5, metadata !23, metadata !DIExpression()), !dbg !24
  %7 = load ptr, ptr %3, align 8, !dbg !25
  store ptr %7, ptr %5, align 8, !dbg !24
  %8 = load i32, ptr %4, align 4, !dbg !26
  %9 = load ptr, ptr %5, align 8, !dbg !27
  store i32 %8, ptr %9, align 4, !dbg !28
  %10 = load ptr, ptr %5, align 8, !dbg !29
  %11 = load i32, ptr %10, align 4, !dbg !30
  store i32 %11, ptr @a, align 4, !dbg !31
  call void @llvm.dbg.declare(metadata ptr %6, metadata !32, metadata !DIExpression()), !dbg !33
  %12 = load i32, ptr %4, align 4, !dbg !34
  store i32 %12, ptr %6, align 4, !dbg !33
  %13 = load i32, ptr %6, align 4, !dbg !35
  ret i32 %13, !dbg !36
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !37 {
  %1 = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %1, metadata !40, metadata !DIExpression()), !dbg !41
  %2 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !42
  store ptr %2, ptr %1, align 8, !dbg !41
  %3 = load ptr, ptr %1, align 8, !dbg !43
  %4 = call i32 @foo(ptr noundef %3, i32 noundef 4), !dbg !44
  ret i32 0, !dbg !45
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
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !5, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C11, file: !3, producer: "clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !4, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "test01.c", directory: "/home/lkl/SoftwareIP/SIP/test", checksumkind: CSK_MD5, checksum: "a836f7e74020b36ac397381bc2583145")
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
!16 = !{!5, !17, !5}
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64)
!18 = !{}
!19 = !DILocalVariable(name: "p", arg: 1, scope: !14, file: !3, line: 4, type: !17)
!20 = !DILocation(line: 4, column: 14, scope: !14)
!21 = !DILocalVariable(name: "b", arg: 2, scope: !14, file: !3, line: 4, type: !5)
!22 = !DILocation(line: 4, column: 21, scope: !14)
!23 = !DILocalVariable(name: "q", scope: !14, file: !3, line: 5, type: !17)
!24 = !DILocation(line: 5, column: 10, scope: !14)
!25 = !DILocation(line: 5, column: 14, scope: !14)
!26 = !DILocation(line: 6, column: 10, scope: !14)
!27 = !DILocation(line: 6, column: 6, scope: !14)
!28 = !DILocation(line: 6, column: 8, scope: !14)
!29 = !DILocation(line: 7, column: 10, scope: !14)
!30 = !DILocation(line: 7, column: 9, scope: !14)
!31 = !DILocation(line: 7, column: 7, scope: !14)
!32 = !DILocalVariable(name: "c", scope: !14, file: !3, line: 8, type: !5)
!33 = !DILocation(line: 8, column: 9, scope: !14)
!34 = !DILocation(line: 8, column: 13, scope: !14)
!35 = !DILocation(line: 9, column: 12, scope: !14)
!36 = !DILocation(line: 9, column: 5, scope: !14)
!37 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 12, type: !38, scopeLine: 12, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !18)
!38 = !DISubroutineType(types: !39)
!39 = !{!5}
!40 = !DILocalVariable(name: "t", scope: !37, file: !3, line: 13, type: !17)
!41 = !DILocation(line: 13, column: 10, scope: !37)
!42 = !DILocation(line: 13, column: 14, scope: !37)
!43 = !DILocation(line: 14, column: 9, scope: !37)
!44 = !DILocation(line: 14, column: 5, scope: !37)
!45 = !DILocation(line: 15, column: 1, scope: !37)
