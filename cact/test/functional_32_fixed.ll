test/samples_generateIR/test_cases/functional/32.cact: Parsing and semantic analysis succeeded.
开始IR代码生成...
开始生成IR代码，模块名: 32
访问编译单元
访问全局常量声明: constfloatRADIUS=5.5,PI=3.141592653589793,EPS=1e-6;
全局常量类型: float
声明全局常量: RADIUS
访问常量初始化值: 5.5
访问常量表达式: 5.5
访问数字: 5.5
声明全局常量: PI
访问常量初始化值: 3.141592653589793
访问常量表达式: 3.141592653589793
访问数字: 3.141592653589793
声明全局常量: EPS
访问常量初始化值: 1e-6
访问常量表达式: 1e-6
访问数字: 1e-6
访问全局常量声明: constfloatPI_HEX=0x1.921fb6p+1,HEX2=0x.AP-3;
全局常量类型: float
声明全局常量: PI_HEX
访问常量初始化值: 0x1.921fb6p+1
访问常量表达式: 0x1.921fb6p+1
访问数字: 0x1.921fb6p+1
声明全局常量: HEX2
访问常量初始化值: 0x.AP-3
访问常量表达式: 0x.AP-3
访问数字: 0x.AP-3
访问全局常量声明: constfloatFACT=-33000.0;
全局常量类型: float
声明全局常量: FACT
访问常量初始化值: -33000.0
访问常量表达式: -33000.0
访问数字: 33000.0
访问全局常量声明: constfloatCONV1=233.0,CONV2=4095.0;
全局常量类型: float
声明全局常量: CONV1
访问常量初始化值: 233.0
访问常量表达式: 233.0
访问数字: 233.0
声明全局常量: CONV2
访问常量初始化值: 4095.0
访问常量表达式: 4095.0
访问数字: 4095.0
访问全局常量声明: constintMAX=1000000000,TWO=2,THREE=3;
全局常量类型: int
声明全局常量: MAX
访问常量初始化值: 1000000000
访问常量表达式: 1000000000
访问数字: 1000000000
声明全局常量: TWO
访问常量初始化值: 2
访问常量表达式: 2
访问数字: 2
声明全局常量: THREE
访问常量初始化值: 3
访问常量表达式: 3
访问数字: 3
访问函数定义: floatfloat_abs(floatx){if(x<0.0)return-x;returnx;}
函数名: float_abs, 返回类型: float
定义基本类型参数: x
访问语句: if(x<0.0)return-x;
处理if语句
访问条件: x<0.0
访问逻辑或表达式: x<0.0
访问逻辑与表达式: x<0.0
访问相等表达式: x<0.0
访问关系表达式: x<0.0
访问关系表达式: x
访问左值: x
访问数字: 0.0
左操作数类型: float
右操作数类型: float
是否为浮点比较: 是
使用浮点比较指令
访问语句: return-x;
处理return语句
访问表达式: -x
访问左值: x
访问语句: returnx;
处理return语句
访问表达式: x
访问左值: x
访问函数定义: intfloat_eq(floata,floatb){if(float_abs(a-b)<EPS){return1;}else{return0;}}
函数名: float_eq, 返回类型: int
定义基本类型参数: a
定义基本类型参数: b
访问语句: if(float_abs(a-b)<EPS){return1;}else{return0;}
处理if语句
访问条件: float_abs(a-b)<EPS
访问逻辑或表达式: float_abs(a-b)<EPS
访问逻辑与表达式: float_abs(a-b)<EPS
访问相等表达式: float_abs(a-b)<EPS
访问关系表达式: float_abs(a-b)<EPS
访问关系表达式: float_abs(a-b)
访问函数调用: float_abs
访问表达式: a-b
访问左值: a
访问左值: b
访问左值: EPS
左操作数类型: float
右操作数类型: float
是否为浮点比较: 是
使用浮点比较指令
访问语句: {return1;}
访问语句: return1;
处理return语句
访问表达式: 1
访问数字: 1
访问语句: {return0;}
访问语句: return0;
处理return语句
访问表达式: 0
访问数字: 0
访问函数定义: voiderror(){print_char('e');print_char('r');print_char('r');print_char('o');print_char('r');print_char('\n');}
函数名: error, 返回类型: void
访问语句: print_char('e');
处理表达式语句: print_char('e')
访问表达式: print_char('e')
访问函数调用: print_char
访问表达式: 'e'
访问数字: 'e'
访问语句: print_char('r');
处理表达式语句: print_char('r')
访问表达式: print_char('r')
访问函数调用: print_char
访问表达式: 'r'
访问数字: 'r'
访问语句: print_char('r');
处理表达式语句: print_char('r')
访问表达式: print_char('r')
访问函数调用: print_char
访问表达式: 'r'
访问数字: 'r'
访问语句: print_char('o');
处理表达式语句: print_char('o')
访问表达式: print_char('o')
访问函数调用: print_char
访问表达式: 'o'
访问数字: 'o'
访问语句: print_char('r');
处理表达式语句: print_char('r')
访问表达式: print_char('r')
访问函数调用: print_char
访问表达式: 'r'
访问数字: 'r'
访问语句: print_char('\n');
处理表达式语句: print_char('\n')
访问表达式: print_char('\n')
访问函数调用: print_char
访问表达式: '\n'
访问数字: '\n'
访问函数定义: voidok(){print_char('o');print_char('k');print_char('\n');}
函数名: ok, 返回类型: void
访问语句: print_char('o');
处理表达式语句: print_char('o')
访问表达式: print_char('o')
访问函数调用: print_char
访问表达式: 'o'
访问数字: 'o'
访问语句: print_char('k');
处理表达式语句: print_char('k')
访问表达式: print_char('k')
访问函数调用: print_char
访问表达式: 'k'
访问数字: 'k'
访问语句: print_char('\n');
处理表达式语句: print_char('\n')
访问表达式: print_char('\n')
访问函数调用: print_char
访问表达式: '\n'
访问数字: '\n'
访问函数定义: voidassert(intcond){if(cond==0){error();}else{ok();}}
函数名: assert, 返回类型: void
定义基本类型参数: cond
访问语句: if(cond==0){error();}else{ok();}
处理if语句
访问条件: cond==0
访问逻辑或表达式: cond==0
访问逻辑与表达式: cond==0
访问相等表达式: cond==0
访问相等表达式: cond
访问关系表达式: cond
访问左值: cond
访问关系表达式: 0
访问数字: 0
访问语句: {error();}
访问语句: error();
处理表达式语句: error()
访问表达式: error()
访问函数调用: error
访问语句: {ok();}
访问语句: ok();
处理表达式语句: ok()
访问表达式: ok()
访问函数调用: ok
访问函数定义: voidassert_not(intcond){if(cond){error();}else{ok();}}
函数名: assert_not, 返回类型: void
定义基本类型参数: cond
访问语句: if(cond){error();}else{ok();}
处理if语句
访问条件: cond
访问逻辑或表达式: cond
访问逻辑与表达式: cond
访问相等表达式: cond
访问关系表达式: cond
访问左值: cond
访问语句: {error();}
访问语句: error();
处理表达式语句: error()
访问表达式: error()
访问函数调用: error
访问语句: {ok();}
访问语句: ok();
处理表达式语句: ok()
访问表达式: ok()
访问函数调用: ok
访问函数定义: intmain(){floatEVAL1=0.0;EVAL1=PI*RADIUS*RADIUS;floatEVAL2=2.0;EVAL2=EVAL2*PI_HEX*RADIUS;floatEVAL3=2.0;EVAL3=PI*EVAL3*RADIUS;intFIVE=0;FIVE=TWO+THREE;assert_not(float_eq(HEX2,FACT));assert_not(float_eq(EVAL1,EVAL2));assert(float_eq(EVAL2,EVAL3));assert_not(float_eq(CONV1,CONV2));return0;}
函数名: main, 返回类型: int
访问变量声明: floatEVAL1=0.0;
变量类型: float
声明变量: EVAL1
访问常量初始化值: 0.0
访问常量表达式: 0.0
访问数字: 0.0
访问语句: EVAL1=PI*RADIUS*RADIUS;
处理赋值语句
访问表达式: PI*RADIUS*RADIUS
访问左值: PI
访问左值: RADIUS
访问左值: RADIUS
访问变量声明: floatEVAL2=2.0;
变量类型: float
声明变量: EVAL2
访问常量初始化值: 2.0
访问常量表达式: 2.0
访问数字: 2.0
访问语句: EVAL2=EVAL2*PI_HEX*RADIUS;
处理赋值语句
访问表达式: EVAL2*PI_HEX*RADIUS
访问左值: EVAL2
访问左值: PI_HEX
访问左值: RADIUS
访问变量声明: floatEVAL3=2.0;
变量类型: float
声明变量: EVAL3
访问常量初始化值: 2.0
访问常量表达式: 2.0
访问数字: 2.0
访问语句: EVAL3=PI*EVAL3*RADIUS;
处理赋值语句
访问表达式: PI*EVAL3*RADIUS
访问左值: PI
访问左值: EVAL3
访问左值: RADIUS
访问变量声明: intFIVE=0;
变量类型: int
声明变量: FIVE
访问常量初始化值: 0
访问常量表达式: 0
访问数字: 0
访问语句: FIVE=TWO+THREE;
处理赋值语句
访问表达式: TWO+THREE
访问左值: TWO
访问左值: THREE
访问语句: assert_not(float_eq(HEX2,FACT));
处理表达式语句: assert_not(float_eq(HEX2,FACT))
访问表达式: assert_not(float_eq(HEX2,FACT))
访问函数调用: assert_not
访问表达式: float_eq(HEX2,FACT)
访问函数调用: float_eq
访问表达式: HEX2
访问左值: HEX2
访问表达式: FACT
访问左值: FACT
访问语句: assert_not(float_eq(EVAL1,EVAL2));
处理表达式语句: assert_not(float_eq(EVAL1,EVAL2))
访问表达式: assert_not(float_eq(EVAL1,EVAL2))
访问函数调用: assert_not
访问表达式: float_eq(EVAL1,EVAL2)
访问函数调用: float_eq
访问表达式: EVAL1
访问左值: EVAL1
访问表达式: EVAL2
访问左值: EVAL2
访问语句: assert(float_eq(EVAL2,EVAL3));
处理表达式语句: assert(float_eq(EVAL2,EVAL3))
访问表达式: assert(float_eq(EVAL2,EVAL3))
访问函数调用: assert
访问表达式: float_eq(EVAL2,EVAL3)
访问函数调用: float_eq
访问表达式: EVAL2
访问左值: EVAL2
访问表达式: EVAL3
访问左值: EVAL3
访问语句: assert_not(float_eq(CONV1,CONV2));
处理表达式语句: assert_not(float_eq(CONV1,CONV2))
访问表达式: assert_not(float_eq(CONV1,CONV2))
访问函数调用: assert_not
访问表达式: float_eq(CONV1,CONV2)
访问函数调用: float_eq
访问表达式: CONV1
访问左值: CONV1
访问表达式: CONV2
访问左值: CONV2
访问语句: return0;
处理return语句
访问表达式: 0
访问数字: 0
test/samples_generateIR/test_cases/functional/32.cact: IR generation succeeded.
IR代码已保存到: 32.ll
生成的IR代码:
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

----------------------------------------

