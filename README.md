# 2025_Spring_UCAS_CPLab

---

## 编译器构建方法

1. 使用 `ANTLR` 生成词法分析器和语法分析器

```bash
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp
    \ CactLexer.g4 CactParser.g4 -visitor -no-listener # 在grammar目录下执行
```

2. 使用 `CMake` 构建项目

```bash
mkdir build && cd build # 在cact目录下执行
cmake ..
make
```
等待编译完成即可。