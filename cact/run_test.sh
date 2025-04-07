# 遍历 ./test 文件夹中的每个文件
for file in ./test/samples_lex_and_syntax/*; do
  # 执行 ./build/compiler 命令，传递文件名作为第二个参数
  ./build/compiler "$file"
done


# ./build/compiler "./test/samples_lex_and_syntax/06_false_hex_num.cact"