# XLight API SDK

XLight API SDK 提供了交易和行情的接口封装,支持 C++ 和 Python 语言。

## 目录结构

```
.
├── docs/                    # 文档目录
│   ├── async_trade_usage.md # 异步交易API使用说明
│   ├── cpp/                # C++ API文档
│   └── python/             # Python API文档
├── src/                    # 源代码目录
│   ├── async_trade_wrapper.py  # 异步交易API封装
│   └── demo_async_trade.py     # 异步交易示例
├── demo_cpp/               # C++示例代码
├── demo_quote_cpp/         # C++行情示例代码  
├── demo_python/            # Python示例代码
├── demo_quote_python/      # Python行情示例代码
└── lib/                    # 依赖库目录
```

## 快速开始

### Python SDK

1. 设置环境变量

```bash
# 方式一:
cd lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)

# 方式二:
chmod +x set_lib_path.sh
source set_lib_path.sh
```

2. 运行异步交易示例

```bash
python src/demo_async_trade.py
```

### C++ SDK

1. 编译交易示例

```bash
cd demo_cpp
mkdir build
cd build
cmake ../src
make && make install
```

2. 编译行情示例

```bash 
cd demo_quote_cpp
mkdir build
cd build
cmake ../src
make && make install
```

可执行文件将生成在各自的 targets/bin 目录下。

## 功能特性

- 支持 C++ 和 Python 语言
- 提供同步和异步 API
- 支持交易和行情功能
- 统一的错误处理
- 完整的类型提示
- 资源自动管理
- 详细的使用文档

## API 文档

- [异步交易 API 使用说明](docs/async_trade_usage.md)
- [C++ API 文档](docs/cpp/html/index.html)
- [Python API 文档](docs/python/html/index.html)

## 示例代码

### Python 异步交易示例

```python
client = AsyncTradeClient()

# 配置初始化
config = xlight.xlt_trade_config_t()
config.path = "."
config.log_level = xlight.XLTLogLevel.LOG_DEBUG
result = await client.initialize(config)

# 登录
result = await client.login(
    account_name="your_account",
    password="your_password",
    pub_key="your_pub_key"
)

# 下单
order_info = xlight.xlt_order_insert_info_t()
order_info.security_code = "600000"
order_info.exchange_index = xlight.XLTExchangeIndex.SH_A
order_info.price = 50000000
order_info.quantity = 8800

result = await client.insert_order(order_info)
```

更多示例请参考:

- C++ 交易示例: demo_cpp/
- C++ 行情示例: demo_quote_cpp/
- Python 交易示例: demo_python/
- Python 行情示例: demo_quote_python/

## 注意事项

1. 使用前请确保正确设置动态库搜索路径
2. Python SDK 需要 Python 3.7+ 版本
3. C++ SDK 需要 C++17 支持
4. 建议使用 logging 模块记录日志
5. 所有异步操作都有默认超时设置

## 许可证

Copyright (c) 2023 XLight. All rights reserved.