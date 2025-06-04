#!/bin/bash

# IR功能测试脚本
# 用于测试CACT编译器的LLVM IR生成功能

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 全局变量
COMPILER_PATH="build/compiler"
TEST_DIR="test/samples_generateIR/test_cases"
RESULTS_DIR="test/samples_generateIR/test_results"
LLI_PATH=$(which lli) # 使用 which lli 获取路径
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# 创建结果目录
mkdir -p "$RESULTS_DIR"

# 检查编译器是否存在
check_compiler() {
    if [ ! -f "$COMPILER_PATH" ]; then
        echo -e "${RED}错误: 编译器不存在: $COMPILER_PATH${NC}"
        echo "请先编译项目: cd build && make"
        exit 1
    fi
}

# 编译CACT源文件为LLVM IR
compile_to_ir() {
    local cact_file="$1"
    local ir_file="$2"
    
    echo "编译 $cact_file 到 $ir_file"
    
    # 编译器输出调试信息到stderr，获取生成的.ll文件名
    local compile_output
    compile_output=$(./"$COMPILER_PATH" "$cact_file" 2>&1)
    local exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}编译失败: $cact_file${NC}"
        echo "编译输出: $compile_output"
        return 1
    fi
    
    # 提取生成的.ll文件名（从编译输出中）
    local generated_ll_file
    generated_ll_file=$(basename "$cact_file" .cact).ll
    
    if [ ! -f "$generated_ll_file" ]; then
        echo -e "${RED}编译失败: 未找到生成的IR文件 $generated_ll_file${NC}"
        echo "编译输出: $compile_output"
        return 1
    fi
    
    # 复制生成的IR文件到目标位置
    cp "$generated_ll_file" "$ir_file"
    # 删除临时生成的IR文件
    rm -f "$generated_ll_file"
    return 0
}

# 使用lli执行LLVM IR
run_ir() {
    local ir_file="$1"
    local input_file="$2"
    local output_file="$3"
    
    if [ ! -f "$LLI_PATH" ]; then
        echo -e "${RED}错误: lli不存在: $LLI_PATH${NC}"
        return 1
    fi
    
    # 检查是否需要运行时库
    local runtime_lib="test/samples_generateIR/runtime_lib/runtime.ll"
    local final_ir_file="$ir_file"
    
    if grep -q "get_int\|get_float\|get_char" "$ir_file" 2>/dev/null; then
        # 需要链接运行时库
        if [ -f "$runtime_lib" ]; then
            local linked_file="${ir_file%.ll}_linked.ll"
            llvm-link "$ir_file" "$runtime_lib" -o "$linked_file" 2>/dev/null
            if [ $? -eq 0 ]; then
                final_ir_file="$linked_file"
            fi
        fi
    fi
    
    if [ -n "$input_file" ] && [ -f "$input_file" ]; then
        # 有输入文件的情况
        "$LLI_PATH" "$final_ir_file" < "$input_file" > "$output_file" 2>/dev/null
        local exit_code=$?
        # 检查输出文件是否存在，不关心程序的退出码
        if [ ! -f "$output_file" ]; then
            echo -e "${RED}IR执行失败: $final_ir_file (使用输入文件 $input_file)${NC}"
            return 1
        fi
    else
        # 没有输入文件的情况
        "$LLI_PATH" "$final_ir_file" > "$output_file" 2>/dev/null
        local exit_code=$?
        # 检查输出文件是否存在，不关心程序的退出码
        if [ ! -f "$output_file" ]; then
            echo -e "${RED}IR执行失败: $final_ir_file${NC}"
            return 1
        fi
    fi
    return 0
}

# 比较输出结果
compare_output() {
    local expected_file="$1"
    local actual_file="$2"
    
    if [ ! -f "$expected_file" ]; then
        echo -e "${RED}期望输出文件不存在: $expected_file${NC}"
        return 1
    fi
    
    if [ ! -f "$actual_file" ]; then
        echo -e "${RED}实际输出文件不存在: $actual_file${NC}"
        return 1
    fi
    
    # 使用diff比较，忽略尾部空白字符
    if diff -q "$expected_file" "$actual_file" > /dev/null 2>&1; then
        return 0
    else
        return 1
    fi
}

# 测试单个文件
test_single_file() {
    local test_name="$1"
    local cact_file="$2"
    local expected_file="$3"
    local input_file="$4"
    
    echo -e "${BLUE}测试: $test_name${NC}"
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # 生成临时文件名
    local ir_file="$RESULTS_DIR/${test_name}.ll"
    local actual_file="$RESULTS_DIR/${test_name}.actual"
    
    # 编译为IR
    if ! compile_to_ir "$cact_file" "$ir_file"; then
        echo -e "${RED}❌ $test_name: 编译失败${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        return 1
    fi
    
    # 执行IR
    if ! run_ir "$ir_file" "$input_file" "$actual_file"; then
        echo -e "${RED}❌ $test_name: 执行失败${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        return 1
    fi
    
    # 比较输出
    if compare_output "$expected_file" "$actual_file"; then
        echo -e "${GREEN}✅ $test_name: 通过${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
        return 0
    else
        echo -e "${RED}❌ $test_name: 输出不匹配${NC}"
        echo "期望输出:"
        cat "$expected_file" | head -5
        echo "实际输出:"
        cat "$actual_file" | head -5
        echo "---"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        return 1
    fi
}

