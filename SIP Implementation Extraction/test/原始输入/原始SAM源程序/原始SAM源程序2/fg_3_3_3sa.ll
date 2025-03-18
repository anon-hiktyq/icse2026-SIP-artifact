; ModuleID = 'fg_3_3_3sa.c'
source_filename = "fg_3_3_3sa.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.TAG_FG_3_3_3SA_RAW = type { double, double, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i16, i16, i16, i8 }

@Fg333sacntFrame = dso_local global i32 0, align 4, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @SendFg333saCmd(ptr noundef %0) #0 !dbg !48 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  call void @llvm.dbg.declare(metadata ptr %2, metadata !53, metadata !DIExpression()), !dbg !54
  call void @llvm.dbg.declare(metadata ptr %3, metadata !55, metadata !DIExpression()), !dbg !56
  %4 = load ptr, ptr %2, align 8, !dbg !57
  %5 = getelementptr inbounds i8, ptr %4, i64 0, !dbg !57
  store i8 -21, ptr %5, align 1, !dbg !58
  %6 = load ptr, ptr %2, align 8, !dbg !59
  %7 = getelementptr inbounds i8, ptr %6, i64 1, !dbg !59
  store i8 -112, ptr %7, align 1, !dbg !60
  store i32 2, ptr %3, align 4, !dbg !61
  %8 = load i32, ptr %3, align 4, !dbg !62
  ret i32 %8, !dbg !63
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @Fg333saCheck(ptr noundef %0, i32 noundef %1, ptr noundef %2, ptr noundef %3) #0 !dbg !64 {
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca i32, align 4
  %10 = alloca i8, align 1
  %11 = alloca ptr, align 8
  store ptr %0, ptr %5, align 8
  call void @llvm.dbg.declare(metadata ptr %5, metadata !70, metadata !DIExpression()), !dbg !71
  store i32 %1, ptr %6, align 4
  call void @llvm.dbg.declare(metadata ptr %6, metadata !72, metadata !DIExpression()), !dbg !73
  store ptr %2, ptr %7, align 8
  call void @llvm.dbg.declare(metadata ptr %7, metadata !74, metadata !DIExpression()), !dbg !75
  store ptr %3, ptr %8, align 8
  call void @llvm.dbg.declare(metadata ptr %8, metadata !76, metadata !DIExpression()), !dbg !77
  call void @llvm.dbg.declare(metadata ptr %9, metadata !78, metadata !DIExpression()), !dbg !79
  call void @llvm.dbg.declare(metadata ptr %10, metadata !80, metadata !DIExpression()), !dbg !81
  call void @llvm.dbg.declare(metadata ptr %11, metadata !82, metadata !DIExpression()), !dbg !83
  %12 = load ptr, ptr %8, align 8, !dbg !84
  store ptr %12, ptr %11, align 8, !dbg !85
  store i32 0, ptr %9, align 4, !dbg !86
  %13 = load i32, ptr %6, align 4, !dbg !87
  %14 = icmp eq i32 %13, 19, !dbg !89
  br i1 %14, label %15, label %90, !dbg !90

15:                                               ; preds = %4
  %16 = load ptr, ptr %11, align 8, !dbg !91
  %17 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %16, i32 0, i32 4, !dbg !93
  store i32 0, ptr %17, align 8, !dbg !94
  %18 = load ptr, ptr %5, align 8, !dbg !95
  %19 = getelementptr inbounds i8, ptr %18, i64 17, !dbg !95
  %20 = load i8, ptr %19, align 1, !dbg !95
  %21 = zext i8 %20 to i32, !dbg !95
  %22 = load ptr, ptr %7, align 8, !dbg !97
  %23 = load i32, ptr %22, align 4, !dbg !98
  %24 = icmp ne i32 %21, %23, !dbg !99
  br i1 %24, label %25, label %80, !dbg !100

25:                                               ; preds = %15
  %26 = load ptr, ptr %11, align 8, !dbg !101
  %27 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %26, i32 0, i32 8, !dbg !103
  store i32 0, ptr %27, align 8, !dbg !104
  %28 = load ptr, ptr %5, align 8, !dbg !105
  %29 = getelementptr inbounds i8, ptr %28, i64 17, !dbg !105
  %30 = load i8, ptr %29, align 1, !dbg !105
  %31 = zext i8 %30 to i32, !dbg !105
  %32 = load ptr, ptr %7, align 8, !dbg !106
  store i32 %31, ptr %32, align 4, !dbg !107
  %33 = load ptr, ptr %5, align 8, !dbg !108
  %34 = getelementptr inbounds i8, ptr %33, i64 0, !dbg !108
  %35 = load i8, ptr %34, align 1, !dbg !108
  %36 = zext i8 %35 to i32, !dbg !108
  %37 = icmp eq i32 %36, 235, !dbg !110
  br i1 %37, label %38, label %70, !dbg !111

