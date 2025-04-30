#pragma once
#include <cstdint>
#include "xlight_quote_data_types.h"
#include "xlight_struct.h"

namespace xlight::api{

/**
 * @brief 行情配置
 */
typedef struct xlt_quote_config_t{
    char path[256] = ".";                 ///< 文件路径
    XLTLogLevel log_level = XLTLogLevel::LOG_INFO;  ///< 日志级别
    uint64_t mem_pool_size = 256;     ///< 内存池大小，单位MB
    xlt_address_t agw_address[32] = {"192.168.1.1:8080"};  ///< AGW地址列表
    char local_address[32] = "0.0.0.0"; ///< 本地网卡地址
    bool is_efvi = false;                   ///< 是否使用EFVI
    bool level1_only = false;               ///< 仅接收level1行情，如果false，则根据用户权限优先接收level2行情
    bool force_sequence = false;            ///< 是否保序
} xlt_quote_config_t;


/**
 * @brief 股票行情静态信息
 */
typedef struct xlt_static_quote_info_t {
    ///交易所代码
    XLTExchangeType exchange_index;
    ///合约代码（不包含交易所信息），不带空格，以'\\0'结尾
    char    security_code[XLT_SECURITY_CODE_LEN];
    /// 合约名称
    char    security_name[XLT_SECURITY_NAME_LEN];
    /// 合约类型
    XLTSecurityType security_type;
    ///昨收盘
    double  pre_close_price;
    ///涨停板价
    double  upper_limit_price;
    ///跌停板价
    double  lower_limit_price;
    ///最小变动价位
    double  price_tick;
    /// 合约最小交易量(买)
    int32_t  buy_qty_unit;
    /// 合约最小交易量(卖)
    int32_t sell_qty_unit;
} xlt_static_quote_info_t;

/**
 * @brief 股票行情全量静态信息
 */
typedef struct xlt_static_quote_full_info_t {
    XLTExchangeType  exchange_index;							///<交易所代码
    char               security_code[XLT_SECURITY_CODE_LEN];	///<证券代码
    char               security_name[XLT_SECURITY_NAME_LEN];	///<证券名称
    XLTSecurityType    security_type;					    ///<合约类型
    XLTQualificationType qualification_class;		        ///<合约适当性类别
    bool is_registration;									///<是否注册制(仅适用创业板股票，创新企业股票及存托凭证)
    bool is_VIE;											///<是否具有协议控制架构(仅适用创业板股票，创新企业股票及存托凭证)
    bool is_noprofit;										///<是否尚未盈利(仅适用创业板股票，创新企业股票及存托凭证)
    bool is_weighted_voting_rights;							///<是否存在投票权差异(仅适用创业板股票，创新企业股票及存托凭证)
    bool is_have_price_limit;								///<是否有涨跌幅限制(注：不提供具体幅度，可通过涨跌停价和昨收价来计算幅度)
    double upper_limit_price;								///<涨停价（仅在有涨跌幅限制时有效）
    double lower_limit_price;								///<跌停价（仅在有涨跌幅限制时有效）
    double pre_close_price;									///<昨收价
    double price_tick;										///<价格最小变动价位
    int32_t bid_qty_upper_limit;							///<限价买委托数量上限
    int32_t bid_qty_lower_limit;							///<限价买委托数量下限
    int32_t bid_qty_unit;									///<限价买数量单位
    int32_t ask_qty_upper_limit;							///<限价卖委托数量上限
    int32_t ask_qty_lower_limit;							///<限价卖委托数量下限
    int32_t ask_qty_unit;									///<限价卖数量单位
    int32_t market_bid_qty_upper_limit;						///<市价买委托数量上限
    int32_t market_bid_qty_lower_limit;						///<市价买委托数量下限
    int32_t market_bid_qty_unit;							///<市价买数量单位
    int32_t market_ask_qty_upper_limit;						///<市价卖委托数量上限
    int32_t market_ask_qty_lower_limit;						///<市价卖委托数量下限
    int32_t market_ask_qty_unit;							///<市价卖数量单位
    xlt_security_status_t security_status;                    ///<证券状态
    uint32_t unknown1;                                      ///<保留字段
    uint64_t unknown[3];                                    ///<保留字段

}xlt_static_quote_full_info_t;

/**
 * @brief 股票、基金 等额外数据
 */
typedef struct xlt_market_data_stock_ex_data_t {
    ///委托买入总量(SH,SZ)
    int64_t total_bid_qty;
    ///委托卖出总量(SH,SZ)
    int64_t total_ask_qty;
    ///加权平均委买价格(SH,SZ)
    double ma_bid_price;
    ///加权平均委卖价格(SH,SZ)
    double ma_ask_price;
    ///债券加权平均委买价格(SH)
    double ma_bond_bid_price;
    ///债券加权平均委卖价格(SH)
    double ma_bond_ask_price;
    ///债券到期收益率(SH)
    double yield_to_maturity;
    ///基金实时参考净值(SH,SZ)
    double iopv;
    ///ETF申购笔数(SH,SZ)
    int32_t etf_buy_count;
    ///ETF赎回笔数(SH,SZ)
    int32_t etf_sell_count;
    ///ETF申购数量(SH,SZ)
    double etf_buy_qty;
    ///ETF申购金额(SH)
    double etf_buy_money;
    ///ETF赎回数量(SH,SZ)
    double etf_sell_qty;
    ///ETF赎回金额(SH)
    double etf_sell_money;
    ///权证执行的总数量(SH)
    double total_warrant_exec_qty;
    ///债券质押式回购品种加权平均价(加权平均回购利率),该字段只对债券质押式协议回购有效,(元)(SH)
    double warrant_lower_price;
    ///IOPV 高精度值(SH)
    double warrant_upper_price;
    ///买入撤单笔数(SH)
    int32_t cancel_buy_count;
    ///卖出撤单笔数(SH)
    int32_t cancel_sell_count;
    ///买入撤单数量(SH)
    double cancel_buy_qty;
    ///卖出撤单数量(SH)
    double cancel_sell_qty;
    ///买入撤单金额(SH)
    double cancel_buy_money;
    ///卖出撤单金额(SH)
    double cancel_sell_money;
    ///买入总笔数(SH)
    int64_t total_buy_count;
    ///卖出总笔数(SH)
    int64_t total_sell_count;
    ///买入委托成交最大等待时间(SH)
    int32_t duration_after_buy;
    ///卖出委托成交最大等待时间(SH)
    int32_t duration_after_sell;
    ///买方委托价位数(SH)
    int32_t num_bid_orders;
    ///卖方委托价位数(SH)
    int32_t num_ask_orders;

    ///基金T-1日净值(SH,SZ)
    double pre_iopv;
    ///预留
    int64_t r1;
    ///预留
    int64_t r2;
} xlt_market_data_stock_ex_data_t;

/**
 * @brief 债券额外数据
 */
typedef struct xlt_market_data_bond_ex_data_t {
    ///委托买入总量(SH,SZ)
    int64_t total_bid_qty;
    ///委托卖出总量(SH,SZ)
    int64_t total_ask_qty;
    ///加权平均委买价格(SZ)
    double ma_bid_price;
    ///加权平均委卖价格(SZ)
    double ma_ask_price;
    ///债券加权平均委买价格(SH)
    double ma_bond_bid_price;
    ///债券加权平均委卖价格(SH)
    double ma_bond_ask_price;
    ///债券到期收益率(无意义)
    double yield_to_maturity;
    ///匹配成交最近价(SZ)
    double match_lastpx;
    ///债券加权平均价格(SH)
    double ma_bond_price;
    ///匹配成交成交量(SZ)
    int64_t match_qty;
    ///匹配成交成交金额(SZ)
    double match_turnover;
    ///预留
    double r4;
    ///预留
    double r5;
    ///预留
    double r6;
    ///预留
    double r7;
    ///预留
    double r8;
    ///买入撤单笔数(SH)
    int32_t cancel_buy_count;
    ///卖出撤单笔数(SH)
    int32_t cancel_sell_count;
    ///买入撤单数量(SH)
    double cancel_buy_qty;
    ///卖出撤单数量(SH)
    double cancel_sell_qty;
    ///买入撤单金额(SH)
    double cancel_buy_money;
    ///卖出撤单金额(SH)
    double cancel_sell_money;
    ///买入总笔数(SH)
    int64_t total_buy_count;
    ///卖出总笔数(SH)
    int64_t total_sell_count;
    ///买入委托成交最大等待时间(SH)
    int32_t duration_after_buy;
    ///卖出委托成交最大等待时间(SH)
    int32_t duration_after_sell;
    ///买方委托价位数(SH)
    int32_t num_bid_orders;
    ///卖方委托价位数(SH)
    int32_t num_ask_orders;
    ///时段(SH, SZ)，L1快照数据没有此字段
    ///SH: 对应上交所InstrumentStatus字段；
    ///SZ: 启用前5位，分别表示：1=匹配成交 2=协商成交 3=点击成交 4=询价成交 5=竞买成交所处的交易阶段代码
    char instrument_status[8];
}xlt_market_data_bond_ex_data_t;

/**
 * @brief 期权额外数据
 */
typedef struct xlt_market_data_option_ex_data_t {
    ///波段性中断参考价
    double  auction_price;
    ///SH: 波段性中断集合竞价虚拟匹配量
    ///SZ: 无意义
    int64_t auction_qty;
    ///SH: 最近询价时间
    ///SZ: 无意义
    int64_t last_enquiry_time;

}xlt_market_data_option_ex_data_t;


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
    // 代码
    ///交易所代码
    XLTExchangeType exchange_index;
    ///合约代码（不包含交易所信息），不带空格，以'\\0'结尾
    char	security_code[XLT_SECURITY_CODE_LEN];

