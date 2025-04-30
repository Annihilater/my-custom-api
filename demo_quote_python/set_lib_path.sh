#!/bin/bash

# 获取脚本所在目录的绝对路径
SCRIPT_DIR=$(dirname "$(realpath "$0")")

# 获取上层目录的路径
PARENT_DIR=$(dirname "$SCRIPT_DIR")

# 获取上层目录中的 lib 目录路径
LIB_DIR="$PARENT_DIR/lib"

# 检查 lib 目录是否存在
if [ -d "$LIB_DIR" ]; then
    # 将 lib 目录加入到 LD_LIBRARY_PATH
    export LD_LIBRARY_PATH="$LIB_DIR:$LD_LIBRARY_PATH"
    echo "Added $LIB_DIR to LD_LIBRARY_PATH"
else
    echo "Error: Directory $LIB_DIR does not exist."
    exit 1
fi