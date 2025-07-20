; ModuleID = '32'
source_filename = "32"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@RADIUS = constant float 5.500000e+00, align 4
@PI = constant float 0x400921FB60000000, align 4
@EPS = constant float 0x3EB0C6F7A0000000, align 4
@PI_HEX = constant float 0x400921FB60000000, align 4
@HEX2 = constant float 7.812500e-02, align 4
@FACT = constant float 0, align 4
@CONV1 = constant float 2.330000e+02, align 4
@CONV2 = constant float 4.095000e+03, align 4
@MAX = constant i32 1000000000, align 4
@TWO = constant i32 2, align 4
@THREE = constant i32 3, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define float @float_abs(float %x) {
entry:
  %x1 = alloca float, align 4
  store float %x, ptr %x1, align 4
  %0 = load float, ptr %x1, align 4
  %1 = fcmp olt float %0, 0.000000e+00
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %4 = load float, ptr %x1, align 4
  %5 = fneg float %4
  ret float %5

if.end:                                           ; preds = %unreachable, %entry
  %6 = load float, ptr %x1, align 4
  ret float %6

unreachable:                                      ; No predecessors!
  br label %if.end

unreachable2:                                     ; No predecessors!
  ret i0 0
}

define i32 @float_eq(float %a, float %b) {
entry:
  %a1 = alloca float, align 4
  store float %a, ptr %a1, align 4
  %b2 = alloca float, align 4
  store float %b, ptr %b2, align 4
  %0 = load float, ptr %a1, align 4
  %1 = load float, ptr %b2, align 4
  %2 = sub float %0, %1
  %3 = call float @float_abs(float %2)
  %4 = load float, ptr @EPS, align 4
  %5 = fcmp olt float %3, %4
  %6 = zext i1 %5 to i32
  %7 = icmp ne i32 %6, 0
  br i1 %7, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  ret i32 1

if.end:                                           ; preds = %unreachable3, %unreachable
  ret i32 0

if.else:                                          ; preds = %entry
  ret i32 0

unreachable:                                      ; No predecessors!
  br label %if.end

unreachable3:                                     ; No predecessors!
  br label %if.end
}

define void @error() {
entry:
  call void @print_char(i8 101)
  call void @print_char(i8 114)
  call void @print_char(i8 114)
  call void @print_char(i8 111)
  call void @print_char(i8 114)
  call void @print_char(i8 10)
  ret void
}

define void @ok() {
entry:
  call void @print_char(i8 111)
  call void @print_char(i8 107)
  call void @print_char(i8 10)
  ret void
}

define void @assert(i32 %cond) {
entry:
  %cond1 = alloca i32, align 4
  store i32 %cond, ptr %cond1, align 4
  %0 = load i32, ptr %cond1, align 4
  %1 = icmp eq i32 %0, 0
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @error()
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void

if.else:                                          ; preds = %entry
  call void @ok()
  br label %if.end
}

define void @assert_not(i32 %cond) {
entry:
  %cond1 = alloca i32, align 4
  store i32 %cond, ptr %cond1, align 4
  %0 = load i32, ptr %cond1, align 4
  %1 = icmp ne i32 %0, 0
  br i1 %1, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @error()
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void

if.else:                                          ; preds = %entry
  call void @ok()
  br label %if.end
}

define i32 @main() {
entry:
  %EVAL1 = alloca float, align 4
  store float 0.000000e+00, ptr %EVAL1, align 4
  %0 = load float, ptr @PI, align 4
  %1 = load float, ptr @RADIUS, align 4
  %2 = mul float %0, %1
  %3 = load float, ptr @RADIUS, align 4
  %4 = mul float %2, %3
  store float %4, ptr %EVAL1, align 4
  %EVAL2 = alloca float, align 4
  store float 2.000000e+00, ptr %EVAL2, align 4
  %5 = load float, ptr %EVAL2, align 4
  %6 = load float, ptr @PI_HEX, align 4
  %7 = mul float %5, %6
  %8 = load float, ptr @RADIUS, align 4
  %9 = mul float %7, %8
  store float %9, ptr %EVAL2, align 4
  %EVAL3 = alloca float, align 4
  store float 2.000000e+00, ptr %EVAL3, align 4
  %10 = load float, ptr @PI, align 4
  %11 = load float, ptr %EVAL3, align 4
  %12 = mul float %10, %11
  %13 = load float, ptr @RADIUS, align 4
  %14 = mul float %12, %13
  store float %14, ptr %EVAL3, align 4
  %FIVE = alloca i32, align 4
  store i32 0, ptr %FIVE, align 4
  %15 = load i32, ptr @TWO, align 4
  %16 = load i32, ptr @THREE, align 4
  %17 = add i32 %15, %16
  store i32 %17, ptr %FIVE, align 4
  %18 = load float, ptr @HEX2, align 4
  %19 = load float, ptr @FACT, align 4
  %20 = call i32 @float_eq(float %18, float %19)
  call void @assert_not(i32 %20)
  %21 = load float, ptr %EVAL1, align 4
  %22 = load float, ptr %EVAL2, align 4
  %23 = call i32 @float_eq(float %21, float %22)
  call void @assert_not(i32 %23)
  %24 = load float, ptr %EVAL2, align 4
  %25 = load float, ptr %EVAL3, align 4
  %26 = call i32 @float_eq(float %24, float %25)
  call void @assert(i32 %26)
  %27 = load float, ptr @CONV1, align 4
  %28 = load float, ptr @CONV2, align 4
  %29 = call i32 @float_eq(float %27, float %28)
  call void @assert_not(i32 %29)
  %30 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  ret i32 0

unreachable:                                      ; No predecessors!
  ret i32 0
}
