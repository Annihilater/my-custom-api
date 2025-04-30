#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <atomic>
#include "xlt_api_trade.h"
#include "my_trade_spi.h"

using namespace xlight::api;

// 测试账号信息
char pub_key_base64[256] = "vU2VTSwdG4mLzIb69dS2EGKmdfZj6sJlspQoyq2dl7kZdEK8GfK2xXtolkejFNSHBqNe6nvqKXUelfbhc3lhAg==";
char account_name[XLT_ACCOUNT_NAME_LEN] = "account_test";
char password[256] = "passwd_123456";
uint8_t client_id = 1;
xlt_trade_config_t config = {
        ".",                    // 文件路径
        XLTLogLevel::LOG_DEBUG, // 日志级别
        64,                     // 内存池大小，单位MB
        {"192.168.17.39:6062"}, // 交易网关地址, 如"192.168.1.1:8080"
        "0.0.0.0",              ///< 本地网卡地址
        "0.0.0.0",              ///< 委托本地网卡地址
        "192.168.24.170:6067",  ///< 联调测试fon地址
        662,                    ///< 联调测试交易账号账号id
};
xlight::api::TradeApi * my_api = xlight::api::TradeApi::create_trade_api(); ///< API实例，全局唯一
uint64_t global_session_id = 0;                          ///< 会话ID
std::atomic_bool global_login_success(false);   ///< 是否正在登录标识
std::atomic_bool global_login_finished(false);  ///< 已建立会话标识
std::atomic_uint64_t global_request_id = 0;     ///< 全局请求id


uint64_t next_request_id() {
    global_request_id++;
    return global_request_id.load();
}


/**
 * 封装异步登录
 */
bool login() {
    if (global_session_id != 0) {
        my_api->logout(global_session_id);
    }

    global_session_id = 0;
    global_login_success.store(false);
    global_login_finished.store(false);

    auto result = my_api->login(client_id, account_name, password, pub_key_base64, 1, next_request_id());

    if ( result > 0 ) {
        printf("Login request failed!!! error_id: %d\n",  result);
        return false;
    }

    while (!global_login_finished.load()) {
        usleep(1000);
    }
    return global_login_success.load();
}


int main() {
    if (!my_api->initialize(&config)){
        printf("Api initialize failed!\n");
        return 0;
    }

    MySpi my_spi;
    my_api->register_spi(&my_spi);

    if (!login()) {
        return 0;
    }

    printf("Login success!!\n");

    // 订单委托
    xlt_order_insert_info_t order_info = {};
    order_info.order_client_id = 1;
    strcpy(order_info.security_code, "600000");
    order_info.exchange_index = XLTExchangeIndex::SH_A;
    order_info.price = 50000000;
    order_info.quantity = 8800;
    order_info.order_price_type = XLTOrderPriceType::LIMIT_PRICE;
    order_info.side = XLTSide::SELL;
    order_info.business_type = XLTBusinessType::CASH;
    uint64_t xid = my_api->insert_order(global_session_id, &order_info);
    if (xid == 0) {
        printf("Insert order request send failed!!!\n");
        my_api->logout(global_session_id);
        return 0;
    }

    printf("Insert order request send success! Wait for response!\n");

    // 撤单
    xlt_order_cancel_info_t order_cancel_info{};
    order_cancel_info.order_client_id = 1;
    order_cancel_info.origin_xid = xid;
    uint64_t cancel_xid = my_api->cancel_order(global_session_id, &order_cancel_info);
    if (cancel_xid == 0) {
        printf("Cancel order request send Failed!!!\n");
        my_api->logout(global_session_id);
        return 0;
    }

    printf("Cancel order request send success! Wait for response!\n");

    // 查询资金
    if (my_api->query_assets(global_session_id, next_request_id()) > 0) {
        printf("Query assets request send failed!!\n");
        my_api->logout(global_session_id);
        return 0;
    }
    printf("Query assets request send success! Wait for response!\n");

    // 查询持仓
    char security_code[XLT_SECURITY_CODE_LEN] = "";
    if ( my_api->query_positions(global_session_id, next_request_id(), security_code, XLTExchangeIndex::INIT, 0) > 0 ) {
        printf("Query positions request send failed!!\n");
        my_api->logout(global_session_id);
        return 0;
    }
    printf("Query positions request send success! Wait for response!\n");

    // 查询订单（根据条件查询）
    xlt_order_query_param_t order_query_param = {};
    order_query_param.xid = xid;
    if ( my_api->query_orders(global_session_id, next_request_id(), &order_query_param) > 0 ) {
        printf("Query orders request send failed!!\n");
        my_api->logout(global_session_id);
        return 0;
    }
    printf("Query orders request send success! Wait for response!\n");

    // 分页查询订单
    xlt_order_query_by_page_param_t query_param = {};
    query_param.req_count = 10;
    query_param.reference = 0;
    if ( my_api->query_orders_by_page(global_session_id, next_request_id(), &query_param, 0) > 0 ) {
        printf("Query orders by page request send failed!!\n");
        my_api->logout(global_session_id);
        return 0;
    }
    printf("Query orders by page request send success! Wait for response!\n");


    // 订单明细查询
    if ( my_api->query_order_details(global_session_id, next_request_id(), xid, 0) > 0 ) {
        printf("Query order details request send failed!!\n");
        my_api->logout(global_session_id);
        return 0;
    }
    printf("Query order details request send success! Wait for response!\n");

    while (true) {
        usleep(1000 * 1000);
    }

    return 0;

}
