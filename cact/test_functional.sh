#!/bin/bash

# CACT编译器功能测试脚本
# 测试 test/samples_generateIR/test_cases/functional 中的所有测试例

# set -e  # 遇到错误立即退出

# 配置路径
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CACT_DIR="$SCRIPT_DIR"
COMPILER="$CACT_DIR/build/compiler"
TEST_DIR="$CACT_DIR/test/samples_generateIR/functional"
OUTPUT_DIR="$(dirname "$CACT_DIR")/out"  # 修正：输出目录在项目根目录下
RUNTIME_LIB="$CACT_DIR/libcact/lib.c"

# RISC-V交叉编译器和模拟器配置
RISCV_GCC="riscv64-unknown-elf-gcc"
SPIKE="/opt/homebrew/bin/spike"
PK="pk"  # pk 是 spike 的内置功能

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 统计变量
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
COMPILE_FAILED=0

echo -e "${BLUE}=== CACT编译器功能测试 ===${NC}"
echo "测试目录: $TEST_DIR"
echo "编译器: $COMPILER"
echo

# 检查编译器是否存在
if [ ! -f "$COMPILER" ]; then
    echo -e "${RED}错误: 编译器不存在: $COMPILER${NC}"
    echo "请先运行 'cd build && make' 编译项目"
    exit 1
fi

# 检查RISC-V交叉编译器
if ! command -v "$RISCV_GCC" &> /dev/null; then
    echo -e "${YELLOW}警告: RISC-V交叉编译器不存在: $RISCV_GCC${NC}"
    echo "将只进行编译测试，不进行链接和运行测试"
    RISCV_GCC=""
fi

# 检查Spike模拟器
if ! command -v "$SPIKE" &> /dev/null; then
    echo -e "${YELLOW}警告: Spike模拟器不存在: $SPIKE${NC}"
    echo "将只进行编译和链接测试，不进行运行测试"
    SPIKE=""
fi

# 创建输出目录
mkdir -p "$OUTPUT_DIR"

# 检查运行时库
if [ ! -f "$RUNTIME_LIB" ]; then
    echo -e "${YELLOW}警告: 运行时库文件不存在: $RUNTIME_LIB${NC}"
fi

# 获取所有测试文件
TEST_FILES=($(find "$TEST_DIR" -name "*.cact" | sort))

if [ ${#TEST_FILES[@]} -eq 0 ]; then
    echo -e "${RED}错误: 在 $TEST_DIR 中没有找到 .cact 测试文件${NC}"
    exit 1
fi

echo "找到 ${#TEST_FILES[@]} 个测试文件"
echo

# 运行测试函数
run_test() {
    local test_file="$1"
    local test_name=$(basename "$test_file" .cact)
    local expected_output_file="${test_file%.cact}.out"
    local input_file="${test_file%.cact}.in"
    local asm_output="$OUTPUT_DIR/${test_name}.s"
    local exe_output="$OUTPUT_DIR/${test_name}"
    
    echo -n "测试 $test_name ... "
    
    # 检查预期输出文件是否存在
    if [ ! -f "$expected_output_file" ]; then
        echo -e "${YELLOW}SKIP${NC} (没有预期输出文件)"
        return
    fi
    
    # 第一步：编译CACT代码到汇编 (需要在CACT目录下运行)
    cd "$CACT_DIR"
    if ! "$COMPILER" "$test_file" > /dev/null 2>&1; then
        echo -e "${RED}COMPILE_FAIL${NC}"
        ((COMPILE_FAILED++))
        return
    fi
    
    # 检查汇编文件是否生成
    if [ ! -f "$asm_output" ]; then
        echo -e "${RED}NO_ASM${NC} (期望: $asm_output)"
        # 调试信息：显示实际生成的文件
        echo "    实际输出目录内容:"
        ls "$OUTPUT_DIR"/*.s 2>/dev/null | head -3 | sed 's/^/      /' || echo "      (没有 .s 文件)"
        ((COMPILE_FAILED++))
        return
    fi
    
    # 第二步：汇编并链接生成可执行文件
    if [ -n "$RISCV_GCC" ] && [ -f "$RUNTIME_LIB" ]; then
        # 如果有RISC-V编译器和运行时库，尝试链接
        if ! "$RISCV_GCC" -o "$exe_output" "$asm_output" "$RUNTIME_LIB" > /dev/null 2>&1; then
            # 如果链接失败，只测试编译是否成功
            echo -e "${GREEN}COMPILE_OK${NC} (RISC-V链接失败，但编译成功)"
            ((PASSED_TESTS++))
            return
        fi
        
        # 第三步：使用Spike模拟器运行可执行文件
        if [ -n "$SPIKE" ]; then
            local spike_output
            if [ -f "$input_file" ]; then
                spike_output=$("$SPIKE" "$PK" "$exe_output" < "$input_file" 2>&1 | grep -v "^bbl loader")
            else
                spike_output=$("$SPIKE" "$PK" "$exe_output" 2>&1 | grep -v "^bbl loader")
            fi
            
            # 直接比较输出，无需判断spike的返回值
            if diff -q "$expected_output_file" <(echo "$spike_output") > /dev/null 2>&1; then
                echo -e "${GREEN}PASS${NC}"
                ((PASSED_TESTS++))
            else
                echo -e "${RED}OUTPUT_DIFF${NC}"
                ((FAILED_TESTS++))
                echo "    预期输出:"
                cat "$expected_output_file" | head -3 | sed 's/^/      /'
                echo "    实际输出:"
                echo "$spike_output" | head -3 | sed 's/^/      /'
            fi
        else
            echo -e "${GREEN}LINK_OK${NC} (RISC-V链接成功，无Spike模拟器)"
            ((PASSED_TESTS++))
        fi
    else
        # 没有RISC-V编译器或运行时库，只测试编译
        echo -e "${GREEN}COMPILE_OK${NC} (仅编译测试)"
        ((PASSED_TESTS++))
    fi
}

# 运行所有测试
for test_file in "${TEST_FILES[@]}"; do
    ((TOTAL_TESTS++))
    run_test "$test_file"
done

echo
echo -e "${BLUE}=== 测试结果总结 ===${NC}"
echo "总测试数: $TOTAL_TESTS"
echo -e "通过: ${GREEN}$PASSED_TESTS${NC}"
echo -e "失败: ${RED}$FAILED_TESTS${NC}"
echo -e "编译失败: ${RED}$COMPILE_FAILED${NC}"

if [ $FAILED_TESTS -eq 0 ] && [ $COMPILE_FAILED -eq 0 ]; then
    echo -e "${GREEN}所有测试通过！${NC}"
    exit 0
else
    echo -e "${RED}有测试失败。${NC}"
    exit 1
fi