    // 价格
    ///最新价
    double	last_price;
    ///昨收盘
    double	pre_close_price;
    ///今开盘
    double	open_price;
    ///最高价
    double	high_price;
    ///最低价
    double	low_price;
    ///今收盘
    double	close_price;

    // 期权数据
    ///昨日持仓量(张)(目前未填写)
    int64_t pre_total_long_position;
    ///持仓量(张)
    int64_t	total_long_position;
    ///昨日结算价（SH）
    double	pre_settle_price;
    ///今日结算价（SH）
    double	settle_price;

    // 涨跌停
    ///涨停价
    double	upper_limit_price;
    ///跌停价
    double	lower_limit_price;
    ///预留
    double	pre_delta;
    ///预留
    double	curr_delta;

    /// 时间类，格式为YYYYMMDDHHMMSSsss
    int64_t data_time;

    // 量额数据
    ///数量，为总成交量（单位股，与交易所一致）
    int64_t	qty;
    ///成交金额，为总成交金额（单位元，与交易所一致）
    double	turnover;
    ///预留(无意义)
    double	avg_price;

    // 买卖盘
    ///十档申买价
    double bid[10];
    ///十档申卖价
    double	ask[10];
    ///十档申买量
    int64_t	bid_qty[10];
    ///十档申卖量
    int64_t	ask_qty[10];
    ///十档申买委托笔数
    int64_t	bid_num_orders[10];
    ///十档申卖委托笔数
    int64_t	ask_num_orders[10];

