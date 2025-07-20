; ModuleID = '04'
source_filename = "04"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define i32 @main() {
entry:
  %a = alloca [4 x [2 x i32]], align 4
  call void @llvm.memset.p0.i64(ptr %a, i8 0, i64 32, i1 false)
  %c = alloca [4 x [2 x i32]], align 4
  call void @llvm.memset.p0.i64(ptr %c, i8 0, i64 32, i1 false)
  %0 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 0, i32 0
  store i32 1, ptr %0, align 4
  %1 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 0, i32 1
  store i32 2, ptr %1, align 4
  %2 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 1, i32 0
  store i32 3, ptr %2, align 4
  %3 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 1, i32 1
  store i32 4, ptr %3, align 4
  %4 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 2, i32 0
  store i32 5, ptr %4, align 4
  %5 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 2, i32 1
  store i32 6, ptr %5, align 4
  %6 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 3, i32 0
  store i32 7, ptr %6, align 4
  %7 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 3, i32 1
  store i32 8, ptr %7, align 4
  %e = alloca [4 x [2 x i32]], align 4
  call void @llvm.memset.p0.i64(ptr %e, i8 0, i64 32, i1 false)
  %8 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 0, i32 0
  store i32 1, ptr %8, align 4
  %9 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 0, i32 1
  store i32 2, ptr %9, align 4
  %10 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 1, i32 0
  store i32 3, ptr %10, align 4
  %11 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 1, i32 1
  store i32 4, ptr %11, align 4
  %12 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 2, i32 0
  store i32 5, ptr %12, align 4
  %13 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 2, i32 1
  store i32 6, ptr %13, align 4
  %14 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 3, i32 0
  store i32 7, ptr %14, align 4
  %15 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 3, i32 1
  store i32 8, ptr %15, align 4
  %16 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 0, i32 0
  %17 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 2, i32 1
  %18 = load i32, ptr %17, align 4
  store i32 %18, ptr %16, align 4
  %19 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 0, i32 1
  %20 = getelementptr [4 x [2 x i32]], ptr %c, i32 0, i32 1, i32 1
  %21 = load i32, ptr %20, align 4
  store i32 %21, ptr %19, align 4
  %22 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 3, i32 1
  %23 = load i32, ptr %22, align 4
  %24 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 0, i32 0
  %25 = load i32, ptr %24, align 4
  %26 = add i32 %23, %25
  %27 = getelementptr [4 x [2 x i32]], ptr %e, i32 0, i32 0, i32 1
  %28 = load i32, ptr %27, align 4
  %29 = add i32 %26, %28
  %30 = getelementptr [4 x [2 x i32]], ptr %a, i32 0, i32 2, i32 0
  %31 = load i32, ptr %30, align 4
  %32 = add i32 %29, %31
  %33 = call i32 (ptr, ...) @printf(ptr @0, i32 %32)
  ret i32 %32

unreachable:                                      ; No predecessors!
  ret i32 0
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #0

attributes #0 = { nocallback nofree nounwind willreturn memory(argmem: write) }
