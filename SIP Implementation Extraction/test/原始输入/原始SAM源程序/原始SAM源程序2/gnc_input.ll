; ModuleID = 'gnc_input.c'
source_filename = "gnc_input.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.TAG_POWER_JUDGE = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%struct.TAG_DEVICE_TABLE = type { i32, i32, i32, i32, i32, i32, i32 }
%struct.TAG_POWER_JUDGE_PARAM = type { i32, i32 }
%struct.TAG_UART = type { i32, [256 x i8], i32, [256 x i8] }
%struct.TAG_FG_3_3_3SA_RAW = type { double, double, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i16, i16, i16, i8 }
%struct.TAG_STS_DATA_RAW = type { i32, i32, i32, i32, i32, i32, i32, [4 x i32], [3 x i32], [4 x double], [3 x double], double, [21 x i8], [64 x i8], [128 x i8], [256 x i8] }
%struct.TAG_STS_PPS = type { double, double, double, i32, i32 }
%struct.TAG_COM_ERROR = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 }

@mPowerJudgeFog = dso_local global [3 x %struct.TAG_POWER_JUDGE] zeroinitializer, align 16, !dbg !0
@gncDevTable = external global [13 x %struct.TAG_DEVICE_TABLE], align 16
@mPowerJudgeFogParam = external global %struct.TAG_POWER_JUDGE_PARAM, align 4
@mUartFog = dso_local global [3 x %struct.TAG_UART] zeroinitializer, align 16, !dbg !10
@mFogDataRaw = dso_local global [3 x %struct.TAG_FG_3_3_3SA_RAW] zeroinitializer, align 16, !dbg !112
@mPowerJudgeSts = dso_local global [3 x %struct.TAG_POWER_JUDGE] zeroinitializer, align 16, !dbg !28
@mStsDataRaw = dso_local global [3 x %struct.TAG_STS_DATA_RAW] zeroinitializer, align 16, !dbg !46
@mStsPps = dso_local global [3 x %struct.TAG_STS_PPS] zeroinitializer, align 16, !dbg !85
@mComErrorSts = dso_local global [3 x %struct.TAG_COM_ERROR] zeroinitializer, align 16, !dbg !96
@mPowerJudgeImuGyro = dso_local global [3 x %struct.TAG_POWER_JUDGE] zeroinitializer, align 16, !dbg !139
@mPowerJudgeDssXY = dso_local global [2 x %struct.TAG_POWER_JUDGE] zeroinitializer, align 16, !dbg !141

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @InputData() #0 !dbg !154 {
  %1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %1, metadata !158, metadata !DIExpression()), !dbg !159
  store i32 0, ptr %1, align 4, !dbg !160
  br label %2, !dbg !162

2:                                                ; preds = %93, %0
  %3 = load i32, ptr %1, align 4, !dbg !163
  %4 = icmp slt i32 %3, 3, !dbg !165
  br i1 %4, label %5, label %96, !dbg !166

5:                                                ; preds = %2
  %6 = load i32, ptr %1, align 4, !dbg !167
  %7 = sext i32 %6 to i64, !dbg !170
  %8 = getelementptr inbounds [3 x %struct.TAG_POWER_JUDGE], ptr @mPowerJudgeFog, i64 0, i64 %7, !dbg !170
  %9 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %8, i32 0, i32 9, !dbg !171
  %10 = load i32, ptr %9, align 4, !dbg !171
  %11 = icmp eq i32 %10, -342879121, !dbg !172
  br i1 %11, label %12, label %23, !dbg !173

12:                                               ; preds = %5
  %13 = load i32, ptr %1, align 4, !dbg !174
  %14 = sext i32 %13 to i64, !dbg !176
  %15 = getelementptr inbounds [3 x %struct.TAG_POWER_JUDGE], ptr @mPowerJudgeFog, i64 0, i64 %14, !dbg !176
  %16 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %15, i32 0, i32 8, !dbg !177
  %17 = load i32, ptr %16, align 8, !dbg !177
  %18 = load i32, ptr %1, align 4, !dbg !178
  %19 = add nsw i32 3, %18, !dbg !179
  %20 = sext i32 %19 to i64, !dbg !180
  %21 = getelementptr inbounds [13 x %struct.TAG_DEVICE_TABLE], ptr @gncDevTable, i64 0, i64 %20, !dbg !180
  %22 = getelementptr inbounds %struct.TAG_DEVICE_TABLE, ptr %21, i32 0, i32 2, !dbg !181
  store i32 %17, ptr %22, align 4, !dbg !182
  br label %23, !dbg !183

23:                                               ; preds = %12, %5
  %24 = load i32, ptr %1, align 4, !dbg !184
  %25 = add nsw i32 3, %24, !dbg !185
  %26 = sext i32 %25 to i64, !dbg !186
  %27 = getelementptr inbounds [13 x %struct.TAG_DEVICE_TABLE], ptr @gncDevTable, i64 0, i64 %26, !dbg !186
  %28 = getelementptr inbounds %struct.TAG_DEVICE_TABLE, ptr %27, i32 0, i32 2, !dbg !187
  %29 = load i32, ptr %28, align 4, !dbg !187
  %30 = load i32, ptr %1, align 4, !dbg !188
  %31 = sext i32 %30 to i64, !dbg !189
  %32 = getelementptr inbounds [3 x %struct.TAG_POWER_JUDGE], ptr @mPowerJudgeFog, i64 0, i64 %31, !dbg !189
  %33 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %32, i32 0, i32 6, !dbg !190
  store i32 %29, ptr %33, align 8, !dbg !191
  %34 = load i32, ptr %1, align 4, !dbg !192
  %35 = sext i32 %34 to i64, !dbg !193
  %36 = getelementptr inbounds [3 x %struct.TAG_POWER_JUDGE], ptr @mPowerJudgeFog, i64 0, i64 %35, !dbg !193
  call void @PowerOnJudge(ptr noundef %36, ptr noundef @mPowerJudgeFogParam), !dbg !194
  %37 = load i32, ptr %1, align 4, !dbg !195
  %38 = add nsw i32 3, %37, !dbg !195
  %39 = sext i32 %38 to i64, !dbg !195
  %40 = getelementptr inbounds [13 x %struct.TAG_DEVICE_TABLE], ptr @gncDevTable, i64 0, i64 %39, !dbg !195
  %41 = getelementptr inbounds %struct.TAG_DEVICE_TABLE, ptr %40, i32 0, i32 2, !dbg !195
  %42 = load i32, ptr %41, align 4, !dbg !195
  %43 = icmp ne i32 %42, 0, !dbg !195
  br i1 %43, label %44, label %83, !dbg !197

