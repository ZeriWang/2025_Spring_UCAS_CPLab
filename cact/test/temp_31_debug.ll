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

@k = local_unnamed_addr global i32 0, align 4
@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...) local_unnamed_addr

declare void @print_int(i32) local_unnamed_addr

declare void @print_char(i8) local_unnamed_addr

define i32 @main() local_unnamed_addr {
entry:
  store i32 3390, ptr @k, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %0 = phi i32 [ %spec.select, %while.body ], [ 112, %entry ]
  %1 = icmp sgt i32 %0, 10
  br i1 %1, label %while.body, label %while.exit

while.body:                                       ; preds = %while.cond
  %2 = add nsw i32 %0, -88
  %3 = icmp slt i32 %0, 1088
  %4 = add nsw i32 %0, -77
  %spec.select = select i1 %3, i32 %4, i32 %2
  br label %while.cond

while.exit:                                       ; preds = %while.cond
  call void @print_int(i32 %0)
  call void @print_char(i8 10)
  %5 = load i32, ptr @k, align 4
  %6 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @0, i32 %5)
  ret i32 %5
}

----------------------------------------

