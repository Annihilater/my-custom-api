import asyncio

from loguru import logger

import lib.py_xlight_trade_api as xlight
from async_trade_wrapper import AsyncTradeClient


async def main():
    # 创建客户端实例
    client = AsyncTradeClient()

    # 初始化配置
    config = xlight.xlt_trade_config_t()
    config.path = "."
    config.log_level = xlight.XLTLogLevel.LOG_DEBUG
    config.mem_pool_size = 64
    config.agw_address[0] = "192.168.17.39:6062"
    config.local_address = "0.0.0.0"
    config.order_local_address = "0.0.0.0"

    # 初始化
    result = await client.initialize(config)
    if not result.success:
        logger.error(f"初始化失败: {result.error}")
        return

    # 登录
    result = await client.login(
        account_name="test_account",
        password="123456",
        pub_key="vU2VTSwdG4mLzIb69dS2EGKmdfZj6sJlspQoyq2dl7kZdEK8GfK2xXtolkejFNSHBqNe6nvqKXUelfbhc3lhAg=="
    )
    if not result.success:
        logger.error(f"登录失败: {result.error}")
        return

    logger.info("登录成功!")

    # 下单示例
    order_info = xlight.xlt_order_insert_info_t()
    order_info.order_client_id = 1
    order_info.security_code = "600000"
    order_info.exchange_index = xlight.XLTExchangeIndex.SH_A
    order_info.price = 50000000
    order_info.quantity = 8800
    order_info.order_price_type = xlight.XLTOrderPriceType.LIMIT_PRICE
    order_info.side = xlight.XLTSide.SELL
    order_info.business_type = xlight.XLTBusinessType.CASH

    result = await client.insert_order(order_info)
    if result.success:
        logger.info(f"下单成功: {result.data}")
    else:
        logger.error(f"下单失败: {result.error}")


if __name__ == "__main__":
    asyncio.run(main())
