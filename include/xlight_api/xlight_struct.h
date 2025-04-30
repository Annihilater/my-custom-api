#pragma once
#include "xlight_data_types.h"

namespace xlight::api{
/**
 * @brief 错误信息
 */
typedef struct {
    int error_id;                     ///< 错误代码
    char error_msg[XLT_ERR_MSG_LEN];  ///< 错误信息
} xlt_error_info_t;

}
