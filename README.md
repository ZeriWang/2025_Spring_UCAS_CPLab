# 2025_Spring_UCAS_CPLab

## 编译器构建方法

1. 使用 `ANTLR` 生成词法分析器和语法分析器

```bash
cd cact/grammar
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp \
    CactLexer.g4 CactParser.g4 -visitor -no-listener
```

2. 使用 `CMake` 构建项目

```bash
cd ..
mkdir build && cd build
cmake ..
make -j4 # -j4表示使用4个线程进行编译
```

等待编译完成。

3. 构建运行时库

```bash
cd ../test/samples_generateIR/runtime_lib
clang -emit-llvm -S runtime.c -o runtime.ll
```

4. 运行测试

```bash
cd ../../..
./test_ir.sh
```

测试脚本会自动链接运行时库，并执行所有测试用例。
