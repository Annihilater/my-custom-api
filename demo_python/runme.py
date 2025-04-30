# file: runme.py

import logging
import os
import sys

# 配置日志
logging.basicConfig(
    level=logging.DEBUG, format="%(asctime)s - %(levelname)s - %(message)s"
)

current_file = os.path.abspath(__file__)
current_dir = os.path.dirname(current_file)
parent_dir = os.path.dirname(current_dir)
lib_dir = os.path.join(parent_dir, "lib")
sys.path.append(lib_dir)

import time
import threading
import lib.my_custom_library.mock_py_xlight_trade_api as xlight
from lib.third_party_library.demo_python.format import *

global_request_id = 0
global_client_id = 1
global_account_name = "test_account"
global_password = "123456"
global_pub_key = "vU2VTSwdG4mLzIb69dS2EGKmdfZj6sJlspQoyq2dl7kZdEK8GfK2xXtolkejFNSHBqNe6nvqKXUelfbhc3lhAg=="
global_biz_type = 1
global_session_id = 0
global_login_event = threading.Event()


def get_next_request_id():
    global global_request_id
    global_request_id += 1
    return global_request_id


class MySpi(xlight.TradeSpi):
    def __init__(self):
        xlight.TradeSpi.__init__(self)
        # self.trade_api = trade_api

    def on_disconnect(self, session_id):
        """
        断线回调
        断线之后触发回调，用户需要主动重新login
        :param session_id 会话ID。
        :return None
        """
        logging.info("Disconnected: {}".format(session_id))
        # re_login_request_id = get_next_request_id()
        # ret = self.trade_api.login(global_client_id, global_account_name, global_password, global_pub_key,
        #                            global_biz_type, re_login_request_id)
        # if ret > 0:
        #     # 登录失败
        #     logging.info("Login error", self.trade_api.get_last_error())
        # else:
        #     logging.info("Login error", self.trade_api.get_last_error())

    def on_login(self, session_id, error_info, request_id):
        """
        登录回调
        :param session_id 本次登录生成的会话ID。如果登录失败则为0。
        :param error_info 登录请求发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。
        :param request_id 此消息响应函数对应的请求ID。
        :return None
        """
        if error_info:
            logging.info(
                "[on_login][request_id={}]Login is failed! error_id={}, error_msg={}".format(
                    request_id, error_info.error_id, error_info.error_msg
                )
            )
        else:
            global global_session_id
            global_session_id = session_id
            global_login_event.set()
            logging.info(
                "[on_login][request_id={}]Login is success! session_id={}".format(
                    request_id, session_id
                )
            )

    def on_order_status_notice(self, session_id, order_status_notice):
        """
        订单状态通知
        :param session_id 会话ID。
        :param order_status_notice 订单状态通知
        :return None
        """
        logging.info(
            "[on_order_status_notice][session_id={}] Order status notice: "
            "xid={}, order_client_id={}, order_brief_status={}".format(
                session_id,
                order_status_notice.xid,  # 报单标识
                order_status_notice.order_client_id,  # 报单引用，由客户自定义
                order_status_notice.order_brief_status,  # 订单简要状态：1：初始；2：已报；3：结束
            )
        )

    def on_order_response(self, session_id, order_response):
        """
        申报响应和撤单成功响应
        :param session_id 会话ID。
        :param order_response 申报响应和撤单成功响应响应数据指针。
        :return None
        """
        logging.info(
            "[on_order_response][session_id={}] {}".format(
                session_id, format_order_response(order_response)
            )
        )

    def on_order_reject(self, session_id, order_reject):
        """
        订单拒绝通知
        :param session_id 会话ID。
        :param order_reject 订单拒绝通知
        :return None
        """
        logging.info(
            "[on_order_reject][session_id={}] {}".format(
                session_id, format_order_reject(order_reject)
            )
        )

    def on_order_cancel_fail(self, session_id, order_cancel_error):
        """
        撤单失败通知
        :param session_id: 会话ID
        :param order_cancel_error: 撤单失败通知
        :return:
        """
        logging.info(
            "[on_trade_report][session_id={}] {}".format(
                session_id, format_order_cancel_fail(order_cancel_error)
            )
        )

    def on_trade_report(self, session_id, trade_report):
        """
        成交回报通知
        :param session_id: 会话ID
        :param trade_report: 成交回报通知
        :return:
        """
        logging.info(
            "[on_trade_report][session_id={}] {}".format(
                session_id, format_trade_report(trade_report)
            )
        )

    def on_positions(self, session_id, positions, data_count):
        """
        持仓变动推送，当持仓发生变化时，会推送给用户。
        :param session_id 会话id，登录时得到
        :param positions 持仓列表，个数由data_count决定
        :param data_count 持仓个数
        """
        logging.info(
            "[on_positions][session_id={}] data_count={}".format(session_id, data_count)
        )
        py_positions = xlight.PositionArray.frompointer(positions)
        for i in range(data_count):
            logging.info(
                "[on_positions][index={}] {}".format(
                    i, format_position(py_positions[i])
                )
            )

    def on_assets(self, session_id, assets, data_count):
        """
        资产变动推送，当资产发生变化时，会推送给用户。
        :param session_id 会话id，登录时得到
        :param assets 资产列表，个数由data_count决定
        :param data_count 资产个数
        """
        logging.info(
            "[on_assets][session_id={}] data_count={}".format(session_id, data_count)
        )
        py_assets = xlight.AssetArray.frompointer(assets)
        for i in range(data_count):
            logging.info(
                "[on_assets][index={}] {}".format(i, format_asset(py_assets[i]))
            )

    def on_query_positions(
        self, session_id, request_id, positions, data_count, is_last, error_info
    ):
        """
        持仓查询响应
        :param session_id 会话id，登录时得到
        :param request_id 此消息响应函数对应的请求ID
        :param positions 本次响应返回的持仓列表，个数由data_count决定
        :param data_count 本次响应返回的持仓个数
        :param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
        :param error_info 查询账户持仓发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
        """
        logging.info(
            "on_query_positions session_id: {} request_id: {} data_count: {} is_last: {}".format(
                session_id, request_id, data_count, is_last
            )
        )
        if error_info is not None:
            logging.info(
                "Error: error_id: {}, error_msg: {}".format(
                    error_info.error_id, error_info.error_msg
                )
            )
            return
        py_positions = xlight.PositionArray.frompointer(positions)
        for i in range(data_count):
            logging.info(
                "[on_query_positions][index={}] {}".format(
                    i, format_position(py_positions[i])
                )
            )

    def on_query_assets(
        self, session_id, request_id, assets, data_count, is_last, error_info
    ):
        """
        资产查询响应
        :param session_id 会话id，登录时得到
        :param request_id 此消息响应函数对应的请求ID
        :param assets 本次响应返回的资产列表，个数由data_count决定
        :param data_count 本次响应返回的资产个数
        :param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
        :param error_info 查询账户资产发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
        """
        logging.info(
            "on_query_assets session_id: {} request_id: {} data_count: {} is_last: {}".format(
                session_id, request_id, data_count, is_last
            )
        )
        if error_info is not None:
            logging.info(
                "Error: error_id: {}, error_msg: {}".format(
                    error_info.error_id, error_info.error_msg
                )
            )
            return
        py_assets = xlight.AssetArray.frompointer(assets)
        for i in range(data_count):
            logging.info(
                "[on_query_assets][index={}] {}".format(i, format_asset(py_assets[i]))
            )

    def on_query_orders(
        self, session_id, request_id, order_infos, data_count, is_last, error_info
    ):
        """
        查询报单响应
        :param session_id 会话id，登录时得到
        :param request_id 此消息响应函数对应的请求ID
        :param order_infos 本次响应返回的订单信息，个数由data_count决定
        :param data_count 本次响应返回的数据条数
        :param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
        :param error_info 查询账户资产发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
        """
        logging.info(
            "on_query_orders session_id: {} request_id: {} data_count: {} is_last: {}".format(
                session_id, request_id, data_count, is_last
            )
        )
        if error_info is not None:
            logging.info(
                "Error: error_id: {}, error_msg: {}".format(
                    error_info.error_id, error_info.error_msg
                )
            )
            return
        py_orders = xlight.OrderArray.frompointer(order_infos)
        for i in range(data_count):
            logging.info(
                "[on_query_orders][index={}] {}".format(i, format_order(py_orders[i]))
            )

    def on_query_orders_by_page(
        self,
        session_id,
        request_id,
        order_infos,
        data_count,
        req_count,
        order_sequence,
        query_reference,
        is_last,
        error_info,
    ):
        """
        查询报单响应
        :param session_id 会话id，登录时得到
        :param request_id 此消息响应函数对应的请求ID
        :param order_infos 本次响应返回的订单信息，个数由data_count决定
        :param data_count 本次响应返回的数据条数
        :param req_count 分页请求的最大数量
        :param order_sequence 分页请求的当前回报数量
        :param query_reference 当前响应最后一条报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
        :param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
        :param error_info 查询账户资产发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
        """
        logging.info(
            "on_query_orders_by_page session_id: {} request_id: {} data_count: {} req_count: {}, "
            "order_sequence: {}, query_reference: {} is_last: {}".format(
                session_id,
                request_id,
                data_count,
                req_count,
                order_sequence,
                query_reference,
                is_last,
            )
        )
        if error_info is not None:
            logging.info(
                "Error: error_id: {}, error_msg: {}".format(
                    error_info.error_id, error_info.error_msg
                )
            )
            return
        py_orders = xlight.OrderArray.frompointer(order_infos)
        for i in range(data_count):
            logging.info(
                "[on_query_orders_by_page][index={}] {}".format(
                    i, format_order(py_orders[i])
                )
            )

    def on_query_order_detail(
        self, session_id, request_id, order_details, data_count, is_last, error_info
    ):
        """
        查询报单明细响应
        :param session_id 会话id，登录时得到
        :param request_id 此消息响应函数对应的请求ID
        :param order_details 本次响应返回的订单明细信息，个数由data_count决定
        :param data_count 本次响应返回的数据条数
        :param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
        :param error_info 查询账户资产发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
        """
        logging.info(
            "on_query_order_details session_id: {} request_id: {} data_count: {} is_last: {}".format(
                session_id, request_id, data_count, is_last
            )
        )
        if error_info is not None:
            logging.info(
                "Error: error_id: {}, error_msg: {}".format(
                    error_info.error_id, error_info.error_msg
                )
            )
            return
        logging.info("on_query_order_details 1")
        py_order_details = xlight.OrderDetailArray.frompointer(order_details)
        for i in range(data_count):
            order_detail = py_order_details[i]
            logging.info("on_query_order_details 2")
            if order_detail.detail_type == xlight.XLTReportType_ORDER_REJECT:
                logging.info("on_query_order_details 3")
                logging.info(
                    "[on_query_order_details][index={}][type={}] {}".format(
                        i,
                        order_detail.detail_type,
                        format_order_reject(order_detail.data.order_reject),
                    )
                )
            elif order_detail.detail_type == xlight.XLTReportType_ORDER_RESPONSE:
                logging.info("on_query_order_details 4")
                logging.info(
                    "[on_query_order_details][index={}][type={}] {}".format(
                        i,
                        order_detail.detail_type,
                        format_order_response(order_detail.data.order_response),
                    )
                )
            elif order_detail.detail_type == xlight.XLTReportType_TRADE_REPORT:
                logging.info("on_query_order_details 5")
                logging.info(
                    "[on_query_order_details][index={}][type={}] {}".format(
                        i,
                        order_detail.detail_type,
                        format_trade_report(order_detail.data.trade_report),
                    )
                )
            elif order_detail.detail_type == xlight.XLTReportType_ORDER_CANCEL_FAIL:
                logging.info("on_query_order_details 6")
                logging.info(
                    "[on_query_order_details][index={}][type={}] {}".format(
                        i,
                        order_detail.detail_type,
                        format_order_cancel_fail(order_detail.data.order_cancel_fail),
                    )
                )

    def on_request_timeout(self, session_id, request_id):
        """
        请求超时回调
        :param session_id 会话ID。
        :param request_id 此消息响应函数对应的请求ID。
        :return None
        """
        logging.info(
            "[on_request_timeout][session_id={}] request_id={}".format(
                session_id, request_id
            )
        )


