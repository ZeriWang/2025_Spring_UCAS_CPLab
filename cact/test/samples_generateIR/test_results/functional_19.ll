; ModuleID = '19'
source_filename = "19"

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
  %i = alloca i32, align 4
  store i32 0, ptr %i, align 4
  %sum = alloca i32, align 4
  store i32 0, ptr %sum, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i32, ptr %i, align 4
  %1 = icmp slt i32 %0, 100
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %4 = load i32, ptr %i, align 4
  %5 = icmp eq i32 %4, 50
  %6 = zext i1 %5 to i32
  %7 = icmp ne i32 %6, 0
  br i1 %7, label %if.then, label %if.end

while.exit:                                       ; preds = %if.then, %while.cond
  %8 = load i32, ptr %sum, align 4
  %9 = srem i32 %8, 256
  %10 = call i32 (ptr, ...) @printf(ptr @0, i32 %9)
  ret i32 %9

if.then:                                          ; preds = %while.body
  br label %while.exit

if.end:                                           ; preds = %unreachable, %while.body
  %11 = load i32, ptr %sum, align 4
  %12 = load i32, ptr %i, align 4
  %13 = add i32 %11, %12
  store i32 %13, ptr %sum, align 4
  %14 = load i32, ptr %i, align 4
  %15 = add i32 %14, 1
  store i32 %15, ptr %i, align 4
  br label %while.cond

unreachable:                                      ; No predecessors!
  br label %if.end

unreachable1:                                     ; No predecessors!
  ret i32 0
}
