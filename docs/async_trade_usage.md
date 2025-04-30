# 异步交易API使用说明

## 简介
这是对XLight交易API的异步封装，使用Python的asyncio实现。该封装提供了更简洁的接口，支持async/await语法，使异步操作更加直观和易于管理。

## 主要特性
- 异步操作支持
- 统一的错误处理
- 超时控制
- 资源自动清理
- 类型提示支持

## 使用示例

### 初始化和登录
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
```

### 下单操作
```python
order_info = xlight.xlt_order_insert_info_t()
order_info.security_code = "600000"
order_info.exchange_index = xlight.XLTExchangeIndex.SH_A
order_info.price = 50000000
order_info.quantity = 8800

result = await client.insert_order(order_info)
if result.success:
    print(f"下单成功: {result.data}")
else:
    print(f"下单失败: {result.error}")
```

## 错误处理
所有操作都返回 TradeResponse 对象，包含以下字段：
- success: bool - 操作是否成功
- data: Any - 成功时的返回数据
- error: Optional[str] - 失败时的错误信息

## 注意事项
1. 所有异步操作都有默认的超时设置
2. 登录成功后才能进行交易操作
3. 资源会在操作完成后自动清理
4. 建议使用 logging 模块记录操作日志