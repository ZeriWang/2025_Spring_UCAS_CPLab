; ModuleID = '01_mm2'
source_filename = "01_mm2"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@N = constant i32 1024, align 4
@A = global [1024 x [1024 x i32]] zeroinitializer, align 4
@B = global [1024 x [1024 x i32]] zeroinitializer, align 4
@C = global [1024 x [1024 x i32]] zeroinitializer, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define void @mm(i32 %n, ptr %A, ptr %B, ptr %C) {
entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca i32, align 4
  store i32 0, ptr %i, align 4
  store i32 0, ptr %j, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.exit4, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr %n1, align 4
  %2 = icmp slt i32 %0, %1
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  store i32 0, ptr %j, align 4
  br label %while.cond2

while.exit:                                       ; preds = %while.cond
  store i32 0, ptr %i, align 4
  store i32 0, ptr %j, align 4
  store i32 0, ptr %k, align 4
  br label %while.cond5

while.cond2:                                      ; preds = %while.body3, %while.body
  %5 = load i32, ptr %j, align 4
  %6 = load i32, ptr %n1, align 4
  %7 = icmp slt i32 %5, %6
  %8 = zext i1 %7 to i32
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %while.body3, label %while.exit4

while.body3:                                      ; preds = %while.cond2
  %10 = load i32, ptr %i, align 4
  %11 = load i32, ptr %j, align 4
  %12 = getelementptr [1024 x i32], ptr %C, i32 %10, i32 %11
  store i32 0, ptr %12, align 4
  %13 = load i32, ptr %j, align 4
  %14 = add i32 %13, 1
  store i32 %14, ptr %j, align 4
  br label %while.cond2

while.exit4:                                      ; preds = %while.cond2
  %15 = load i32, ptr %i, align 4
  %16 = add i32 %15, 1
  store i32 %16, ptr %i, align 4
  br label %while.cond

while.cond5:                                      ; preds = %while.exit10, %while.exit
  %17 = load i32, ptr %k, align 4
  %18 = load i32, ptr %n1, align 4
  %19 = icmp slt i32 %17, %18
  %20 = zext i1 %19 to i32
  %21 = icmp ne i32 %20, 0
  br i1 %21, label %while.body6, label %while.exit7

while.body6:                                      ; preds = %while.cond5
  store i32 0, ptr %i, align 4
  br label %while.cond8

while.exit7:                                      ; preds = %while.cond5
  ret void

while.cond8:                                      ; preds = %while.exit13, %if.then, %while.body6
  %22 = load i32, ptr %i, align 4
  %23 = load i32, ptr %n1, align 4
  %24 = icmp slt i32 %22, %23
  %25 = zext i1 %24 to i32
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %while.body9, label %while.exit10

while.body9:                                      ; preds = %while.cond8
  %27 = load i32, ptr %i, align 4
  %28 = load i32, ptr %k, align 4
  %29 = getelementptr [1024 x i32], ptr %A, i32 %27, i32 %28
  %30 = load i32, ptr %29, align 4
  %31 = icmp eq i32 %30, 0
  %32 = zext i1 %31 to i32
  %33 = icmp ne i32 %32, 0
  br i1 %33, label %if.then, label %if.end

while.exit10:                                     ; preds = %while.cond8
  %34 = load i32, ptr %k, align 4
  %35 = add i32 %34, 1
  store i32 %35, ptr %k, align 4
  br label %while.cond5

if.then:                                          ; preds = %while.body9
  %36 = load i32, ptr %i, align 4
  %37 = add i32 %36, 1
  store i32 %37, ptr %i, align 4
  br label %while.cond8

if.end:                                           ; preds = %unreachable, %while.body9
  store i32 0, ptr %j, align 4
  br label %while.cond11

unreachable:                                      ; No predecessors!
  br label %if.end

while.cond11:                                     ; preds = %while.body12, %if.end
  %38 = load i32, ptr %j, align 4
  %39 = load i32, ptr %n1, align 4
  %40 = icmp slt i32 %38, %39
  %41 = zext i1 %40 to i32
  %42 = icmp ne i32 %41, 0
  br i1 %42, label %while.body12, label %while.exit13

while.body12:                                     ; preds = %while.cond11
  %43 = load i32, ptr %i, align 4
  %44 = load i32, ptr %j, align 4
  %45 = getelementptr [1024 x i32], ptr %C, i32 %43, i32 %44
  %46 = load i32, ptr %i, align 4
  %47 = load i32, ptr %j, align 4
  %48 = getelementptr [1024 x i32], ptr %C, i32 %46, i32 %47
  %49 = load i32, ptr %48, align 4
  %50 = load i32, ptr %i, align 4
  %51 = load i32, ptr %k, align 4
  %52 = getelementptr [1024 x i32], ptr %A, i32 %50, i32 %51
  %53 = load i32, ptr %52, align 4
  %54 = load i32, ptr %k, align 4
  %55 = load i32, ptr %j, align 4
  %56 = getelementptr [1024 x i32], ptr %B, i32 %54, i32 %55
  %57 = load i32, ptr %56, align 4
  %58 = mul i32 %53, %57
  %59 = add i32 %49, %58
  store i32 %59, ptr %45, align 4
  %60 = load i32, ptr %j, align 4
  %61 = add i32 %60, 1
  store i32 %61, ptr %j, align 4
  br label %while.cond11

while.exit13:                                     ; preds = %while.cond11
  %62 = load i32, ptr %i, align 4
  %63 = add i32 %62, 1
  store i32 %63, ptr %i, align 4
  br label %while.cond8
}

