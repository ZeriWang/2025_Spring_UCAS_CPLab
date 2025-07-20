; ModuleID = '30'
source_filename = "30"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@a = global i32 7, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define i32 @func() {
entry:
  %b = alloca i32, align 4
  store i32 -1, ptr %b, align 4
  %0 = load i32, ptr @a, align 4
  store i32 %0, ptr %b, align 4
  %a = alloca i32, align 4
  store i32 1, ptr %a, align 4
  %1 = load i32, ptr %a, align 4
  %2 = load i32, ptr %b, align 4
  %3 = icmp eq i32 %1, %2
  %4 = zext i1 %3 to i32
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %6 = load i32, ptr %a, align 4
  %7 = add i32 %6, 1
  store i32 %7, ptr %a, align 4
  ret i32 1

if.end:                                           ; preds = %unreachable1, %unreachable
  ret i32 0

if.else:                                          ; preds = %entry
  ret i32 0

unreachable:                                      ; No predecessors!
  br label %if.end

unreachable1:                                     ; No predecessors!
  br label %if.end
}

define i32 @main() {
entry:
  %result = alloca i32, align 4
  store i32 0, ptr %result, align 4
  %i = alloca i32, align 4
  store i32 0, ptr %i, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i32, ptr %i, align 4
  %1 = icmp slt i32 %0, 100
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %4 = call i32 @func()
  %5 = icmp eq i32 %4, 1
  %6 = zext i1 %5 to i32
  %7 = icmp ne i32 %6, 0
  br i1 %7, label %if.then, label %if.end

while.exit:                                       ; preds = %while.cond
  %8 = load i32, ptr %result, align 4
  %9 = icmp slt i32 %8, 100
  %10 = zext i1 %9 to i32
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %if.then1, label %if.else

if.then:                                          ; preds = %while.body
  %12 = load i32, ptr %result, align 4
  %13 = add i32 %12, 1
  store i32 %13, ptr %result, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %while.body
  %14 = load i32, ptr %i, align 4
  %15 = add i32 %14, 1
  store i32 %15, ptr %i, align 4
  br label %while.cond

if.then1:                                         ; preds = %while.exit
  call void @print_int(i32 1)
  br label %if.end2

if.end2:                                          ; preds = %if.else, %if.then1
  call void @print_char(i8 10)
  %16 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  ret i32 0

if.else:                                          ; preds = %while.exit
  call void @print_int(i32 0)
  br label %if.end2

unreachable:                                      ; No predecessors!
  ret i32 0
}
