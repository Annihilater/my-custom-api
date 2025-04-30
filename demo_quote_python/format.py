def format_order_insert_info(xid, order_insert_info):
    return ("Order insert info: xid={}, order_client_id={}, security_code={}, "
            "exchange_id={}, price={}, quantity={}, order_price_type={}, side={}, business_type={}"
    .format(
        xid,
        order_insert_info.order_client_id,  # 报单引用，由客户自定义
        order_insert_info.security_code,  # 证券代码
        order_insert_info.exchange_index,  # 交易市场
        order_insert_info.price,  # 价格放大10000倍
        order_insert_info.quantity,  # 数量
        order_insert_info.order_price_type,  # 报单价格类型
        order_insert_info.side,  # 买卖方向
        order_insert_info.business_type,  # 业务类型
    ))


def format_order_cancel_info(xid, order_cancel_info):
    return ("Order cancel info: xid={}, order_client_id={}, origin_xid={}"
    .format(
        xid,  # 撤单委托ID
        order_cancel_info.order_client_id,  # 撤单引用，由客户自定义
        order_cancel_info.origin_xid  # 被撤订单委托ID
    ))


def format_order_response(order_response):
    return ("Order response: report_id={}, xid={}, order_client_id={}, orig_xid={}, orig_order_client_id={}, "
            "security_code={}, exchange_index={}, business_type={}, side={}, price={}, quantity={}, price_type={}, "
            "leaves_qty={}, cum_qty={}, cxl_qty={}, exec_type={}, order_status={}, error_id={}, error_msg={}, "
            "report_time={}"
    .format(
        order_response.report_id,  # 回报标识
        order_response.xid,  # 报单标识
        order_response.order_client_id,  # 报单引用
        order_response.orig_xid,  # 原始订单标识（撤单申报时有意义）
        order_response.orig_order_client_id,  # 原始订单操作引用，用户定义（撤单申报时有意义）
        order_response.security_code,  # 证券代码
        order_response.exchange_index,  # 交易市场
        order_response.business_type,  # 业务类型:XLT_BUSINESS_TYPE_CASH, XLT_BUSINESS_TYPE_BOND_MATCH,
        # XLT_BUSINESS_TYPE_ETF, XLT_BUSINESS_TYPE_ISSUE, XLT_BUSINESS_TYPE_ALLOTMENT,
        # XLT_BUSINESS_TYPE_BOND_CONVERT, XLT_BUSINESS_TYPE_PLEDGE_STYLE_REPO
        order_response.side,  # 买卖方向
        order_response.price,  # 报单价格
        order_response.quantity,  # 报单数量
        order_response.order_price_type,  # 订单价格类型
        order_response.leaves_qty,  # 剩余数量
        order_response.cum_qty,  # 累计执行数量
        order_response.cxl_qty,  # 撤单数量
        order_response.exec_type,  # 执行类型
        order_response.order_status,  # 订单状态  TODO 此字段待确定是否会存在
        order_response.error_id,  # 错误代码
        order_response.error_msg,  # 错误信息
        order_response.report_time  # 交易所回报时间，格式为YYYYMMDDHHMMSSsss
    ))


def format_order_reject(order_reject):
    return ("Order reject: report_id={}, xid={}, order_client_id={}, orig_xid={}, orig_order_client_id={}, "
            "security_code={}, exchange_index={}, business_type={}, side={}, price={}, quantity={},"
            "order_price_type={}, error_id={}, error_msg={}"
    .format(
        order_reject.report_id,  # 回报标识
        order_reject.xid,  # 报单标识
        order_reject.order_client_id,  # 报单引用
        order_reject.orig_xid,  # 原始订单标识（撤单申报时有意义）
        order_reject.orig_order_client_id,  # 原始订单操作引用，用户定义（撤单申报时有意义）
        order_reject.security_code,  # 证券代码
        order_reject.exchange_index,  # 交易市场
        order_reject.business_type,  # 业务类型:XLT_BUSINESS_TYPE_CASH, XLT_BUSINESS_TYPE_BOND_MATCH,
        # XLT_BUSINESS_TYPE_ETF, XLT_BUSINESS_TYPE_ISSUE, XLT_BUSINESS_TYPE_ALLOTMENT,
        # XLT_BUSINESS_TYPE_BOND_CONVERT, XLT_BUSINESS_TYPE_PLEDGE_STYLE_REPO
        order_reject.side,  # 买卖方向
        order_reject.price,  # 报单价格
        order_reject.quantity,  # 报单数量
        order_reject.order_price_type,  # 订单价格类型
        order_reject.error_id,  # 错误代码
        order_reject.error_msg,  # 交易所回报时间，格式为YYYYMMDDHHMMSSsss
    ))


