; ModuleID = 'test02.c'
source_filename = "test02.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(ptr noundef %0, i32 noundef %1) #0 !dbg !10 {
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  %8 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  call void @llvm.dbg.declare(metadata ptr %3, metadata !16, metadata !DIExpression()), !dbg !17
  store i32 %1, ptr %4, align 4
  call void @llvm.dbg.declare(metadata ptr %4, metadata !18, metadata !DIExpression()), !dbg !19
  call void @llvm.dbg.declare(metadata ptr %5, metadata !20, metadata !DIExpression()), !dbg !21
  store ptr %4, ptr %5, align 8, !dbg !21
  call void @llvm.dbg.declare(metadata ptr %6, metadata !22, metadata !DIExpression()), !dbg !24
  %9 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !25
  store ptr %9, ptr %6, align 8, !dbg !24
  %10 = load i32, ptr %4, align 4, !dbg !26
  %11 = icmp sgt i32 %10, 0, !dbg !28
  br i1 %11, label %12, label %15, !dbg !29

12:                                               ; preds = %2
  %13 = load ptr, ptr %3, align 8, !dbg !30
  %14 = load ptr, ptr %6, align 8, !dbg !31
  store ptr %13, ptr %14, align 8, !dbg !32
  br label %18, !dbg !33

15:                                               ; preds = %2
  %16 = load ptr, ptr %5, align 8, !dbg !34
  %17 = load ptr, ptr %6, align 8, !dbg !35
  store ptr %16, ptr %17, align 8, !dbg !36
  br label %18

18:                                               ; preds = %15, %12
  call void @llvm.dbg.declare(metadata ptr %7, metadata !37, metadata !DIExpression()), !dbg !38
  %19 = load ptr, ptr %6, align 8, !dbg !39
  %20 = load ptr, ptr %19, align 8, !dbg !40
  store ptr %20, ptr %7, align 8, !dbg !38
  %21 = load i32, ptr %4, align 4, !dbg !41
  %22 = load ptr, ptr %7, align 8, !dbg !42
  store i32 %21, ptr %22, align 4, !dbg !43
  call void @llvm.dbg.declare(metadata ptr %8, metadata !44, metadata !DIExpression()), !dbg !45
  %23 = load ptr, ptr %3, align 8, !dbg !46
  %24 = load i32, ptr %23, align 4, !dbg !47
  store i32 %24, ptr %8, align 4, !dbg !45
  %25 = load i32, ptr %8, align 4, !dbg !48
  ret i32 %25, !dbg !49
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind allocsize(0)
declare noalias ptr @malloc(i64 noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !50 {
  %1 = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %1, metadata !53, metadata !DIExpression()), !dbg !54
  %2 = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !55
  store ptr %2, ptr %1, align 8, !dbg !54
  %3 = load ptr, ptr %1, align 8, !dbg !56
  %4 = call i32 @foo(ptr noundef %3, i32 noundef 4), !dbg !57
  ret i32 0, !dbg !58
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { nounwind allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind allocsize(0) }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "test02.c", directory: "/home/lkl/SoftwareIP/SIP/test", checksumkind: CSK_MD5, checksum: "f61d617fc531651138d9b78faa322872")
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
!18 = !DILocalVariable(name: "b", arg: 2, scope: !10, file: !1, line: 3, type: !13)
!19 = !DILocation(line: 3, column: 21, scope: !10)
!20 = !DILocalVariable(name: "q", scope: !10, file: !1, line: 4, type: !14)
!21 = !DILocation(line: 4, column: 10, scope: !10)
!22 = !DILocalVariable(name: "a", scope: !10, file: !1, line: 5, type: !23)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64)
!24 = !DILocation(line: 5, column: 11, scope: !10)
!25 = !DILocation(line: 5, column: 15, scope: !10)
!26 = !DILocation(line: 6, column: 8, scope: !27)
!27 = distinct !DILexicalBlock(scope: !10, file: !1, line: 6, column: 8)
!28 = !DILocation(line: 6, column: 10, scope: !27)
!29 = !DILocation(line: 6, column: 8, scope: !10)
!30 = !DILocation(line: 7, column: 14, scope: !27)
!31 = !DILocation(line: 7, column: 10, scope: !27)
!32 = !DILocation(line: 7, column: 12, scope: !27)
!33 = !DILocation(line: 7, column: 9, scope: !27)
!34 = !DILocation(line: 9, column: 14, scope: !27)
!35 = !DILocation(line: 9, column: 10, scope: !27)
!36 = !DILocation(line: 9, column: 12, scope: !27)
!37 = !DILocalVariable(name: "t", scope: !10, file: !1, line: 10, type: !14)
!38 = !DILocation(line: 10, column: 10, scope: !10)
!39 = !DILocation(line: 10, column: 15, scope: !10)
!40 = !DILocation(line: 10, column: 14, scope: !10)
!41 = !DILocation(line: 11, column: 10, scope: !10)
!42 = !DILocation(line: 11, column: 6, scope: !10)
!43 = !DILocation(line: 11, column: 8, scope: !10)
!44 = !DILocalVariable(name: "c", scope: !10, file: !1, line: 12, type: !13)
!45 = !DILocation(line: 12, column: 9, scope: !10)
!46 = !DILocation(line: 12, column: 14, scope: !10)
!47 = !DILocation(line: 12, column: 13, scope: !10)
!48 = !DILocation(line: 13, column: 12, scope: !10)
!49 = !DILocation(line: 13, column: 5, scope: !10)
!50 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 16, type: !51, scopeLine: 16, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!51 = !DISubroutineType(types: !52)
!52 = !{!13}
!53 = !DILocalVariable(name: "p", scope: !50, file: !1, line: 17, type: !14)
!54 = !DILocation(line: 17, column: 10, scope: !50)
!55 = !DILocation(line: 17, column: 14, scope: !50)
!56 = !DILocation(line: 18, column: 9, scope: !50)
!57 = !DILocation(line: 18, column: 5, scope: !50)
!58 = !DILocation(line: 19, column: 1, scope: !50)
