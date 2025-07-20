; ModuleID = '28'
source_filename = "28"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@g = global i32 0, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define i32 @func(i32 %n) {
entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  %0 = load i32, ptr @g, align 4
  %1 = load i32, ptr %n1, align 4
  %2 = add i32 %0, %1
  store i32 %2, ptr @g, align 4
  %3 = load i32, ptr @g, align 4
  call void @print_int(i32 %3)
  %4 = load i32, ptr @g, align 4
  ret i32 %4

unreachable:                                      ; No predecessors!
  ret i32 0
}

define i32 @main() {
entry:
  %i = alloca i32, align 4
  %0 = call i32 @get_int()
  store i32 %0, ptr %i, align 4
  %1 = load i32, ptr %i, align 4
  %2 = icmp sgt i32 %1, 10
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %and.eval_right, label %and.merge

if.then:                                          ; preds = %and.merge
  store i32 1, ptr %i, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %5 = call i32 @get_int()
  store i32 %5, ptr %i, align 4
  %6 = load i32, ptr %i, align 4
  %7 = icmp sgt i32 %6, 11
  %8 = zext i1 %7 to i32
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %and.eval_right4, label %and.merge5

if.else:                                          ; preds = %and.merge
  store i32 0, ptr %i, align 4
  br label %if.end

and.eval_right:                                   ; preds = %entry
  %10 = load i32, ptr %i, align 4
  %11 = call i32 @func(i32 %10)
  %12 = icmp ne i32 %11, 0
  br label %and.merge

and.merge:                                        ; preds = %and.eval_right, %entry
  %13 = phi i1 [ false, %entry ], [ %12, %and.eval_right ]
  %14 = zext i1 %13 to i32
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %if.then, label %if.else

if.then1:                                         ; preds = %and.merge5
  store i32 1, ptr %i, align 4
  br label %if.end2

if.end2:                                          ; preds = %if.else3, %if.then1
  %16 = call i32 @get_int()
  store i32 %16, ptr %i, align 4
  %17 = load i32, ptr %i, align 4
  %18 = icmp sle i32 %17, 99
  %19 = zext i1 %18 to i32
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %or.merge, label %or.eval_right

if.else3:                                         ; preds = %and.merge5
  store i32 0, ptr %i, align 4
  br label %if.end2

and.eval_right4:                                  ; preds = %if.end
  %21 = load i32, ptr %i, align 4
  %22 = call i32 @func(i32 %21)
  %23 = icmp ne i32 %22, 0
  br label %and.merge5

and.merge5:                                       ; preds = %and.eval_right4, %if.end
  %24 = phi i1 [ false, %if.end ], [ %23, %and.eval_right4 ]
  %25 = zext i1 %24 to i32
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %if.then1, label %if.else3

if.then6:                                         ; preds = %or.merge
  store i32 1, ptr %i, align 4
  br label %if.end7

if.end7:                                          ; preds = %if.else8, %if.then6
  %27 = call i32 @get_int()
  store i32 %27, ptr %i, align 4
  %28 = load i32, ptr %i, align 4
  %29 = icmp sle i32 %28, 100
  %30 = zext i1 %29 to i32
  %31 = icmp ne i32 %30, 0
  br i1 %31, label %or.merge13, label %or.eval_right12

if.else8:                                         ; preds = %or.merge
  store i32 0, ptr %i, align 4
  br label %if.end7

or.eval_right:                                    ; preds = %if.end2
  %32 = load i32, ptr %i, align 4
  %33 = call i32 @func(i32 %32)
  %34 = icmp ne i32 %33, 0
  br label %or.merge

or.merge:                                         ; preds = %or.eval_right, %if.end2
  %35 = phi i1 [ true, %if.end2 ], [ %34, %or.eval_right ]
  %36 = zext i1 %35 to i32
  %37 = icmp ne i32 %36, 0
  br i1 %37, label %if.then6, label %if.else8

if.then9:                                         ; preds = %or.merge13
  store i32 1, ptr %i, align 4
  br label %if.end10

if.end10:                                         ; preds = %if.else11, %if.then9
  %38 = call i32 @func(i32 99)
  %39 = icmp eq i32 %38, 0
  %40 = zext i1 %39 to i32
  %41 = icmp ne i32 %40, 0
  br i1 %41, label %and.eval_right17, label %and.merge18

if.else11:                                        ; preds = %or.merge13
  store i32 0, ptr %i, align 4
  br label %if.end10

or.eval_right12:                                  ; preds = %if.end7
  %42 = load i32, ptr %i, align 4
  %43 = call i32 @func(i32 %42)
  %44 = icmp ne i32 %43, 0
  br label %or.merge13

or.merge13:                                       ; preds = %or.eval_right12, %if.end7
  %45 = phi i1 [ true, %if.end7 ], [ %44, %or.eval_right12 ]
  %46 = zext i1 %45 to i32
  %47 = icmp ne i32 %46, 0
  br i1 %47, label %if.then9, label %if.else11

if.then14:                                        ; preds = %and.merge18
  store i32 1, ptr %i, align 4
  br label %if.end15

if.end15:                                         ; preds = %if.else16, %if.then14
  call void @print_char(i8 10)
  %48 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  ret i32 0

if.else16:                                        ; preds = %and.merge18
  store i32 0, ptr %i, align 4
  br label %if.end15

and.eval_right17:                                 ; preds = %if.end10
  %49 = call i32 @func(i32 100)
  %50 = icmp ne i32 %49, 0
  br label %and.merge18

and.merge18:                                      ; preds = %and.eval_right17, %if.end10
  %51 = phi i1 [ false, %if.end10 ], [ %50, %and.eval_right17 ]
  %52 = zext i1 %51 to i32
  %53 = icmp ne i32 %52, 0
  br i1 %53, label %if.then14, label %if.else16

unreachable:                                      ; No predecessors!
  ret i32 0
}
