#pragma once
#include "xlt_data_type.h"

namespace x1{
#pragma pack(push, 1)
/**
 * @brief 订单状态通知(初始\已报\结束)
 */
typedef struct {
    int64_t sequence;                     ///< 消息序号(大于0有效)
    char report_id[CONST_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;                     ///< 报单标识
    uint32_t report_num;                 ///< 结束状态时填写订单的成交回报数量
    OrderBriefStatus order_brief_status; ///< 订单简要状态：1：初始；2：已报；3：结束
} xlt_order_status_notice_t;

/**
 * @brief 新订单申报成功响应
 */
typedef struct {
    int64_t sequence;                     ///< 消息序号(大于0有效)
    char report_id[CONST_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;                     ///< 报单标识
    OrderStatus order_status;      ///< 订单状态
    quantity_t leaves_quantity;               ///< 剩余数量
    quantity_t cancel_quantity;                  ///< 撤单数量
} xlt_order_response_t;

/**
 * @brief 撤单申报成功响应
 */
typedef struct {
    int64_t sequence;                     ///< 消息序号(大于0有效)
    char report_id[CONST_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;                     ///< 报单标识
    uint64_t origin_xid;              ///< 原始订单标识（撤单申报时有意义）
    OrderStatus origin_order_status; ///< 原始订单状态 (部撤/全撤)
    quantity_t cancel_quantity;                  ///< 撤单数量
} xlt_cancel_response_t;

/**
 * @brief 成交回报
 */
typedef struct {
    int64_t sequence;                     ///< 消息序号(大于0有效)
    char report_id[CONST_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;                     ///< 报单标识
    OrderStatus order_status;      ///< 订单状态
    price_t price;                    ///< 成交价格，该笔成交回报的成交价格，放大10000倍
    quantity_t quantity;                 ///< 成交数量，该笔成交回报的成交数量
    quantity_t leaves_quantity;          ///< 剩余数量
} xlt_trade_report_t;

/**
 * @brief 申报失败响应（新订单申报失败，撤单失败）
 */
typedef struct {
    int64_t sequence;                     ///< 消息序号(大于0有效)
    char report_id[CONST_REPORT_ID_LEN]; ///< 回报标识
    uint64_t xid;              ///< 撤单标识
    uint64_t origin_xid;              ///< 原始订单标识
    int error_id;                     ///< 错误代码
    char error_msg[CONST_ERROR_MSG_LEN];  ///< 错误信息，如果是交易所返回的错误在该字段中会包含交易所错误码，其他情况该字段会填写具体的错误原因
} xlt_order_error_response_t;

/**
 * @brief 订单信息结构体
 */
typedef struct {
    uint64_t xid;                     ///< 报单标识
    uint64_t origin_xid;              ///< 撤单标识，在xlight系统中唯一  origin_xid
    OrderStatus order_status;         ///< 订单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
    char security_code[CONST_STR_SECURITY_CODE_LEN]; ///< 证券代码
    ExchangeIndex exchange_index;     ///< 交易市场
    OrdType order_price_type;         ///< 报单价格类型
    Side side;                        ///< 买卖方向
    BusinessType business_type;       ///< 业务类型
    price_t order_price;              ///< 委托价格
    quantity_t order_quantity;        ///< 委托数量
    amount_t order_amount;            ///< 委托金额
    amount_t order_fee;               ///< 委托费用
    quantity_t traded_quantity;       ///< 成交数量
    amount_t traded_amount;           ///< 成交金额
    amount_t traded_fee;              ///< 成交费用
    amount_t traded_fix_fee;          ///< 成交固定费用
    uint32_t traded_count;            ///< 成交笔数
    quantity_t leaves_quantity;       ///< 剩余数量
    quantity_t cancel_quantity;       ///< 撤单数量
    int64_t insert_time;              ///< 委托时间，格式为YYYYMMDDHHMMSSsss
    int64_t traded_time;              ///< 最后一笔成交时间，格式为YYYYMMDDHHMMSSsss
    char cl_order_id[CONST_CL_ORD_ID_LEN];  ///< 报盘合同号
    int error_id;                     ///< 错误代码
    char error_msg[CONST_ERROR_MSG_LEN];  ///< 错误信息，如果是交易所返回的错误在该字段中会包含交易所错误码，其他情况该字段会填写具体的错误原因
} xlt_order_info_t;

/**
 * @brief 持仓结构体
 */
typedef struct {
    char security_code[CONST_STR_SECURITY_CODE_LEN]; ///< 证券代码
    PositionSecurityType position_security_type; ///< 持仓类型(区分股份是否为配售)
    ExchangeIndex exchange_index;        ///< 交易市场
    quantity_t initial_quantity;         ///< 日初持仓数量
    quantity_t total_quantity;           ///< 总持仓
    quantity_t sellable_quantity;        ///< 可卖持仓
    quantity_t frozen_quantity;          ///< 卖出冻结数量
} xlt_position_info_t;

/**
 * @brief 账户资金信息
 */
typedef struct {
    amount_t available_amount;      ///< 可用资金
    amount_t initial_amount;        ///< 日初可用资金
    amount_t withholding_amount;    ///< 系统预扣的资金（买入未成交冻结资金）
    amount_t fund_buy_amount;       ///< 累计买入成交金额
    amount_t fund_buy_fee;          ///< 累计买入成交费用
    amount_t fund_sell_amount;      ///< 累计卖出成交金额
    amount_t fund_sell_fee;         ///< 累计卖出成交费用
} xlt_asset_info_t;
#pragma pack(pop)
}


