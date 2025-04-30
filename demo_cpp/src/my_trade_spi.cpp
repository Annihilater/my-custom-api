#include "my_trade_spi.h"

void MySpi::on_disconnect(uint64_t session_id) {
    printf("on_disconnect session_id: %lu\n", session_id);
    global_session_id = 0;
    global_login_success.store(false);
    global_login_finished.store(false);
}

void MySpi::on_login(uint64_t session_id, xlt_error_info_t *error_info, uint64_t request_id) {
    printf("on_login session_id: %lu, request_id: %lu\n", session_id, request_id);
    if (error_info == nullptr) {
        global_session_id = session_id;
        global_login_success.store(true);
    } else {
        global_login_success.store(false);
    }
    global_login_finished.store(true);
}

void MySpi::on_order_status_notice(uint64_t session_id, xlt_order_status_notice_t *order_status_notice) {
    printf("on_order_status_notice session_id: %lu, xid: %lu, order_client_id: %u, order_brief_status: %d\n",
            session_id,
            order_status_notice->xid,
            order_status_notice->order_client_id,
            (int)order_status_notice->order_brief_status);

}

void MySpi::on_order_reject(uint64_t session_id, xlt_order_reject_t *order_reject) {
    printf("on_order_reject session_id: %lu, report_id: %s, xid: %lu, order_client_id: %u, orig_xid: %lu, "
           "orig_order_client_id: %u, security_code: %s, exchange_id: %d, business_type: %d, side: %d, price: "
           "%lu, quantity: %lu, order_price_type: %d, error_id: %d, error_msg: %s, report_time: %lu\n",
            session_id,
            order_reject->report_id,
            order_reject->xid,
            order_reject->order_client_id,
            order_reject->orig_xid,
            order_reject->orig_order_client_id,
            order_reject->security_code,
            (int)order_reject->exchange_index,
            (int)order_reject->business_type,
            (int)order_reject->side,
            order_reject->price,
            order_reject->quantity,
            (int)order_reject->order_price_type,
            order_reject->error_id,
            order_reject->error_msg,
            order_reject->report_time);
}

void MySpi::on_order_response(uint64_t session_id, xlt_order_response_t *order_response) {
    printf("on_order_response session_id: %lu, report_id: %s, xid: %lu, order_client_id: %u, orig_xid: %lu, "
           "orig_order_client_id: %u, security_code: %s, exchange_id: %d, business_type: %d, side: %d, price: "
           "%lu, quantity: %lu, order_price_type: %d, leaves_qty: %ld, cum_qty: %ld, cxl_qty: %ld, exec_type: %c, "
           "order_status: %d, error_id: %d, error_msg: %s, report_time: %lu\n",
            session_id,
            order_response->report_id,
            order_response->xid,
            order_response->order_client_id,
            order_response->orig_xid,
            order_response->orig_order_client_id,
            order_response->security_code,
            (int)order_response->exchange_index,
            (int)order_response->business_type,
            (int)order_response->side,
            order_response->price,
            order_response->quantity,
            (int)order_response->order_price_type,
            order_response->leaves_qty,
            order_response->cum_qty,
            order_response->cxl_qty,
            order_response->exec_type,
            (int)order_response->order_status,
            order_response->error_id,
            order_response->error_msg,
            order_response->report_time
    );
}

void MySpi::on_order_cancel_fail(uint64_t session_id, xlt_order_cancel_fail_t *cancel_fail) {
    printf("on_order_cancel_fail session_id: %lu, report_id: %s, cancel_xid: %lu, cancel_client_id: %u, "
           "orig_xid: %lu, orig_order_client_id: %u, security_code: %s, exchange_id: %d, business_type: %d, "
           "error_id: %d, error_msg: %s\n",
            session_id,
            cancel_fail->report_id,
            cancel_fail->xid,
            cancel_fail->order_client_id,
            cancel_fail->orig_xid,
            cancel_fail->orig_order_client_id,
            cancel_fail->security_code,
            (int)cancel_fail->exchange_index,
            (int)cancel_fail->business_type,
            cancel_fail->error_id,
            cancel_fail->error_msg);
}

void MySpi::on_trade_report(uint64_t session_id, xlt_trade_report_t *trade_report) {
    printf("on_trade_report session_id: %lu, report_id: %s, xid: %lu, order_client_id: %u, security_code: %s, "
           "exchange_id: %d, business_type: %d, side: %d,  order_status: %d, price: "
           "%lu, quantity: %lu, leaves_qty: %lu, report_time: %lu\n",
            session_id,
            trade_report->report_id,
            trade_report->xid,
            trade_report->order_client_id,
            trade_report->security_code,
            (int)trade_report->exchange_index,
            (int)trade_report->business_type,
            (int)trade_report->side,
//                trade_report->exec_id,
//                trade_report->exec_type,
            (int)trade_report->order_status,
            trade_report->price,
            trade_report->quantity,
            trade_report->leaves_qty,
            trade_report->report_time);
}

