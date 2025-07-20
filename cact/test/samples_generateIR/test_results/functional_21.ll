; ModuleID = '21'
source_filename = "21"

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

define i32 @whileIf() {
entry:
  %a = alloca i32, align 4
  store i32 0, ptr %a, align 4
  %b = alloca i32, align 4
  store i32 0, ptr %b, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i32, ptr %a, align 4
  %1 = icmp slt i32 %0, 100
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %4 = load i32, ptr %a, align 4
  %5 = icmp eq i32 %4, 5
  %6 = zext i1 %5 to i32
  %7 = icmp ne i32 %6, 0
  br i1 %7, label %if.then, label %if.else

while.exit:                                       ; preds = %while.cond
  %8 = load i32, ptr %b, align 4
  ret i32 %8

if.then:                                          ; preds = %while.body
  store i32 25, ptr %b, align 4
  br label %if.end

if.end:                                           ; preds = %if.end2, %if.then
  %9 = load i32, ptr %a, align 4
  %10 = add i32 %9, 1
  store i32 %10, ptr %a, align 4
  br label %while.cond

if.else:                                          ; preds = %while.body
  %11 = load i32, ptr %a, align 4
  %12 = icmp eq i32 %11, 10
  %13 = zext i1 %12 to i32
  %14 = icmp ne i32 %13, 0
  br i1 %14, label %if.then1, label %if.else3

if.then1:                                         ; preds = %if.else
  store i32 42, ptr %b, align 4
  br label %if.end2

if.end2:                                          ; preds = %if.else3, %if.then1
  br label %if.end

if.else3:                                         ; preds = %if.else
  %15 = load i32, ptr %a, align 4
  %16 = mul i32 %15, 2
  store i32 %16, ptr %b, align 4
  br label %if.end2

unreachable:                                      ; No predecessors!
  ret i32 0
}

define i32 @main() {
entry:
  %0 = call i32 @whileIf()
  %1 = call i32 (ptr, ...) @printf(ptr @0, i32 %0)
  ret i32 %0

unreachable:                                      ; No predecessors!
  ret i32 0
}
