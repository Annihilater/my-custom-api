# file: runme.py

import sys
import os
import logging

# 配置日志
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

current_file = os.path.abspath(__file__)
current_dir = os.path.dirname(current_file)
parent_dir = os.path.dirname(current_dir)
lib_dir = os.path.join(parent_dir, "lib")
sys.path.append(lib_dir)

import py_xlight_quote_api as xlight
import time
import threading
from format import *

global_request_id = 0
global_client_id = 1
global_account_name = "test_account"
global_password = "123456"
global_pub_key = "vU2VTSwdG4mLzIb69dS2EGKmdfZj6sJlspQoyq2dl7kZdEK8GfK2xXtolkejFNSHBqNe6nvqKXUelfbhc3lhAg=="
global_biz_type = 1
global_login_result = False
global_login_event = threading.Event()


def get_next_request_id():
    global global_request_id
    global_request_id += 1
    return global_request_id


class MyQuoteSpi(xlight.QuoteSpi):
    def __init__(self):
        xlight.QuoteSpi.__init__(self)

    def on_login(self, request_id, success, error_info):
        """
        登录回调
        """
        logging.info("on_login")
        print(success)
        if success:
            logging.info("[on_login][request_id={}]Login is success!"
                         .format(request_id))
        else:
            logging.info("[on_login][request_id={}]Login is failed! error_id={}, error_msg={}"
                         .format(request_id, error_info.error_id, error_info.error_msg))

        global global_login_result
        global global_login_event
        global_login_result = success
        global_login_event.set()

    def on_market_data(self, market_data):
        '''
        快照行情回调
        :param market_data: 行情数据
        :return:
        '''
        print("on_market_data")
        market_data_str = ("OnMarketData: "
                           "exchange_index: {}, "
                           "security_code:{}, "
                           "last_price: {}, "
                           "pre_close_price: {}, "
                           "open_price: {}, "
                           "high_price: {}, "
                           "low_price: {}, "
                           "close_price: {}, "
                           "pre_total_long_position: {}, "
                           "total_long_position: {}, "
                           "pre_settle_price: {}, "
                           "settle_price: {}, "
                           "upper_limit_price: {}, "
                           "lower_limit_price: {}, "
                           "pre_delta: {}, "
                           "curr_delta: {}, "
                           "data_time: {}, "
                           "qty: {}, "
                           "turnover: {}, "
                           "avg_price: {}, "
                           "bid: {}, "
                           "ask: {}, "
                           "bid_qty: {}, "
                           "ask_qty: {}, "
                           "bid_num_orders: {}, "
                           "ask_num_orders: {}, "
                           "trades_count: {}, "
                           "ticker_status: {}, "
                           "data_type: {}, "
        .format(
            int(market_data.exchange_index),
            market_data.security_code,
            market_data.last_price,
            market_data.pre_close_price,
            market_data.open_price,
            market_data.high_price,
            market_data.low_price,
            market_data.close_price,
            market_data.pre_total_long_position,
            market_data.total_long_position,
            market_data.pre_settle_price,
            market_data.settle_price,
            market_data.upper_limit_price,
            market_data.lower_limit_price,
            market_data.pre_delta,
            market_data.curr_delta,
            market_data.data_time,
            market_data.qty,
            market_data.turnover,
            market_data.avg_price,
            market_data.bid,  ## list
            market_data.ask,  ## list
            market_data.bid_qty,  ## list
            market_data.ask_qty,  ## list
            market_data.bid_num_orders,  ## list
            market_data.ask_num_orders,  ## list
            market_data.trades_count,
            market_data.ticker_status,
            market_data.data_type, ))

        market_data_str += "bid_queue_cnt: {}, bid_queue_cnt: {}, ".format(
            market_data.bid_queue_cnt, market_data.bid_queue)
        market_data_str += "ask_queue_cnt: {}, ask_queue: {}, ".format(
            market_data.ask_queue_cnt, market_data.ask_queue)

        if market_data.data_type == xlight.MARKETDATA_ACTUAL:
            ## 股票
            market_data_str += (
                "total_bid_qty: {}, "
                "total_ask_qty: {}, "
                "ma_bid_price: {}, "
                "ma_ask_price: {}, "
                "ma_bond_bid_price: {}, "
                "ma_bond_ask_price: {}, "
                "yield_to_maturity: {}, "
                "iopv: {}, "
                "etf_buy_count: {}, "
                "etf_sell_count: {}, "
                "etf_buy_qty: {}, "
                "etf_buy_money: {}, "
                "etf_sell_qty: {}, "
                "etf_sell_money: {}, "
                "total_warrant_exec_qty: {}, "
                "warrant_lower_price: {}, "
                "warrant_upper_price: {}, "
                "cancel_buy_count: {}, "
                "cancel_sell_count: {}, "
                "cancel_buy_qty: {}, "
                "cancel_sell_qty: {}, "
                "cancel_buy_money: {}, "
                "cancel_sell_money: {}, "
                "total_buy_count: {}, "
                "total_sell_count: {}, "
                "duration_after_buy: {}, "
                "duration_after_sell: {}, "
                "num_bid_orders: {}, "
                "num_ask_orders: {}, "
                "pre_iopv: {}, "
                "r1: {}, "
                "r2: {}, "
                .format(market_data.ex_data.stk.total_bid_qty,
                        market_data.ex_data.stk.total_ask_qty,
                        market_data.ex_data.stk.ma_bid_price,
                        market_data.ex_data.stk.ma_ask_price,
                        market_data.ex_data.stk.ma_bond_bid_price,
                        market_data.ex_data.stk.ma_bond_ask_price,
                        market_data.ex_data.stk.yield_to_maturity,
                        market_data.ex_data.stk.iopv,
                        market_data.ex_data.stk.etf_buy_count,
                        market_data.ex_data.stk.etf_sell_count,
                        market_data.ex_data.stk.etf_buy_qty,
                        market_data.ex_data.stk.etf_buy_money,
                        market_data.ex_data.stk.etf_sell_qty,
                        market_data.ex_data.stk.etf_sell_money,
                        market_data.ex_data.stk.total_warrant_exec_qty,
                        market_data.ex_data.stk.warrant_lower_price,
                        market_data.ex_data.stk.warrant_upper_price,
                        market_data.ex_data.stk.cancel_buy_count,
                        market_data.ex_data.stk.cancel_sell_count,
                        market_data.ex_data.stk.cancel_buy_qty,
                        market_data.ex_data.stk.cancel_sell_qty,
                        market_data.ex_data.stk.cancel_buy_money,
                        market_data.ex_data.stk.cancel_sell_money,
                        market_data.ex_data.stk.total_buy_count,
                        market_data.ex_data.stk.total_sell_count,
                        market_data.ex_data.stk.duration_after_buy,
                        market_data.ex_data.stk.duration_after_sell,
                        market_data.ex_data.stk.num_bid_orders,
                        market_data.ex_data.stk.num_ask_orders,
                        market_data.ex_data.stk.pre_iopv,
                        market_data.ex_data.stk.r1,
                        market_data.ex_data.stk.r2,
                        ))
        elif market_data.data_type == xlight.MARKETDATA_BOND:
            ## 债券
            market_data_str += ("total_bid_qty: {}, "
                                "total_ask_qty: {}, "
                                "ma_bid_price: {}, "
                                "ma_ask_price: {}, "
                                "ma_bond_bid_price: {}, "
                                "ma_bond_ask_price: {}, "
                                "yield_to_maturity: {}, "
                                "match_lastpx: {}, "
                                "ma_bond_price: {}, "
                                "match_qty: {}, "
                                "match_turnover: {}, "
                                "r4: {}, "
                                "r5: {}, "
                                "r6: {}, "
                                "r7: {}, "
                                "r8: {}, "
                                "cancel_buy_count: {}, "
                                "cancel_sell_count: {}, "
                                "cancel_buy_qty: {}, "
                                "cancel_sell_qty: {}, "
                                "cancel_buy_money: {}, "
                                "cancel_sell_money: {}, "
                                "total_buy_count: {}, "
                                "total_sell_count: {}, "
                                "duration_after_buy: {}, "
                                "duration_after_sell: {}, "
                                "num_bid_orders: {}, "
                                "num_ask_orders: {}, "
                                "instrument_status: {}, "
                                .format(market_data.ex_data.bond.total_bid_qty,
                                        market_data.ex_data.bond.total_ask_qty,
                                        market_data.ex_data.bond.ma_bid_price,
                                        market_data.ex_data.bond.ma_ask_price,
                                        market_data.ex_data.bond.ma_bond_bid_price,
                                        market_data.ex_data.bond.ma_bond_ask_price,
                                        market_data.ex_data.bond.yield_to_maturity,
                                        market_data.ex_data.bond.match_lastpx,
                                        market_data.ex_data.bond.ma_bond_price,
                                        market_data.ex_data.bond.match_qty,
                                        market_data.ex_data.bond.match_turnover,
                                        market_data.ex_data.bond.r4,
                                        market_data.ex_data.bond.r5,
                                        market_data.ex_data.bond.r6,
                                        market_data.ex_data.bond.r7,
                                        market_data.ex_data.bond.r8,
                                        market_data.ex_data.bond.cancel_buy_count,
                                        market_data.ex_data.bond.cancel_sell_count,
                                        market_data.ex_data.bond.cancel_buy_qty,
                                        market_data.ex_data.bond.cancel_sell_qty,
                                        market_data.ex_data.bond.cancel_buy_money,
                                        market_data.ex_data.bond.cancel_sell_money,
                                        market_data.ex_data.bond.total_buy_count,
                                        market_data.ex_data.bond.total_sell_count,
                                        market_data.ex_data.bond.duration_after_buy,
                                        market_data.ex_data.bond.duration_after_sell,
                                        market_data.ex_data.bond.num_bid_orders,
                                        market_data.ex_data.bond.num_ask_orders,
                                        market_data.ex_data.bond.instrument_status
                                        ))
        elif market_data.data_type == xlight.MARKETDATA_OPTION:
            ## 期权
            market_data_str += ("auction_price: {}, "
                                "auction_qty: {}, "
                                "last_enquiry_time: {}, "
            .format(
                market_data.ex_data.opt.auction_price,
                market_data.ex_data.opt.auction_qty,
                market_data.ex_data.opt.last_enquiry_time,
            ))

        print(market_data_str)

    def on_tick_by_tick(self, tbt_data):
        '''
        逐笔行情回调
        :param tbt_data: 逐笔行情数据
        :return:
        '''
        print("on_tick_by_tick")
        tbt_data_str = ("OnTickByTick："
                        "exchange_index： {},"
                        "security_code {}, "
                        "data_time: {}, "
                        "type: {}, ".format(
            int(tbt_data.exchange_index),
            tbt_data.security_code,
            tbt_data.data_time,
            tbt_data.type,
        ))
        if tbt_data.type == xlight.TBT_ENTRUST:
            ## 逐笔委托
            tbt_data_str += ("channel_no: {}, "
                             "seq: {}, "
                             "price: {}, "
                             "qty: {}, "
                             "side: {}, "
                             "ord_type: {}, "
                             "order_no: {}, "
                             "traded_qty: {}, "
            .format(
                tbt_data.data.entrust.channel_no,
                tbt_data.data.entrust.seq,
                tbt_data.data.entrust.price,
                tbt_data.data.entrust.qty,
                tbt_data.data.entrust.side,
                tbt_data.data.entrust.ord_type,
                tbt_data.data.entrust.order_no,
                tbt_data.data.entrust.traded_qty,
            ))
        elif tbt_data.type == xlight.TBT_TRADE:
            ## 逐笔成交
            tbt_data_str += ("channel_no: {}, "
                             "seq: {}, "
                             "price: {}, "
                             "qty: {}, "
                             "money: {}, "
                             "bid_no: {}, "
                             "ask_no: {}, "
                             "trade_flag: {}".format(
                tbt_data.data.trade.channel_no,
                tbt_data.data.trade.seq,
                tbt_data.data.trade.price,
                tbt_data.data.trade.qty,
                tbt_data.data.trade.money,
                tbt_data.data.trade.bid_no,
                tbt_data.data.trade.ask_no,
                tbt_data.data.trade.trade_flag
            ))
        elif tbt_data.type == xlight.TBT_STATE:
            ## 状态
            tbt_data_str += ("channel_no: {}, "
                             "seq: {}, "
                             "flag: {}".format(
                tbt_data.data.state.channel_no,
                tbt_data.data.state.seq,
                tbt_data.data.state.flag
            ))
        print(tbt_data_str)

    def on_query_static_quote_full_info(self, request_id, static_quote_full_infos, data_count, is_last, error_info):
        '''
        查询全量静态行情信息响应
        :param request_id: 请求ID
        :param static_quote_full_infos: 本次响应返回的全量静态行情信息列表，个数由data_count决定
        :param data_count: 本次响应返回的数据个数
        :param is_last: 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
        :param error_info: 查询发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
        :return:
        '''
        print("on_query_static_quote_full_info request_id: {}, data_count: {}, is_last: {}".format(
            request_id, data_count, is_last))
        if error_info:
            print("on_query_static_quote_full_info error_id: {}, error_msg: {}".format(
                error_info.error_id, error_info.error_msg))
            return

        py_static_quotes = xlight.StaticQuoteFullInfoArray.frompointer(static_quote_full_infos)
        for i in range(data_count):
            print("security_full_info[{}]: exchange_index={}, security_code={}, security_name={}, "
                  "security_type={}, qualification_class={}, is_registration={}, is_VIE={}, is_noprofit={}, "
                  "is_weighted_voting_rights={}, is_have_price_limit={}, upper_limit_price={}, "
                  "lower_limit_price={}, pre_close_price={}, price_tick={}, bid_qty_upper_limit={}, ".format(
                i,
                py_static_quotes[i].exchange_index,
                py_static_quotes[i].security_code,
                py_static_quotes[i].security_name,
                py_static_quotes[i].security_type,
                py_static_quotes[i].qualification_class,
                py_static_quotes[i].is_registration,
                py_static_quotes[i].is_VIE,
                py_static_quotes[i].is_noprofit,
                py_static_quotes[i].is_weighted_voting_rights,
                py_static_quotes[i].is_have_price_limit,
                py_static_quotes[i].upper_limit_price,
                py_static_quotes[i].lower_limit_price,
                py_static_quotes[i].pre_close_price,
                py_static_quotes[i].price_tick,
                py_static_quotes[i].bid_qty_upper_limit
            ))
            print("bid_qty_lower_limit={}, bid_qty_unit={}, ask_qty_upper_limit={}, ask_qty_lower_limit={}, "
                  "ask_qty_unit={}, market_bid_qty_upper_limit={}, market_bid_qty_lower_limit={}, "
                  "market_bid_qty_unit={}, market_ask_qty_upper_limit={}, market_ask_qty_lower_limit={}, "
                  "market_ask_qty_unit={}, security_status={}".format(
                py_static_quotes[i].bid_qty_lower_limit,
                py_static_quotes[i].bid_qty_unit,
                py_static_quotes[i].ask_qty_upper_limit,
                py_static_quotes[i].ask_qty_lower_limit,
                py_static_quotes[i].ask_qty_unit,
                py_static_quotes[i].market_bid_qty_upper_limit,
                py_static_quotes[i].market_bid_qty_lower_limit,
                py_static_quotes[i].market_bid_qty_unit,
                py_static_quotes[i].market_ask_qty_upper_limit,
                py_static_quotes[i].market_ask_qty_lower_limit,
                py_static_quotes[i].market_ask_qty_unit,
                py_static_quotes[i].security_status))


