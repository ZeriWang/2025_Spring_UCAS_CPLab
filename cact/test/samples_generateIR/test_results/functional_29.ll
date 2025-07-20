; ModuleID = '29'
source_filename = "29"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@a = global i32 0, align 4
@b = global i32 0, align 4
@d = global i32 0, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_char(i8)

declare i32 @get_int()

declare float @get_float()

declare i8 @get_char()

define i32 @set_a(i32 %val) {
entry:
  %val1 = alloca i32, align 4
  store i32 %val, ptr %val1, align 4
  %0 = load i32, ptr %val1, align 4
  store i32 %0, ptr @a, align 4
  %1 = load i32, ptr @a, align 4
  ret i32 %1

unreachable:                                      ; No predecessors!
  ret i32 0
}

define i32 @set_b(i32 %val) {
entry:
  %val1 = alloca i32, align 4
  store i32 %val, ptr %val1, align 4
  %0 = load i32, ptr %val1, align 4
  store i32 %0, ptr @b, align 4
  %1 = load i32, ptr @b, align 4
  ret i32 %1

unreachable:                                      ; No predecessors!
  ret i32 0
}

define i32 @set_d(i32 %val) {
entry:
  %val1 = alloca i32, align 4
  store i32 %val, ptr %val1, align 4
  %0 = load i32, ptr %val1, align 4
  store i32 %0, ptr @d, align 4
  %1 = load i32, ptr @d, align 4
  ret i32 %1

unreachable:                                      ; No predecessors!
  ret i32 0
}

