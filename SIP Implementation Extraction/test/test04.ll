; ModuleID = 'test04.c'
source_filename = "test04.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @add(ptr noundef %p) #0 !dbg !10 {
entry:
  %p.addr = alloca ptr, align 8
  store ptr %p, ptr %p.addr, align 8
  call void @llvm.dbg.declare(metadata ptr %p.addr, metadata !16, metadata !DIExpression()), !dbg !17
  %0 = load ptr, ptr %p.addr, align 8, !dbg !18
  store i32 2, ptr %0, align 4, !dbg !19
  ret void, !dbg !20
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @bar(ptr noundef %q) #0 !dbg !21 {
entry:
  %q.addr = alloca ptr, align 8
  store ptr %q, ptr %q.addr, align 8
  call void @llvm.dbg.declare(metadata ptr %q.addr, metadata !22, metadata !DIExpression()), !dbg !23
  %0 = load ptr, ptr %q.addr, align 8, !dbg !24
  call void @add(ptr noundef %0), !dbg !25
  ret void, !dbg !26
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @foo(ptr noundef %q) #0 !dbg !27 {
entry:
  %q.addr = alloca ptr, align 8
  store ptr %q, ptr %q.addr, align 8
  call void @llvm.dbg.declare(metadata ptr %q.addr, metadata !28, metadata !DIExpression()), !dbg !29
  %0 = load ptr, ptr %q.addr, align 8, !dbg !30
  call void @bar(ptr noundef %0), !dbg !31
  ret void, !dbg !32
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !33 {
entry:
  %p = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %p, metadata !36, metadata !DIExpression()), !dbg !37
  %call = call noalias ptr @malloc(i64 noundef 4) #3, !dbg !38
  store ptr %call, ptr %p, align 8, !dbg !37
  %0 = load ptr, ptr %p, align 8, !dbg !39
  call void @foo(ptr noundef %0), !dbg !40
  ret i32 0, !dbg !41
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
!1 = !DIFile(filename: "test04.c", directory: "/home/lkl/SoftwareIP/SIP/test", checksumkind: CSK_MD5, checksum: "385f538b8156c369111c448cd92ff171")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 8, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 2}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)"}
!10 = distinct !DISubprogram(name: "add", scope: !1, file: !1, line: 6, type: !11, scopeLine: 6, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!11 = !DISubroutineType(types: !12)
!12 = !{null, !13}
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64)
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !{}
!16 = !DILocalVariable(name: "p", arg: 1, scope: !10, file: !1, line: 6, type: !13)
!17 = !DILocation(line: 6, column: 15, scope: !10)
!18 = !DILocation(line: 7, column: 6, scope: !10)
!19 = !DILocation(line: 7, column: 8, scope: !10)
!20 = !DILocation(line: 8, column: 1, scope: !10)
!21 = distinct !DISubprogram(name: "bar", scope: !1, file: !1, line: 10, type: !11, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!22 = !DILocalVariable(name: "q", arg: 1, scope: !21, file: !1, line: 10, type: !13)
!23 = !DILocation(line: 10, column: 16, scope: !21)
!24 = !DILocation(line: 11, column: 9, scope: !21)
!25 = !DILocation(line: 11, column: 5, scope: !21)
!26 = !DILocation(line: 12, column: 1, scope: !21)
!27 = distinct !DISubprogram(name: "foo", scope: !1, file: !1, line: 14, type: !11, scopeLine: 14, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!28 = !DILocalVariable(name: "q", arg: 1, scope: !27, file: !1, line: 14, type: !13)
!29 = !DILocation(line: 14, column: 15, scope: !27)
!30 = !DILocation(line: 15, column: 9, scope: !27)
!31 = !DILocation(line: 15, column: 5, scope: !27)
!32 = !DILocation(line: 16, column: 1, scope: !27)
!33 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 18, type: !34, scopeLine: 18, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !15)
!34 = !DISubroutineType(types: !35)
!35 = !{!14}
!36 = !DILocalVariable(name: "p", scope: !33, file: !1, line: 19, type: !13)
!37 = !DILocation(line: 19, column: 10, scope: !33)
!38 = !DILocation(line: 19, column: 14, scope: !33)
!39 = !DILocation(line: 20, column: 9, scope: !33)
!40 = !DILocation(line: 20, column: 5, scope: !33)
!41 = !DILocation(line: 21, column: 1, scope: !33)