if __name__ == '__main__':
    ## 创建回调处理实例
    my_spi = MyQuoteSpi()  ### 确保Spi对象在整个程序运行期间都有效
    ## 创建API实例
    my_api = xlight.QuoteApi.create_quote_api()

    ## 配置
    xlt_quote_config = xlight.xlt_quote_config_t()
    xlt_quote_config.path = ""
    xlt_quote_config.log_level = xlight.XLTLogLevel_LOG_TRACE
    xlt_quote_config.local_address = "0.0.0.0"
    xlt_quote_config.agw_address = ["192.168.17.22:6062"]  ### AGW地址
    xlt_quote_config.is_efvi = False
    xlt_quote_config.level1_only = False
    xlt_quote_config.force_sequence = False

    ## 初始化，只能初始化一次
    if my_api.initialize(xlt_quote_config) == False:
        sys.exit(0)

    ## 注册回调
    my_api.register_spi(my_spi)

    ## 订阅全市场股票
    my_api.subscribe_all()
    # subscribe_list = ["000001", "000012", "118004"]
    # my_api.subscribe(subscribe_list, len(subscribe_list), xlight.EXCHANGE_SH)

    ## 登录请求
    login_request_id = get_next_request_id()
    result = my_api.login(request_id=login_request_id, account_name=global_account_name, password=global_password,
                          pub_key=global_pub_key)

    if result > 0:
        ## 登录请求发送失败
        logging.info("[request_id={}]Login error: {} ".format(login_request_id, result))
        sys.exit(0)
    else:
        logging.info("[request_id={}]Login request send! Wait for response (on_login). ".format(login_request_id))

    ## 等待登录响应
    global_login_event.wait()

    if global_login_result == False:
        ## 登录失败
        sys.exit(0)

    my_api.query_static_quote_full_info(get_next_request_id())

    while True:
        time.sleep(1)

    ## 登出
    my_api.logout()
