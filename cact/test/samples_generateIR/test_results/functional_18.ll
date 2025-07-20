; ModuleID = '18'
source_filename = "18"

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

define i32 @ifElseIf() {
entry:
  %a = alloca i32, align 4
  store i32 5, ptr %a, align 4
  %b = alloca i32, align 4
  store i32 10, ptr %b, align 4
  %0 = load i32, ptr %a, align 4
  %1 = icmp eq i32 %0, 6
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %or.merge, label %or.eval_right

if.then:                                          ; preds = %or.merge
  %4 = load i32, ptr %a, align 4
  ret i32 %4

if.end:                                           ; preds = %if.end2, %unreachable
  %5 = load i32, ptr %a, align 4
  ret i32 %5

if.else:                                          ; preds = %or.merge
  %6 = load i32, ptr %b, align 4
  %7 = icmp eq i32 %6, 10
  %8 = zext i1 %7 to i32
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %and.eval_right, label %and.merge

or.eval_right:                                    ; preds = %entry
  %10 = load i32, ptr %b, align 4
  %11 = icmp eq i32 %10, 11
  %12 = zext i1 %11 to i32
  %13 = icmp ne i32 %12, 0
  br label %or.merge

or.merge:                                         ; preds = %or.eval_right, %entry
  %14 = phi i1 [ true, %entry ], [ %13, %or.eval_right ]
  %15 = zext i1 %14 to i32
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %if.then, label %if.else

unreachable:                                      ; No predecessors!
  br label %if.end

if.then1:                                         ; preds = %and.merge
  store i32 25, ptr %a, align 4
  br label %if.end2

if.end2:                                          ; preds = %if.end5, %if.then1
  br label %if.end

if.else3:                                         ; preds = %and.merge
  %17 = load i32, ptr %b, align 4
  %18 = icmp eq i32 %17, 10
  %19 = zext i1 %18 to i32
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %and.eval_right7, label %and.merge8

and.eval_right:                                   ; preds = %if.else
  %21 = load i32, ptr %a, align 4
  %22 = icmp eq i32 %21, 1
  %23 = zext i1 %22 to i32
  %24 = icmp ne i32 %23, 0
  br label %and.merge

and.merge:                                        ; preds = %and.eval_right, %if.else
  %25 = phi i1 [ false, %if.else ], [ %24, %and.eval_right ]
  %26 = zext i1 %25 to i32
  %27 = icmp ne i32 %26, 0
  br i1 %27, label %if.then1, label %if.else3

if.then4:                                         ; preds = %and.merge8
  %28 = load i32, ptr %a, align 4
  %29 = add i32 %28, 15
  store i32 %29, ptr %a, align 4
  br label %if.end5

if.end5:                                          ; preds = %if.else6, %if.then4
  br label %if.end2

if.else6:                                         ; preds = %and.merge8
  %30 = load i32, ptr %a, align 4
  %31 = sub i32 0, %30
  store i32 %31, ptr %a, align 4
  br label %if.end5

and.eval_right7:                                  ; preds = %if.else3
  %32 = load i32, ptr %a, align 4
  %33 = icmp eq i32 %32, -5
  %34 = zext i1 %33 to i32
  %35 = icmp ne i32 %34, 0
  br label %and.merge8

and.merge8:                                       ; preds = %and.eval_right7, %if.else3
  %36 = phi i1 [ false, %if.else3 ], [ %35, %and.eval_right7 ]
  %37 = zext i1 %36 to i32
  %38 = icmp ne i32 %37, 0
  br i1 %38, label %if.then4, label %if.else6

unreachable9:                                     ; No predecessors!
  ret i32 0
}

define i32 @main() {
entry:
  %0 = call i32 @ifElseIf()
  call void @print_int(i32 %0)
  call void @print_char(i8 10)
  %1 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  ret i32 0

unreachable:                                      ; No predecessors!
  ret i32 0
}
