#pragma once
#include <cstdint>
#include <climits>

namespace x1{
// 常量定义
constexpr uint8_t CONST_STR_SECURITY_CODE_LEN = 9; ///< 证券代码长度，含字符串终止符
constexpr uint8_t CONST_ERROR_MSG_LEN = 129; ///< 错误信息长度
constexpr uint8_t CONST_SECURITY_NAME_LEN = 33; ///< 证券名称长度
constexpr uint8_t CONST_CL_ORD_ID_LEN = 10; ///< 委托合同号长度
constexpr uint8_t CONST_REPORT_ID_LEN = 32; ///< 委托回报ID长度
constexpr uint8_t CONST_ACC_NAME_LEN = 64 + 1; ///< 账户名称长度
constexpr uint8_t CONST_ACC_PASSWD_LEN = 128 + 1; ///< 账户密码长度

// 类型定义
typedef int64_t amount_t; ///< 金额 类型
typedef int64_t price_t; ///< 价格 类型
typedef int64_t quantity_t; ///< 数量 类型
typedef char security_status_t[9];  ///< 证券状态类型


/**
 * @brief 交易消息重传类型
 */
enum class TradeResumeType : uint8_t {
    RESTART = 1,        ///< 从本交易日日初开始
    QUICK = 2,          ///< 从最新数据开始
    SPECIFY = 3,        ///< 从指定sequence开始
    RESUME = 4,         ///< 从上次接收到的数据开始
};


/**
 * @brief 交易所编号定义
 */
enum class ExchangeIndex : uint8_t {
    INIT = 0,    ///<初始化值或者未知
    SH = 1,      ///< 上海证券交易所。
    SZ = 2,      ///< 深圳证券交易所。
};


/**
 * @brief 报单价格类型
 */
enum class OrdType: uint8_t {
    NONE = 0, ///< 无特定类型。
    BEST_FIVE_PRICE_OR_CANCEL, ///< 市转撤（市价最优五档全额成交剩余撤销）。
    LIMIT_PRICE, ///< 限价。
    BEST_FIVE_PRICE_TO_LIMIT, ///< 市转限（市价最优五档全额成交剩余转限价）。
    SELF_BEST, ///< 本方最优。
    COUNTER_BEST, ///< 对手方最优。
    MARKET_PRICE_OR_CANCEL, ///< 市价立即成交剩余撤销。
    MARKET_PRICE_ALL_OR_CANCEL ///< 市价全额成交或撤销。
};


/**
 * @brief 买卖方向
 */
enum class Side : uint8_t {
    BUY = 1, ///< 买入(ETF申购)。
    SELL = 2 ///< 卖出(ETF赎回)。
};


/**
 * @brief 业务类型
 */
enum class BusinessType : uint8_t {
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
enum class OrderBriefStatus : uint8_t {
    INIT = 1,   ///< 初始。
    SUBMITTED = 2,   ///< 已报。
    FINISHED = 3    ///< 结束。
};


/**
 * @brief 订单状态
 */
enum class OrderStatus : uint8_t {
    INIT, ///< 初始。
    ALL_TRADED, ///< 全部成交。
    PART_TRADED, ///< 部分成交。
    PART_CANCELED, ///< 部分撤单。
    NOT_TRADED, ///< 未成交。
    ALL_CANCELED, ///< 全部撤单/已撤单。
    REJECTED, ///< 废单。
    COUNT ///< 委托状态数量。
};


/**
 * @brief 持仓证券类型
 */
enum class PositionSecurityType : uint8_t {
    NORMAL = 0,      ///<普通持仓
    PLACEMENT = 1,   ///<配售类型的持仓，包含配股、配债等
    UNKNOWN = 2,     ///<未知类型
};


/**
 * @brief 交易所业务平台类型
 */
enum class ExchangePlatformType : uint8_t {
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

/**
* @brief 证券类型
*/
enum class QuoteSecurityType : uint8_t{
    SECURITY_TYPE_STOCK = 0,            ///<股票
    SECURITY_TYPE_INDEX,                ///<指数
    SECURITY_TYPE_FUND,                 ///<基金
    SECURITY_TYPE_BOND,                 ///<债券
    SECURITY_TYPE_OPTION,               ///<期权
    SECURITY_TYPE_UNKNOWN               ///<未知类型
};

/**
* @brief 证券适当性枚举类型
*/
enum class QualificationType : uint8_t{
    QUALIFICATION_PUBLIC = 1,			///<包括普通投资者、专业投资者 在内的所有投资者
    QUALIFICATION_COMMON = 2,			///<仅专业投资者
    QUALIFICATION_ORGANIZATION = 3,		///<仅专业投资者中的机构投资者
    QUALIFICATION_UNKNOWN = 99		    ///<其他
};

/**
 * @brief 逐笔数据类型
 */
typedef enum TbtType {
    TBT_ENTRUST = 1,	///<逐笔委托
    TBT_TRADE = 2,		///<逐笔成交
    TBT_STATE = 3,      ///<逐笔状态订单，为上海新债券Level2行情中独有
}TbtType;


/**
 * @brief 行情快照数据类型
 */
typedef enum MarketDataType {
    MARKETDATA_INDEX  = 0, ///< 指数
    MARKETDATA_OPTION = 1, ///< 期权
    MARKETDATA_ACTUAL = 2, ///< 现货(股票/基金等)
    MARKETDATA_BOND   = 3, ///< 债券
}MarketDataType;

}

