# 2025_Spring_UCAS_CPLab

## 编译器构建方法

1. 使用 `ANTLR` 生成词法分析器和语法分析器

```bash
cd cact/grammar
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp \
    CACT.g4 -visitor -listener
```

2. 使用 `CMake` 构建项目

```bash
cd ..
mkdir build && cd build
cmake ..
make -j4 # -j4表示使用4个线程进行编译
```

等待编译完成。

3. 运行功能测试

```bash
cd ..
./test_functional.sh
```

功能测试脚本会：

- 编译所有 `test/samples_generateIR/functional/` 目录下的 `.cact` 测试文件
- 生成RISC-V汇编代码
- 使用RISC-V交叉编译器链接运行时库
- 使用Spike模拟器运行测试并验证输出

## 依赖工具

### 必需工具

- Java 8+ (用于运行ANTLR)
- CMake 3.10+
- C++编译器 (支持C++17)
- RISC-V交叉编译器: `riscv64-unknown-elf-gcc`
- Spike RISC-V模拟器: `spike`

如果缺少RISC-V工具链，测试脚本会自动降级为仅编译测试。

## 测试说明

- `./test_functional.sh` - 运行所有功能测试
- 测试结果会显示为 PASS/FAIL/COMPILE_FAIL 等状态
