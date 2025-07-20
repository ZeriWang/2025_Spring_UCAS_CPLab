; ModuleID = '23'
source_filename = "23"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@a = global i32 1, align 4
@b = global i32 0, align 4
@c = global i32 1, align 4
@d = global i32 2, align 4
@e = global i32 4, align 4
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
  %flag = alloca i32, align 4
  store i32 0, ptr %flag, align 4
  %0 = load i32, ptr @a, align 4
  %1 = load i32, ptr @b, align 4
  %2 = mul i32 %0, %1
  %3 = load i32, ptr @c, align 4
  %4 = sdiv i32 %2, %3
  %5 = load i32, ptr @e, align 4
  %6 = load i32, ptr @d, align 4
  %7 = add i32 %5, %6
  %8 = icmp eq i32 %4, %7
  %9 = zext i1 %8 to i32
  %10 = icmp ne i32 %9, 0
  br i1 %10, label %and.eval_right, label %and.merge

if.then:                                          ; preds = %or.merge
  store i32 1, ptr %flag, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %or.merge
  %11 = load i32, ptr %flag, align 4
  call void @print_int(i32 %11)
  call void @print_char(i8 10)
  %12 = load i32, ptr %flag, align 4
  %13 = call i32 (ptr, ...) @printf(ptr @0, i32 %12)
  ret i32 %12

or.eval_right:                                    ; preds = %and.merge
  %14 = load i32, ptr @a, align 4
  %15 = load i32, ptr @b, align 4
  %16 = load i32, ptr @c, align 4
  %17 = mul i32 %15, %16
  %18 = sub i32 %14, %17
  %19 = load i32, ptr @d, align 4
  %20 = load i32, ptr @a, align 4
  %21 = load i32, ptr @c, align 4
  %22 = sdiv i32 %20, %21
  %23 = sub i32 %19, %22
  %24 = icmp eq i32 %18, %23
  %25 = zext i1 %24 to i32
  %26 = icmp ne i32 %25, 0
  br label %or.merge

or.merge:                                         ; preds = %or.eval_right, %and.merge
  %27 = phi i1 [ true, %and.merge ], [ %26, %or.eval_right ]
  %28 = zext i1 %27 to i32
  %29 = icmp ne i32 %28, 0
  br i1 %29, label %if.then, label %if.end

and.eval_right:                                   ; preds = %entry
  %30 = load i32, ptr @a, align 4
  %31 = load i32, ptr @a, align 4
  %32 = load i32, ptr @b, align 4
  %33 = add i32 %31, %32
  %34 = mul i32 %30, %33
  %35 = load i32, ptr @c, align 4
  %36 = add i32 %34, %35
  %37 = load i32, ptr @d, align 4
  %38 = load i32, ptr @e, align 4
  %39 = add i32 %37, %38
  %40 = icmp sle i32 %36, %39
  %41 = zext i1 %40 to i32
  %42 = icmp ne i32 %41, 0
  br label %and.merge

and.merge:                                        ; preds = %and.eval_right, %entry
  %43 = phi i1 [ false, %entry ], [ %42, %and.eval_right ]
  %44 = zext i1 %43 to i32
  %45 = icmp ne i32 %44, 0
  br i1 %45, label %or.merge, label %or.eval_right

unreachable:                                      ; No predecessors!
  ret i32 0
}