44:                                               ; preds = %23
  %45 = load i32, ptr %1, align 4, !dbg !198
  %46 = sext i32 %45 to i64, !dbg !200
  %47 = getelementptr inbounds [3 x %struct.TAG_UART], ptr @mUartFog, i64 0, i64 %46, !dbg !200
  %48 = getelementptr inbounds %struct.TAG_UART, ptr %47, i32 0, i32 1, !dbg !201
  %49 = getelementptr inbounds [256 x i8], ptr %48, i64 0, i64 0, !dbg !200
  %50 = load i32, ptr %1, align 4, !dbg !202
  %51 = sext i32 %50 to i64, !dbg !203
  %52 = getelementptr inbounds [3 x %struct.TAG_UART], ptr @mUartFog, i64 0, i64 %51, !dbg !203
  %53 = getelementptr inbounds %struct.TAG_UART, ptr %52, i32 0, i32 0, !dbg !204
  %54 = load i32, ptr %53, align 8, !dbg !204
  %55 = load i32, ptr %1, align 4, !dbg !205
  %56 = sext i32 %55 to i64, !dbg !206
  %57 = getelementptr inbounds [3 x %struct.TAG_FG_3_3_3SA_RAW], ptr @mFogDataRaw, i64 0, i64 %56, !dbg !206
  %58 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %57, i32 0, i32 2, !dbg !207
  %59 = load i32, ptr %1, align 4, !dbg !208
  %60 = sext i32 %59 to i64, !dbg !209
  %61 = getelementptr inbounds [3 x %struct.TAG_FG_3_3_3SA_RAW], ptr @mFogDataRaw, i64 0, i64 %60, !dbg !209
  %62 = call i32 @Fg333saCheck(ptr noundef %49, i32 noundef %54, ptr noundef %58, ptr noundef %61), !dbg !210
  %63 = load i32, ptr %1, align 4, !dbg !211
  %64 = sext i32 %63 to i64, !dbg !212
  %65 = getelementptr inbounds [3 x %struct.TAG_FG_3_3_3SA_RAW], ptr @mFogDataRaw, i64 0, i64 %64, !dbg !212
  %66 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %65, i32 0, i32 3, !dbg !213
  store i32 %62, ptr %66, align 4, !dbg !214
  %67 = load i32, ptr %1, align 4, !dbg !215
  %68 = sext i32 %67 to i64, !dbg !217
  %69 = getelementptr inbounds [3 x %struct.TAG_FG_3_3_3SA_RAW], ptr @mFogDataRaw, i64 0, i64 %68, !dbg !217
  %70 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %69, i32 0, i32 3, !dbg !218
  %71 = load i32, ptr %70, align 4, !dbg !218
  %72 = icmp eq i32 %71, -342879121, !dbg !219
  br i1 %72, label %73, label %82, !dbg !220

73:                                               ; preds = %44
  %74 = load i32, ptr %1, align 4, !dbg !221
  %75 = sext i32 %74 to i64, !dbg !223
  %76 = getelementptr inbounds [3 x %struct.TAG_FG_3_3_3SA_RAW], ptr @mFogDataRaw, i64 0, i64 %75, !dbg !223
  %77 = load i32, ptr %1, align 4, !dbg !224
  %78 = sext i32 %77 to i64, !dbg !225
  %79 = getelementptr inbounds [3 x %struct.TAG_UART], ptr @mUartFog, i64 0, i64 %78, !dbg !225
  %80 = getelementptr inbounds %struct.TAG_UART, ptr %79, i32 0, i32 1, !dbg !226
  %81 = getelementptr inbounds [256 x i8], ptr %80, i64 0, i64 0, !dbg !225
  call void @Fg333saUnPack(ptr noundef %76, ptr noundef %81, double noundef 6.400000e-02), !dbg !227
  br label %82, !dbg !228

82:                                               ; preds = %73, %44
  br label %92, !dbg !229

83:                                               ; preds = %23
  %84 = load i32, ptr %1, align 4, !dbg !230
  %85 = sext i32 %84 to i64, !dbg !232
  %86 = getelementptr inbounds [3 x %struct.TAG_FG_3_3_3SA_RAW], ptr @mFogDataRaw, i64 0, i64 %85, !dbg !232
  %87 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %86, i32 0, i32 3, !dbg !233
  store i32 0, ptr %87, align 4, !dbg !234
  %88 = load i32, ptr %1, align 4, !dbg !235
  %89 = sext i32 %88 to i64, !dbg !236
  %90 = getelementptr inbounds [3 x %struct.TAG_FG_3_3_3SA_RAW], ptr @mFogDataRaw, i64 0, i64 %89, !dbg !236
  %91 = getelementptr inbounds %struct.TAG_FG_3_3_3SA_RAW, ptr %90, i32 0, i32 0, !dbg !237
  store double 0.000000e+00, ptr %91, align 8, !dbg !238
  br label %92

92:                                               ; preds = %83, %82
  br label %93, !dbg !239

93:                                               ; preds = %92
  %94 = load i32, ptr %1, align 4, !dbg !240
  %95 = add nsw i32 %94, 1, !dbg !240
  store i32 %95, ptr %1, align 4, !dbg !240
  br label %2, !dbg !241, !llvm.loop !242