    // 委托队列
    int32_t bid_queue_cnt;          ///< 买一队列发布委托笔数
    int32_t ask_queue_cnt;          ///< 卖一队列发布委托笔数
    int64_t bid_queue[50];          ///< 买一队列数量;
    int64_t ask_queue[50];          ///< 卖一队列数量;

    // 额外数据
    ///成交笔数
    int64_t trades_count;
    ///当前交易状态说明，参阅《XLT API常见问题.doc》文档
    char ticker_status[8];

    /// 对于新三板行情来说，以下结构和字段均无效
    /// 数据
    xlt_market_data_ex_data_t ex_data;
    /// 数据
//    union {
//        xlt_market_data_stock_ex_data_t  stk;  ///< 股票扩展字段
//        xlt_market_data_option_ex_data_t opt;  ///< 期权扩展字段
//        xlt_market_data_bond_ex_data_t  bond;  ///< 债券扩展字段
//    } ;

    ///决定了ex_data是哪种数据类型
    XLTMarketDataType data_type;
} xlt_market_data_t;

/**
 * @brief 逐笔委托
 */
typedef struct xlt_tick_by_tick_entrust_t {
    ///频道代码
    int32_t channel_no;
    ///SH: 委托序号(委托单独编号, 同一channel_no内连续)
    ///SZ: 委托序号(委托成交统一编号, 同一channel_no内连续)
    ///XLT: SH,SZ一致，都为业务序号
    int64_t seq;
    ///委托价格
    double  price;
    ///SH: 剩余委托数量(balance)
    ///SZ: 委托数量
    int64_t qty;
    ///SH: 'B':买; 'S':卖
    ///SZ: '1':买; '2':卖; 'G':借入; 'F':出借
    char  side;
    ///SH: 'A': 增加; 'D': 删除
    ///SZ: 订单类别: '1': 市价; '2': 限价; 'U': 本方最优
    char ord_type;
    ///SH: 原始订单号
    ///SZ: 无意义
    int64_t order_no;
    ///SH: 已成交的委托数量
    ///SZ: 无意义
    int64_t traded_qty;
}xlt_tick_by_tick_entrust_t;