def format_order_cancel_fail(order_cancel_fail):
    return ("Order cancel fail: report_id={}, xid={}, order_client_id={}, orig_xid={}, "
            "orig_order_client_id={}, security_code={}, exchange_index={}, business_type={}, error_id={}, "
            "error_msg={}"
    .format(
        order_cancel_fail.report_id,  # 回报标识
        order_cancel_fail.xid,  # 撤单标识
        order_cancel_fail.order_client_id,  # 撤单引用
        order_cancel_fail.orig_xid,  # 原始订单标识（撤单申报时有意义）
        order_cancel_fail.orig_order_client_id,  # 原始订单操作引用，用户定义（撤单申报时有意义）
        order_cancel_fail.security_code,  # 证券代码
        order_cancel_fail.exchange_index,  # 交易市场
        order_cancel_fail.business_type,  # 业务类型:XLT_BUSINESS_TYPE_CASH, XLT_BUSINESS_TYPE_BOND_MATCH,
        # XLT_BUSINESS_TYPE_ETF, XLT_BUSINESS_TYPE_ISSUE, XLT_BUSINESS_TYPE_ALLOTMENT,
        # XLT_BUSINESS_TYPE_BOND_CONVERT, XLT_BUSINESS_TYPE_PLEDGE_STYLE_REPO
        order_cancel_fail.error_id,  # 错误代码
        order_cancel_fail.error_msg,  # 交易所回报时间，格式为YYYYMMDDHHMMSSsss
    ))


def format_trade_report(trade_report):
    return ("Trade report: report_id={}, xid={}, order_client_id={}, security_code={}, "
            "exchange_index={}, business_type={}, side={}, exec_id={}, exec_type={}, order_status={}, "
            "price={}, quantity={}, leaves_qty={}, report_time={}"
    .format(
        trade_report.report_id,  # 回报标识
        trade_report.xid,  # 报单标识
        trade_report.order_client_id,  # 撤单引用
        trade_report.security_code,  # 证券代码
        trade_report.exchange_index,  # 交易市场
        trade_report.business_type,  # 业务类型:XLT_BUSINESS_TYPE_CASH, XLT_BUSINESS_TYPE_BOND_MATCH,
        # XLT_BUSINESS_TYPE_ETF, XLT_BUSINESS_TYPE_ISSUE, XLT_BUSINESS_TYPE_ALLOTMENT,
        # XLT_BUSINESS_TYPE_BOND_CONVERT, XLT_BUSINESS_TYPE_PLEDGE_STYLE_REPO
        trade_report.side,  # 买卖方向
        trade_report.exec_id,  # 成交编号。深交所，上交所每笔交易唯一。
        trade_report.exec_type,  # 执行类型
        trade_report.order_status,  # 订单状态
        trade_report.price,  # 成交价格，该笔成交回报的成交价格，放大10000倍
        trade_report.quantity,  # 成交数量，该笔成交回报的成交数量
        trade_report.leaves_qty,  # 剩余数量
        trade_report.report_time,  # 交易所回报时间，格式为YYYYMMDDHHMMSSsss
    ))