def login(api):
    login_request_id = get_next_request_id()
    result = api.login(
        client_id=global_client_id,
        account_name=global_account_name,
        password=global_password,
        pub_key=global_pub_key,
        biz_type=global_biz_type,
        request_id=login_request_id,
    )

    format_login_request = (
        "Login info: "
        "client_id={}, account_name={}, password={}, pub_key={}, biz_type={}".format(
            global_client_id,
            global_account_name,
            global_password,
            global_pub_key,
            global_biz_type,
        )
    )
    if result > 0:
        logging.info("[request_id={}]Login error: {} ".format(login_request_id, result))
        return 0
    else:
        logging.info(
            "[request_id={}]Login request send! Wait for response (on_login). ".format(
                login_request_id
            )
            + format_login_request
        )
        global_login_event.wait()
        return global_session_id


def logout(api, session_id):
    api.logout(session_id)


def insert_order(api, session_id):
    """
    委托
    :param api:
    :param session_id:
    :return:
    """
    order_insert_info = xlight.xlt_order_insert_info_t()
    order_insert_info.order_client_id = 1  # 报单引用，由客户自定义
    order_insert_info.security_code = "600000"  # 证券代码
    order_insert_info.exchange_index = xlight.XLTExchangeIndex_SH_A  # 交易市场
    order_insert_info.price = 120000  # 价格放大10000倍
    order_insert_info.quantity = 200  # 数量
    order_insert_info.order_price_type = (
        xlight.XLTOrderPriceType_LIMIT_PRICE
    )  # 报单价格类型
    order_insert_info.side = xlight.XLTSide_BUY  # 买卖方向
    order_insert_info.business_type = xlight.XLTBusinessType_CASH  # 业务类型

    xid = api.insert_order(
        session_id=session_id, order=order_insert_info, algo_order_id=0
    )
    if xid == 0:
        logging.info(
            "[session_id={}][xid={}]Inser order error! ".format(session_id, xid)
            + format_order_insert_info(xid, order_insert_info)
        )
    else:
        logging.info(
            "[session_id={}][xid={}]Inser order send. Wait for response".format(
                session_id, xid
            )
            + format_order_insert_info(xid, order_insert_info)
        )

    return xid