38:                                               ; preds = %25
  %39 = load ptr, ptr %5, align 8, !dbg !112
  %40 = getelementptr inbounds i8, ptr %39, i64 1, !dbg !112
  %41 = load i8, ptr %40, align 1, !dbg !112
  %42 = zext i8 %41 to i32, !dbg !112
  %43 = icmp eq i32 %42, 144, !dbg !113
  br i1 %43, label %44, label %70, !dbg !114

44:                                               ; preds = %38
  %45 = load ptr, ptr %11, align 8, !dbg !115
  %46 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %45, i32 0, i32 5, !dbg !117
  store i32 0, ptr %46, align 4, !dbg !118
  %47 = load ptr, ptr %5, align 8, !dbg !119
  %48 = getelementptr inbounds i8, ptr %47, i64 0, !dbg !119
  %49 = call zeroext i8 @CheckSumAdd08(ptr noundef %48, i32 noundef 18), !dbg !120
  store i8 %49, ptr %10, align 1, !dbg !121
  %50 = load i8, ptr %10, align 1, !dbg !122
  %51 = zext i8 %50 to i32, !dbg !122
  %52 = load ptr, ptr %5, align 8, !dbg !124
  %53 = getelementptr inbounds i8, ptr %52, i64 18, !dbg !124
  %54 = load i8, ptr %53, align 1, !dbg !124
  %55 = zext i8 %54 to i32, !dbg !124
  %56 = icmp eq i32 %51, %55, !dbg !125
  br i1 %56, label %57, label %60, !dbg !126

57:                                               ; preds = %44
  %58 = load ptr, ptr %11, align 8, !dbg !127
  %59 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %58, i32 0, i32 7, !dbg !129
  store i32 0, ptr %59, align 4, !dbg !130
  store i32 -342879121, ptr %9, align 4, !dbg !131
  br label %69, !dbg !132

60:                                               ; preds = %44
  %61 = load ptr, ptr %11, align 8, !dbg !133
  %62 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %61, i32 0, i32 7, !dbg !135
  %63 = load i32, ptr %62, align 4, !dbg !136
  %64 = add nsw i32 %63, 1, !dbg !136
  store i32 %64, ptr %62, align 4, !dbg !136
  %65 = load ptr, ptr %11, align 8, !dbg !137
  %66 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %65, i32 0, i32 12, !dbg !138
  %67 = load i32, ptr %66, align 8, !dbg !139
  %68 = add nsw i32 %67, 1, !dbg !139
  store i32 %68, ptr %66, align 8, !dbg !139
  br label %69

69:                                               ; preds = %60, %57
  br label %79, !dbg !140

70:                                               ; preds = %38, %25
  %71 = load ptr, ptr %11, align 8, !dbg !141
  %72 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %71, i32 0, i32 5, !dbg !143
  %73 = load i32, ptr %72, align 4, !dbg !144
  %74 = add nsw i32 %73, 1, !dbg !144
  store i32 %74, ptr %72, align 4, !dbg !144
  %75 = load ptr, ptr %11, align 8, !dbg !145
  %76 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %75, i32 0, i32 10, !dbg !146
  %77 = load i32, ptr %76, align 8, !dbg !147
  %78 = add nsw i32 %77, 1, !dbg !147
  store i32 %78, ptr %76, align 8, !dbg !147
  br label %79

79:                                               ; preds = %70, %69
  br label %89, !dbg !148

80:                                               ; preds = %15
  %81 = load ptr, ptr %11, align 8, !dbg !149
  %82 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %81, i32 0, i32 8, !dbg !151
  %83 = load i32, ptr %82, align 8, !dbg !152
  %84 = add nsw i32 %83, 1, !dbg !152
  store i32 %84, ptr %82, align 8, !dbg !152
  %85 = load ptr, ptr %11, align 8, !dbg !153
  %86 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %85, i32 0, i32 13, !dbg !154
  %87 = load i32, ptr %86, align 4, !dbg !155
  %88 = add nsw i32 %87, 1, !dbg !155
  store i32 %88, ptr %86, align 4, !dbg !155
  br label %89

89:                                               ; preds = %80, %79
  br label %99, !dbg !156

90:                                               ; preds = %4
  %91 = load ptr, ptr %11, align 8, !dbg !157
  %92 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %91, i32 0, i32 4, !dbg !159
  %93 = load i32, ptr %92, align 8, !dbg !160
  %94 = add nsw i32 %93, 1, !dbg !160
  store i32 %94, ptr %92, align 8, !dbg !160
  %95 = load ptr, ptr %11, align 8, !dbg !161
  %96 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %95, i32 0, i32 9, !dbg !162
  %97 = load i32, ptr %96, align 4, !dbg !163
  %98 = add nsw i32 %97, 1, !dbg !163
  store i32 %98, ptr %96, align 4, !dbg !163
  br label %99