void MySpi::on_positions(uint64_t session_id, xlt_position_info_t *positions, uint32_t data_count) {
    printf("on_positions session_id: %lu, data_count: %u ", session_id, data_count);
    for (uint32_t i = 0; i < data_count; ++i) {
        printf("Position %d: security_code: %s, security_name: %s, exchange_id: %d, "
               "total_qty: %ld, sellable_qty: %ld, avg_price: %ld, unrealized_pnl: %ld, "
               "yesterday_position: %ld, purchase_redeemable_qty: %ld, "
               "position_security_type: %d, profit_price: %ld, buy_cost: %ld, profit_cost: %ld, "
               "market_value: %ld, last_buy_cost: %ld, last_profit_cost: %ld\n",
                i + 1,
                positions[i].security_code,
                positions[i].security_name,
                (int)positions[i].exchange_index,
                positions[i].total_qty,
                positions[i].sellable_qty,
                positions[i].avg_price,
                positions[i].unrealized_pnl,
                positions[i].yesterday_position,
                positions[i].purchase_redeemable_qty,
                (int)positions[i].position_security_type,
                positions[i].profit_price,
                positions[i].buy_cost,
                positions[i].profit_cost,
                positions[i].market_value,
                positions[i].last_buy_cost,
                positions[i].last_profit_cost);
    }
}

void MySpi::on_assets(uint64_t session_id, xlt_asset_info_t assets[], uint32_t data_count) {
    printf("on_assets session_id: %lu, data_count: %u ", session_id, data_count);
    for (uint32_t i = 0; i < data_count; ++i) {
        printf("Asset %d: total_asset: %ld, buying_power: %ld, initial_buying_power: %ld, security_asset: %ld, "
               "fund_buy_amount: %ld, fund_buy_fee: %ld, fund_sell_amount: %ld, fund_sell_fee: %ld, "
               "withholding_amount: %ld\n",
                i + 1,
                assets[i].total_asset,
                assets[i].buying_power,
                assets[i].initial_buying_power,
                assets[i].security_asset,
                assets[i].fund_buy_amount,
                assets[i].fund_buy_fee,
                assets[i].fund_sell_amount,
                assets[i].fund_sell_fee,
                assets[i].withholding_amount);
    }
}

void MySpi::on_query_positions(uint64_t session_id, uint64_t request_id, xlt_position_info_t *positions,
                               uint32_t data_count, bool is_last, xlt_error_info_t *error_info) {
    printf("on_query_positions session_id: %lu request_id: %lu data_count: %u is_last: %d\n",
            session_id, request_id, data_count, is_last);
    if (error_info != nullptr) {
        printf("Error: error_id: %d, error_msg: %s\n", error_info->error_id, error_info->error_msg);
        return;
    }
    for (uint32_t i = 0; i < data_count; ++i ) {
        printf("Position %d: security_code: %s, security_name: %s, exchange_id: %d, "
               "total_qty: %ld, sellable_qty: %ld, avg_price: %ld, unrealized_pnl: %ld, "
               "yesterday_position: %ld, purchase_redeemable_qty: %ld, "
               "position_security_type: %d, profit_price: %ld, buy_cost: %ld, profit_cost: %ld, "
               "market_value: %ld, last_buy_cost: %ld, last_profit_cost: %ld\n",
                i + 1,
                positions[i].security_code,
                positions[i].security_name,
                (int)positions[i].exchange_index,
                positions[i].total_qty,
                positions[i].sellable_qty,
                positions[i].avg_price,
                positions[i].unrealized_pnl,
                positions[i].yesterday_position,
                positions[i].purchase_redeemable_qty,
                (int)positions[i].position_security_type,
                positions[i].profit_price,
                positions[i].buy_cost,
                positions[i].profit_cost,
                positions[i].market_value,
                positions[i].last_buy_cost,
                positions[i].last_profit_cost);
    }
}

