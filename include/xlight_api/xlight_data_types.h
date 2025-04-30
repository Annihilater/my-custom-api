
#pragma once

#include <cstdint>

namespace xlight::api {

// 常量定义
#define XLT_SECURITY_CODE_LEN      9    ///< 证券代码长度
#define XLT_SECURITY_NAME_LEN      33   ///< 证券名称长度
#define XLT_ERR_MSG_LEN         129  ///< 错误信息长度
#define XLT_ACCOUNT_NAME_LEN    65   ///< 账户名称长度

typedef char xlt_address_t[32];          ///< 地址类型

/**
 * @brief 日志级别
 */
enum class XLTLogLevel : uint8_t {
    LOG_TRACE = 1,      ///<trace级别
    LOG_DEBUG,          ///<debug级别
    LOG_INFO,           ///<info级别
    LOG_WARN,           ///<警告级别
    LOG_ERROR,          ///<错误级别
    LOG_FATAL           ///<严重错误级别
};


}