def format_position(position):
    return ("Position: security_code={}, security_name={}, exchange_index={}, total_qty={}, "
            "sellable_qty={}, avg_price={}, unrealized_pnl={}, yesterday_position={}, purchase_redeemable_qty={}, "
            "position_security_type={}, profit_price={}, buy_cost={}, profit_cost={}, market_value={}, "
            "last_buy_cost={}, last_profit_cost={}"
    .format(
        position.security_code,  # 证券代码
        position.security_name,  # 证券名称
        position.exchange_index,  # 交易市场
        position.total_qty,  # 总持仓
        position.sellable_qty,  # 可卖持仓
        position.avg_price,  # 持仓成本
        position.unrealized_pnl,  # 浮动盈亏（保留字段）
        position.yesterday_position,  # 昨日持仓
        position.purchase_redeemable_qty,  # 今日申购赎回数量（申购和赎回数量不可能同时存在，因此可以共用一个字段）
        position.position_security_type,  # 持仓类型(此字段所有账户都可能用到，可以用来区分股份是否为配售)
        position.profit_price,  # 盈亏成本价
        position.buy_cost,  # 买入成本
        position.profit_cost,  # 盈亏成本
        position.market_value,  # 持仓市值（此字段目前只有期权账户有值，其他类型账户为0）
        position.last_buy_cost,  # 昨日买入成本
        position.last_profit_cost  # 昨日盈亏成本
    ))


def format_asset(asset):
    return ("Asset: total_asset={}, buying_power={}, initial_buying_power={}, "
            "security_asset={}, fund_buy_amount={}, fund_buy_fee={}, "
            "fund_sell_amount={}, fund_sell_fee={}, withholding_amount={}"
    .format(
        asset.total_asset,  # 总资产
        asset.buying_power,  # 可用资金
        asset.initial_buying_power,  # 日初可用资金
        asset.security_asset,  # 证券资产（保留字段，目前为0）
        asset.fund_buy_amount,  # 累计买入成交证券占用资金（仅限现货账户/期权账户，信用账户暂不可用）
        asset.fund_buy_fee,  # 累计买入成交交易费用（仅限现货账户/期权账户，信用账户暂不可用）
        asset.fund_sell_amount,  # 累计卖出成交证券所得资金（仅限现货账户/期权账户，信用账户暂不可用）
        asset.fund_sell_fee,  # 累计卖出成交交易费用（仅限现货账户/期权账户，信用账户暂不可用）
        asset.withholding_amount  # xlight系统预扣的资金（包括买卖股票时预扣的交易资金+预扣手续费）
    ))


def format_order(order):
    return ("Order xid: {}, order_client_id: {}, cancel_xid: {}, cancel_order_client_id: {}, "
            "security_code: {}, exchange_id: {}, price: {}, quantity: {}, order_price_type: {}, "
            "side: {}, business_type: {}, qty_traded: {}, qty_left: {}, "
            "insert_time: {}, update_time: {}, cancel_time: {}, trade_amount: {}, order_local_id: {}, "
            "order_status: {}, order_exch_id: {}, error_id: {}, error_msg: {}"
    .format(
        order.xid,                  # 报单标识
        order.order_client_id,            # 报单引用
        order.cancel_xid,                 # 撤单标识
        order.cancel_order_client_id,     # 撤单引用
        order.security_code,              # 证券代码
        order.exchange_index,             # 交易市场
        order.price,                      # 报单价格
        order.quantity,                   # 报单数量
        order.order_price_type,           # 报单价格类型
        order.side,                       # 买卖方向
        order.business_type,              # 业务类型
        order.qty_traded,                 # 累计成交数量
        order.qty_left,                   # 剩余数量
        order.insert_time,                # 报单时间
        order.update_time,                # 最后修改时间
        order.cancel_time,                # 撤单时间
        order.trade_amount,               # 成交金额
        order.order_local_id,             # 本地报单编号
        order.order_status,               # 订单状态
        order.order_exch_id,              # 交易所报单编号
        order.error_id,                   # 错误代码
        order.error_msg                   # 错误信息
    ))