def cancel_order(api: xlight.TradeApi, session_id, xid):
    """
    撤单
    :param api:
    :param session_id:
    :param xid:
    :return:
    """
    order_cancel_info = xlight.xlt_order_cancel_info_t()
    order_cancel_info.order_client_id = 1  # 报单引用，由客户自定义
    order_cancel_info.origin_xid = xid  # 被撤委托ID

    cancel_xid = api.cancel_order(
        session_id=session_id, cancel_info=order_cancel_info, algo_order_id=0
    )
    if cancel_xid == 0:
        logging.info(
            "[session_id={}][cancel_xid={}]Cancel order error! ".format(
                session_id, cancel_xid
            )
            + format_order_cancel_info(cancel_xid, order_cancel_info)
        )
    else:
        logging.info(
            "[session_id={}][cancel_xid={}]Cancel order send. Wait for response ".format(
                session_id, cancel_xid
            )
            + format_order_cancel_info(cancel_xid, order_cancel_info)
        )
    return cancel_xid


if __name__ == "__main__":
    my_spi = MySpi()  ### 确保Spi对象在整个程序运行期间都有效
    my_api = xlight.TradeApi.create_trade_api()
    xlt_trade_config = xlight.xlt_trade_config_t()
    xlt_trade_config.path = ""
    xlt_trade_config.log_level = xlight.XLTLogLevel_LOG_TRACE
    xlt_trade_config.local_address = "0.0.0.0"
    xlt_trade_config.order_local_address = "0.0.0.0"
    xlt_trade_config.agw_address = ["192.168.17.39:6062"]  ### AGW地址
    xlt_trade_config.join_test_fon = "192.168.17.31:6067"  ### 联调测试设置fon地址，如果设置为空字符串则使用AGW返回的fon
    xlt_trade_config.join_test_account_index = (
        662  ### 联调测试设置资金账号ID，如果为0则使用AGW返回的资金账号ID
    )

    if my_api.initialize(xlt_trade_config):
        my_api.register_spi(my_spi)
    else:
        sys.exit(0)

    my_session_id = login(my_api)
    if my_session_id == 0:
        sys.exit(0)

    order_xid = insert_order(my_api, my_session_id)
    if order_xid == 0:
        my_api.logout(my_session_id)
        sys.exit(0)

    cancel_xid = cancel_order(my_api, my_session_id, order_xid)
    if cancel_xid == 0:
        my_api.logout(my_session_id)
        sys.exit(0)

    # # 查询持仓
    # my_api.query_positions(session_id=my_session_id, request_id=get_next_request_id(), security_code="",
    #                        exchange_index=xlight.XLTExchangeIndex_INIT, algo_order_id=0)
    #
    # # 查询资产
    # my_api.query_assets(session_id=my_session_id, request_id=get_next_request_id(), algo_order_id=0)

    # 查询订单（根据条件查询）
    # order_query_param = xlight.xlt_order_query_param_t()
    # order_query_param.xid = order_xid
    # my_api.query_orders(session_id=my_session_id, request_id=get_next_request_id(),
    #                     order_query_param=order_query_param, algo_order_id=0)

    # # 分页查询订单
    # order_query_by_page_param = xlight.xlt_order_query_by_page_param_t()
    # order_query_by_page_param.req_count = 10
    # order_query_by_page_param.reference = 0
    # my_api.query_orders_by_page(session_id=my_session_id, request_id=get_next_request_id(),
    #                             page_query_param=order_query_by_page_param, algo_order_id=0)
    #
    # # 查询订单明细
    # my_api.query_order_details(session_id=my_session_id, request_id=get_next_request_id(),
    #                            order_xid=order_xid, algo_order_id=0)
    while True:
        time.sleep(1)

    my_api.logout(my_session_id)
