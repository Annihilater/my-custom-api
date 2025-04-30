#pragma once
#include "xlt_data_type.h"

namespace x1{
#pragma pack(push, 1)
typedef char address_t[64];          ///< 地址类型
/**
 * @brief 日志级别
 */
enum class ApiLogLevel : uint8_t {
    LOG_TRACE = 1,      ///<trace级别
    LOG_DEBUG = 2,      ///<debug级别
    LOG_INFO  = 3,      ///<info级别
    LOG_WARN  = 4,      ///<警告级别
    LOG_ERROR = 5,      ///<错误级别
    LOG_FATAL = 6       ///<严重错误级别
};

/**
 * @brief 错误信息
 */
typedef struct {
    int error_id;                         ///< 错误代码
    char error_msg[CONST_ERROR_MSG_LEN];  ///< 错误信息
} xlt_error_info_t;



#pragma pack(pop)
}
