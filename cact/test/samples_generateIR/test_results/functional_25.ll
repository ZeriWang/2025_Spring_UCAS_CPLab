; ModuleID = '25'
source_filename = "25"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@a = global i32 0, align 4
@b = global i32 0, align 4
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
  %0 = call i32 @get_int()
  store i32 %0, ptr @a, align 4
  %1 = call i32 @get_int()
  store i32 %1, ptr @b, align 4
  %c = alloca i32, align 4
  %2 = load i32, ptr @a, align 4
  %3 = load i32, ptr @b, align 4
  %4 = icmp eq i32 %2, %3
  %5 = zext i1 %4 to i32
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %and.eval_right, label %and.merge

if.then:                                          ; preds = %and.merge
  store i32 1, ptr %c, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %7 = load i32, ptr %c, align 4
  %8 = call i32 (ptr, ...) @printf(ptr @0, i32 %7)
  ret i32 %7

if.else:                                          ; preds = %and.merge
  store i32 0, ptr %c, align 4
  br label %if.end

and.eval_right:                                   ; preds = %entry
  %9 = load i32, ptr @a, align 4
  %10 = icmp ne i32 %9, 3
  %11 = zext i1 %10 to i32
  %12 = icmp ne i32 %11, 0
  br label %and.merge

and.merge:                                        ; preds = %and.eval_right, %entry
  %13 = phi i1 [ false, %entry ], [ %12, %and.eval_right ]
  %14 = zext i1 %13 to i32
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %if.then, label %if.else

unreachable:                                      ; No predecessors!
  ret i32 0
}
