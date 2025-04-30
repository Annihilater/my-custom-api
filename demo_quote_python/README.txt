需要将lib目录添加进动态库搜索路径中
方式一：
cd ../lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)

方式二：
chmod +x set_lib_path.sh
source set_lib_path.sh