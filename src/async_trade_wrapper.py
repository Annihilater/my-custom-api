import asyncio
from dataclasses import dataclass
from typing import Optional, Dict, Any

import lib.py_xlight_trade_api as xlight


@dataclass
class TradeResponse:
    success: bool
    data: Any = None
    error: Optional[str] = None


class AsyncTradeClient:
    def __init__(self):
        self._api = xlight.TradeApi.create_trade_api()
        self._spi = AsyncTradeSpi()
        self._spi.client = self
        self._futures: Dict[int, asyncio.Future] = {}
        self._session_id = 0
        self._request_id = 0

    async def initialize(self, config) -> TradeResponse:
        if not self._api.initialize(config):
            return TradeResponse(success=False, error="初始化失败")
        self._api.register_spi(self._spi)
        return TradeResponse(success=True)

    async def login(self, account_name: str, password: str, pub_key: str) -> TradeResponse:
        self._request_id += 1
        request_id = self._request_id

        # 创建Future对象用于等待异步结果
        future = asyncio.Future()
        self._futures[request_id] = future

        # 发送登录请求
        result = self._api.login(request_id, account_name, password, pub_key)
        if result > 0:
            del self._futures[request_id]
            return TradeResponse(success=False, error=f"登录请求发送失败: {result}")

        try:
            # 等待登录响应
            response = await asyncio.wait_for(future, timeout=10.0)
            if response.get("success"):
                self._session_id = response.get("session_id")
                return TradeResponse(success=True, data=response)
            return TradeResponse(success=False, error=response.get("error"))
        except asyncio.TimeoutError:
            return TradeResponse(success=False, error="登录超时")
        finally:
            if request_id in self._futures:
                del self._futures[request_id]

    async def insert_order(self, order_info) -> TradeResponse:
        if not self._session_id:
            return TradeResponse(success=False, error="未登录")

        xid = self._api.insert_order(self._session_id, order_info)
        if xid == 0:
            return TradeResponse(success=False, error="订单发送失败")

        # 创建Future等待订单响应
        future = asyncio.Future()
        self._futures[xid] = future

        try:
            response = await asyncio.wait_for(future, timeout=5.0)
            return TradeResponse(success=True, data=response)
        except asyncio.TimeoutError:
            return TradeResponse(success=False, error="订单响应超时")
        finally:
            if xid in self._futures:
                del self._futures[xid]


class AsyncTradeSpi(xlight.TradeSpi):
    def __init__(self):
        super().__init__()
        self.client = None

    def on_login(self, session_id, error_info, request_id):
        if not self.client or request_id not in self.client._futures:
            return

        future = self.client._futures[request_id]
        if error_info and error_info.error_id != 0:
            future.set_result({
                "success": False,
                "error": error_info.error_msg,
                "error_id": error_info.error_id
            })
        else:
            future.set_result({
                "success": True,
                "session_id": session_id
            })

    def on_order_response(self, session_id, order_response):
        if not self.client:
            return

        xid = order_response.xid
        if xid in self.client._futures:
            future = self.client._futures[xid]
            future.set_result({
                "success": True,
                "order_response": order_response
            })
