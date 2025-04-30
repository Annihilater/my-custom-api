
#pragma once

#include <cstdint>
#include "xlight_data_types.h"

namespace xlight::api {


#define XLT_REPORT_ID_LEN       32   ///< 回报标识长度


#define XLT_EXEC_ID_LEN         16   ///< 成交编号长度
#define XLT_ORDER_LOCAL_ID_LEN  10   ///< 发送到交易所的委托合同号长度
#define XLT_ORDER_EXCH_ID_LEN   16   ///< 交易所单号长度


enum class XLTResumeType : uint8_t {
    RESTART = 1,        ///< 从本交易日日初开始
    QUITE = 2,          ///< 从最新数据开始
    SPECIFY = 3,        ///< 从指定sequence开始
    RESUME = 4,         ///< 从上次接收到的数据开始
};

/**
 * @brief 交易所编号定义
 */
enum class XLTExchangeIndex : uint8_t {
    INIT = 0,    ///<初始化值或者未知
    SH_A = 1,    ///<上海A股
    SZ_A = 2,    ///<深圳A股
    BJ_A = 3,    ///<北京A股
    HK = 4,    ///<港股
    UNKNOWN = 5  ///<未知交易市场类型
};

/**
 * @brief 报单价格类型
 */
enum class XLTOrderPriceType : uint8_t {
    NONE = 0,  ///< 无特定类型。
    REAL_TIME_BEST_FIVE_OR_CANCEL = 1,  ///< 市转撤（市价最优五档全额成交剩余撤销）。
    LIMIT_PRICE = 2,  ///< 限价。
    REAL_TIME_TRADE_TO_LIMIT = 3,  ///< 市转限。
    SELF_BEST = 4,  ///< 本方最优。
    COUNTER_BEST = 5,  ///< 对手方最优。
    REAL_TIME_TRADE_OR_CANCEL = 6,  ///< 市价立即成交剩余撤销。
    REAL_TIME_FULL_TRADE_OR_CANCEL = 7   ///< 市价全额成交或撤销。
};

/**
 * @brief 买卖方向
 */
enum class XLTSide : uint8_t {
    BUY = 1, ///< 买入(ETF申购)。
    SELL = 2 ///< 卖出(ETF赎回)。
};

/**
 * @brief 业务类型
 */
enum class XLTBusinessType : uint8_t {
    NONE = 0,  ///<未知类型
    CASH = 1,  ///<现货（股票、基金、深圳可转债等）集中竞价交易
    BOND_MATCH = 2,  ///<债券现券竞价交易
    ETF = 3,  ///<ETF申赎业务
    ISSUE = 4,  ///<网上发行业务
    ALLOT = 5,  ///<配售业务
    BOND_CONVERT = 6,  ///<债转股业务
    PLEDGE_STYLE_REPO = 7,  ///<债券质押式回购
};

/**
 * @brief 订单简要状态，API订单状态通知使用
 */
enum class XLTOrderBriefStatus : uint8_t {
    INIT = 1,   ///< 初始。
    SUBMITTED = 2,   ///< 已报。
    FINISHED = 3    ///< 结束。
};

/**
 * @brief 订单状态
 */
enum class XLTOrderStatus : uint8_t {
    INIT = 0,       ///< 初始。
    ALL_TRADED = 1,       ///< 全部成交。
    PART_TRADED = 2,       ///< 部分成交。
    PART_CANCELED = 3,       ///< 部分撤单。
    NOT_TRADED = 4,       ///< 未成交。
    ALL_CANCELED = 5,       ///< 全部撤单/已撤单。
    REJECTED = 6,       ///< 废单。
    UNKNOW = 7,       ///< 委托状态数量。
};

/**
 * @brief 持仓证券类型
 */
enum class XLTPositionSecurityType : uint8_t {
    NORMAL = 0,      ///<普通持仓
    PLACEMENT = 1,   ///<配售类型的持仓，包含配股、配债等
    UNKNOWN = 2,    ///<未知类型
};

/**
 * @brief 回报响应类型
 */
enum class XLTReportType : uint8_t {
    ORDER_REJECT = 1,               ///<订单拒绝
    ORDER_RESPONSE,                 ///<申报响应及撤单成功响应
    TRADE_REPORT,                   ///<成交回报
    ORDER_CANCEL_FAIL              ///<撤单失败响应
};

/**
 * @brief 交易所业务平台类型
 */
enum class XLTExchangePlatformType : uint8_t {
    SH_MTP = 1,                ///<上海交易网关竞价撮合平台。
    SH_ATP = 2,                ///<上海交易网关综合业务平台。
    SH_DTP = 3,                ///<上海交易网关期权业务平台。
    SH_XBTP = 4,               ///<上海交易网关新债券交易平台。
    SH_ITP = 5,                ///<上海交易网关港股通平台。
    SH_FISP = 6,               ///<上海交易网关固定收益平台。
    SH_IITP = 7,               ///<上海交易网关互联网交易平台。
    SZ_CASH = 11,              ///<深圳交易网关现货集中竞价交易平台。
    SZ_FIN = 12,               ///<深圳交易网关综合金融服务平台。
    SZ_NON = 13,               ///<深圳交易网关非交易处理平台。
    SZ_OPTION = 14,            ///<深圳交易网关衍生品集中竞价交易平台。
    SZ_INTL = 15,              ///<深圳交易网关国际市场互联平台。
    SZ_FIXED = 16              ///<深圳交易网关固定收益交易平台。
};

}