define i32 @main() {
entry:
  store i32 2, ptr @a, align 4
  store i32 3, ptr @b, align 4
  %0 = call i32 @set_a(i32 0)
  %1 = icmp ne i32 %0, 0
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %and.eval_right, label %and.merge

if.then:                                          ; preds = %and.merge
  br label %if.end

if.end:                                           ; preds = %if.then, %and.merge
  %4 = load i32, ptr @a, align 4
  call void @print_int(i32 %4)
  call void @print_char(i8 32)
  %5 = load i32, ptr @b, align 4
  call void @print_int(i32 %5)
  call void @print_char(i8 32)
  store i32 2, ptr @a, align 4
  store i32 3, ptr @b, align 4
  %6 = call i32 @set_a(i32 0)
  %7 = icmp ne i32 %6, 0
  %8 = zext i1 %7 to i32
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %and.eval_right3, label %and.merge4

and.eval_right:                                   ; preds = %entry
  %10 = call i32 @set_b(i32 1)
  %11 = icmp ne i32 %10, 0
  %12 = zext i1 %11 to i32
  %13 = icmp ne i32 %12, 0
  br label %and.merge

and.merge:                                        ; preds = %and.eval_right, %entry
  %14 = phi i1 [ false, %entry ], [ %13, %and.eval_right ]
  %15 = zext i1 %14 to i32
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %if.then, label %if.end

if.then1:                                         ; preds = %and.merge4
  br label %if.end2

if.end2:                                          ; preds = %if.then1, %and.merge4
  %17 = load i32, ptr @a, align 4
  call void @print_int(i32 %17)
  call void @print_char(i8 32)
  %18 = load i32, ptr @b, align 4
  call void @print_int(i32 %18)
  call void @print_char(i8 10)
  %c = alloca i32, align 4
  store i32 1, ptr %c, align 4
  store i32 2, ptr @d, align 4
  %19 = load i32, ptr %c, align 4
  %20 = icmp sge i32 %19, 1
  %21 = zext i1 %20 to i32
  %22 = icmp ne i32 %21, 0
  br i1 %22, label %and.eval_right7, label %and.merge8

and.eval_right3:                                  ; preds = %if.end
  %23 = call i32 @set_b(i32 1)
  %24 = icmp ne i32 %23, 0
  %25 = zext i1 %24 to i32
  %26 = icmp ne i32 %25, 0
  br label %and.merge4

and.merge4:                                       ; preds = %and.eval_right3, %if.end
  %27 = phi i1 [ false, %if.end ], [ %26, %and.eval_right3 ]
  %28 = zext i1 %27 to i32
  %29 = icmp ne i32 %28, 0
  br i1 %29, label %if.then1, label %if.end2

if.then5:                                         ; preds = %and.merge8
  br label %if.end6

if.end6:                                          ; preds = %if.then5, %and.merge8
  %30 = load i32, ptr @d, align 4
  call void @print_int(i32 %30)
  call void @print_char(i8 32)
  %31 = load i32, ptr %c, align 4
  %32 = icmp sle i32 %31, 1
  %33 = zext i1 %32 to i32
  %34 = icmp ne i32 %33, 0
  br i1 %34, label %or.merge, label %or.eval_right

and.eval_right7:                                  ; preds = %if.end2
  %35 = call i32 @set_d(i32 3)
  %36 = icmp ne i32 %35, 0
  %37 = zext i1 %36 to i32
  %38 = icmp ne i32 %37, 0
  br label %and.merge8

and.merge8:                                       ; preds = %and.eval_right7, %if.end2
  %39 = phi i1 [ false, %if.end2 ], [ %38, %and.eval_right7 ]
  %40 = zext i1 %39 to i32
  %41 = icmp ne i32 %40, 0
  br i1 %41, label %if.then5, label %if.end6

if.then9:                                         ; preds = %or.merge
  br label %if.end10

if.end10:                                         ; preds = %if.then9, %or.merge
  %42 = load i32, ptr @d, align 4
  call void @print_int(i32 %42)
  call void @print_char(i8 10)
  br i1 true, label %if.then11, label %if.end12

or.eval_right:                                    ; preds = %if.end6
  %43 = call i32 @set_d(i32 4)
  %44 = icmp ne i32 %43, 0
  %45 = zext i1 %44 to i32
  %46 = icmp ne i32 %45, 0
  br label %or.merge

or.merge:                                         ; preds = %or.eval_right, %if.end6
  %47 = phi i1 [ true, %if.end6 ], [ %46, %or.eval_right ]
  %48 = zext i1 %47 to i32
  %49 = icmp ne i32 %48, 0
  br i1 %49, label %if.then9, label %if.end10

if.then11:                                        ; preds = %if.end10
  call void @print_char(i8 65)
  br label %if.end12

if.end12:                                         ; preds = %if.then11, %if.end10
  br i1 false, label %if.then13, label %if.end14

if.then13:                                        ; preds = %if.end12
  call void @print_char(i8 66)
  br label %if.end14

if.end14:                                         ; preds = %if.then13, %if.end12
  br i1 false, label %if.then15, label %if.end16

if.then15:                                        ; preds = %if.end14
  call void @print_char(i8 67)
  br label %if.end16

if.end16:                                         ; preds = %if.then15, %if.end14
  br i1 true, label %if.then17, label %if.end18

if.then17:                                        ; preds = %if.end16
  call void @print_char(i8 68)
  br label %if.end18

if.end18:                                         ; preds = %if.then17, %if.end16
  br i1 true, label %if.then19, label %if.end20

if.then19:                                        ; preds = %if.end18
  call void @print_char(i8 69)
  br label %if.end20

if.end20:                                         ; preds = %if.then19, %if.end18
  call void @print_char(i8 10)
  %i0 = alloca i32, align 4
  store i32 0, ptr %i0, align 4
  %i1 = alloca i32, align 4
  store i32 1, ptr %i1, align 4
  %i2 = alloca i32, align 4
  store i32 2, ptr %i2, align 4
  %i3 = alloca i32, align 4
  store i32 3, ptr %i3, align 4
  %i4 = alloca i32, align 4
  store i32 4, ptr %i4, align 4
  %50 = load i32, ptr %i0, align 4
  %51 = load i32, ptr %i1, align 4
  %52 = icmp sge i32 %50, %51
  %53 = zext i1 %52 to i32
  %54 = icmp ne i32 %53, 0
  br i1 %54, label %or.merge24, label %or.eval_right23

if.then21:                                        ; preds = %or.merge24
  call void @print_char(i8 72)
  br label %if.end22

if.end22:                                         ; preds = %if.then21, %or.merge24
  %55 = load i32, ptr %i2, align 4
  %56 = load i32, ptr %i1, align 4
  %57 = icmp sge i32 %55, %56
  %58 = zext i1 %57 to i32
  %59 = icmp ne i32 %58, 0
  br i1 %59, label %and.eval_right27, label %and.merge28

or.eval_right23:                                  ; preds = %if.end20
  %60 = load i32, ptr %i1, align 4
  %61 = load i32, ptr %i0, align 4
  %62 = icmp sle i32 %60, %61
  %63 = zext i1 %62 to i32
  %64 = icmp ne i32 %63, 0
  br label %or.merge24

or.merge24:                                       ; preds = %or.eval_right23, %if.end20
  %65 = phi i1 [ true, %if.end20 ], [ %64, %or.eval_right23 ]
  %66 = zext i1 %65 to i32
  %67 = icmp ne i32 %66, 0
  br i1 %67, label %if.then21, label %if.end22

if.then25:                                        ; preds = %and.merge28
  call void @print_char(i8 73)
  br label %if.end26

if.end26:                                         ; preds = %if.then25, %and.merge28
  %68 = load i32, ptr %i0, align 4
  %69 = load i32, ptr %i1, align 4
  %70 = icmp eq i32 %69, 0
  %71 = zext i1 %70 to i32
  %72 = icmp eq i32 %68, %71
  %73 = zext i1 %72 to i32
  %74 = icmp ne i32 %73, 0
  br i1 %74, label %and.eval_right33, label %and.merge34

and.eval_right27:                                 ; preds = %if.end22
  %75 = load i32, ptr %i4, align 4
  %76 = load i32, ptr %i3, align 4
  %77 = icmp ne i32 %75, %76
  %78 = zext i1 %77 to i32
  %79 = icmp ne i32 %78, 0
  br label %and.merge28

and.merge28:                                      ; preds = %and.eval_right27, %if.end22
  %80 = phi i1 [ false, %if.end22 ], [ %79, %and.eval_right27 ]
  %81 = zext i1 %80 to i32
  %82 = icmp ne i32 %81, 0
  br i1 %82, label %if.then25, label %if.end26

if.then29:                                        ; preds = %or.merge32
  call void @print_char(i8 74)
  br label %if.end30

if.end30:                                         ; preds = %if.then29, %or.merge32
  %83 = load i32, ptr %i0, align 4
  %84 = load i32, ptr %i1, align 4
  %85 = icmp eq i32 %84, 0
  %86 = zext i1 %85 to i32
  %87 = icmp eq i32 %83, %86
  %88 = zext i1 %87 to i32
  %89 = icmp ne i32 %88, 0
  br i1 %89, label %or.merge38, label %or.eval_right37

or.eval_right31:                                  ; preds = %and.merge34
  %90 = load i32, ptr %i4, align 4
  %91 = load i32, ptr %i4, align 4
  %92 = icmp sge i32 %90, %91
  %93 = zext i1 %92 to i32
  %94 = icmp ne i32 %93, 0
  br label %or.merge32

or.merge32:                                       ; preds = %or.eval_right31, %and.merge34
  %95 = phi i1 [ true, %and.merge34 ], [ %94, %or.eval_right31 ]
  %96 = zext i1 %95 to i32
  %97 = icmp ne i32 %96, 0
  br i1 %97, label %if.then29, label %if.end30

and.eval_right33:                                 ; preds = %if.end26
  %98 = load i32, ptr %i3, align 4
  %99 = load i32, ptr %i3, align 4
  %100 = icmp slt i32 %98, %99
  %101 = zext i1 %100 to i32
  %102 = icmp ne i32 %101, 0
  br label %and.merge34

and.merge34:                                      ; preds = %and.eval_right33, %if.end26
  %103 = phi i1 [ false, %if.end26 ], [ %102, %and.eval_right33 ]
  %104 = zext i1 %103 to i32
  %105 = icmp ne i32 %104, 0
  br i1 %105, label %or.merge32, label %or.eval_right31

if.then35:                                        ; preds = %or.merge38
  call void @print_char(i8 75)
  br label %if.end36

if.end36:                                         ; preds = %if.then35, %or.merge38
  call void @print_char(i8 10)
  %106 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  ret i32 0

or.eval_right37:                                  ; preds = %if.end30
  %107 = load i32, ptr %i3, align 4
  %108 = load i32, ptr %i3, align 4
  %109 = icmp slt i32 %107, %108
  %110 = zext i1 %109 to i32
  %111 = icmp ne i32 %110, 0
  br i1 %111, label %and.eval_right39, label %and.merge40

or.merge38:                                       ; preds = %and.merge40, %if.end30
  %112 = phi i1 [ true, %if.end30 ], [ %122, %and.merge40 ]
  %113 = zext i1 %112 to i32
  %114 = icmp ne i32 %113, 0
  br i1 %114, label %if.then35, label %if.end36

and.eval_right39:                                 ; preds = %or.eval_right37
  %115 = load i32, ptr %i4, align 4
  %116 = load i32, ptr %i4, align 4
  %117 = icmp sge i32 %115, %116
  %118 = zext i1 %117 to i32
  %119 = icmp ne i32 %118, 0
  br label %and.merge40

and.merge40:                                      ; preds = %and.eval_right39, %or.eval_right37
  %120 = phi i1 [ false, %or.eval_right37 ], [ %119, %and.eval_right39 ]
  %121 = zext i1 %120 to i32
  %122 = icmp ne i32 %121, 0
  br label %or.merge38

unreachable:                                      ; No predecessors!
  ret i32 0
}
