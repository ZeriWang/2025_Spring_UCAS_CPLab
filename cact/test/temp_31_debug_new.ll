test/samples_generateIR/test_cases/functional/31.cact: Parsing and semantic analysis succeeded.
开始IR代码生成...
开始生成IR代码，模块名: 31
访问编译单元
访问全局变量声明: intk;
全局变量类型: int
声明全局变量: k
访问函数定义: intmain(){k=3389;if(k<10000){k=k+1;intk=112;while(k>10){k=k-88;if(k<1000){intg=9;{intl=11;{g=10;k=k-g;intg=11;k=k+g+l;}}}}print_int(k);}print_char('\n');returnk;}
函数名: main, 返回类型: int
访问语句: k=3389;
处理赋值语句
访问表达式: 3389
访问数字: 3389
访问语句: if(k<10000){k=k+1;intk=112;while(k>10){k=k-88;if(k<1000){intg=9;{intl=11;{g=10;k=k-g;intg=11;k=k+g+l;}}}}print_int(k);}
处理if语句
访问条件: k<10000
访问逻辑或表达式: k<10000
访问逻辑与表达式: k<10000
访问相等表达式: k<10000
访问关系表达式: k<10000
访问关系表达式: k
访问左值: k
访问数字: 10000
访问语句: {k=k+1;intk=112;while(k>10){k=k-88;if(k<1000){intg=9;{intl=11;{g=10;k=k-g;intg=11;k=k+g+l;}}}}print_int(k);}
访问语句: k=k+1;
处理赋值语句
访问表达式: k+1
访问左值: k
访问数字: 1
访问变量声明: intk=112;
变量类型: int
声明变量: k
访问常量初始化值: 112
访问常量表达式: 112
访问数字: 112
访问语句: while(k>10){k=k-88;if(k<1000){intg=9;{intl=11;{g=10;k=k-g;intg=11;k=k+g+l;}}}}
处理while语句
访问条件: k>10
访问逻辑或表达式: k>10
访问逻辑与表达式: k>10
访问相等表达式: k>10
访问关系表达式: k>10
访问关系表达式: k
访问左值: k
访问数字: 10
访问语句: {k=k-88;if(k<1000){intg=9;{intl=11;{g=10;k=k-g;intg=11;k=k+g+l;}}}}
访问语句: k=k-88;
处理赋值语句
访问表达式: k-88
访问左值: k
访问数字: 88
访问语句: if(k<1000){intg=9;{intl=11;{g=10;k=k-g;intg=11;k=k+g+l;}}}
处理if语句
访问条件: k<1000
访问逻辑或表达式: k<1000
访问逻辑与表达式: k<1000
访问相等表达式: k<1000
访问关系表达式: k<1000
访问关系表达式: k
访问左值: k
访问数字: 1000
访问语句: {intg=9;{intl=11;{g=10;k=k-g;intg=11;k=k+g+l;}}}
访问变量声明: intg=9;
变量类型: int
声明变量: g
访问常量初始化值: 9
访问常量表达式: 9
访问数字: 9
访问语句: {intl=11;{g=10;k=k-g;intg=11;k=k+g+l;}}
访问变量声明: intl=11;
变量类型: int
声明变量: l
访问常量初始化值: 11
访问常量表达式: 11
访问数字: 11
访问语句: {g=10;k=k-g;intg=11;k=k+g+l;}
访问语句: g=10;
处理赋值语句
访问表达式: 10
访问数字: 10
访问语句: k=k-g;
处理赋值语句
访问表达式: k-g
访问左值: k
访问左值: g
访问变量声明: intg=11;
变量类型: int
声明变量: g
访问常量初始化值: 11
访问常量表达式: 11
访问数字: 11
访问语句: k=k+g+l;
处理赋值语句
访问表达式: k+g+l
访问左值: k
访问左值: g
访问左值: l
访问语句: print_int(k);
处理表达式语句: print_int(k)
访问表达式: print_int(k)
访问函数调用: print_int
访问表达式: k
访问左值: k
访问语句: print_char('\n');
处理表达式语句: print_char('\n')
访问表达式: print_char('\n')
访问函数调用: print_char
访问表达式: '\n'
访问数字: '\n'
访问语句: returnk;
处理return语句
访问表达式: k
访问左值: k
开始LLVM IR优化...
优化函数: main
运行模块级优化...
LLVM IR优化完成
test/samples_generateIR/test_cases/functional/31.cact: IR generation succeeded.
IR代码已保存到: 31.ll
生成的IR代码:
; ModuleID = '31'
source_filename = "31"

@.str.int = private constant [4 x i8] c"%d\0A\00", align 1
@.str.float = private constant [4 x i8] c"%f\0A\00", align 1
@.str.char = private constant [4 x i8] c"%c\0A\00", align 1
@k = global i32 0, align 4
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
  store i32 3389, ptr @k, align 4
  %0 = load i32, ptr @k, align 4
  %1 = icmp slt i32 %0, 10000
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %4 = load i32, ptr @k, align 4
  %5 = add i32 %4, 1
  store i32 %5, ptr @k, align 4
  %k = alloca i32, align 4
  store i32 112, ptr %k, align 4
  br label %while.cond

if.end:                                           ; preds = %while.exit, %entry
  call void @print_char(i8 10)
  %6 = load i32, ptr @k, align 4
  %7 = call i32 (ptr, ...) @printf(ptr @0, i32 %6)
  ret i32 %6

while.cond:                                       ; preds = %if.end2, %if.then
  %8 = load i32, ptr %k, align 4
  %9 = icmp sgt i32 %8, 10
  %10 = zext i1 %9 to i32
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %12 = load i32, ptr %k, align 4
  %13 = sub i32 %12, 88
  store i32 %13, ptr %k, align 4
  %14 = load i32, ptr %k, align 4
  %15 = icmp slt i32 %14, 1000
  %16 = zext i1 %15 to i32
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %if.then1, label %if.end2

while.exit:                                       ; preds = %while.cond
  %18 = load i32, ptr %k, align 4
  call void @print_int(i32 %18)
  br label %if.end

if.then1:                                         ; preds = %while.body
  %g = alloca i32, align 4
  store i32 9, ptr %g, align 4
  %l = alloca i32, align 4
  store i32 11, ptr %l, align 4
  store i32 10, ptr %g, align 4
  %19 = load i32, ptr %k, align 4
  %20 = load i32, ptr %g, align 4
  %21 = sub i32 %19, %20
  store i32 %21, ptr %k, align 4
  %g3 = alloca i32, align 4
  store i32 11, ptr %g3, align 4
  %22 = load i32, ptr %k, align 4
  %23 = load i32, ptr %g, align 4
  %24 = add i32 %22, %23
  %25 = load i32, ptr %l, align 4
  %26 = add i32 %24, %25
  store i32 %26, ptr %k, align 4
  br label %if.end2

if.end2:                                          ; preds = %if.then1, %while.body
  br label %while.cond
}

----------------------------------------

