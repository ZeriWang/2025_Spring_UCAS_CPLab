; ModuleID = '02_mv2'
source_filename = "02_mv2"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@x = global i32 0, align 4
@N = constant i32 2010, align 4
@A = global [2010 x [2010 x i32]] zeroinitializer, align 4
@B = global [2010 x i32] zeroinitializer, align 4
@C = global [2010 x i32] zeroinitializer, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define void @mv(i32 %n, ptr %A, ptr %b, ptr %res) {
entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  store i32 0, ptr %y, align 4
  store i32 11, ptr %x, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store i32 0, ptr %i, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr %n1, align 4
  %2 = icmp slt i32 %0, %1
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %5 = load i32, ptr %i, align 4
  %6 = getelementptr i32, ptr %res, i32 %5
  store i32 0, ptr %6, align 4
  %7 = load i32, ptr %i, align 4
  %8 = add i32 %7, 1
  store i32 %8, ptr %i, align 4
  br label %while.cond

while.exit:                                       ; preds = %while.cond
  store i32 0, ptr %i, align 4
  store i32 0, ptr %j, align 4
  br label %while.cond2

while.cond2:                                      ; preds = %while.exit7, %while.exit
  %9 = load i32, ptr %i, align 4
  %10 = load i32, ptr %n1, align 4
  %11 = icmp slt i32 %9, %10
  %12 = zext i1 %11 to i32
  %13 = icmp ne i32 %12, 0
  br i1 %13, label %while.body3, label %while.exit4

while.body3:                                      ; preds = %while.cond2
  store i32 0, ptr %j, align 4
  br label %while.cond5

while.exit4:                                      ; preds = %while.cond2
  ret void

while.cond5:                                      ; preds = %if.end, %while.body3
  %14 = load i32, ptr %j, align 4
  %15 = load i32, ptr %n1, align 4
  %16 = icmp slt i32 %14, %15
  %17 = zext i1 %16 to i32
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %while.body6, label %while.exit7

while.body6:                                      ; preds = %while.cond5
  %19 = load i32, ptr %i, align 4
  %20 = load i32, ptr %j, align 4
  %21 = getelementptr [2010 x i32], ptr %A, i32 %19, i32 %20
  %22 = load i32, ptr %21, align 4
  %23 = icmp eq i32 %22, 0
  %24 = zext i1 %23 to i32
  %25 = icmp ne i32 %24, 0
  br i1 %25, label %if.then, label %if.else

while.exit7:                                      ; preds = %while.cond5
  %26 = load i32, ptr %i, align 4
  %27 = add i32 %26, 1
  store i32 %27, ptr %i, align 4
  br label %while.cond2

if.then:                                          ; preds = %while.body6
  %28 = load i32, ptr %x, align 4
  %29 = load i32, ptr %i, align 4
  %30 = getelementptr i32, ptr %b, i32 %29
  %31 = load i32, ptr %30, align 4
  %32 = mul i32 %28, %31
  %33 = load i32, ptr %j, align 4
  %34 = getelementptr i32, ptr %b, i32 %33
  %35 = load i32, ptr %34, align 4
  %36 = add i32 %32, %35
  store i32 %36, ptr %x, align 4
  %37 = load i32, ptr %y, align 4
  %38 = load i32, ptr %x, align 4
  %39 = sub i32 %37, %38
  store i32 %39, ptr %y, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %40 = load i32, ptr %j, align 4
  %41 = add i32 %40, 1
  store i32 %41, ptr %j, align 4
  br label %while.cond5

if.else:                                          ; preds = %while.body6
  %42 = load i32, ptr %i, align 4
  %43 = getelementptr i32, ptr %res, i32 %42
  %44 = load i32, ptr %i, align 4
  %45 = getelementptr i32, ptr %res, i32 %44
  %46 = load i32, ptr %45, align 4
  %47 = load i32, ptr %i, align 4
  %48 = load i32, ptr %j, align 4
  %49 = getelementptr [2010 x i32], ptr %A, i32 %47, i32 %48
  %50 = load i32, ptr %49, align 4
  %51 = load i32, ptr %j, align 4
  %52 = getelementptr i32, ptr %b, i32 %51
  %53 = load i32, ptr %52, align 4
  %54 = mul i32 %50, %53
  %55 = add i32 %46, %54
  store i32 %55, ptr %43, align 4
  br label %if.end
}

define i32 @main() {
entry:
  %n = alloca i32, align 4
  %0 = call i32 @get_int()
  store i32 %0, ptr %n, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %res = alloca i32, align 4
  store i32 0, ptr %res, align 4
  store i32 0, ptr %i, align 4
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
  %13 = getelementptr [2010 x [2010 x i32]], ptr @A, i32 0, i32 %11, i32 %12
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

while.cond4:                                      ; preds = %while.body5, %while.exit
  %19 = load i32, ptr %i, align 4
  %20 = load i32, ptr %n, align 4
  %21 = icmp slt i32 %19, %20
  %22 = zext i1 %21 to i32
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %while.body5, label %while.exit6

while.body5:                                      ; preds = %while.cond4
  %24 = load i32, ptr %i, align 4
  %25 = getelementptr [2010 x i32], ptr @B, i32 0, i32 %24
  %26 = call i32 @get_int()
  store i32 %26, ptr %25, align 4
  %27 = load i32, ptr %i, align 4
  %28 = add i32 %27, 1
  store i32 %28, ptr %i, align 4
  br label %while.cond4

while.exit6:                                      ; preds = %while.cond4
  store i32 0, ptr %i, align 4
  br label %while.cond7

while.cond7:                                      ; preds = %while.body8, %while.exit6
  %29 = load i32, ptr %i, align 4
  %30 = icmp slt i32 %29, 50
  %31 = zext i1 %30 to i32
  %32 = icmp ne i32 %31, 0
  br i1 %32, label %while.body8, label %while.exit9

while.body8:                                      ; preds = %while.cond7
  %33 = load i32, ptr %n, align 4
  call void @mv(i32 %33, ptr @A, ptr @B, ptr @C)
  %34 = load i32, ptr %n, align 4
  call void @mv(i32 %34, ptr @A, ptr @C, ptr @B)
  %35 = load i32, ptr %i, align 4
  %36 = add i32 %35, 1
  store i32 %36, ptr %i, align 4
  br label %while.cond7

while.exit9:                                      ; preds = %while.cond7
  store i32 0, ptr %i, align 4
  br label %while.cond10

while.cond10:                                     ; preds = %while.body11, %while.exit9
  %37 = load i32, ptr %i, align 4
  %38 = load i32, ptr %n, align 4
  %39 = icmp slt i32 %37, %38
  %40 = zext i1 %39 to i32
  %41 = icmp ne i32 %40, 0
  br i1 %41, label %while.body11, label %while.exit12

while.body11:                                     ; preds = %while.cond10
  %42 = load i32, ptr %res, align 4
  %43 = load i32, ptr %i, align 4
  %44 = getelementptr [2010 x i32], ptr @C, i32 0, i32 %43
  %45 = load i32, ptr %44, align 4
  %46 = add i32 %42, %45
  %47 = load i32, ptr %n, align 4
  %48 = srem i32 %46, %47
  store i32 %48, ptr %res, align 4
  %49 = load i32, ptr %i, align 4
  %50 = add i32 %49, 1
  store i32 %50, ptr %i, align 4
  br label %while.cond10

while.exit12:                                     ; preds = %while.cond10
  %51 = load i32, ptr %res, align 4
  call void @print_int(i32 %51)
  call void @print_char(i8 10)
  %52 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  ret i32 0

unreachable:                                      ; No predecessors!
  ret i32 0
}
