#pragma once
#include "xlt_api_define.h"
#include "xlt_api_quote_struct.h"

namespace x1{
#pragma pack(push, 1)

/**
 * @brief 行情配置
 */
typedef struct xlt_quote_config_t{
    char path[256] = ".";                   ///< 文件路径
    ApiLogLevel log_level = ApiLogLevel::LOG_INFO;  ///< 日志级别
    uint64_t mem_pool_size = 256;           ///< 内存池大小，单位MB
    address_t agw_address[32] = {"192.168.1.1:8080"};  ///< AGW地址列表
    address_t local_address = "0.0.0.0";    ///< 本地网卡地址
    bool is_efvi = false;                   ///< 是否使用EFVI
    bool level1_only = false;               ///< 仅接收level1行情，如果false，则根据用户权限优先接收level2行情
    bool force_sequence = false;            ///< 是否保序
} xlt_quote_config_t;

/**
 * @brief 股票、基金 等额外数据
 */
typedef struct xlt_market_data_stock_ex_data_t {
    int64_t total_bid_qty;          ///< 委托买入总量(SH,SZ)
    int64_t total_ask_qty;          ///< 委托卖出总量(SH,SZ)
    double ma_bid_price;            ///< 加权平均委买价格(SH,SZ)
    double ma_ask_price;            ///< 加权平均委卖价格(SH,SZ)
    double ma_bond_bid_price;       ///< 债券加权平均委买价格(SH)
    double ma_bond_ask_price;       ///< 债券加权平均委卖价格(SH)
    double yield_to_maturity;       ///< 债券到期收益率(SH)
    double iopv;                    ///< 基金实时参考净值(SH,SZ)
    int32_t etf_buy_count;          ///< ETF申购笔数(SH,SZ)
    int32_t etf_sell_count;         ///< ETF赎回笔数(SH,SZ)
    double etf_buy_qty;             ///< ETF申购数量(SH,SZ)
    double etf_buy_money;           ///< ETF申购金额(SH)
    double etf_sell_qty;            ///< ETF赎回数量(SH,SZ)
    double etf_sell_money;          ///< ETF赎回金额(SH)
    double total_warrant_exec_qty;  ///< 权证执行的总数量(SH)
    double warrant_lower_price;     ///< 债券质押式回购品种加权平均价(加权平均回购利率),该字段只对债券质押式协议回购有效,(元)(SH)
    double warrant_upper_price;     ///< IOPV 高精度值(SH)
    int32_t cancel_buy_count;       ///< 买入撤单笔数(SH)
    int32_t cancel_sell_count;      ///< 卖出撤单笔数(SH)
    double cancel_buy_qty;          ///< 买入撤单数量(SH)
    double cancel_sell_qty;         ///< 卖出撤单数量(SH)
    double cancel_buy_money;        ///< 买入撤单金额(SH)
    double cancel_sell_money;       ///< 卖出撤单金额(SH)
    int64_t total_buy_count;        ///< 买入总笔数(SH)
    int64_t total_sell_count;       ///< 卖出总笔数(SH)
    int32_t duration_after_buy;     ///< 买入委托成交最大等待时间(SH)
    int32_t duration_after_sell;    ///< 卖出委托成交最大等待时间(SH)
    int32_t num_bid_orders;         ///< 买方委托价位数(SH)
    int32_t num_ask_orders;         ///< 卖方委托价位数(SH)
    double pre_iopv;                ///< 基金T-1日净值(SH,SZ)
    int64_t r1;                     ///< 预留
    int64_t r2;                     ///< 预留
} xlt_market_data_stock_ex_data_t;

/**
 * @brief 债券额外数据
 */
typedef struct xlt_market_data_bond_ex_data_t {
    int64_t total_bid_qty;          ///< 委托买入总量(SH,SZ)
    int64_t total_ask_qty;          ///< 委托卖出总量(SH,SZ)
    double ma_bid_price;            ///< 加权平均委买价格(SZ)
    double ma_ask_price;            ///< 加权平均委卖价格(SZ)
    double ma_bond_bid_price;       ///< 债券加权平均委买价格(SH)
    double ma_bond_ask_price;       ///< 债券加权平均委卖价格(SH)
    double yield_to_maturity;       ///< 债券到期收益率(无意义)
    double match_lastpx;            ///< 匹配成交最近价(SZ)
    double ma_bond_price;           ///< 债券加权平均价格(SH)
    int64_t match_qty;              ///< 匹配成交成交量(SZ)
    double match_turnover;          ///< 匹配成交成交金额(SZ)
    double r4;                      ///< 预留
    double r5;                      ///< 预留
    double r6;                      ///< 预留
    double r7;                      ///< 预留
    double r8;                      ///< 预留
    int32_t cancel_buy_count;       ///< 买入撤单笔数(SH)
    int32_t cancel_sell_count;      ///< 卖出撤单笔数(SH)
    double cancel_buy_qty;          ///< 买入撤单数量(SH)
    double cancel_sell_qty;         ///< 卖出撤单数量(SH)
    double cancel_buy_money;        ///< 买入撤单金额(SH)
    double cancel_sell_money;       ///< 卖出撤单金额(SH)
    int64_t total_buy_count;        ///< 买入总笔数(SH)
    int64_t total_sell_count;       ///< 卖出总笔数(SH)
    int32_t duration_after_buy;     ///< 买入委托成交最大等待时间(SH)
    int32_t duration_after_sell;    ///< 卖出委托成交最大等待时间(SH)
    int32_t num_bid_orders;         ///< 买方委托价位数(SH)
    int32_t num_ask_orders;         ///< 卖方委托价位数(SH)
    char instrument_status[8];      ///< 时段(SH, SZ)，L1快照数据没有此字段;SH: 对应上交所InstrumentStatus字段；SZ: 启用前5位，分别表示：1=匹配成交 2=协商成交 3=点击成交 4=询价成交 5=竞买成交所处的交易阶段代码
}xlt_market_data_bond_ex_data_t;

/**
 * @brief 期权额外数据
 */
typedef struct xlt_market_data_option_ex_data_t {
    double  auction_price;          ///< 波段性中断参考价
    int64_t auction_qty;            ///< SH: 波段性中断集合竞价虚拟匹配量;SZ: 无意义
    int64_t last_enquiry_time;      ///< SH: 最近询价时间;SZ: 无意义

}xlt_market_data_option_ex_data_t;

/**
 * @brief 快照扩展数据
 */
typedef union {
    xlt_market_data_stock_ex_data_t  stk;  ///< 股票扩展字段
    xlt_market_data_option_ex_data_t opt;  ///< 期权扩展字段
    xlt_market_data_bond_ex_data_t  bond;  ///< 债券扩展字段
} xlt_market_data_ex_data_t;

/**
 * @brief 快照行情
 */
typedef struct xlt_market_data_t
{
    ExchangeIndex exchange_index;           ///< 交易所代码
    char	security_code[CONST_STR_SECURITY_CODE_LEN]; ///< 证券代码（不包含交易所信息），不带空格，以'\\0'结尾

    // 价格
    double	last_price;                     ///< 最新价
    double	pre_close_price;                ///< 昨收盘
    double	open_price;                     ///< 今开盘
    double	high_price;                     ///< 最高价
    double	low_price;                      ///< 最低价
    double	close_price;                    ///< 今收盘

    // 期权数据
    int64_t pre_total_long_position;        ///< 昨日持仓量(张)(目前未填写)
    int64_t	total_long_position;            ///< 持仓量(张)
    double	pre_settle_price;               ///< 昨日结算价（SH）
    double	settle_price;                   ///< 今日结算价（SH）

    // 涨跌停
    double	upper_limit_price;              ///< 涨停价
    double	lower_limit_price;              ///< 跌停价
    double	pre_delta;                      ///< 预留
    double	curr_delta;                     ///< 预留

    int64_t data_time;                      ///< 时间，格式为YYYYMMDDHHMMSSsss

    // 量额数据
    int64_t	qty;                            ///< 数量，为总成交量（单位股，与交易所一致）
    double	turnover;                       ///< 成交金额，为总成交金额（单位元，与交易所一致）
    double	avg_price;                      ///< 预留(无意义)

    // 买卖盘
    double bid[10];                         ///< 十档申买价
    double	ask[10];                        ///< 十档申卖价
    int64_t	bid_qty[10];                    ///< 十档申买量
    int64_t	ask_qty[10];                    ///< 十档申卖量
    int64_t	bid_num_orders[10];             ///< 十档申买委托笔数
    int64_t	ask_num_orders[10];             ///< 十档申卖委托笔数

    // 委托队列
    int32_t bid_queue_cnt;                  ///< 买一队列发布委托笔数
    int32_t ask_queue_cnt;                  ///< 卖一队列发布委托笔数
    int64_t bid_queue[50];                  ///< 买一队列数量;
    int64_t ask_queue[50];                  ///< 卖一队列数量;

    // 额外数据
    int64_t trades_count;                   ///< 成交笔数
    char ticker_status[8];                  ///< 当前交易状态说明

    /// 对于新三板行情来说，以下结构和字段均无效
    xlt_market_data_ex_data_t ex_data;      //< 扩展数据
    MarketDataType data_type;               ///< 决定了ex_data是哪种数据类型
} xlt_market_data_t;

/**
 * @brief 逐笔委托
 */
typedef struct xlt_tick_by_tick_entrust_t {
    int32_t channel_no;                     ///< 频道代码
    int64_t seq;                            ///< 业务序号
    double  price;                          ///< 委托价格
    int64_t qty;                            ///< SH: 剩余委托数量(balance); SZ: 委托数量
    char  side;                             ///< SH: 'B':买; 'S':卖; SZ: '1':买; '2':卖; 'G':借入; 'F':出借
    char ord_type;                          ///< SH: 'A': 增加; 'D': 删除; SZ: 订单类别: '1': 市价; '2': 限价; 'U': 本方最优
    int64_t order_no;                       ///< SH: 原始订单号; SZ: 无意义
    int64_t traded_qty;                     ///< SH: 已成交的委托数量;SZ: 无意义
}xlt_tick_by_tick_entrust_t;

/**
 * @brief 逐笔成交
 */
typedef struct xlt_tick_by_tick_trade_t {
    int32_t channel_no;                     ///< 频道代码
    int64_t seq;                            ///< SH,SZ一致，业务序号
    double price;                           ///< 成交价格
    int64_t qty;                            ///< 成交量
    double money;                           ///< 成交金额(仅适用上交所)
    int64_t bid_no;                         ///< SH: 买方订单号;SZ:买方委托索引
    int64_t ask_no;                         ///< SH: 卖方订单号; SZ: 卖方委托索引
    char trade_flag;                        ///< SH: 内外盘标识('B':主动买; 'S':主动卖; 'N':未知);SZ: 成交标识('4':撤; 'F':成交)
}xlt_tick_by_tick_trade_t;

/**
 * @brief 逐笔状态订单
 */
typedef struct xlt_tick_by_tick_status_t {
    int32_t channel_no;                     ///< 频道代码
    int64_t seq;                            ///< 同一channel_no内连续
    char flag[8];                           ///< 状态信息
}xlt_tick_by_tick_status_t;

/**
 * @brief 逐笔数据联合体
 */
typedef union {
    xlt_tick_by_tick_entrust_t entrust; ///< 逐笔委托
    xlt_tick_by_tick_trade_t     trade; ///< 逐笔成交
    xlt_tick_by_tick_status_t    state; ///< 状态
} xlt_tick_by_tick_data_t;

/**
 * @brief 逐笔数据信息
 */
typedef struct xlt_tick_by_tick_t {
    ExchangeIndex exchange_index;       ///< 交易所代码
    char security_code[CONST_STR_SECURITY_CODE_LEN];  ///< 合约代码（不包含交易所信息），不带空格，以'\\0'结尾
    int64_t data_time;                  ///< 委托时间 or 成交时间
    TbtType type;                       ///< 委托 or 成交 or 状态
    xlt_tick_by_tick_data_t data;       ///< 逐笔数据

} xlt_tick_by_tick_t;

#pragma pack(pop)
}