void MySpi::on_query_assets(uint64_t session_id, uint64_t request_id, xlt_asset_info_t *assets,
                            uint32_t data_count, bool is_last, xlt_error_info_t *error_info) {
    printf("on_query_assets session_id: %lu request_id: %lu data_count: %u is_last: %d\n",
            session_id, request_id, data_count, is_last);
    if (error_info != nullptr) {
        printf("Error: error_id: %d, error_msg: %s\n", error_info->error_id, error_info->error_msg);
        return;
    }
    for (uint32_t i = 0; i < data_count; ++i) {
        printf("Asset %d: total_asset: %ld, buying_power: %ld, initial_buying_power: %ld, security_asset: %ld, "
               "fund_buy_amount: %ld, fund_buy_fee: %ld, fund_sell_amount: %ld, fund_sell_fee: %ld, "
               "withholding_amount: %ld\n",
                i + 1,
                assets[i].total_asset,
                assets[i].buying_power,
                assets[i].initial_buying_power,
                assets[i].security_asset,
                assets[i].fund_buy_amount,
                assets[i].fund_buy_fee,
                assets[i].fund_sell_amount,
                assets[i].fund_sell_fee,
                assets[i].withholding_amount);
    }
}

void MySpi::on_query_orders(uint64_t session_id, uint64_t request_id, xlt_order_info_t *order_infos, uint32_t data_count,
                            bool is_last, xlt_error_info_t *error_info) {
    printf("on_query_orders session_id: %lu request_id: %lu data_count: %u is_last: %d\n",
            session_id, request_id, data_count, is_last);
    if (error_info != nullptr) {
        printf("Error: error_id: %d, error_msg: %s\n", error_info->error_id, error_info->error_msg);
        return;
    }

    for (uint32_t i = 0; i < data_count; ++i) {
        const xlt_order_info_t &order = order_infos[i];
        printf("Order %d:, xid: %lu, order_client_id: %u, cancel_xid: %lu, cancel_order_client_id: %u, "
               "security_code: %s, exchange_id: %d, price: %lu, quantity: %lu, order_price_type: %d, "
               "side: %d, business_type: %d, order_status: %d, qty_traded: %lu, qty_left: %lu, ",
                i + 1,
                order.xid, order.order_client_id, order.cancel_xid, order.cancel_order_client_id, order.security_code,
                (int)order.exchange_index, order.price, order.quantity, (int)order.order_price_type, (int)order.side,
                (int)order.business_type, (int)order.order_status, order.qty_traded, order.qty_left);
        printf("insert_time: %lu, "
               "update_time: %lu, cancel_time: %lu, trade_amount: %lu, order_local_id: %s, order_status: %d, "
               "order_exch_id: %s, error_id: %d, error_msg: %s\n",
                order.insert_time,
                order.update_time, order.cancel_time, order.trade_amount, order.order_local_id, (int)order.order_status,
                order.order_exch_id, order.error_id, order.error_msg);
    }

}

void MySpi::on_query_orders_by_page(uint64_t session_id, uint64_t request_id, xlt_order_info_t *order_infos,
                                    uint32_t data_count, int64_t req_count, int64_t order_sequence,
                                    int64_t query_reference, bool is_last, xlt_error_info_t *error_info) {
    printf("on_query_orders_by_page session_id: %lu request_id: %lu data_count: %u req_count: %ld, "
           "order_sequence: %ld, query_reference: %ld is_last: %d\n",
            session_id, request_id, data_count, req_count, order_sequence, query_reference, is_last);
    if (error_info != nullptr) {
        printf("Error: error_id: %d, error_msg: %s\n", error_info->error_id, error_info->error_msg);
        return;
    }
    for (uint32_t i = 0; i < data_count; ++i) {
        const xlt_order_info_t &order = order_infos[i];
        printf("Order %d:, xid: %lu, order_client_id: %u, cancel_xid: %lu, cancel_order_client_id: %u, "
               "security_code: %s, exchange_id: %d, price: %lu, quantity: %lu, order_price_type: %d, "
               "side: %d, business_type: %d, order_status: %d, qty_traded: %lu, qty_left: %lu,",
                i + 1,
                order.xid, order.order_client_id, order.cancel_xid, order.cancel_order_client_id, order.security_code,
                (int)order.exchange_index, order.price, order.quantity, (int)order.order_price_type, (int)order.side,
                (int)order.business_type, (int)order.order_status, order.qty_traded, order.qty_left);
        printf("insert_time: %lu, "
               "update_time: %lu, cancel_time: %lu, trade_amount: %lu, order_local_id: %s, order_status: %d, "
               "order_exch_id: %s, error_id: %d, error_msg: %s\n",
                order.insert_time,
                order.update_time, order.cancel_time, order.trade_amount, order.order_local_id, (int)order.order_status,
                order.order_exch_id, order.error_id, order.error_msg);
    }
}

