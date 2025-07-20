; ModuleID = '27'
source_filename = "27"

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
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %result = alloca i32, align 4
  store i32 5, ptr %a, align 4
  store i32 5, ptr %b, align 4
  store i32 1, ptr %c, align 4
  store i32 -2, ptr %d, align 4
  store i32 2, ptr %result, align 4
  %0 = load i32, ptr %d, align 4
  %1 = mul i32 %0, 1
  %2 = sdiv i32 %1, 2
  %3 = icmp slt i32 %2, 0
  %4 = zext i1 %3 to i32
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %or.merge, label %or.eval_right

if.then:                                          ; preds = %or.merge
  %6 = load i32, ptr %result, align 4
  call void @print_int(i32 %6)
  br label %if.end

if.end:                                           ; preds = %if.then, %or.merge
  %7 = load i32, ptr %d, align 4
  %8 = srem i32 %7, 2
  %9 = add i32 %8, 67
  %10 = icmp slt i32 %9, 0
  %11 = zext i1 %10 to i32
  %12 = icmp ne i32 %11, 0
  br i1 %12, label %or.merge4, label %or.eval_right3

or.eval_right:                                    ; preds = %entry
  %13 = load i32, ptr %a, align 4
  %14 = load i32, ptr %b, align 4
  %15 = sub i32 %13, %14
  %16 = icmp ne i32 %15, 0
  %17 = zext i1 %16 to i32
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %and.eval_right, label %and.merge

or.merge:                                         ; preds = %and.merge, %entry
  %19 = phi i1 [ true, %entry ], [ %30, %and.merge ]
  %20 = zext i1 %19 to i32
  %21 = icmp ne i32 %20, 0
  br i1 %21, label %if.then, label %if.end

and.eval_right:                                   ; preds = %or.eval_right
  %22 = load i32, ptr %c, align 4
  %23 = add i32 %22, 3
  %24 = srem i32 %23, 2
  %25 = icmp ne i32 %24, 0
  %26 = zext i1 %25 to i32
  %27 = icmp ne i32 %26, 0
  br label %and.merge

and.merge:                                        ; preds = %and.eval_right, %or.eval_right
  %28 = phi i1 [ false, %or.eval_right ], [ %27, %and.eval_right ]
  %29 = zext i1 %28 to i32
  %30 = icmp ne i32 %29, 0
  br label %or.merge

if.then1:                                         ; preds = %or.merge4
  store i32 4, ptr %result, align 4
  %31 = load i32, ptr %result, align 4
  call void @print_int(i32 %31)
  br label %if.end2

if.end2:                                          ; preds = %if.then1, %or.merge4
  call void @print_char(i8 10)
  %32 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  ret i32 0

or.eval_right3:                                   ; preds = %if.end
  %33 = load i32, ptr %a, align 4
  %34 = load i32, ptr %b, align 4
  %35 = sub i32 %33, %34
  %36 = icmp ne i32 %35, 0
  %37 = zext i1 %36 to i32
  %38 = icmp ne i32 %37, 0
  br i1 %38, label %and.eval_right5, label %and.merge6

or.merge4:                                        ; preds = %and.merge6, %if.end
  %39 = phi i1 [ true, %if.end ], [ %50, %and.merge6 ]
  %40 = zext i1 %39 to i32
  %41 = icmp ne i32 %40, 0
  br i1 %41, label %if.then1, label %if.end2

and.eval_right5:                                  ; preds = %or.eval_right3
  %42 = load i32, ptr %c, align 4
  %43 = add i32 %42, 2
  %44 = srem i32 %43, 2
  %45 = icmp ne i32 %44, 0
  %46 = zext i1 %45 to i32
  %47 = icmp ne i32 %46, 0
  br label %and.merge6

and.merge6:                                       ; preds = %and.eval_right5, %or.eval_right3
  %48 = phi i1 [ false, %or.eval_right3 ], [ %47, %and.eval_right5 ]
  %49 = zext i1 %48 to i32
  %50 = icmp ne i32 %49, 0
  br label %or.merge4

unreachable:                                      ; No predecessors!
  ret i32 0
}
