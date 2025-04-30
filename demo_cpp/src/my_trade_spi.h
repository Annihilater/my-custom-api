#include <atomic>
#include <cstring>
#include "xlt_api_trade.h"

using namespace xlight::api;
extern xlight::api::TradeApi * my_api; ///< API实例，全局唯一
extern uint64_t global_session_id;                          ///< 会话ID
extern std::atomic_bool global_login_success;   ///< 是否正在登录标识
extern std::atomic_bool global_login_finished;  ///< 已建立会话标识
extern std::atomic_uint64_t global_request_id;     ///< 全局请求id

class MySpi : public xlight::api::TradeSpi {
public:
    using xlight::api::TradeSpi::TradeSpi;
    void on_disconnect(uint64_t session_id) override;
    void on_login(uint64_t session_id, xlt_error_info_t *error_info, uint64_t request_id) override;
    void on_test_pong(uint64_t session_id, uint64_t sequence, uint32_t msg_len, char *msg, uint64_t timestamp) override {};
    void on_order_status_notice(uint64_t session_id, xlt_order_status_notice_t *order_status_notice) override;
    void on_order_reject(uint64_t session_id, xlt_order_reject_t *order_reject) override;
    void on_order_response(uint64_t session_id, xlt_order_response_t *order_response) override;
    void on_order_cancel_fail(uint64_t session_id, xlt_order_cancel_fail_t *cancel_fail) override;
    void on_trade_report(uint64_t session_id, xlt_trade_report_t *trade_report) override;
    void on_assets(uint64_t session_id, xlt_asset_info_t assets[], uint32_t data_count) override;
    void on_positions(uint64_t session_id, xlt_position_info_t *positions, uint32_t data_count) override;
    void on_query_positions(uint64_t session_id, uint64_t request_id, xlt_position_info_t *positions,
                            uint32_t data_count, bool is_last, xlt_error_info_t *error_info) override;
    void on_query_assets(uint64_t session_id, uint64_t request_id, xlt_asset_info_t *assets,
                         uint32_t data_count, bool is_last, xlt_error_info_t *error_info) override;
    void on_query_orders(uint64_t session_id, uint64_t request_id, xlt_order_info_t *order_infos, uint32_t data_count,
                         bool is_last, xlt_error_info_t *error_info) override;
    void on_query_orders_by_page(uint64_t session_id, uint64_t request_id, xlt_order_info_t *order_infos,
                                 uint32_t data_count, int64_t req_count, int64_t order_sequence,
                                 int64_t query_reference, bool is_last, xlt_error_info_t *error_info) override;
    void on_query_order_detail(uint64_t session_id, uint64_t request_id, xlt_order_detail_t *order_details,
                               uint32_t data_count, bool is_last, xlt_error_info_t *error_info) override;
    void on_request_timeout(uint64_t session_id, uint64_t request_id) override;

};