96:                                               ; preds = %2
  ret void, !dbg !245
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @PowerOnJudge(ptr noundef %0, ptr noundef %1) #0 !dbg !246 {
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  call void @llvm.dbg.declare(metadata ptr %3, metadata !256, metadata !DIExpression()), !dbg !257
  store ptr %1, ptr %4, align 8
  call void @llvm.dbg.declare(metadata ptr %4, metadata !258, metadata !DIExpression()), !dbg !259
  call void @llvm.dbg.declare(metadata ptr %5, metadata !260, metadata !DIExpression()), !dbg !261
  %6 = load ptr, ptr %3, align 8, !dbg !262
  %7 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %6, i32 0, i32 6, !dbg !263
  %8 = load i32, ptr %7, align 4, !dbg !263
  store i32 %8, ptr %5, align 4, !dbg !264
  %9 = load i32, ptr %5, align 4, !dbg !265
  %10 = icmp eq i32 %9, 0, !dbg !267
  br i1 %10, label %11, label %32, !dbg !268

11:                                               ; preds = %2
  %12 = load ptr, ptr %3, align 8, !dbg !269
  %13 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %12, i32 0, i32 0, !dbg !272
  %14 = load i32, ptr %13, align 4, !dbg !272
  %15 = load ptr, ptr %4, align 8, !dbg !273
  %16 = getelementptr inbounds %struct.TAG_POWER_JUDGE_PARAM, ptr %15, i32 0, i32 0, !dbg !274
  %17 = load i32, ptr %16, align 4, !dbg !274
  %18 = icmp slt i32 %14, %17, !dbg !275
  br i1 %18, label %19, label %24, !dbg !276

19:                                               ; preds = %11
  %20 = load ptr, ptr %3, align 8, !dbg !277
  %21 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %20, i32 0, i32 0, !dbg !279
  %22 = load i32, ptr %21, align 4, !dbg !280
  %23 = add nsw i32 %22, 1, !dbg !280
  store i32 %23, ptr %21, align 4, !dbg !280
  br label %31, !dbg !281

24:                                               ; preds = %11
  %25 = load ptr, ptr %3, align 8, !dbg !282
  %26 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %25, i32 0, i32 1, !dbg !284
  store i32 0, ptr %26, align 4, !dbg !285
  %27 = load ptr, ptr %3, align 8, !dbg !286
  %28 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %27, i32 0, i32 3, !dbg !287
  store i32 0, ptr %28, align 4, !dbg !288
  %29 = load ptr, ptr %3, align 8, !dbg !289
  %30 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %29, i32 0, i32 2, !dbg !290
  store i32 0, ptr %30, align 4, !dbg !291
  br label %31

31:                                               ; preds = %24, %19
  br label %63, !dbg !292

32:                                               ; preds = %2
  %33 = load ptr, ptr %3, align 8, !dbg !293
  %34 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %33, i32 0, i32 3, !dbg !295
  %35 = load i32, ptr %34, align 4, !dbg !295
  %36 = icmp eq i32 %35, 0, !dbg !296
  br i1 %36, label %37, label %59, !dbg !297

37:                                               ; preds = %32
  %38 = load i32, ptr %5, align 4, !dbg !298
  %39 = icmp eq i32 %38, 255, !dbg !299
  br i1 %39, label %40, label %59, !dbg !300

40:                                               ; preds = %37
  %41 = load ptr, ptr %3, align 8, !dbg !301
  %42 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %41, i32 0, i32 1, !dbg !303
  %43 = load i32, ptr %42, align 4, !dbg !304
  %44 = add nsw i32 %43, 1, !dbg !304
  store i32 %44, ptr %42, align 4, !dbg !304
  %45 = load ptr, ptr %3, align 8, !dbg !305
  %46 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %45, i32 0, i32 1, !dbg !307
  %47 = load i32, ptr %46, align 4, !dbg !307
  %48 = load ptr, ptr %4, align 8, !dbg !308
  %49 = getelementptr inbounds %struct.TAG_POWER_JUDGE_PARAM, ptr %48, i32 0, i32 1, !dbg !309
  %50 = load i32, ptr %49, align 4, !dbg !309
  %51 = icmp sgt i32 %47, %50, !dbg !310
  br i1 %51, label %52, label %57, !dbg !311

52:                                               ; preds = %40
  %53 = load ptr, ptr %3, align 8, !dbg !312
  %54 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %53, i32 0, i32 0, !dbg !314
  store i32 0, ptr %54, align 4, !dbg !315
  %55 = load ptr, ptr %3, align 8, !dbg !316
  %56 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %55, i32 0, i32 2, !dbg !317
  store i32 -342879121, ptr %56, align 4, !dbg !318
  br label %58, !dbg !319

57:                                               ; preds = %40
  store i32 0, ptr %5, align 4, !dbg !320
  br label %58

58:                                               ; preds = %57, %52
  br label %62, !dbg !322

59:                                               ; preds = %37, %32
  br label %60, !dbg !323

60:                                               ; preds = %59
  br label %61, !dbg !325

61:                                               ; preds = %60
  br label %62

62:                                               ; preds = %61, %58
  br label %63

63:                                               ; preds = %62, %31
  %64 = load i32, ptr %5, align 4, !dbg !327
  %65 = load ptr, ptr %3, align 8, !dbg !328
  %66 = getelementptr inbounds %struct.TAG_POWER_JUDGE, ptr %65, i32 0, i32 3, !dbg !329
  store i32 %64, ptr %66, align 4, !dbg !330
  ret void, !dbg !331
}

declare i32 @Fg333saCheck(ptr noundef, i32 noundef, ptr noundef, ptr noundef) #2