define i32 @main() {
entry:
  %n = alloca i32, align 4
  %0 = call i32 @get_int()
  store i32 %0, ptr %n, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store i32 0, ptr %i, align 4
  store i32 0, ptr %j, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.exit3, %entry
  %1 = load i32, ptr %i, align 4
  %2 = load i32, ptr %n, align 4
  %3 = icmp slt i32 %1, %2
  %4 = zext i1 %3 to i32
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  store i32 0, ptr %j, align 4
  br label %while.cond1

while.exit:                                       ; preds = %while.cond
  store i32 0, ptr %i, align 4
  store i32 0, ptr %j, align 4
  br label %while.cond4

while.cond1:                                      ; preds = %while.body2, %while.body
  %6 = load i32, ptr %j, align 4
  %7 = load i32, ptr %n, align 4
  %8 = icmp slt i32 %6, %7
  %9 = zext i1 %8 to i32
  %10 = icmp ne i32 %9, 0
  br i1 %10, label %while.body2, label %while.exit3

while.body2:                                      ; preds = %while.cond1
  %11 = load i32, ptr %i, align 4
  %12 = load i32, ptr %j, align 4
  %13 = getelementptr [1024 x [1024 x i32]], ptr @A, i32 0, i32 %11, i32 %12
  %14 = call i32 @get_int()
  store i32 %14, ptr %13, align 4
  %15 = load i32, ptr %j, align 4
  %16 = add i32 %15, 1
  store i32 %16, ptr %j, align 4
  br label %while.cond1

while.exit3:                                      ; preds = %while.cond1
  %17 = load i32, ptr %i, align 4
  %18 = add i32 %17, 1
  store i32 %18, ptr %i, align 4
  br label %while.cond

while.cond4:                                      ; preds = %while.exit9, %while.exit
  %19 = load i32, ptr %i, align 4
  %20 = load i32, ptr %n, align 4
  %21 = icmp slt i32 %19, %20
  %22 = zext i1 %21 to i32
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %while.body5, label %while.exit6

while.body5:                                      ; preds = %while.cond4
  store i32 0, ptr %j, align 4
  br label %while.cond7

while.exit6:                                      ; preds = %while.cond4
  store i32 0, ptr %i, align 4
  br label %while.cond10

while.cond7:                                      ; preds = %while.body8, %while.body5
  %24 = load i32, ptr %j, align 4
  %25 = load i32, ptr %n, align 4
  %26 = icmp slt i32 %24, %25
  %27 = zext i1 %26 to i32
  %28 = icmp ne i32 %27, 0
  br i1 %28, label %while.body8, label %while.exit9

while.body8:                                      ; preds = %while.cond7
  %29 = load i32, ptr %i, align 4
  %30 = load i32, ptr %j, align 4
  %31 = getelementptr [1024 x [1024 x i32]], ptr @B, i32 0, i32 %29, i32 %30
  %32 = call i32 @get_int()
  store i32 %32, ptr %31, align 4
  %33 = load i32, ptr %j, align 4
  %34 = add i32 %33, 1
  store i32 %34, ptr %j, align 4
  br label %while.cond7

while.exit9:                                      ; preds = %while.cond7
  %35 = load i32, ptr %i, align 4
  %36 = add i32 %35, 1
  store i32 %36, ptr %i, align 4
  br label %while.cond4

while.cond10:                                     ; preds = %while.body11, %while.exit6
  %37 = load i32, ptr %i, align 4
  %38 = icmp slt i32 %37, 5
  %39 = zext i1 %38 to i32
  %40 = icmp ne i32 %39, 0
  br i1 %40, label %while.body11, label %while.exit12

while.body11:                                     ; preds = %while.cond10
  %41 = load i32, ptr %n, align 4
  call void @mm(i32 %41, ptr @A, ptr @B, ptr @C)
  %42 = load i32, ptr %n, align 4
  call void @mm(i32 %42, ptr @A, ptr @C, ptr @B)
  %43 = load i32, ptr %i, align 4
  %44 = add i32 %43, 1
  store i32 %44, ptr %i, align 4
  br label %while.cond10

while.exit12:                                     ; preds = %while.cond10
  %ans = alloca i32, align 4
  store i32 0, ptr %ans, align 4
  store i32 0, ptr %i, align 4
  br label %while.cond13

while.cond13:                                     ; preds = %while.exit18, %while.exit12
  %45 = load i32, ptr %i, align 4
  %46 = load i32, ptr %n, align 4
  %47 = icmp slt i32 %45, %46
  %48 = zext i1 %47 to i32
  %49 = icmp ne i32 %48, 0
  br i1 %49, label %while.body14, label %while.exit15

while.body14:                                     ; preds = %while.cond13
  store i32 0, ptr %j, align 4
  br label %while.cond16

while.exit15:                                     ; preds = %while.cond13
  %50 = load i32, ptr %ans, align 4
  call void @print_int(i32 %50)
  call void @print_char(i8 10)
  %51 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  ret i32 0

while.cond16:                                     ; preds = %while.body17, %while.body14
  %52 = load i32, ptr %j, align 4
  %53 = load i32, ptr %n, align 4
  %54 = icmp slt i32 %52, %53
  %55 = zext i1 %54 to i32
  %56 = icmp ne i32 %55, 0
  br i1 %56, label %while.body17, label %while.exit18

while.body17:                                     ; preds = %while.cond16
  %57 = load i32, ptr %ans, align 4
  %58 = load i32, ptr %i, align 4
  %59 = load i32, ptr %j, align 4
  %60 = getelementptr [1024 x [1024 x i32]], ptr @B, i32 0, i32 %58, i32 %59
  %61 = load i32, ptr %60, align 4
  %62 = add i32 %57, %61
  store i32 %62, ptr %ans, align 4
  %63 = load i32, ptr %j, align 4
  %64 = add i32 %63, 1
  store i32 %64, ptr %j, align 4
  br label %while.cond16

while.exit18:                                     ; preds = %while.cond16
  %65 = load i32, ptr %i, align 4
  %66 = add i32 %65, 1
  store i32 %66, ptr %i, align 4
  br label %while.cond13

unreachable:                                      ; No predecessors!
  ret i32 0
}
