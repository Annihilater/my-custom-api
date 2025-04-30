#pragma once
#include "xlt_api_define.h"
#include "xlt_api_trade_struct.h"

namespace x1{
#pragma pack(push, 1)

constexpr uint8_t CONST_VERSION_LEN = 16;          ///< 存放版本号的字符串长度
constexpr uint8_t CONST_INET_ADDRESS_STR_LEN = 64; ///< IP地址的字符串长度
constexpr uint8_t CONST_MAC_ADDRESS_LEN = 16;      ///< MAC地址的字符串长度
constexpr uint8_t CONST_HARDDISK_SN_LEN = 24;      ///< 硬盘序列号的字符串长度
constexpr uint8_t CONST_MACOS_SNO_LEN = 21;        ///< MacOS系统序列号的字符串长度
typedef char xlt_version_type_t[CONST_VERSION_LEN];  /// 版本号类型

/**
 * @brief 终端类型
 */
enum class TerminalType : uint8_t {
    PC = 1,            ///<"PC",PC-windows及MacOS
    ANDROID,           ///<"MA",Mobile-Android
    IOS,               ///<"MI",Mobile-Ios
    WP,                ///<"MW",Mobile-Windows Phone
    STATION,           ///<"WP",无盘站
    TEL,               ///<"TO",电话委托
    PC_LINUX           ///<"OH",PC-linux及其他终端
};


/**
* @brief 交易API配置
*/
typedef struct xlt_trade_config_t {
    char path[256] = ".";                           ///< 文件路径
    ApiLogLevel log_level = ApiLogLevel::LOG_INFO;  ///< 日志级别
    uint64_t mem_pool_size = 256;                   ///< 内存池大小，单位MB
    address_t agw_address[32] = {"192.168.1.1:8080"};  ///< AGW地址列表
    address_t local_address = "0.0.0.0";             ///< 本地网卡地址
    address_t order_local_address = "0.0.0.0";       ///< 本地委托网卡地址
} xlt_trade_config_t;

/**
 * @brief 新订单请求
 */
typedef struct {
    uint32_t order_client_id;         ///< 报单引用，由客户自定义
    char security_code[CONST_STR_SECURITY_CODE_LEN]; ///< 证券代码
    ExchangeIndex exchange_index;     ///< 交易市场
    int64_t price;                    ///< 价格放大10000倍
    int64_t quantity;                 ///< 数量
    OrdType order_price_type;         ///< 报单价格类型
    Side side;                        ///< 买卖方向
    BusinessType business_type;       ///< 业务类型
} xlt_order_insert_info_t;

/**
 * @brief 撤单请求
 */
typedef struct {
    uint32_t order_client_id;         ///< 报单引用，由客户自定义
    uint64_t origin_xid;              ///< 被撤委托ID
} xlt_order_cancel_info_t;


/**
 * @brief 报单查询请求-条件查询
 */
typedef struct {
    uint64_t xid;                     ///< 需要查询的委托编号，如果为0则根据后续条件进行查询，如果不为0，则只查询指定订单，忽略后续查询条件
    char security_code[CONST_STR_SECURITY_CODE_LEN]; ///<证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
    int64_t begin_time;               ///< 格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t end_time;                 ///< 格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    uint8_t query_unfinished;         ///< 是否只查询未完成订单：1是，0否
} xlt_order_query_param_t;

/**
 * @brief 申报用户的ip和mac等信息
 */
typedef struct xlt_user_terminal_info_t {
    char  local_ip[CONST_INET_ADDRESS_STR_LEN];			///< 本地IP地址
    char  mac_addr[CONST_MAC_ADDRESS_LEN];				///< MAC地址
    char  hd[CONST_HARDDISK_SN_LEN];					///< 硬盘序列号
    TerminalType term_type;							    ///< 终端类型
    char  internet_ip[CONST_INET_ADDRESS_STR_LEN];		///< 公网IP地址
    int32_t internet_port;								///< 公网端口号
    xlt_version_type_t  client_version;					///< 客户端版本号
    char  macos_sno[CONST_MACOS_SNO_LEN];				///< MacOS系统的序列号，仅为MacOS系统需要填写
    char  unused[27];									///< 预留
}xlt_user_terminal_info_t;

#pragma pack(pop)
}