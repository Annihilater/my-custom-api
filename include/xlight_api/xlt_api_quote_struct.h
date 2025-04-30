#pragma once
#include "xlt_data_type.h"

namespace x1{
#pragma pack(push, 1)
/**
 * @brief 股票行情全量静态信息
 */
typedef struct xlt_static_quote_full_info_t {
    ExchangeIndex  exchange_index;							///<交易所代码
    char               security_code[CONST_STR_SECURITY_CODE_LEN];	///<证券代码
    char               security_name[CONST_SECURITY_NAME_LEN];	///<证券名称
    QuoteSecurityType  security_type;					    ///<合约类型
    QualificationType  qualification_class;		            ///<合约适当性类别
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
    security_status_t security_status;                      ///<证券状态
    uint32_t unknown1;                                      ///<保留字段
    uint64_t unknown[3];                                    ///<保留字段

}xlt_static_quote_full_info_t;
#pragma pack(pop)
}