# 测试functional目录
test_functional() {
    echo -e "${YELLOW}=== 测试 Functional 测试用例 ===${NC}"
    
    local functional_dir="$TEST_DIR/functional"
    
    if [ ! -d "$functional_dir" ]; then
        echo -e "${RED}错误: Functional测试目录不存在: $functional_dir${NC}"
        return 1
    fi
    
    # 查找所有.cact文件并排序
    for cact_file in $(find "$functional_dir" -name "*.cact" | sort -V); do
        local base_name=$(basename "$cact_file" .cact)
        local expected_file="${functional_dir}/${base_name}.out"
        local input_file="${functional_dir}/${base_name}.in"
        
        # 检查是否存在对应的.out文件
        if [ ! -f "$expected_file" ]; then
            echo -e "${YELLOW}跳过 $base_name: 没有期望输出文件${NC}"
            continue
        fi
        
        # 检查是否需要输入文件
        local input_arg=""
        if [ -f "$input_file" ]; then
            input_arg="$input_file"
        fi
        
        test_single_file "functional_$base_name" "$cact_file" "$expected_file" "$input_arg"
    done
}

# 测试performance目录
test_performance() {
    echo -e "${YELLOW}=== 测试 Performance 测试用例 ===${NC}"
    
    local performance_dir="$TEST_DIR/performance"
    
    if [ ! -d "$performance_dir" ]; then
        echo -e "${RED}错误: Performance测试目录不存在: $performance_dir${NC}"
        return 1
    fi
    
    # 查找所有.cact文件并排序
    for cact_file in $(find "$performance_dir" -name "*.cact" | sort -V); do
        local base_name=$(basename "$cact_file" .cact)
        local expected_file="${performance_dir}/${base_name}.out"
        local input_file="${performance_dir}/${base_name}.in"
        
        # 检查是否存在对应的.out文件
        if [ ! -f "$expected_file" ]; then
            echo -e "${YELLOW}跳过 $base_name: 没有期望输出文件${NC}"
            continue
        fi
        
        # Performance测试通常都需要输入文件
        if [ ! -f "$input_file" ]; then
            echo -e "${YELLOW}跳过 $base_name: 没有输入文件${NC}"
            continue
        fi
        
        test_single_file "performance_$base_name" "$cact_file" "$expected_file" "$input_file"
    done
}

# 清理函数
cleanup() {
    echo -e "${BLUE}清理临时文件...${NC}"
    # 可以选择清理生成的.ll和.actual文件
    # rm -f "$RESULTS_DIR"/*.ll "$RESULTS_DIR"/*.actual
}

# 打印测试统计
print_statistics() {
    echo -e "${YELLOW}=== 测试统计 ===${NC}"
    echo -e "总计测试: ${BLUE}$TOTAL_TESTS${NC}"
    echo -e "通过测试: ${GREEN}$PASSED_TESTS${NC}"
    echo -e "失败测试: ${RED}$FAILED_TESTS${NC}"
    
    if [ $TOTAL_TESTS -gt 0 ]; then
        local pass_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
        echo -e "通过率: ${BLUE}$pass_rate%${NC}"
    fi
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "${GREEN}🎉 所有测试通过！${NC}"
        return 0
    else
        echo -e "${RED}❌ 有 $FAILED_TESTS 个测试失败${NC}"
        return 1
    fi
}

# 主函数
main() {
    echo -e "${BLUE}=== CACT编译器IR功能测试 ===${NC}"
    echo "编译器路径: $COMPILER_PATH"
    echo "测试目录: $TEST_DIR"
    echo "结果目录: $RESULTS_DIR"
    echo ""
    
    # 检查编译器
    check_compiler
    
    # 检查lli是否可用
    if ! command -v "$LLI_PATH" > /dev/null 2>&1; then
        echo -e "${RED}错误: $LLI_PATH命令不可用，请确保LLVM已安装${NC}"
        exit 1
    fi
    
    # 运行测试
    test_functional
    echo ""
    test_performance
    echo ""
    
    # 打印统计信息
    print_statistics
    
    # 清理
    trap cleanup EXIT
    
    # 返回适当的退出码
    if [ $FAILED_TESTS -eq 0 ]; then
        exit 0
    else
        exit 1
    fi
}

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        --clean)
            echo "清理结果目录..."
            rm -rf "$RESULTS_DIR"
            mkdir -p "$RESULTS_DIR"
            shift
            ;;
        --functional-only)
            echo "仅运行functional测试"
            main() {
                check_compiler
                test_functional
                print_statistics
            }
            shift
            ;;
        --performance-only)
            echo "仅运行performance测试"
            main() {
                check_compiler
                test_performance
                print_statistics
            }
            shift
            ;;
        -h|--help)
            echo "用法: $0 [选项]"
            echo "选项:"
            echo "  --clean              清理结果目录"
            echo "  --functional-only    仅运行functional测试"
            echo "  --performance-only   仅运行performance测试"
            echo "  -h, --help          显示帮助信息"
            exit 0
            ;;
        *)
            echo "未知选项: $1"
            exit 1
            ;;
    esac
done

# 运行主函数
main 