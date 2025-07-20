; ModuleID = '03'
source_filename = "03"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@3 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

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
  store i32 8, ptr %b, align 4
  %c = alloca i32, align 4
  store i32 12, ptr %c, align 4
  %0 = load i32, ptr %b, align 4
  %1 = load i32, ptr %c, align 4
  %2 = add i32 %0, %1
  store i32 %2, ptr %a, align 4
  %3 = load i32, ptr %a, align 4
  %4 = call i32 (ptr, ...) @printf(ptr @0, i32 %3)
  ret i32 %3

unreachable:                                      ; No predecessors!
  %d = alloca i32, align 4
  store i32 9, ptr %d, align 4
  %5 = load i32, ptr %a, align 4
  %6 = load i32, ptr %d, align 4
  %7 = mul i32 %5, %6
  store i32 %7, ptr %a, align 4
  %8 = load i32, ptr %a, align 4
  %9 = call i32 (ptr, ...) @printf(ptr @1, i32 %8)
  ret i32 %8

unreachable1:                                     ; No predecessors!
  %A = alloca i32, align 4
  store i32 4, ptr %A, align 4
  %10 = load i32, ptr %A, align 4
  %11 = load i32, ptr %b, align 4
  %12 = sub i32 %10, %11
  %13 = load i32, ptr %c, align 4
  %14 = mul i32 %12, %13
  store i32 %14, ptr %a, align 4
  %15 = load i32, ptr %a, align 4
  %16 = call i32 (ptr, ...) @printf(ptr @2, i32 %15)
  ret i32 %15

unreachable2:                                     ; No predecessors!
  %17 = load i32, ptr %a, align 4
  %18 = call i32 (ptr, ...) @printf(ptr @3, i32 %17)
  ret i32 %17

unreachable3:                                     ; No predecessors!
  ret i32 0
}
