; ModuleID = '22'
source_filename = "22"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@arr = global [6 x i32] [i32 1, i32 2, i32 33, i32 4, i32 5, i32 6], align 4
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
  %i = alloca i32, align 4
  store i32 0, ptr %i, align 4
  %sum = alloca i32, align 4
  store i32 0, ptr %sum, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i32, ptr %i, align 4
  %1 = icmp slt i32 %0, 6
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %4 = load i32, ptr %sum, align 4
  %5 = load i32, ptr %i, align 4
  %6 = getelementptr [6 x i32], ptr @arr, i32 0, i32 %5
  %7 = load i32, ptr %6, align 4
  %8 = add i32 %4, %7
  store i32 %8, ptr %sum, align 4
  %9 = load i32, ptr %i, align 4
  %10 = add i32 %9, 1
  store i32 %10, ptr %i, align 4
  br label %while.cond

while.exit:                                       ; preds = %while.cond
  %11 = load i32, ptr %sum, align 4
  %12 = call i32 (ptr, ...) @printf(ptr @0, i32 %11)
  ret i32 %11

unreachable:                                      ; No predecessors!
  ret i32 0
}