99:                                               ; preds = %90, %89
  %100 = load i32, ptr %9, align 4, !dbg !164
  ret i32 %100, !dbg !165
}

declare zeroext i8 @CheckSumAdd08(ptr noundef, i32 noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @Fg333saUnPack(ptr noundef %0, ptr noundef %1, double noundef %2) #0 !dbg !166 {
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca double, align 8
  %7 = alloca ptr, align 8
  %8 = alloca i32, align 4
  store ptr %0, ptr %4, align 8
  call void @llvm.dbg.declare(metadata ptr %4, metadata !169, metadata !DIExpression()), !dbg !170
  store ptr %1, ptr %5, align 8
  call void @llvm.dbg.declare(metadata ptr %5, metadata !171, metadata !DIExpression()), !dbg !172
  store double %2, ptr %6, align 8
  call void @llvm.dbg.declare(metadata ptr %6, metadata !173, metadata !DIExpression()), !dbg !174
  call void @llvm.dbg.declare(metadata ptr %7, metadata !175, metadata !DIExpression()), !dbg !176
  call void @llvm.dbg.declare(metadata ptr %8, metadata !177, metadata !DIExpression()), !dbg !178
  %9 = load ptr, ptr %4, align 8, !dbg !179
  store ptr %9, ptr %7, align 8, !dbg !180
  %10 = load ptr, ptr %5, align 8, !dbg !181
  %11 = getelementptr inbounds i8, ptr %10, i64 2, !dbg !181
  %12 = load i8, ptr %11, align 1, !dbg !181
  %13 = zext i8 %12 to i32, !dbg !181
  %14 = shl i32 %13, 24, !dbg !181
  %15 = load ptr, ptr %5, align 8, !dbg !181
  %16 = getelementptr inbounds i8, ptr %15, i64 3, !dbg !181
  %17 = load i8, ptr %16, align 1, !dbg !181
  %18 = zext i8 %17 to i32, !dbg !181
  %19 = shl i32 %18, 16, !dbg !181
  %20 = or i32 %14, %19, !dbg !181
  %21 = load ptr, ptr %5, align 8, !dbg !181
  %22 = getelementptr inbounds i8, ptr %21, i64 4, !dbg !181
  %23 = load i8, ptr %22, align 1, !dbg !181
  %24 = zext i8 %23 to i32, !dbg !181
  %25 = shl i32 %24, 8, !dbg !181
  %26 = or i32 %20, %25, !dbg !181
  %27 = load ptr, ptr %5, align 8, !dbg !181
  %28 = getelementptr inbounds i8, ptr %27, i64 5, !dbg !181
  %29 = load i8, ptr %28, align 1, !dbg !181
  %30 = zext i8 %29 to i32, !dbg !181
  %31 = or i32 %26, %30, !dbg !181
  store i32 %31, ptr %8, align 4, !dbg !182
  %32 = load i32, ptr %8, align 4, !dbg !183
  %33 = sitofp i32 %32 to double, !dbg !184
  %34 = fdiv double %33, 3.000000e+06, !dbg !185
  %35 = fmul double %34, 0x3F91DF46A2529D3A, !dbg !186
  %36 = load ptr, ptr %7, align 8, !dbg !187
  %37 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %36, i32 0, i32 1, !dbg !188
  store double %35, ptr %37, align 8, !dbg !189
  %38 = load ptr, ptr %5, align 8, !dbg !190
  %39 = getelementptr inbounds i8, ptr %38, i64 6, !dbg !190
  %40 = load i8, ptr %39, align 1, !dbg !190
  %41 = zext i8 %40 to i32, !dbg !190
  %42 = shl i32 %41, 8, !dbg !190
  %43 = load ptr, ptr %5, align 8, !dbg !190
  %44 = getelementptr inbounds i8, ptr %43, i64 7, !dbg !190
  %45 = load i8, ptr %44, align 1, !dbg !190
  %46 = zext i8 %45 to i32, !dbg !190
  %47 = or i32 %42, %46, !dbg !190
  %48 = trunc i32 %47 to i16, !dbg !190
  %49 = load ptr, ptr %7, align 8, !dbg !191
  %50 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %49, i32 0, i32 14, !dbg !192
  store i16 %48, ptr %50, align 8, !dbg !193
  %51 = load ptr, ptr %5, align 8, !dbg !194
  %52 = getelementptr inbounds i8, ptr %51, i64 8, !dbg !194
  %53 = load i8, ptr %52, align 1, !dbg !194
  %54 = zext i8 %53 to i32, !dbg !194
  %55 = shl i32 %54, 8, !dbg !194
  %56 = load ptr, ptr %5, align 8, !dbg !194
  %57 = getelementptr inbounds i8, ptr %56, i64 9, !dbg !194
  %58 = load i8, ptr %57, align 1, !dbg !194
  %59 = zext i8 %58 to i32, !dbg !194
  %60 = or i32 %55, %59, !dbg !194
  %61 = trunc i32 %60 to i16, !dbg !194
  %62 = load ptr, ptr %7, align 8, !dbg !195
  %63 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %62, i32 0, i32 15, !dbg !196
  store i16 %61, ptr %63, align 2, !dbg !197
  %64 = load ptr, ptr %5, align 8, !dbg !198
  %65 = getelementptr inbounds i8, ptr %64, i64 10, !dbg !198
  %66 = load i8, ptr %65, align 1, !dbg !198
  %67 = zext i8 %66 to i32, !dbg !198
  %68 = shl i32 %67, 8, !dbg !198
  %69 = load ptr, ptr %5, align 8, !dbg !198
  %70 = getelementptr inbounds i8, ptr %69, i64 11, !dbg !198
  %71 = load i8, ptr %70, align 1, !dbg !198
  %72 = zext i8 %71 to i32, !dbg !198
  %73 = or i32 %68, %72, !dbg !198
  %74 = trunc i32 %73 to i16, !dbg !198
  %75 = load ptr, ptr %7, align 8, !dbg !199
  %76 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %75, i32 0, i32 16, !dbg !200
  store i16 %74, ptr %76, align 4, !dbg !201
  %77 = load ptr, ptr %5, align 8, !dbg !202
  %78 = getelementptr inbounds i8, ptr %77, i64 16, !dbg !202
  %79 = load i8, ptr %78, align 1, !dbg !202
  %80 = load ptr, ptr %7, align 8, !dbg !203
  %81 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %80, i32 0, i32 17, !dbg !204
  store i8 %79, ptr %81, align 2, !dbg !205
  %82 = load ptr, ptr %7, align 8, !dbg !206
  %83 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %82, i32 0, i32 1, !dbg !207
  %84 = load double, ptr %83, align 8, !dbg !207
  %85 = load double, ptr %6, align 8, !dbg !208
  %86 = fmul double %84, %85, !dbg !209
  %87 = load ptr, ptr %7, align 8, !dbg !210
  %88 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %87, i32 0, i32 0, !dbg !211
  store double %86, ptr %88, align 8, !dbg !212
  ret void, !dbg !213
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !214 {
  %1 = alloca ptr, align 8
  %2 = alloca i32, align 4
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca double, align 8
  call void @llvm.dbg.declare(metadata ptr %1, metadata !217, metadata !DIExpression()), !dbg !218
  %8 = call noalias ptr @malloc(i64 noundef 1) #4, !dbg !219
  store ptr %8, ptr %1, align 8, !dbg !218
  call void @llvm.dbg.declare(metadata ptr %2, metadata !220, metadata !DIExpression()), !dbg !221
  store i32 2, ptr %2, align 4, !dbg !221
  call void @llvm.dbg.declare(metadata ptr %3, metadata !222, metadata !DIExpression()), !dbg !223
  %9 = call noalias ptr @malloc(i64 noundef 4) #4, !dbg !224
  store ptr %9, ptr %3, align 8, !dbg !223
  call void @llvm.dbg.declare(metadata ptr %4, metadata !225, metadata !DIExpression()), !dbg !226
  %10 = call noalias ptr @malloc(i64 noundef 4) #4, !dbg !227
  store ptr %10, ptr %4, align 8, !dbg !226
  %11 = load ptr, ptr %1, align 8, !dbg !228
  %12 = load i32, ptr %2, align 4, !dbg !229
  %13 = load ptr, ptr %3, align 8, !dbg !230
  %14 = load ptr, ptr %4, align 8, !dbg !231
  %15 = call i32 @Fg333saCheck(ptr noundef %11, i32 noundef %12, ptr noundef %13, ptr noundef %14), !dbg !232
  call void @llvm.dbg.declare(metadata ptr %5, metadata !233, metadata !DIExpression()), !dbg !234
  %16 = call noalias ptr @malloc(i64 noundef 4) #4, !dbg !235
  store ptr %16, ptr %5, align 8, !dbg !234
  call void @llvm.dbg.declare(metadata ptr %6, metadata !236, metadata !DIExpression()), !dbg !237
  %17 = call noalias ptr @malloc(i64 noundef 1) #4, !dbg !238
  store ptr %17, ptr %6, align 8, !dbg !237
  call void @llvm.dbg.declare(metadata ptr %7, metadata !239, metadata !DIExpression()), !dbg !240
  store double 1.000000e+00, ptr %7, align 8, !dbg !240
  %18 = load ptr, ptr %5, align 8, !dbg !241
  %19 = load ptr, ptr %6, align 8, !dbg !242
  %20 = load double, ptr %7, align 8, !dbg !243
  call void @Fg333saUnPack(ptr noundef %18, ptr noundef %19, double noundef %20), !dbg !244
  ret i32 0, !dbg !245
}

; Function Attrs: nounwind allocsize(0)
declare noalias ptr @malloc(i64 noundef) #3

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind allocsize(0) }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!40, !41, !42, !43, !44, !45, !46}
!llvm.ident = !{!47}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "Fg333sacntFrame", scope: !2, file: !3, line: 5, type: !16, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C11, file: !3, producer: "clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !4, globals: !39, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "fg_3_3_3sa.c", directory: "/home/lkl/SoftwareIP/SIP/test/\E5\8E\9F\E5\A7\8B\E8\BE\93\E5\85\A5/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F2", checksumkind: CSK_MD5, checksum: "3cfae7693f67b6cc4fa35e8832aa12a8")
!4 = !{!5, !16, !11, !20, !32}
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64)
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "SFg333saRaw", file: !7, line: 32, baseType: !8)
!7 = !DIFile(filename: "./fg_3_3_3sa.h", directory: "/home/lkl/SoftwareIP/SIP/test/\E5\8E\9F\E5\A7\8B\E8\BE\93\E5\85\A5/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F2", checksumkind: CSK_MD5, checksum: "9fbbc49f5b7e542a48f527a2161899c7")
!8 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TAG_FG_3_3_3SA_RAW", file: !7, line: 8, size: 576, elements: !9)
!9 = !{!10, !14, !15, !18, !19, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !34, !35, !36}
!10 = !DIDerivedType(tag: DW_TAG_member, name: "gf", scope: !8, file: !7, line: 10, baseType: !11, size: 64)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "float64", file: !12, line: 17, baseType: !13)
!12 = !DIFile(filename: "./std_basal.h", directory: "/home/lkl/SoftwareIP/SIP/test/\E5\8E\9F\E5\A7\8B\E8\BE\93\E5\85\A5/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F2", checksumkind: CSK_MD5, checksum: "e6894d170243f183681360646add8143")
!13 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "wt0", scope: !8, file: !7, line: 11, baseType: !11, size: 64, offset: 64)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "cntFrame", scope: !8, file: !7, line: 12, baseType: !16, size: 32, offset: 128)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "unint32", file: !12, line: 15, baseType: !17)
!17 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "bComSuc", scope: !8, file: !7, line: 14, baseType: !16, size: 32, offset: 160)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "cntLenRd", scope: !8, file: !7, line: 16, baseType: !20, size: 32, offset: 192)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "siint32", file: !12, line: 14, baseType: !21)
!21 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "cntHead", scope: !8, file: !7, line: 17, baseType: !20, size: 32, offset: 224)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "cntLen", scope: !8, file: !7, line: 18, baseType: !20, size: 32, offset: 256)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "cntCheck", scope: !8, file: !7, line: 19, baseType: !20, size: 32, offset: 288)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "cntUpdata", scope: !8, file: !7, line: 20, baseType: !20, size: 32, offset: 320)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "totalLenRd", scope: !8, file: !7, line: 22, baseType: !20, size: 32, offset: 352)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "totalHead", scope: !8, file: !7, line: 23, baseType: !20, size: 32, offset: 384)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "totalLen", scope: !8, file: !7, line: 24, baseType: !20, size: 32, offset: 416)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "totalCheck", scope: !8, file: !7, line: 25, baseType: !20, size: 32, offset: 448)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "totalUpdata", scope: !8, file: !7, line: 26, baseType: !20, size: 32, offset: 480)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "glwd1", scope: !8, file: !7, line: 28, baseType: !32, size: 16, offset: 512)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "unint16", file: !12, line: 13, baseType: !33)
!33 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "glwd2", scope: !8, file: !7, line: 29, baseType: !32, size: 16, offset: 528)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "dlwd", scope: !8, file: !7, line: 30, baseType: !32, size: 16, offset: 544)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "status", scope: !8, file: !7, line: 31, baseType: !37, size: 8, offset: 560)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "unint08", file: !12, line: 11, baseType: !38)
!38 = !DIBasicType(name: "unsigned char", size: 8, encoding: DW_ATE_unsigned_char)
!39 = !{!0}
!40 = !{i32 7, !"Dwarf Version", i32 5}
!41 = !{i32 2, !"Debug Info Version", i32 3}
!42 = !{i32 1, !"wchar_size", i32 4}
!43 = !{i32 8, !"PIC Level", i32 2}
!44 = !{i32 7, !"PIE Level", i32 2}
!45 = !{i32 7, !"uwtable", i32 2}
!46 = !{i32 7, !"frame-pointer", i32 2}
!47 = !{!"clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)"}
!48 = distinct !DISubprogram(name: "SendFg333saCmd", scope: !3, file: !3, line: 8, type: !49, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !52)
!49 = !DISubroutineType(types: !50)
!50 = !{!16, !51}
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64)
!52 = !{}
!53 = !DILocalVariable(name: "pSendBuf", arg: 1, scope: !48, file: !3, line: 8, type: !51)
!54 = !DILocation(line: 8, column: 33, scope: !48)
!55 = !DILocalVariable(name: "tmpLen", scope: !48, file: !3, line: 10, type: !16)
!56 = !DILocation(line: 10, column: 10, scope: !48)
!57 = !DILocation(line: 13, column: 5, scope: !48)
!58 = !DILocation(line: 13, column: 17, scope: !48)
!59 = !DILocation(line: 14, column: 5, scope: !48)
!60 = !DILocation(line: 14, column: 17, scope: !48)
!61 = !DILocation(line: 16, column: 9, scope: !48)
!62 = !DILocation(line: 18, column: 12, scope: !48)
!63 = !DILocation(line: 18, column: 5, scope: !48)
!64 = distinct !DISubprogram(name: "Fg333saCheck", scope: !3, file: !3, line: 23, type: !65, scopeLine: 24, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !52)
!65 = !DISubroutineType(types: !66)
!66 = !{!16, !67, !16, !69, !69}
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64)
!68 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64)
!70 = !DILocalVariable(name: "pbuff", arg: 1, scope: !64, file: !3, line: 23, type: !67)
!71 = !DILocation(line: 23, column: 37, scope: !64)
!72 = !DILocalVariable(name: "rdLen", arg: 2, scope: !64, file: !3, line: 23, type: !16)
!73 = !DILocation(line: 23, column: 52, scope: !64)
!74 = !DILocalVariable(name: "frm", arg: 3, scope: !64, file: !3, line: 23, type: !69)
!75 = !DILocation(line: 23, column: 68, scope: !64)
!76 = !DILocalVariable(name: "pFgRaw", arg: 4, scope: !64, file: !3, line: 23, type: !69)
!77 = !DILocation(line: 23, column: 82, scope: !64)
!78 = !DILocalVariable(name: "bComSuc", scope: !64, file: !3, line: 25, type: !16)
!79 = !DILocation(line: 25, column: 10, scope: !64)
!80 = !DILocalVariable(name: "chksum", scope: !64, file: !3, line: 26, type: !37)
!81 = !DILocation(line: 26, column: 10, scope: !64)
!82 = !DILocalVariable(name: "pRaw", scope: !64, file: !3, line: 27, type: !5)
!83 = !DILocation(line: 27, column: 15, scope: !64)
!84 = !DILocation(line: 29, column: 24, scope: !64)
!85 = !DILocation(line: 29, column: 7, scope: !64)
!86 = !DILocation(line: 31, column: 10, scope: !64)
!87 = !DILocation(line: 33, column: 5, scope: !88)
!88 = distinct !DILexicalBlock(scope: !64, file: !3, line: 33, column: 5)
!89 = !DILocation(line: 33, column: 11, scope: !88)
!90 = !DILocation(line: 33, column: 5, scope: !64)
!91 = !DILocation(line: 35, column: 3, scope: !92)
!92 = distinct !DILexicalBlock(scope: !88, file: !3, line: 34, column: 2)
!93 = !DILocation(line: 35, column: 9, scope: !92)
!94 = !DILocation(line: 35, column: 18, scope: !92)
!95 = !DILocation(line: 38, column: 7, scope: !96)
!96 = distinct !DILexicalBlock(scope: !92, file: !3, line: 38, column: 7)
!97 = !DILocation(line: 38, column: 22, scope: !96)
!98 = !DILocation(line: 38, column: 21, scope: !96)
!99 = !DILocation(line: 38, column: 17, scope: !96)
!100 = !DILocation(line: 38, column: 7, scope: !92)
!101 = !DILocation(line: 40, column: 4, scope: !102)
!102 = distinct !DILexicalBlock(scope: !96, file: !3, line: 39, column: 3)
!103 = !DILocation(line: 40, column: 10, scope: !102)
!104 = !DILocation(line: 40, column: 20, scope: !102)
!105 = !DILocation(line: 42, column: 11, scope: !102)
!106 = !DILocation(line: 42, column: 5, scope: !102)
!107 = !DILocation(line: 42, column: 9, scope: !102)
!108 = !DILocation(line: 45, column: 8, scope: !109)
!109 = distinct !DILexicalBlock(scope: !102, file: !3, line: 45, column: 7)
!110 = !DILocation(line: 45, column: 17, scope: !109)
!111 = !DILocation(line: 45, column: 25, scope: !109)
!112 = !DILocation(line: 45, column: 28, scope: !109)
!113 = !DILocation(line: 45, column: 37, scope: !109)
!114 = !DILocation(line: 45, column: 7, scope: !102)
!115 = !DILocation(line: 47, column: 5, scope: !116)
!116 = distinct !DILexicalBlock(scope: !109, file: !3, line: 46, column: 4)
!117 = !DILocation(line: 47, column: 11, scope: !116)
!118 = !DILocation(line: 47, column: 19, scope: !116)
!119 = !DILocation(line: 50, column: 29, scope: !116)
!120 = !DILocation(line: 50, column: 14, scope: !116)
!121 = !DILocation(line: 50, column: 12, scope: !116)
!122 = !DILocation(line: 53, column: 8, scope: !123)
!123 = distinct !DILexicalBlock(scope: !116, file: !3, line: 53, column: 8)
!124 = !DILocation(line: 53, column: 18, scope: !123)
!125 = !DILocation(line: 53, column: 15, scope: !123)
!126 = !DILocation(line: 53, column: 8, scope: !116)
!127 = !DILocation(line: 55, column: 6, scope: !128)
!128 = distinct !DILexicalBlock(scope: !123, file: !3, line: 54, column: 5)
!129 = !DILocation(line: 55, column: 12, scope: !128)
!130 = !DILocation(line: 55, column: 21, scope: !128)
!131 = !DILocation(line: 57, column: 14, scope: !128)
!132 = !DILocation(line: 58, column: 5, scope: !128)
!133 = !DILocation(line: 62, column: 6, scope: !134)
!134 = distinct !DILexicalBlock(scope: !123, file: !3, line: 60, column: 5)
!135 = !DILocation(line: 62, column: 12, scope: !134)
!136 = !DILocation(line: 62, column: 20, scope: !134)
!137 = !DILocation(line: 63, column: 6, scope: !134)
!138 = !DILocation(line: 63, column: 12, scope: !134)
!139 = !DILocation(line: 63, column: 22, scope: !134)
!140 = !DILocation(line: 65, column: 4, scope: !116)
!141 = !DILocation(line: 69, column: 5, scope: !142)
!142 = distinct !DILexicalBlock(scope: !109, file: !3, line: 67, column: 4)
!143 = !DILocation(line: 69, column: 11, scope: !142)
!144 = !DILocation(line: 69, column: 18, scope: !142)
!145 = !DILocation(line: 70, column: 5, scope: !142)
!146 = !DILocation(line: 70, column: 11, scope: !142)
!147 = !DILocation(line: 70, column: 20, scope: !142)
!148 = !DILocation(line: 72, column: 3, scope: !102)
!149 = !DILocation(line: 75, column: 4, scope: !150)
!150 = distinct !DILexicalBlock(scope: !96, file: !3, line: 74, column: 3)
!151 = !DILocation(line: 75, column: 10, scope: !150)
!152 = !DILocation(line: 75, column: 19, scope: !150)
!153 = !DILocation(line: 76, column: 4, scope: !150)
!154 = !DILocation(line: 76, column: 10, scope: !150)
!155 = !DILocation(line: 76, column: 21, scope: !150)
!156 = !DILocation(line: 78, column: 2, scope: !92)
!157 = !DILocation(line: 82, column: 3, scope: !158)
!158 = distinct !DILexicalBlock(scope: !88, file: !3, line: 80, column: 2)
!159 = !DILocation(line: 82, column: 9, scope: !158)
!160 = !DILocation(line: 82, column: 17, scope: !158)
!161 = !DILocation(line: 83, column: 3, scope: !158)
!162 = !DILocation(line: 83, column: 9, scope: !158)
!163 = !DILocation(line: 83, column: 19, scope: !158)
!164 = !DILocation(line: 86, column: 9, scope: !64)
!165 = !DILocation(line: 86, column: 2, scope: !64)
!166 = distinct !DISubprogram(name: "Fg333saUnPack", scope: !3, file: !3, line: 90, type: !167, scopeLine: 91, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !52)
!167 = !DISubroutineType(types: !168)
!168 = !{null, !69, !67, !11}
!169 = !DILocalVariable(name: "pFgRaw", arg: 1, scope: !166, file: !3, line: 90, type: !69)
!170 = !DILocation(line: 90, column: 29, scope: !166)
!171 = !DILocalVariable(name: "pRecvbuf", arg: 2, scope: !166, file: !3, line: 90, type: !67)
!172 = !DILocation(line: 90, column: 52, scope: !166)
!173 = !DILocalVariable(name: "dtime", arg: 3, scope: !166, file: !3, line: 90, type: !11)
!174 = !DILocation(line: 90, column: 69, scope: !166)
!175 = !DILocalVariable(name: "pRaw", scope: !166, file: !3, line: 92, type: !5)
!176 = !DILocation(line: 92, column: 15, scope: !166)
!177 = !DILocalVariable(name: "temp_var", scope: !166, file: !3, line: 93, type: !16)
!178 = !DILocation(line: 93, column: 10, scope: !166)
!179 = !DILocation(line: 95, column: 24, scope: !166)
!180 = !DILocation(line: 95, column: 7, scope: !166)
!181 = !DILocation(line: 97, column: 13, scope: !166)
!182 = !DILocation(line: 97, column: 11, scope: !166)
!183 = !DILocation(line: 98, column: 33, scope: !166)
!184 = !DILocation(line: 98, column: 15, scope: !166)
!185 = !DILocation(line: 98, column: 43, scope: !166)
!186 = !DILocation(line: 98, column: 51, scope: !166)
!187 = !DILocation(line: 98, column: 2, scope: !166)
!188 = !DILocation(line: 98, column: 8, scope: !166)
!189 = !DILocation(line: 98, column: 12, scope: !166)
!190 = !DILocation(line: 100, column: 16, scope: !166)
!191 = !DILocation(line: 100, column: 2, scope: !166)
!192 = !DILocation(line: 100, column: 8, scope: !166)
!193 = !DILocation(line: 100, column: 14, scope: !166)
!194 = !DILocation(line: 101, column: 16, scope: !166)
!195 = !DILocation(line: 101, column: 2, scope: !166)
!196 = !DILocation(line: 101, column: 8, scope: !166)
!197 = !DILocation(line: 101, column: 14, scope: !166)
!198 = !DILocation(line: 102, column: 15, scope: !166)
!199 = !DILocation(line: 102, column: 2, scope: !166)
!200 = !DILocation(line: 102, column: 8, scope: !166)
!201 = !DILocation(line: 102, column: 13, scope: !166)
!202 = !DILocation(line: 104, column: 17, scope: !166)
!203 = !DILocation(line: 104, column: 2, scope: !166)
!204 = !DILocation(line: 104, column: 8, scope: !166)
!205 = !DILocation(line: 104, column: 15, scope: !166)
!206 = !DILocation(line: 107, column: 13, scope: !166)
!207 = !DILocation(line: 107, column: 19, scope: !166)
!208 = !DILocation(line: 107, column: 25, scope: !166)
!209 = !DILocation(line: 107, column: 23, scope: !166)
!210 = !DILocation(line: 107, column: 2, scope: !166)
!211 = !DILocation(line: 107, column: 8, scope: !166)
!212 = !DILocation(line: 107, column: 11, scope: !166)
!213 = !DILocation(line: 109, column: 2, scope: !166)
!214 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 113, type: !215, scopeLine: 113, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !52)
!215 = !DISubroutineType(types: !216)
!216 = !{!21}
!217 = !DILocalVariable(name: "pbuff", scope: !214, file: !3, line: 114, type: !51)
!218 = !DILocation(line: 114, column: 14, scope: !214)
!219 = !DILocation(line: 114, column: 22, scope: !214)
!220 = !DILocalVariable(name: "rdLen", scope: !214, file: !3, line: 115, type: !16)
!221 = !DILocation(line: 115, column: 13, scope: !214)
!222 = !DILocalVariable(name: "frm", scope: !214, file: !3, line: 116, type: !69)
!223 = !DILocation(line: 116, column: 14, scope: !214)
!224 = !DILocation(line: 116, column: 20, scope: !214)
!225 = !DILocalVariable(name: "pFgRaw", scope: !214, file: !3, line: 117, type: !69)
!226 = !DILocation(line: 117, column: 14, scope: !214)
!227 = !DILocation(line: 117, column: 23, scope: !214)
!228 = !DILocation(line: 118, column: 18, scope: !214)
!229 = !DILocation(line: 118, column: 25, scope: !214)
!230 = !DILocation(line: 118, column: 32, scope: !214)
!231 = !DILocation(line: 118, column: 37, scope: !214)
!232 = !DILocation(line: 118, column: 5, scope: !214)
!233 = !DILocalVariable(name: "pFgRaw_2", scope: !214, file: !3, line: 120, type: !69)
!234 = !DILocation(line: 120, column: 14, scope: !214)
!235 = !DILocation(line: 120, column: 25, scope: !214)
!236 = !DILocalVariable(name: "pRecvbuf", scope: !214, file: !3, line: 121, type: !67)
!237 = !DILocation(line: 121, column: 20, scope: !214)
!238 = !DILocation(line: 121, column: 31, scope: !214)
!239 = !DILocalVariable(name: "dtime", scope: !214, file: !3, line: 122, type: !11)
!240 = !DILocation(line: 122, column: 13, scope: !214)
!241 = !DILocation(line: 123, column: 19, scope: !214)
!242 = !DILocation(line: 123, column: 29, scope: !214)
!243 = !DILocation(line: 123, column: 39, scope: !214)
!244 = !DILocation(line: 123, column: 5, scope: !214)
!245 = !DILocation(line: 125, column: 1, scope: !214)
