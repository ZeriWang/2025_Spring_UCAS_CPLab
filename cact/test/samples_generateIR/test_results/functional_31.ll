; ModuleID = '31'
source_filename = "31"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@k = global i32 0, align 4
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
  store i32 3389, ptr @k, align 4
  %0 = load i32, ptr @k, align 4
  %1 = icmp slt i32 %0, 10000
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %4 = load i32, ptr @k, align 4
  %5 = add i32 %4, 1
  store i32 %5, ptr @k, align 4
  %k = alloca i32, align 4
  store i32 112, ptr %k, align 4
  br label %while.cond

if.end:                                           ; preds = %while.exit, %entry
  call void @print_char(i8 10)
  %6 = load i32, ptr @k, align 4
  %7 = call i32 (ptr, ...) @printf(ptr @0, i32 %6)
  ret i32 %6

while.cond:                                       ; preds = %if.end2, %if.then
  %8 = load i32, ptr %k, align 4
  %9 = icmp sgt i32 %8, 10
  %10 = zext i1 %9 to i32
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %12 = load i32, ptr %k, align 4
  %13 = sub i32 %12, 88
  store i32 %13, ptr %k, align 4
  %14 = load i32, ptr %k, align 4
  %15 = icmp slt i32 %14, 1000
  %16 = zext i1 %15 to i32
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %if.then1, label %if.end2

while.exit:                                       ; preds = %while.cond
  %18 = load i32, ptr %k, align 4
  call void @print_int(i32 %18)
  br label %if.end

if.then1:                                         ; preds = %while.body
  %g = alloca i32, align 4
  store i32 9, ptr %g, align 4
  %l = alloca i32, align 4
  store i32 11, ptr %l, align 4
  store i32 10, ptr %g, align 4
  %19 = load i32, ptr %k, align 4
  %20 = load i32, ptr %g, align 4
  %21 = sub i32 %19, %20
  store i32 %21, ptr %k, align 4
  %g3 = alloca i32, align 4
  store i32 11, ptr %g3, align 4
  %22 = load i32, ptr %k, align 4
  %23 = load i32, ptr %g3, align 4
  %24 = add i32 %22, %23
  %25 = load i32, ptr %l, align 4
  %26 = add i32 %24, %25
  store i32 %26, ptr %k, align 4
  br label %if.end2

if.end2:                                          ; preds = %if.then1, %while.body
  br label %while.cond

unreachable:                                      ; No predecessors!
  ret i32 0
}