declare void @Fg333saUnPack(ptr noundef, ptr noundef, double noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !332 {
  %1 = alloca ptr, align 8
  %2 = alloca ptr, align 8
  call void @llvm.dbg.declare(metadata ptr %1, metadata !335, metadata !DIExpression()), !dbg !336
  %3 = call noalias ptr @malloc(i64 noundef 40) #4, !dbg !337
  store ptr %3, ptr %1, align 8, !dbg !336
  call void @llvm.dbg.declare(metadata ptr %2, metadata !338, metadata !DIExpression()), !dbg !339
  %4 = call noalias ptr @malloc(i64 noundef 8) #4, !dbg !340
  store ptr %4, ptr %2, align 8, !dbg !339
  %5 = load ptr, ptr %1, align 8, !dbg !341
  %6 = load ptr, ptr %2, align 8, !dbg !342
  call void @PowerOnJudge(ptr noundef %5, ptr noundef %6), !dbg !343
  ret i32 0, !dbg !344
}

; Function Attrs: nounwind allocsize(0)
declare noalias ptr @malloc(i64 noundef) #3

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind allocsize(0) }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!146, !147, !148, !149, !150, !151, !152}
!llvm.ident = !{!153}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "mPowerJudgeFog", scope: !2, file: !3, line: 10, type: !30, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C11, file: !3, producer: "clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !4, globals: !9, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "gnc_input.c", directory: "/home/lkl/SoftwareIP/SIP/test/\E5\8E\9F\E5\A7\8B\E8\BE\93\E5\85\A5/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F2", checksumkind: CSK_MD5, checksum: "89404daeecc9493372e648e15d4c348d")
!4 = !{!5}
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64)
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "unint32", file: !7, line: 15, baseType: !8)
!7 = !DIFile(filename: "./std_basal.h", directory: "/home/lkl/SoftwareIP/SIP/test/\E5\8E\9F\E5\A7\8B\E8\BE\93\E5\85\A5/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F2", checksumkind: CSK_MD5, checksum: "e6894d170243f183681360646add8143")
!8 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!9 = !{!10, !28, !46, !85, !96, !0, !112, !139, !141}
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "mUartFog", scope: !2, file: !12, line: 187, type: !13, isLocal: false, isDefinition: true)
!12 = !DIFile(filename: "./gnc_input.h", directory: "/home/lkl/SoftwareIP/SIP/test/\E5\8E\9F\E5\A7\8B\E8\BE\93\E5\85\A5/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F2", checksumkind: CSK_MD5, checksum: "81616c755c19e8e1b15da02f1299160e")
!13 = !DICompositeType(tag: DW_TAG_array_type, baseType: !14, size: 12480, elements: !26)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "SUart", file: !12, line: 185, baseType: !15)
!15 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TAG_UART", file: !12, line: 178, size: 4160, elements: !16)
!16 = !{!17, !18, !24, !25}
!17 = !DIDerivedType(tag: DW_TAG_member, name: "cntRead", scope: !15, file: !12, line: 180, baseType: !6, size: 32)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "buff08Read", scope: !15, file: !12, line: 181, baseType: !19, size: 2048, offset: 32)
!19 = !DICompositeType(tag: DW_TAG_array_type, baseType: !20, size: 2048, elements: !22)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "unint08", file: !7, line: 11, baseType: !21)
!21 = !DIBasicType(name: "unsigned char", size: 8, encoding: DW_ATE_unsigned_char)
!22 = !{!23}
!23 = !DISubrange(count: 256)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "cntWrite", scope: !15, file: !12, line: 183, baseType: !6, size: 32, offset: 2080)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "buff08Write", scope: !15, file: !12, line: 184, baseType: !19, size: 2048, offset: 2112)
!26 = !{!27}
!27 = !DISubrange(count: 3)
!28 = !DIGlobalVariableExpression(var: !29, expr: !DIExpression())
!29 = distinct !DIGlobalVariable(name: "mPowerJudgeSts", scope: !2, file: !3, line: 6, type: !30, isLocal: false, isDefinition: true)
!30 = !DICompositeType(tag: DW_TAG_array_type, baseType: !31, size: 960, elements: !26)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "SPowerJudge", file: !12, line: 138, baseType: !32)
!32 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TAG_POWER_JUDGE", file: !12, line: 124, size: 320, elements: !33)
!33 = !{!34, !37, !38, !39, !40, !41, !42, !43, !44, !45}
!34 = !DIDerivedType(tag: DW_TAG_member, name: "cntPowerOff", scope: !32, file: !12, line: 126, baseType: !35, size: 32)
!35 = !DIDerivedType(tag: DW_TAG_typedef, name: "siint32", file: !7, line: 14, baseType: !36)
!36 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "cntPowerOn", scope: !32, file: !12, line: 127, baseType: !35, size: 32, offset: 32)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "bPowerOnOk", scope: !32, file: !12, line: 128, baseType: !6, size: 32, offset: 64)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "powerPr1", scope: !32, file: !12, line: 129, baseType: !6, size: 32, offset: 96)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "cntSoftPowerOn", scope: !32, file: !12, line: 131, baseType: !35, size: 32, offset: 128)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "softPowerPr1", scope: !32, file: !12, line: 132, baseType: !6, size: 32, offset: 160)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "flgPower", scope: !32, file: !12, line: 134, baseType: !6, size: 32, offset: 192)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "flgHardPower", scope: !32, file: !12, line: 135, baseType: !6, size: 32, offset: 224)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "flgSoftPower", scope: !32, file: !12, line: 136, baseType: !6, size: 32, offset: 256)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "flgPowerSel", scope: !32, file: !12, line: 137, baseType: !6, size: 32, offset: 288)
!46 = !DIGlobalVariableExpression(var: !47, expr: !DIExpression())
!47 = distinct !DIGlobalVariable(name: "mStsDataRaw", scope: !2, file: !3, line: 7, type: !48, isLocal: false, isDefinition: true)
!48 = !DICompositeType(tag: DW_TAG_array_type, baseType: !49, size: 14208, elements: !26)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "SStsDataRaw", file: !12, line: 103, baseType: !50)
!50 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TAG_STS_DATA_RAW", file: !12, line: 81, size: 4736, elements: !51)
!51 = !{!52, !53, !54, !55, !56, !57, !58, !59, !63, !65, !69, !71, !72, !76, !80, !84}
!52 = !DIDerivedType(tag: DW_TAG_member, name: "bComSuc", scope: !50, file: !12, line: 83, baseType: !6, size: 32)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "bValid", scope: !50, file: !12, line: 84, baseType: !6, size: 32, offset: 32)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "flagStatus", scope: !50, file: !12, line: 85, baseType: !6, size: 32, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "cntSynPulse", scope: !50, file: !12, line: 86, baseType: !35, size: 32, offset: 96)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "datation", scope: !50, file: !12, line: 87, baseType: !35, size: 32, offset: 128)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "quality", scope: !50, file: !12, line: 88, baseType: !6, size: 32, offset: 160)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "NumStarsIdentified", scope: !50, file: !12, line: 89, baseType: !6, size: 32, offset: 192)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "qRaw", scope: !50, file: !12, line: 90, baseType: !60, size: 128, offset: 224)
!60 = !DICompositeType(tag: DW_TAG_array_type, baseType: !6, size: 128, elements: !61)
!61 = !{!62}
!62 = !DISubrange(count: 4)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "wRaw", scope: !50, file: !12, line: 91, baseType: !64, size: 96, offset: 352)
!64 = !DICompositeType(tag: DW_TAG_array_type, baseType: !6, size: 96, elements: !26)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "q", scope: !50, file: !12, line: 93, baseType: !66, size: 256, offset: 448)
!66 = !DICompositeType(tag: DW_TAG_array_type, baseType: !67, size: 256, elements: !61)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "float64", file: !7, line: 17, baseType: !68)
!68 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "w", scope: !50, file: !12, line: 94, baseType: !70, size: 192, offset: 704)
!70 = !DICompositeType(tag: DW_TAG_array_type, baseType: !67, size: 192, elements: !26)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !50, file: !12, line: 96, baseType: !67, size: 64, offset: 896)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "tmBuff08", scope: !50, file: !12, line: 98, baseType: !73, size: 168, offset: 960)
!73 = !DICompositeType(tag: DW_TAG_array_type, baseType: !20, size: 168, elements: !74)
!74 = !{!75}
!75 = !DISubrange(count: 21)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "tmHk1Buff08", scope: !50, file: !12, line: 100, baseType: !77, size: 512, offset: 1128)
!77 = !DICompositeType(tag: DW_TAG_array_type, baseType: !20, size: 512, elements: !78)
!78 = !{!79}
!79 = !DISubrange(count: 64)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "tmZtBuff08", scope: !50, file: !12, line: 101, baseType: !81, size: 1024, offset: 1640)
!81 = !DICompositeType(tag: DW_TAG_array_type, baseType: !20, size: 1024, elements: !82)
!82 = !{!83}
!83 = !DISubrange(count: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "tmHknBuff08", scope: !50, file: !12, line: 102, baseType: !19, size: 2048, offset: 2664)
!85 = !DIGlobalVariableExpression(var: !86, expr: !DIExpression())
!86 = distinct !DIGlobalVariable(name: "mStsPps", scope: !2, file: !3, line: 8, type: !87, isLocal: false, isDefinition: true)
!87 = !DICompositeType(tag: DW_TAG_array_type, baseType: !88, size: 768, elements: !26)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "SStsPps", file: !12, line: 121, baseType: !89)
!89 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TAG_STS_PPS", file: !12, line: 112, size: 256, elements: !90)
!90 = !{!91, !92, !93, !94, !95}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "timePps", scope: !89, file: !12, line: 114, baseType: !67, size: 64)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "timePpsPr1", scope: !89, file: !12, line: 115, baseType: !67, size: 64, offset: 64)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "dltPps", scope: !89, file: !12, line: 117, baseType: !67, size: 64, offset: 128)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "cntSynPulse", scope: !89, file: !12, line: 119, baseType: !35, size: 32, offset: 192)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "cntSynPulsePr1", scope: !89, file: !12, line: 120, baseType: !35, size: 32, offset: 224)
!96 = !DIGlobalVariableExpression(var: !97, expr: !DIExpression())
!97 = distinct !DIGlobalVariable(name: "mComErrorSts", scope: !2, file: !3, line: 9, type: !98, isLocal: false, isDefinition: true)
!98 = !DICompositeType(tag: DW_TAG_array_type, baseType: !99, size: 960, elements: !26)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "SComError", file: !12, line: 167, baseType: !100)
!100 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TAG_COM_ERROR", file: !12, line: 154, size: 320, elements: !101)
!101 = !{!102, !103, !104, !105, !106, !107, !108, !109, !110, !111}
!102 = !DIDerivedType(tag: DW_TAG_member, name: "cntLenRd", scope: !100, file: !12, line: 156, baseType: !35, size: 32)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "cntHead", scope: !100, file: !12, line: 157, baseType: !35, size: 32, offset: 32)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "cntLen", scope: !100, file: !12, line: 158, baseType: !35, size: 32, offset: 64)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "cntCheck", scope: !100, file: !12, line: 159, baseType: !35, size: 32, offset: 96)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "cntUpdata", scope: !100, file: !12, line: 160, baseType: !35, size: 32, offset: 128)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "totalLenRd", scope: !100, file: !12, line: 162, baseType: !35, size: 32, offset: 160)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "totalHead", scope: !100, file: !12, line: 163, baseType: !35, size: 32, offset: 192)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "totalLen", scope: !100, file: !12, line: 164, baseType: !35, size: 32, offset: 224)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "totalCheck", scope: !100, file: !12, line: 165, baseType: !35, size: 32, offset: 256)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "totalUpdata", scope: !100, file: !12, line: 166, baseType: !35, size: 32, offset: 288)
!112 = !DIGlobalVariableExpression(var: !113, expr: !DIExpression())
!113 = distinct !DIGlobalVariable(name: "mFogDataRaw", scope: !2, file: !3, line: 11, type: !114, isLocal: false, isDefinition: true)
!114 = !DICompositeType(tag: DW_TAG_array_type, baseType: !115, size: 1728, elements: !26)
!115 = !DIDerivedType(tag: DW_TAG_typedef, name: "SFg333saRaw", file: !116, line: 32, baseType: !117)
!116 = !DIFile(filename: "./fg_3_3_3sa.h", directory: "/home/lkl/SoftwareIP/SIP/test/\E5\8E\9F\E5\A7\8B\E8\BE\93\E5\85\A5/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F/\E5\8E\9F\E5\A7\8BSAM\E6\BA\90\E7\A8\8B\E5\BA\8F2", checksumkind: CSK_MD5, checksum: "9fbbc49f5b7e542a48f527a2161899c7")
!117 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TAG_FG_3_3_3SA_RAW", file: !116, line: 8, size: 576, elements: !118)
!118 = !{!119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !136, !137, !138}
!119 = !DIDerivedType(tag: DW_TAG_member, name: "gf", scope: !117, file: !116, line: 10, baseType: !67, size: 64)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "wt0", scope: !117, file: !116, line: 11, baseType: !67, size: 64, offset: 64)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "cntFrame", scope: !117, file: !116, line: 12, baseType: !6, size: 32, offset: 128)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "bComSuc", scope: !117, file: !116, line: 14, baseType: !6, size: 32, offset: 160)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "cntLenRd", scope: !117, file: !116, line: 16, baseType: !35, size: 32, offset: 192)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "cntHead", scope: !117, file: !116, line: 17, baseType: !35, size: 32, offset: 224)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "cntLen", scope: !117, file: !116, line: 18, baseType: !35, size: 32, offset: 256)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "cntCheck", scope: !117, file: !116, line: 19, baseType: !35, size: 32, offset: 288)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "cntUpdata", scope: !117, file: !116, line: 20, baseType: !35, size: 32, offset: 320)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "totalLenRd", scope: !117, file: !116, line: 22, baseType: !35, size: 32, offset: 352)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "totalHead", scope: !117, file: !116, line: 23, baseType: !35, size: 32, offset: 384)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "totalLen", scope: !117, file: !116, line: 24, baseType: !35, size: 32, offset: 416)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "totalCheck", scope: !117, file: !116, line: 25, baseType: !35, size: 32, offset: 448)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "totalUpdata", scope: !117, file: !116, line: 26, baseType: !35, size: 32, offset: 480)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "glwd1", scope: !117, file: !116, line: 28, baseType: !134, size: 16, offset: 512)
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "unint16", file: !7, line: 13, baseType: !135)
!135 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "glwd2", scope: !117, file: !116, line: 29, baseType: !134, size: 16, offset: 528)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "dlwd", scope: !117, file: !116, line: 30, baseType: !134, size: 16, offset: 544)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "status", scope: !117, file: !116, line: 31, baseType: !20, size: 8, offset: 560)
!139 = !DIGlobalVariableExpression(var: !140, expr: !DIExpression())
!140 = distinct !DIGlobalVariable(name: "mPowerJudgeImuGyro", scope: !2, file: !3, line: 12, type: !30, isLocal: false, isDefinition: true)
!141 = !DIGlobalVariableExpression(var: !142, expr: !DIExpression())
!142 = distinct !DIGlobalVariable(name: "mPowerJudgeDssXY", scope: !2, file: !3, line: 13, type: !143, isLocal: false, isDefinition: true)
!143 = !DICompositeType(tag: DW_TAG_array_type, baseType: !31, size: 640, elements: !144)
!144 = !{!145}
!145 = !DISubrange(count: 2)
!146 = !{i32 7, !"Dwarf Version", i32 5}
!147 = !{i32 2, !"Debug Info Version", i32 3}
!148 = !{i32 1, !"wchar_size", i32 4}
!149 = !{i32 8, !"PIC Level", i32 2}
!150 = !{i32 7, !"PIE Level", i32 2}
!151 = !{i32 7, !"uwtable", i32 2}
!152 = !{i32 7, !"frame-pointer", i32 2}
!153 = !{!"clang version 16.0.0 (https://github.com/zbchen/GVFG-LLVM.git a44eb0d204ec5f401fb9df0f956112e21f6cf859)"}
!154 = distinct !DISubprogram(name: "InputData", scope: !3, file: !3, line: 19, type: !155, scopeLine: 20, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !157)
!155 = !DISubroutineType(types: !156)
!156 = !{null}
!157 = !{}
!158 = !DILocalVariable(name: "si", scope: !154, file: !3, line: 21, type: !35)
!159 = !DILocation(line: 21, column: 10, scope: !154)
!160 = !DILocation(line: 24, column: 8, scope: !161)
!161 = distinct !DILexicalBlock(scope: !154, file: !3, line: 24, column: 2)
!162 = !DILocation(line: 24, column: 6, scope: !161)
!163 = !DILocation(line: 24, column: 11, scope: !164)
!164 = distinct !DILexicalBlock(scope: !161, file: !3, line: 24, column: 2)
!165 = !DILocation(line: 24, column: 13, scope: !164)
!166 = !DILocation(line: 24, column: 2, scope: !161)
!167 = !DILocation(line: 27, column: 22, scope: !168)
!168 = distinct !DILexicalBlock(scope: !169, file: !3, line: 27, column: 7)
!169 = distinct !DILexicalBlock(scope: !164, file: !3, line: 25, column: 2)
!170 = !DILocation(line: 27, column: 7, scope: !168)
!171 = !DILocation(line: 27, column: 26, scope: !168)
!172 = !DILocation(line: 27, column: 38, scope: !168)
!173 = !DILocation(line: 27, column: 7, scope: !169)
!174 = !DILocation(line: 29, column: 57, scope: !175)
!175 = distinct !DILexicalBlock(scope: !168, file: !3, line: 28, column: 3)
!176 = !DILocation(line: 29, column: 42, scope: !175)
!177 = !DILocation(line: 29, column: 61, scope: !175)
!178 = !DILocation(line: 29, column: 27, scope: !175)
!179 = !DILocation(line: 29, column: 26, scope: !175)
!180 = !DILocation(line: 29, column: 4, scope: !175)
!181 = !DILocation(line: 29, column: 31, scope: !175)
!182 = !DILocation(line: 29, column: 40, scope: !175)
!183 = !DILocation(line: 30, column: 3, scope: !175)
!184 = !DILocation(line: 31, column: 56, scope: !169)
!185 = !DILocation(line: 31, column: 55, scope: !169)
!186 = !DILocation(line: 31, column: 33, scope: !169)
!187 = !DILocation(line: 31, column: 60, scope: !169)
!188 = !DILocation(line: 31, column: 18, scope: !169)
!189 = !DILocation(line: 31, column: 3, scope: !169)
!190 = !DILocation(line: 31, column: 22, scope: !169)
!191 = !DILocation(line: 31, column: 31, scope: !169)
!192 = !DILocation(line: 34, column: 32, scope: !169)
!193 = !DILocation(line: 34, column: 17, scope: !169)
!194 = !DILocation(line: 34, column: 3, scope: !169)
!195 = !DILocation(line: 36, column: 6, scope: !196)
!196 = distinct !DILexicalBlock(scope: !169, file: !3, line: 36, column: 6)
!197 = !DILocation(line: 36, column: 6, scope: !169)
!198 = !DILocation(line: 38, column: 53, scope: !199)
!199 = distinct !DILexicalBlock(scope: !196, file: !3, line: 37, column: 3)
!200 = !DILocation(line: 38, column: 44, scope: !199)
!201 = !DILocation(line: 38, column: 57, scope: !199)
!202 = !DILocation(line: 38, column: 81, scope: !199)
!203 = !DILocation(line: 38, column: 72, scope: !199)
!204 = !DILocation(line: 38, column: 85, scope: !199)
!205 = !DILocation(line: 38, column: 107, scope: !199)
!206 = !DILocation(line: 38, column: 95, scope: !199)
!207 = !DILocation(line: 38, column: 111, scope: !199)
!208 = !DILocation(line: 38, column: 145, scope: !199)
!209 = !DILocation(line: 38, column: 133, scope: !199)
!210 = !DILocation(line: 38, column: 30, scope: !199)
!211 = !DILocation(line: 38, column: 16, scope: !199)
!212 = !DILocation(line: 38, column: 4, scope: !199)
!213 = !DILocation(line: 38, column: 20, scope: !199)
!214 = !DILocation(line: 38, column: 28, scope: !199)
!215 = !DILocation(line: 40, column: 20, scope: !216)
!216 = distinct !DILexicalBlock(scope: !199, file: !3, line: 40, column: 8)
!217 = !DILocation(line: 40, column: 8, scope: !216)
!218 = !DILocation(line: 40, column: 24, scope: !216)
!219 = !DILocation(line: 40, column: 32, scope: !216)
!220 = !DILocation(line: 40, column: 8, scope: !199)
!221 = !DILocation(line: 42, column: 44, scope: !222)
!222 = distinct !DILexicalBlock(scope: !216, file: !3, line: 41, column: 4)
!223 = !DILocation(line: 42, column: 32, scope: !222)
!224 = !DILocation(line: 42, column: 60, scope: !222)
!225 = !DILocation(line: 42, column: 51, scope: !222)
!226 = !DILocation(line: 42, column: 64, scope: !222)
!227 = !DILocation(line: 42, column: 5, scope: !222)
!228 = !DILocation(line: 43, column: 4, scope: !222)
!229 = !DILocation(line: 44, column: 3, scope: !199)
!230 = !DILocation(line: 47, column: 16, scope: !231)
!231 = distinct !DILexicalBlock(scope: !196, file: !3, line: 46, column: 3)
!232 = !DILocation(line: 47, column: 4, scope: !231)
!233 = !DILocation(line: 47, column: 20, scope: !231)
!234 = !DILocation(line: 47, column: 28, scope: !231)
!235 = !DILocation(line: 50, column: 16, scope: !231)
!236 = !DILocation(line: 50, column: 4, scope: !231)
!237 = !DILocation(line: 50, column: 20, scope: !231)
!238 = !DILocation(line: 50, column: 23, scope: !231)
!239 = !DILocation(line: 52, column: 2, scope: !169)
!240 = !DILocation(line: 24, column: 24, scope: !164)
!241 = !DILocation(line: 24, column: 2, scope: !164)
!242 = distinct !{!242, !166, !243, !244}
!243 = !DILocation(line: 52, column: 2, scope: !161)
!244 = !{!"llvm.loop.mustprogress"}
!245 = !DILocation(line: 53, column: 2, scope: !154)
!246 = distinct !DISubprogram(name: "PowerOnJudge", scope: !3, file: !3, line: 57, type: !247, scopeLine: 58, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !157)
!247 = !DISubroutineType(types: !248)
!248 = !{null, !249, !250}
!249 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64)
!250 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !251, size: 64)
!251 = !DIDerivedType(tag: DW_TAG_typedef, name: "SPowerJudgeParam", file: !12, line: 144, baseType: !252)
!252 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TAG_POWER_JUDGE_PARAM", file: !12, line: 140, size: 64, elements: !253)
!253 = !{!254, !255}
!254 = !DIDerivedType(tag: DW_TAG_member, name: "numOffPeriod", scope: !252, file: !12, line: 142, baseType: !35, size: 32)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "numOnPeriod", scope: !252, file: !12, line: 143, baseType: !35, size: 32, offset: 32)
!256 = !DILocalVariable(name: "ptrPowerJudge", arg: 1, scope: !246, file: !3, line: 57, type: !249)
!257 = !DILocation(line: 57, column: 32, scope: !246)
!258 = !DILocalVariable(name: "ptrPowerJudgeParam", arg: 2, scope: !246, file: !3, line: 57, type: !250)
!259 = !DILocation(line: 57, column: 64, scope: !246)
!260 = !DILocalVariable(name: "powerState", scope: !246, file: !3, line: 59, type: !6)
!261 = !DILocation(line: 59, column: 10, scope: !246)
!262 = !DILocation(line: 61, column: 15, scope: !246)
!263 = !DILocation(line: 61, column: 30, scope: !246)
!264 = !DILocation(line: 61, column: 13, scope: !246)
!265 = !DILocation(line: 64, column: 5, scope: !266)
!266 = distinct !DILexicalBlock(scope: !246, file: !3, line: 64, column: 5)
!267 = !DILocation(line: 64, column: 16, scope: !266)
!268 = !DILocation(line: 64, column: 5, scope: !246)
!269 = !DILocation(line: 66, column: 6, scope: !270)
!270 = distinct !DILexicalBlock(scope: !271, file: !3, line: 66, column: 6)
!271 = distinct !DILexicalBlock(scope: !266, file: !3, line: 65, column: 2)
!272 = !DILocation(line: 66, column: 21, scope: !270)
!273 = !DILocation(line: 66, column: 35, scope: !270)
!274 = !DILocation(line: 66, column: 55, scope: !270)
!275 = !DILocation(line: 66, column: 33, scope: !270)
!276 = !DILocation(line: 66, column: 6, scope: !271)
!277 = !DILocation(line: 68, column: 4, scope: !278)
!278 = distinct !DILexicalBlock(scope: !270, file: !3, line: 67, column: 3)
!279 = !DILocation(line: 68, column: 19, scope: !278)
!280 = !DILocation(line: 68, column: 30, scope: !278)
!281 = !DILocation(line: 69, column: 3, scope: !278)
!282 = !DILocation(line: 73, column: 4, scope: !283)
!283 = distinct !DILexicalBlock(scope: !270, file: !3, line: 71, column: 3)
!284 = !DILocation(line: 73, column: 19, scope: !283)
!285 = !DILocation(line: 73, column: 30, scope: !283)
!286 = !DILocation(line: 74, column: 4, scope: !283)
!287 = !DILocation(line: 74, column: 19, scope: !283)
!288 = !DILocation(line: 74, column: 28, scope: !283)
!289 = !DILocation(line: 75, column: 4, scope: !283)
!290 = !DILocation(line: 75, column: 19, scope: !283)
!291 = !DILocation(line: 75, column: 30, scope: !283)
!292 = !DILocation(line: 77, column: 2, scope: !271)
!293 = !DILocation(line: 78, column: 11, scope: !294)
!294 = distinct !DILexicalBlock(scope: !266, file: !3, line: 78, column: 10)
!295 = !DILocation(line: 78, column: 26, scope: !294)
!296 = !DILocation(line: 78, column: 35, scope: !294)
!297 = !DILocation(line: 78, column: 51, scope: !294)
!298 = !DILocation(line: 78, column: 55, scope: !294)
!299 = !DILocation(line: 78, column: 66, scope: !294)
!300 = !DILocation(line: 78, column: 10, scope: !266)
!301 = !DILocation(line: 80, column: 3, scope: !302)
!302 = distinct !DILexicalBlock(scope: !294, file: !3, line: 79, column: 2)
!303 = !DILocation(line: 80, column: 18, scope: !302)
!304 = !DILocation(line: 80, column: 28, scope: !302)
!305 = !DILocation(line: 82, column: 6, scope: !306)
!306 = distinct !DILexicalBlock(scope: !302, file: !3, line: 82, column: 6)
!307 = !DILocation(line: 82, column: 21, scope: !306)
!308 = !DILocation(line: 82, column: 34, scope: !306)
!309 = !DILocation(line: 82, column: 54, scope: !306)
!310 = !DILocation(line: 82, column: 32, scope: !306)
!311 = !DILocation(line: 82, column: 6, scope: !302)
!312 = !DILocation(line: 84, column: 4, scope: !313)
!313 = distinct !DILexicalBlock(scope: !306, file: !3, line: 83, column: 3)
!314 = !DILocation(line: 84, column: 19, scope: !313)
!315 = !DILocation(line: 84, column: 31, scope: !313)
!316 = !DILocation(line: 87, column: 4, scope: !313)
!317 = !DILocation(line: 87, column: 19, scope: !313)
!318 = !DILocation(line: 87, column: 30, scope: !313)
!319 = !DILocation(line: 89, column: 3, scope: !313)
!320 = !DILocation(line: 93, column: 15, scope: !321)
!321 = distinct !DILexicalBlock(scope: !306, file: !3, line: 91, column: 3)
!322 = !DILocation(line: 95, column: 2, scope: !302)
!323 = !DILocation(line: 99, column: 3, scope: !324)
!324 = distinct !DILexicalBlock(scope: !294, file: !3, line: 97, column: 2)
!325 = !DILocation(line: 99, column: 3, scope: !326)
!326 = distinct !DILexicalBlock(scope: !324, file: !3, line: 99, column: 3)
!327 = !DILocation(line: 103, column: 28, scope: !246)
!328 = !DILocation(line: 103, column: 2, scope: !246)
!329 = !DILocation(line: 103, column: 17, scope: !246)
!330 = !DILocation(line: 103, column: 26, scope: !246)
!331 = !DILocation(line: 105, column: 2, scope: !246)
!332 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 108, type: !333, scopeLine: 108, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !157)
!333 = !DISubroutineType(types: !334)
!334 = !{!36}
!335 = !DILocalVariable(name: "ptrPowerJudge", scope: !332, file: !3, line: 109, type: !249)
!336 = !DILocation(line: 109, column: 18, scope: !332)
!337 = !DILocation(line: 109, column: 34, scope: !332)
!338 = !DILocalVariable(name: "ptrPowerJudgeParam", scope: !332, file: !3, line: 110, type: !250)
!339 = !DILocation(line: 110, column: 23, scope: !332)
!340 = !DILocation(line: 110, column: 44, scope: !332)
!341 = !DILocation(line: 111, column: 18, scope: !332)
!342 = !DILocation(line: 111, column: 33, scope: !332)
!343 = !DILocation(line: 111, column: 5, scope: !332)
!344 = !DILocation(line: 112, column: 1, scope: !332)
