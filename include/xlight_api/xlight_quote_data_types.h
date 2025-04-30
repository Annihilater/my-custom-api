#pragma once

#include <cstdint>
#include "xlight_data_types.h"

namespace xlight::api {

/**
 * @brief 交易所类别
 */
typedef enum XLTExchangeType{
    EXCHANGE_SH = 1,    ///<上海
    EXCHANGE_SZ = 2,    ///<深圳
}XLTExchangeType;

/**
 * @brief 证券类型
 */
typedef enum XLTSecurityType
{
    SECURITY_TYPE_STOCK = 0,            ///<股票
    SECURITY_TYPE_INDEX,                ///<指数
    SECURITY_TYPE_FUND,                 ///<基金
    SECURITY_TYPE_BOND,                 ///<债券
    SECURITY_TYPE_OPTION,               ///<期权
    SECURITY_TYPE_UNKNOWN               ///<未知类型

}XLTSecurityType;

/**
 * @brief 证券适当性枚举类型
 */
typedef enum  XLTQualificationType
{
    QUALIFICATION_PUBLIC = 1,			///<包括普通投资者、专业投资者 在内的所有投资者
    QUALIFICATION_COMMON = 2,			///<仅专业投资者
    QUALIFICATION_ORGANIZATION = 3,		///<仅专业投资者中的机构投资者
    QUALIFICATION_UNKNOWN = 99		    ///<其他
}XLTQualificationType;

/**
 * @brief 逐笔数据类型
 */
typedef enum XLTTbtType {
    TBT_ENTRUST = 1,	///<逐笔委托
    TBT_TRADE = 2,		///<逐笔成交
    TBT_STATE = 3,      ///<逐笔状态订单，为上海新债券Level2行情中独有
}XLTTbtType;

/// @brief 证券状态类型
typedef uint16_t xlt_security_status_t;

/**
 * @brief 证券状态标志
 */
typedef enum XLTSecurityStatusFlag{
    STATUS_SUSPENSION            = 1<<0,    ///< 停牌
    STATUS_EX_ENTITLEMENT        = 1<<1,    ///< 除权
    STATUS_EX_DIVIDEND           = 1<<2,    ///< 除息
    STATUS_ST                    = 1<<3,    ///< ST
    STATUS_SST                   = 1<<4,    ///< *ST
    STATUS_FIRST_DAY             = 1<<5,    ///< 上市首日
    STATUS_DELISTING_ARRANGEMENT = 1<<6,    ///< 退市整理期
    STATUS_LISTING_EARLY         = 1<<7     ///< 上市初期（前五天）
}XLTSecurityStatusFlag;

/**
 * @brief 行情快照数据类型
 */
typedef enum XLTMarketDataType {
    MARKETDATA_INDEX  = 0, ///< 指数
    MARKETDATA_OPTION = 1, ///< 期权
    MARKETDATA_ACTUAL = 2, ///< 现货(股票/基金等)
    MARKETDATA_BOND   = 3, ///< 债券
}XLTMarketDataType;

}
