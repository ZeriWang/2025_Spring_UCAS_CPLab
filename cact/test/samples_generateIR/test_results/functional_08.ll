; ModuleID = '08'
source_filename = "08"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@a = global i32 0, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define i32 @func(i32 %p) {
entry:
  %p1 = alloca i32, align 4
  store i32 %p, ptr %p1, align 4
  %0 = load i32, ptr %p1, align 4
  %1 = sub i32 %0, 1
  store i32 %1, ptr %p1, align 4
  %2 = load i32, ptr %p1, align 4
  ret i32 %2

unreachable:                                      ; No predecessors!
  ret i32 0
}

define i32 @main() {
entry:
  %b = alloca i32, align 4
  store i32 10, ptr @a, align 4
  %0 = load i32, ptr @a, align 4
  %1 = call i32 @func(i32 %0)
  store i32 %1, ptr %b, align 4
  %2 = load i32, ptr %b, align 4
  %3 = call i32 (ptr, ...) @printf(ptr @0, i32 %2)
  ret i32 %2

unreachable:                                      ; No predecessors!
  ret i32 0
}
