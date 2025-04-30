#pragma once

#include "xlight_struct.h"
#include "xlight_trade_data_types.h"


namespace xlight::api {

typedef struct xlt_trade_config_t {
    char path[256] = ".";                 ///< 文件路径
    XLTLogLevel log_level = XLTLogLevel::LOG_INFO;  ///< 日志级别
    uint64_t mem_pool_size = 256;     ///< 内存池大小，单位MB
    xlt_address_t agw_address[32] = {"192.168.1.1:8080"};  ///< AGW地址列表
    char local_address[32] = "0.0.0.0"; ///< 本地网卡地址
    char order_local_address[32] = "0.0.0.0"; ///< 本地委托网卡地址
    char join_test_fon[32] = {0};  // 联调测试FON 委托地址
    uint64_t join_test_account_index = 0; // 联调测试，账号id
} xlt_trade_config_t;


/**
 * @brief 新订单请求
 */
typedef struct {
    uint32_t order_client_id;         ///< 报单引用，由客户自定义
    char security_code[XLT_SECURITY_CODE_LEN]; ///< 证券代码
    XLTExchangeIndex exchange_index;     ///< 交易市场
    int64_t price;                    ///< 价格放大10000倍
    int64_t quantity;                 ///< 数量
    XLTOrderPriceType order_price_type; ///< 报单价格类型
    XLTSide side;                     ///< 买卖方向
    XLTBusinessType business_type;    ///< 业务类型
} xlt_order_insert_info_t;

/**
 * @brief 撤单请求
 */
typedef struct {
    uint32_t order_client_id;         ///< 报单引用，由客户自定义
    uint64_t origin_xid;              ///< 被撤委托ID
} xlt_order_cancel_info_t;

/**
 * @brief 订单状态通知(初始\已报\结束)
 */
typedef struct {
//    int64_t seq;                     ///< 消息序号(大于0有效)
//    char report_id[XLT_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;                     ///< 报单标识
    uint32_t order_client_id;         ///< 报单引用，由客户自定义
    XLTOrderBriefStatus order_brief_status; ///< 订单简要状态：1：初始；2：已报；3：结束
} xlt_order_status_notice_t;

/**
 * @brief 订单拒绝通知(包含xlight系统内部委托拒单，xlight系统内部撤单拒单，交易网关订单委托拒绝，交易网关订单撤单拒绝。)
 */
typedef struct {
    int64_t seq;                     ///< 消息序号(大于0有效)
    char report_id[XLT_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;                     ///< 报单标识
    uint32_t order_client_id;         ///< 报单引用
    uint64_t orig_xid;                ///< 原始订单标识（撤单申报时有意义）
    uint32_t orig_order_client_id;    ///< 原始订单操作引用，用户定义（撤单申报时有意义）
    char security_code[XLT_SECURITY_CODE_LEN]; ///< 证券代码
    XLTExchangeIndex exchange_index;  ///< 交易市场
    XLTBusinessType business_type;    ///< 业务类型
    XLTSide side;                     ///< 买卖方向
    int64_t price;                    ///< 价格放大10000倍
    int64_t quantity;                 ///< 委托数量
    XLTOrderPriceType order_price_type; ///<报单价格类型
    int error_id;                     ///< 错误代码
    char error_msg[XLT_ERR_MSG_LEN];  ///< 错误信息，如果是交易所返回的错误在该字段中会包含交易所错误码，其他情况该字段会填写具体的错误原因
    int64_t report_time;              ///< 拒单时间，格式为YYYYMMDDHHMMSSsss
} xlt_order_reject_t;

/**
 * @brief 申报响应及撤单成功响应
 */
typedef struct {
    int64_t seq;                     ///< 消息序号(大于0有效)
    char report_id[XLT_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;                     ///< 报单标识
    uint32_t order_client_id;         ///< 报单引用
    uint64_t orig_xid;                ///< 原始订单标识（撤单申报时有意义）
    uint32_t orig_order_client_id;          ///< 原始订单操作引用，用户定义（撤单申报时有意义）
    char security_code[XLT_SECURITY_CODE_LEN]; ///< 证券代码
    XLTExchangeIndex exchange_index;     ///< 交易市场
    XLTBusinessType business_type;    ///< 业务类型
    XLTSide side;                     ///< 买卖方向
    int64_t price;                    ///< 价格放大10000倍
    int64_t quantity;                 ///< 委托数量
    XLTOrderPriceType order_price_type; ///<报单价格类型
    int64_t leaves_qty;               ///< 剩余数量
    int64_t cum_qty;                  ///< 累计执行数量
    int64_t cxl_qty;                  ///< 撤单数量
    char exec_type;                   ///< 执行类型
    XLTOrderStatus order_status;      ///< 订单状态
    int error_id;                     ///< 错误代码，仅拒绝响应时有意义
    char error_msg[XLT_ERR_MSG_LEN];  ///< 错误信息，仅拒绝响应时有意义
    int64_t report_time;              ///< 交易所回报时间，格式为YYYYMMDDHHMMSSsss
} xlt_order_response_t;

/**
 * @brief 成交回报通知
 */
typedef struct {
    int64_t seq;                     ///< 消息序号(大于0有效)
    char report_id[XLT_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;                     ///< 报单标识
    uint32_t order_client_id;         ///< 报单引用
    char security_code[XLT_SECURITY_CODE_LEN]; ///< 证券代码
    XLTExchangeIndex exchange_index;     ///< 交易市场
    XLTBusinessType business_type;    ///< 业务类型
    XLTSide side;                     ///< 买卖方向
    char exec_id[XLT_EXEC_ID_LEN];    ///< 成交编号。深交所，上交所每笔交易唯一。
    char exec_type;                   ///< 执行类型
    XLTOrderStatus order_status;      ///< 订单状态
    int64_t price;                    ///< 成交价格，该笔成交回报的成交价格，放大10000倍
    int64_t quantity;                 ///< 成交数量，该笔成交回报的成交数量
    int64_t leaves_qty;               ///< 剩余数量
    int64_t report_time;              ///< 交易所回报时间，格式为YYYYMMDDHHMMSSsss
} xlt_trade_report_t;

/**
 * @brief 撤单失败通知
 */
typedef struct {
    int64_t seq;                     ///< 消息序号(大于0有效)
    char report_id[XLT_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;              ///< 撤单标识
    uint32_t order_client_id;        ///< 撤单引用
    uint64_t orig_xid;                ///< 原始订单标识
    uint32_t orig_order_client_id;          ///< 原始订单报单引用
    char security_code[XLT_SECURITY_CODE_LEN]; ///< 证券代码
    XLTExchangeIndex exchange_index;     ///< 交易市场
    XLTBusinessType business_type;    ///< 业务类型
    int error_id;                     ///< 错误代码
    char error_msg[XLT_ERR_MSG_LEN];  ///< 错误信息，如果是交易所返回的错误在该字段中会包含交易所错误码，其他情况该字段会填写具体的错误原因
} xlt_order_cancel_fail_t;


/**
 * @brief 报单查询请求-条件查询
 */
typedef struct {
    uint64_t xid;                     ///< 需要查询的委托编号，如果为0则根据后续条件进行查询，如果不为0，则只查询指定订单，忽略后续查询条件
    char security_code[XLT_SECURITY_CODE_LEN]; ///<证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
    int64_t begin_time;               ///< 格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t end_time;                 ///< 格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    uint8_t query_unfinished;         ///< 是否只查询未完成订单：1是，0否
} xlt_order_query_param_t;

/**
 * @struct xlt_order_query_by_page_param_t
 * @brief 查询订单请求-分页查询
 */
typedef struct {
    int64_t req_count;                ///< 需要查询的订单条数
    int64_t reference;                ///< 上一次收到的查询订单结果中带回来的索引，如果是从头查询，请置0
    int64_t reserved;                 ///< 保留字段
} xlt_order_query_by_page_param_t;


/**
 * @brief 订单信息结构体
 */
typedef struct {
    uint64_t xid;                     ///< 报单标识
    uint32_t order_client_id;         ///< 报单引用，用户自定义
    uint64_t cancel_xid;              ///< 撤单标识，在xlight系统中唯一
    uint32_t cancel_order_client_id;  ///< 撤单操作引用，用户自定义
    char security_code[XLT_SECURITY_CODE_LEN]; ///< 证券代码
    XLTExchangeIndex exchange_index;     ///< 交易市场
    int64_t price;                    ///< 价格
    int64_t quantity;                 ///< 数量，此订单的报单数量
    XLTOrderPriceType order_price_type; ///<报单价格类型
    XLTSide side;                     ///< 买卖方向
    XLTBusinessType business_type;    ///< 业务类型
    int64_t qty_traded;               ///< 今成交数量，为此订单累计成交数量
    int64_t qty_left;                 ///< 剩余数量，当撤单成功时，表示撤单数量
    int64_t insert_time;              ///< 委托时间，格式为YYYYMMDDHHMMSSsss
    int64_t update_time;              ///< 最后修改时间，格式为YYYYMMDDHHMMSSsss
    int64_t cancel_time;              ///< 撤销时间，格式为YYYYMMDDHHMMSSsss
    int64_t trade_amount;             ///< 成交金额，为此订单的成交总金额
    char order_local_id[XLT_ORDER_LOCAL_ID_LEN];  ///< 本地报单编号 OMS生成的单号，不等同于order_xid，为服务器传到报盘的单号
    XLTOrderStatus order_status;      ///< 订单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
    char order_exch_id[XLT_ORDER_EXCH_ID_LEN]; ///<报单编号 --交易所单号，上交所为空，深交所有此字段
    int error_id;                     ///< 错误代码
    char error_msg[XLT_ERR_MSG_LEN];  ///< 错误信息，如果是交易所返回的错误在该字段中会包含交易所错误码，其他情况该字段会填写具体的错误原因
} xlt_order_info_t;


/**
 * @brief 查询股票持仓情况
 */
typedef struct {
    char security_code[XLT_SECURITY_CODE_LEN]; ///< 证券代码
    char security_name[XLT_SECURITY_NAME_LEN]; ///< 证券名称
    XLTExchangeIndex exchange_index;        ///< 交易市场
    int64_t total_qty;                ///< 总持仓
    int64_t sellable_qty;             ///< 可卖持仓
    int64_t avg_price;                ///< 持仓成本
    int64_t unrealized_pnl;           ///< 浮动盈亏（保留字段）
    int64_t yesterday_position;       ///< 昨日持仓
    int64_t purchase_redeemable_qty;  ///< 今日申购赎回数量（申购和赎回数量不可能同时存在，因此可以共用一个字段）

    XLTPositionSecurityType position_security_type;///< 持仓类型(此字段所有账户都可能用到，可以用来区分股份是否为配售)

    //以下为现货用户关心字段
    int64_t profit_price;        ///< 盈亏成本价
    int64_t buy_cost;            ///< 买入成本
    int64_t profit_cost;         ///< 盈亏成本

    int64_t market_value;        ///< 持仓市值（此字段目前只有期权账户有值，其他类型账户为0）

    int64_t last_buy_cost;       ///< 昨日买入成本
    int64_t last_profit_cost;    ///< 昨日盈亏成本

} xlt_position_info_t;


/**
 * @brief 账户资金查询响应结构体
 */
typedef struct {
    int64_t total_asset;            ///< 总资产（现货账户/期权账户参考公式：总资产 = 可用资金 + 证券资产（目前为0）+ 预扣的资金），（信用账户参考公式：总资产 = 可用资金 +
    // 融券卖出所得资金余额 + 证券资产+ 预扣的资金）
    int64_t buying_power;           ///< 可用资金
    int64_t initial_buying_power;   ///< 日初可用资金
    int64_t security_asset;         ///< 证券资产（保留字段，目前为0）
    int64_t fund_buy_amount;        ///< 累计买入成交证券占用资金（仅限现货账户/期权账户，信用账户暂不可用）
    int64_t fund_buy_fee;           ///< 累计买入成交交易费用（仅限现货账户/期权账户，信用账户暂不可用）
    int64_t fund_sell_amount;       ///< 累计卖出成交证券所得资金（仅限现货账户/期权账户，信用账户暂不可用）
    int64_t fund_sell_fee;          ///< 累计卖出成交交易费用（仅限现货账户/期权账户，信用账户暂不可用）
    int64_t withholding_amount;     ///< xlight系统预扣的资金（包括买卖股票时预扣的交易资金+预扣手续费）

} xlt_asset_info_t;

typedef union {
    xlt_order_reject_t order_reject;
    xlt_order_response_t order_response;
    xlt_trade_report_t trade_report;
    xlt_order_cancel_fail_t order_cancel_fail;
} xlt_detail_data_t;

typedef struct {
    uint64_t xid;
    XLTReportType detail_type;
    xlt_detail_data_t data;
} xlt_order_detail_t;

}