void MySpi::on_query_order_detail(uint64_t session_id, uint64_t request_id, xlt_order_detail_t *order_details,
                                  uint32_t data_count, bool is_last, xlt_error_info_t *error_info) {
    printf("on_query_order_detail session_id: %lu request_id: %lu data_count: %u is_last: %d\n",
            session_id, request_id, data_count, is_last);
    if (error_info != nullptr) {
        printf("Error: error_id: %d, error_msg: %s\n", error_info->error_id, error_info->error_msg);
        return;
    }
    for (uint32_t i = 0; i < data_count; ++i) {
        const xlt_order_detail_t &detail = order_details[i];
        switch ( detail.detail_type ) {
            case XLTReportType::ORDER_REJECT: {
                auto order_reject = &detail.data.order_reject;
                printf("detail: %u, type: order_reject, report_id: %s, xid: %lu, order_client_id: %u, "
                       "orig_xid: %lu, orig_order_client_id: %u, security_code: %s, exchange_id: %d, "
                       "business_type: %d, side: %d, price: %lu, quantity: %lu, order_price_type: %d, "
                       "error_id: %d, error_msg: %s, report_time: %lu\n",
                        i+1,
                        order_reject->report_id,
                        order_reject->xid,
                        order_reject->order_client_id,
                        order_reject->orig_xid,
                        order_reject->orig_order_client_id,
                        order_reject->security_code,
                        (int) order_reject->exchange_index,
                        (int) order_reject->business_type,
                        (int) order_reject->side,
                        order_reject->price,
                        order_reject->quantity,
                        (int) order_reject->order_price_type,
                        order_reject->error_id,
                        order_reject->error_msg,
                        order_reject->report_time);
                break;
            }
            case XLTReportType::ORDER_RESPONSE:
            {
                auto order_response = &detail.data.order_response;
                printf("detail: %u, type: order_response, report_id: %s, xid: %lu, "
                       "order_client_id: %u, orig_xid: %lu, orig_order_client_id: %u, security_code: %s, "
                       "exchange_id: %d, business_type: %d, side: %d, price: %lu, quantity: %lu, "
                       "order_price_type: %d, leaves_qty: %ld, cum_qty: %ld, cxl_qty: %ld, exec_type: %c, "
                       "order_status: %d, error_id: %d, error_msg: %s, report_time: %lu\n",
                        i+1,
                        order_response->report_id,
                        order_response->xid,
                        order_response->order_client_id,
                        order_response->orig_xid,
                        order_response->orig_order_client_id,
                        order_response->security_code,
                        (int)order_response->exchange_index,
                        (int)order_response->business_type,
                        (int)order_response->side,
                        order_response->price,
                        order_response->quantity,
                        (int)order_response->order_price_type,
                        order_response->leaves_qty,
                        order_response->cum_qty,
                        order_response->cxl_qty,
                        order_response->exec_type,
                        (int)order_response->order_status,
                        order_response->error_id,
                        order_response->error_msg,
                        order_response->report_time
                );
                break;
            }
            case XLTReportType::TRADE_REPORT:
            {
                auto trade_report = &detail.data.trade_report;
                printf("detail: %u, type: trade_report, report_id: %s, xid: %lu, order_client_id: %u, "
                       "security_code: %s, exchange_id: %d, business_type: %d, side: %d,  "
                       "order_status: %d, price: %lu, quantity: %lu, leaves_qty: %lu, report_time: %lu\n",
                        i+1,
                        trade_report->report_id,
                        trade_report->xid,
                        trade_report->order_client_id,
                        trade_report->security_code,
                        (int)trade_report->exchange_index,
                        (int)trade_report->business_type,
                        (int)trade_report->side,
                        (int)trade_report->order_status,
                        trade_report->price,
                        trade_report->quantity,
                        trade_report->leaves_qty,
                        trade_report->report_time);
                break;
            }
            case XLTReportType::ORDER_CANCEL_FAIL:
            {
                auto cancel_fail = &detail.data.order_cancel_fail;
                printf("detail: %u, type: order_cancel_fail, report_id: %s, cancel_xid: %lu, "
                       "cancel_client_id: %u, orig_xid: %lu, orig_order_client_id: %u, security_code: %s, "
                       "exchange_id: %d, business_type: %d, error_id: %d, error_msg: %s\n",
                        i+1,
                        cancel_fail->report_id,
                        cancel_fail->xid,
                        cancel_fail->order_client_id,
                        cancel_fail->orig_xid,
                        cancel_fail->orig_order_client_id,
                        cancel_fail->security_code,
                        (int)cancel_fail->exchange_index,
                        (int)cancel_fail->business_type,
                        cancel_fail->error_id,
                        cancel_fail->error_msg);
                break;
            }
            default:
                break;
        }
    }
}

void MySpi::on_request_timeout(uint64_t session_id, uint64_t request_id) {
    printf("on_request_timeout session_id: %lu, request_id: %lu\n", session_id, request_id);
}