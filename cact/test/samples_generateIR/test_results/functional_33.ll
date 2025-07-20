; ModuleID = '33'
source_filename = "33"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@a = global i32 -1, align 4
@b = global i32 1, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define i32 @inc_a() {
entry:
  %b = alloca i32, align 4
  store i32 0, ptr %b, align 4
  %0 = load i32, ptr @a, align 4
  store i32 %0, ptr %b, align 4
  %1 = load i32, ptr %b, align 4
  %2 = add i32 %1, 1
  store i32 %2, ptr %b, align 4
  %3 = load i32, ptr %b, align 4
  store i32 %3, ptr @a, align 4
  %4 = load i32, ptr @a, align 4
  ret i32 %4

unreachable:                                      ; No predecessors!
  ret i32 0
}

define i32 @main() {
entry:
  %k = alloca i32, align 4
  store i32 5, ptr %k, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end4, %entry
  %0 = load i32, ptr %k, align 4
  %1 = icmp sge i32 %0, 0
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %4 = call i32 @inc_a()
  %5 = icmp ne i32 %4, 0
  %6 = zext i1 %5 to i32
  %7 = icmp ne i32 %6, 0
  br i1 %7, label %and.eval_right1, label %and.merge2

while.exit:                                       ; preds = %while.cond
  %8 = load i32, ptr @a, align 4
  %9 = load i32, ptr @b, align 4
  %10 = add i32 %8, %9
  %11 = call i32 (ptr, ...) @printf(ptr @0, i32 %10)
  ret i32 %10

if.then:                                          ; preds = %and.merge
  %12 = load i32, ptr @a, align 4
  %13 = load i32, ptr @b, align 4
  %14 = add i32 %12, %13
  store i32 %14, ptr @a, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %and.merge
  %15 = call i32 @inc_a()
  %16 = icmp slt i32 %15, 14
  %17 = zext i1 %16 to i32
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %or.merge, label %or.eval_right

and.eval_right:                                   ; preds = %and.merge2
  %19 = call i32 @inc_a()
  %20 = icmp ne i32 %19, 0
  %21 = zext i1 %20 to i32
  %22 = icmp ne i32 %21, 0
  br label %and.merge

and.merge:                                        ; preds = %and.eval_right, %and.merge2
  %23 = phi i1 [ false, %and.merge2 ], [ %22, %and.eval_right ]
  %24 = zext i1 %23 to i32
  %25 = icmp ne i32 %24, 0
  br i1 %25, label %if.then, label %if.end

and.eval_right1:                                  ; preds = %while.body
  %26 = call i32 @inc_a()
  %27 = icmp ne i32 %26, 0
  %28 = zext i1 %27 to i32
  %29 = icmp ne i32 %28, 0
  br label %and.merge2

and.merge2:                                       ; preds = %and.eval_right1, %while.body
  %30 = phi i1 [ false, %while.body ], [ %29, %and.eval_right1 ]
  %31 = zext i1 %30 to i32
  %32 = icmp ne i32 %31, 0
  br i1 %32, label %and.eval_right, label %and.merge

if.then3:                                         ; preds = %or.merge
  %33 = load i32, ptr @b, align 4
  store i32 %33, ptr @a, align 4
  %34 = load i32, ptr @b, align 4
  %35 = mul i32 %34, 2
  store i32 %35, ptr @b, align 4
  br label %if.end4

if.end4:                                          ; preds = %if.else, %if.then3
  %36 = load i32, ptr %k, align 4
  %37 = sub i32 %36, 1
  store i32 %37, ptr %k, align 4
  br label %while.cond

if.else:                                          ; preds = %or.merge
  %38 = call i32 @inc_a()
  br label %if.end4

or.eval_right:                                    ; preds = %if.end
  %39 = call i32 @inc_a()
  %40 = icmp ne i32 %39, 0
  %41 = zext i1 %40 to i32
  %42 = icmp ne i32 %41, 0
  br i1 %42, label %and.eval_right5, label %and.merge6

or.merge:                                         ; preds = %and.merge6, %if.end
  %43 = phi i1 [ true, %if.end ], [ %55, %and.merge6 ]
  %44 = zext i1 %43 to i32
  %45 = icmp ne i32 %44, 0
  br i1 %45, label %if.then3, label %if.else

and.eval_right5:                                  ; preds = %or.eval_right
  %46 = call i32 @inc_a()
  %47 = call i32 @inc_a()
  %48 = sub i32 %46, %47
  %49 = add i32 %48, 1
  %50 = icmp ne i32 %49, 0
  %51 = zext i1 %50 to i32
  %52 = icmp ne i32 %51, 0
  br label %and.merge6

and.merge6:                                       ; preds = %and.eval_right5, %or.eval_right
  %53 = phi i1 [ false, %or.eval_right ], [ %52, %and.eval_right5 ]
  %54 = zext i1 %53 to i32
  %55 = icmp ne i32 %54, 0
  br label %or.merge

unreachable:                                      ; No predecessors!
  ret i32 0
}
