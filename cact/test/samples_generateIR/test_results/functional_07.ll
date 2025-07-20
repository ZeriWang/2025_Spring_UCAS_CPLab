; ModuleID = '07'
source_filename = "07"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@a = constant [5 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4], align 4
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
  %0 = load i32, ptr getelementptr ([5 x i32], ptr @a, i32 0, i32 4), align 4
  %1 = call i32 (ptr, ...) @printf(ptr @0, i32 %0)
  ret i32 %0

unreachable:                                      ; No predecessors!
  ret i32 0
}