/**
 * @brief 逐笔成交
 */
typedef struct xlt_tick_by_tick_trade_t {
    ///频道代码
    int32_t channel_no;
    ///SH: 成交序号(成交单独编号, 同一channel_no内连续)
    ///SZ: 成交序号(委托成交统一编号, 同一channel_no内连续)
    ///XLT: SH,SZ一致，都填业务序号
    int64_t seq;
    ///成交价格
    double price;
    ///成交量
    int64_t qty;
    ///成交金额(仅适用上交所)
    double money;
    ///SH: 买方订单号
    ///SZ:买方委托索引
    int64_t bid_no;
    ///SH: 卖方订单号
    ///SZ: 卖方委托索引
    int64_t ask_no;
    /// SH: 内外盘标识('B':主动买; 'S':主动卖; 'N':未知)
    /// SZ: 成交标识('4':撤; 'F':成交)
    char trade_flag;
}xlt_tick_by_tick_trade_t;

/**
 * @brief 逐笔状态订单
 */
typedef struct xlt_tick_by_tick_status_t {
    ///频道代码
    int32_t channel_no;
    ///同一channel_no内连续
    int64_t seq;
    ///状态信息
    char flag[8];
}xlt_tick_by_tick_status_t;

typedef union {
    xlt_tick_by_tick_entrust_t entrust; ///< 逐笔委托
    xlt_tick_by_tick_trade_t     trade; ///< 逐笔成交
    xlt_tick_by_tick_status_t    state; ///< 状态
} xlt_tick_by_tick_data_t;

/**
 * @brief 逐笔数据信息
 */
typedef struct xlt_tick_by_tick_t {
    ///交易所代码
    XLTExchangeType exchange_index;
    ///合约代码（不包含交易所信息），不带空格，以'\\0'结尾
    char security_code[XLT_SECURITY_CODE_LEN];
//    /// SH: 业务序号（委托成交统一编号，同一个channel_no内连续，此seq区别于联合体内的seq，channel_no等同于联合体内的channel_no）
//    /// SZ: 无意义
//    /// XLT：SH,SZ一致，都填业务序号
//    int64_t seq;
    ///委托时间 or 成交时间
    int64_t data_time;
    ///委托 or 成交 or 状态
    XLTTbtType type;

    /// 逐笔数据
    xlt_tick_by_tick_data_t data;

//    union {
//        xlt_tick_by_tick_entrust_t entrust; ///< 逐笔委托
//        xlt_tick_by_tick_trade_t     trade; ///< 逐笔成交
//        xlt_tick_by_tick_status_t    state; ///< 状态
//    };
} xlt_tick_by_tick_t;

}



