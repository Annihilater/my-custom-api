#include <csignal>
#include <cstdlib>
#include <sys/resource.h>
#include <iostream>
#include "xlt_api_quote.h"
#include <fstream>
#include <array>
#include <atomic>

using namespace xlight::api;
using namespace std;

// 测试账号信息
char pub_key_base64[256] = "vU2VTSwdG4mLzIb69dS2EGKmdfZj6sJlspQoyq2dl7kZdEK8GfK2xXtolkejFNSHBqNe6nvqKXUelfbhc3lhAg==";
char account_name[XLT_ACCOUNT_NAME_LEN] = "account_test";
char password[256] = "passwd_123456";
std::atomic_bool global_login_success(false);   ///< 是否正在登录标识
std::atomic_bool global_login_finished(false);  ///< 已建立会话标识

class MyQuoteSpi:public QuoteSpi
{
private:
    std::ofstream md_csv_;              ///< 快照输出csv
    std::ofstream tbt_csv_;             ///< 逐笔输出csv
public:
    MyQuoteSpi():
            md_csv_("md.csv"),
            tbt_csv_("tbt.csv")
    {
        md_csv_<<md_public_header()<<md_stock_header()<<md_bond_header()<<md_opt_header()<<std::endl;
        tbt_csv_<<tbt_header()<<std::endl;
    };
    ~MyQuoteSpi(){
    };

    void on_login(uint64_t request_id, bool success, xlt_error_info_t *error_info) override {
        printf("on_login request_id: %lu, success: %d", request_id, success);
        global_login_success.store(success);
        global_login_finished.store(true);
    }

    static std::string tbt_header() {
        return "exchange_id, ticker, data_time, type, "
               "entrust_channel_no, entrust_seq, entrust_price, entrust_qty, entrust_side, entrust_ord_type, entrust_order_no, "
               "trade_channel_no, trade_seq, trade_price, trade_qty, trade_money, trade_bid_no, trade_ask_no, trade_trade_flag, "
               "state_channel_no, state_seq, state_flag, ";
    };

    static std::string md_public_header(){
        return "exchange_id, ticker, last_price, pre_close_price, open_price, high_price, low_price, close_price, "
               "pre_total_long_position, total_long_position, pre_settle_price, settle_price, "
               "upper_limit_price, lower_limit_price, pre_delta, curr_delta, "
               "data_time, qty, turnover, avg_price, trades_count, ticker_status, data_type, data_type_v2, "
               "bid_0, bid_1, bid_2, bid_3, bid_4, bid_5, bid_6, bid_7, bid_8, bid_9, "
               "ask_0, ask_1, ask_2, ask_3, ask_4, ask_5, ask_6, ask_7, ask_8, ask_9, "
               "bid_qty_0, bid_qty_1, bid_qty_2, bid_qty_3, bid_qty_4, bid_qty_5, bid_qty_6, bid_qty_7, bid_qty_8, bid_qty_9, "
               "ask_qty_0, ask_qty_1, ask_qty_2, ask_qty_3, ask_qty_4, ask_qty_5, ask_qty_6, ask_qty_7, ask_qty_8, ask_qty_9, "
               "bid_queue_cnt, offer_queue_cnt, "
                ;
    };

    static std::string md_stock_header(){
        std::array<std::string, 32> headers = {
                "total_bid_qty", "total_ask_qty", "ma_bid_price", "ma_ask_price", "ma_bond_bid_price", "ma_bond_ask_price",
                "yield_to_maturity", "iopv", "etf_buy_count", "etf_sell_count", "etf_buy_qty", "etf_buy_money", "etf_sell_qty", "etf_sell_money",
                "total_warrant_exec_qty", "warrant_lower_price", "warrant_upper_price", "cancel_buy_count", "cancel_sell_count",
                "cancel_buy_qty", "cancel_sell_qty", "cancel_buy_money", "cancel_sell_money", "total_buy_count", "total_sell_count",
                "duration_after_buy", "duration_after_sell", "num_bid_orders", "num_ask_orders", "pre_iopv", "r1", "r2"};
        std::string result;
        for (auto & header : headers) {
            result += "stk_" + header + ", ";
        }
        return result;
    };

    static std::string md_bond_header(){
        std::array<std::string, 29> headers = {
                "total_bid_qty", "total_ask_qty", "ma_bid_price", "ma_ask_price", "ma_bond_bid_price", "ma_bond_ask_price",
                "yield_to_maturity", "match_lastpx", "ma_bond_price", "match_qty", "match_turnover", "r4", "r5", "r6", "r7", "r8",
                "cancel_buy_count", "cancel_sell_count", "cancel_buy_qty", "cancel_sell_qty", "cancel_buy_money", "cancel_sell_money",
                "total_buy_count", "total_sell_count", "duration_after_buy", "duration_after_sell",
                "num_bid_orders", "num_ask_orders", "instrument_status"};
        std::string result;
        for (auto & header : headers) {
            result += "bond_" + header + ", ";
        }
        return result;
    };

    static std::string md_opt_header(){
        return "opt_auction_price, opt_auction_qty, opt_last_enquiry_time";
    };
    static std::string md_stock_none(){
        std::string result;
        for (int i=0;i<32;i++){
            result += "0, ";
        }
        return result;
    };

    static std::string md_bond_none(){
        std::string result;
        for (int i=0;i<29;i++){
            result += "0, ";
        }
        return result;
    };

    static std::string md_opt_none(){
        return "0, 0, 0, ";
    }

    void on_market_data(xlt_market_data_t *market_data) override {
        std::cout << "on_market_data ticker: " << std::string(market_data->security_code)
                  << ", exchange: " << (int)market_data->exchange_index << std::endl;
//        md_timestamp();
//        return;
        md_csv_ << (int)market_data->exchange_index << ", ";
        md_csv_ << market_data->security_code << ", ";
        md_csv_ << market_data->last_price << ", ";
        md_csv_ << market_data->pre_close_price << ", ";
        md_csv_ << market_data->open_price << ", ";
        md_csv_ << market_data->high_price << ", ";
        md_csv_ << market_data->low_price << ", ";
        md_csv_ << market_data->close_price << ", ";
        md_csv_ << market_data->pre_total_long_position << ", ";
        md_csv_ << market_data->total_long_position << ", ";
        md_csv_ << market_data->pre_settle_price << ", ";
        md_csv_ << market_data->settle_price << ", ";
        md_csv_ << market_data->upper_limit_price << ", ";
        md_csv_ << market_data->lower_limit_price << ", ";
        md_csv_ << market_data->pre_delta<<", ";
        md_csv_ << market_data->curr_delta<<", ";
        md_csv_ << market_data->data_time<<", ";
        md_csv_ << market_data->qty<<", ";
        md_csv_ << market_data->turnover<<", ";
        md_csv_ << market_data->avg_price<<", ";


        md_csv_<<market_data->bid_queue_cnt<<", ";
//        for (int i=0;i<50;i++){
//            md_csv_<<"bid_queue["<<i<<"]: "<<market_data->bid_queue[i]<<", ";
//        }
        md_csv_<<market_data->ask_queue_cnt<<", ";
//        for (int i=0;i<50;i++){
//            md_csv_<<market_data->ask_queue[i]<<", ";
//        }

        md_csv_ << market_data->trades_count<<", ";
        md_csv_ << std::string(market_data->ticker_status, 8)<<", ";
        md_csv_ << market_data->data_type<<", ";
        md_csv_ << market_data->data_type<<", ";

        if ( market_data->data_type == MARKETDATA_ACTUAL) {
            md_csv_<<market_data->ex_data.stk.total_bid_qty<<", ";
            md_csv_<<market_data->ex_data.stk.total_ask_qty<<", ";
            md_csv_<<market_data->ex_data.stk.ma_bid_price<<", ";
            md_csv_<<market_data->ex_data.stk.ma_ask_price<<", ";
            md_csv_<<market_data->ex_data.stk.ma_bond_bid_price<<", ";
            md_csv_<<market_data->ex_data.stk.ma_bond_ask_price<<", ";
            md_csv_<<market_data->ex_data.stk.yield_to_maturity<<", ";
            md_csv_<<market_data->ex_data.stk.iopv<<", ";
            md_csv_<<market_data->ex_data.stk.etf_buy_count<<", ";
            md_csv_<<market_data->ex_data.stk.etf_sell_count<<", ";
            md_csv_<<market_data->ex_data.stk.etf_buy_qty<<", ";
            md_csv_<<market_data->ex_data.stk.etf_buy_money<<", ";
            md_csv_<<market_data->ex_data.stk.etf_sell_qty<<", ";
            md_csv_<<market_data->ex_data.stk.etf_sell_money<<", ";
            md_csv_<<market_data->ex_data.stk.total_warrant_exec_qty<<", ";
            md_csv_<<market_data->ex_data.stk.warrant_lower_price<<", ";
            md_csv_<<market_data->ex_data.stk.warrant_upper_price<<", ";
            md_csv_<<market_data->ex_data.stk.cancel_buy_count<<", ";
            md_csv_<<market_data->ex_data.stk.cancel_sell_count<<", ";
            md_csv_<<market_data->ex_data.stk.cancel_buy_qty<<", ";
            md_csv_<<market_data->ex_data.stk.cancel_sell_qty<<", ";
            md_csv_<<market_data->ex_data.stk.cancel_buy_money<<", ";
            md_csv_<<market_data->ex_data.stk.cancel_sell_money<<", ";
            md_csv_<<market_data->ex_data.stk.total_buy_count<<", ";
            md_csv_<<market_data->ex_data.stk.total_sell_count<<", ";
            md_csv_<<market_data->ex_data.stk.duration_after_buy<<", ";
            md_csv_<<market_data->ex_data.stk.duration_after_sell<<", ";
            md_csv_<<market_data->ex_data.stk.num_bid_orders<<", ";
            md_csv_<<market_data->ex_data.stk.num_ask_orders<<", ";
            md_csv_<<market_data->ex_data.stk.pre_iopv<<", ";
            md_csv_<<market_data->ex_data.stk.r1<<", ";
            md_csv_<<market_data->ex_data.stk.r2<<", ";
            md_csv_<<md_bond_none();
            md_csv_<<md_opt_none();
        } else if ( market_data->data_type == MARKETDATA_BOND) {
            md_csv_<<md_stock_none();
            md_csv_<<market_data->ex_data.bond.total_bid_qty<<", ";
            md_csv_<<market_data->ex_data.bond.total_ask_qty<<", ";
            md_csv_<<market_data->ex_data.bond.ma_bid_price<<", ";
            md_csv_<<market_data->ex_data.bond.ma_ask_price<<", ";
            md_csv_<<market_data->ex_data.bond.ma_bond_bid_price<<", ";
            md_csv_<<market_data->ex_data.bond.ma_bond_ask_price<<", ";
            md_csv_<<market_data->ex_data.bond.yield_to_maturity<<", ";
            md_csv_<<market_data->ex_data.bond.match_lastpx<<", ";
            md_csv_<<market_data->ex_data.bond.ma_bond_price<<", ";
            md_csv_<<market_data->ex_data.bond.match_qty<<", ";
            md_csv_<<market_data->ex_data.bond.match_turnover<<", ";
            md_csv_<<market_data->ex_data.bond.r4<<", ";
            md_csv_<<market_data->ex_data.bond.r5<<", ";
            md_csv_<<market_data->ex_data.bond.r6<<", ";
            md_csv_<<market_data->ex_data.bond.r7<<", ";
            md_csv_<<market_data->ex_data.bond.r8<<", ";
            md_csv_<<market_data->ex_data.bond.cancel_buy_count<<", ";
            md_csv_<<market_data->ex_data.bond.cancel_sell_count<<", ";
            md_csv_<<market_data->ex_data.bond.cancel_buy_qty<<", ";
            md_csv_<<market_data->ex_data.bond.cancel_sell_qty<<", ";
            md_csv_<<market_data->ex_data.bond.cancel_buy_money<<", ";
            md_csv_<<market_data->ex_data.bond.cancel_sell_money<<", ";
            md_csv_<<market_data->ex_data.bond.total_buy_count<<", ";
            md_csv_<<market_data->ex_data.bond.total_sell_count<<", ";
            md_csv_<<market_data->ex_data.bond.duration_after_buy<<", ";
            md_csv_<<market_data->ex_data.bond.duration_after_sell<<", ";
            md_csv_<<market_data->ex_data.bond.num_bid_orders<<", ";
            md_csv_<<market_data->ex_data.bond.num_ask_orders<<", ";
            md_csv_<<std::string(market_data->ex_data.bond.instrument_status, 8)<<", ";
            md_csv_<<md_opt_none();
        }
        md_csv_ << endl;
    };

    void on_tick_by_tick(xlt_tick_by_tick_t *tbt_data) override {
        std::cout << "on_tick_by_tick ticker: " << std::string(tbt_data->security_code)
                  << ", exchange: " << tbt_data->exchange_index << std::endl;
//        tbt_timestamp();
//        return;

        tbt_csv_ << (int)tbt_data->exchange_index << ", ";
        tbt_csv_ << tbt_data->security_code << ", ";
//        tbt_csv_ << tbt_data->seq << ", ";
        tbt_csv_ << tbt_data->data_time << ", ";
        tbt_csv_ << (int)tbt_data->type << ", ";
        if (tbt_data->type == XLTTbtType::TBT_ENTRUST) {
            tbt_csv_ << tbt_data->data.entrust.channel_no << ", ";
            tbt_csv_ << tbt_data->data.entrust.seq << ", ";
            tbt_csv_ << tbt_data->data.entrust.price << ", ";
            tbt_csv_ << tbt_data->data.entrust.qty << ", ";
            tbt_csv_ << tbt_data->data.entrust.side << ", ";
            tbt_csv_ << tbt_data->data.entrust.ord_type << ", ";
            tbt_csv_ << tbt_data->data.entrust.order_no << ", ";
            tbt_csv_ << "0, 0, 0.0, 0, 0.0, 0, 0, N, ";
            tbt_csv_ << "0, 0, , ";
        } else if (tbt_data->type == XLTTbtType::TBT_TRADE) {
            tbt_csv_ << "0, 0, 0.0, 0, , , 0, ";
            tbt_csv_ << tbt_data->data.trade.channel_no << ", ";
            tbt_csv_ << tbt_data->data.trade.seq << ", ";
            tbt_csv_ << tbt_data->data.trade.price << ", ";
            tbt_csv_ << tbt_data->data.trade.qty << ", ";
            tbt_csv_ << tbt_data->data.trade.money << ", ";
            tbt_csv_ << tbt_data->data.trade.bid_no << ", ";
            tbt_csv_ << tbt_data->data.trade.ask_no << ", ";
            tbt_csv_ << tbt_data->data.trade.trade_flag << ", ";
            tbt_csv_ << "0, 0, , ";
        } else {
            tbt_csv_ << "0, 0, 0.0, 0, , , 0, ";
            tbt_csv_ << "0, 0, 0.0, 0, 0.0, 0, 0, N, ";
            tbt_csv_ << tbt_data->data.state.channel_no << ", ";
            tbt_csv_ << tbt_data->data.state.seq << ", ";
            tbt_csv_ << std::string(tbt_data->data.state.flag, 8) << ", ";
        }
        tbt_csv_<<std::endl;
    };

    virtual void
    on_query_static_quote_full_info(uint64_t request_id, xlt_static_quote_full_info_t static_quote_full_infos[], uint32_t data_count,
                                    bool is_last, xlt_error_info_t *error_info) override {
        printf("on_query_static_quote_full_info request_id: %lu, data_count: %u, is_last: %d\n",
                request_id, data_count, is_last);
        if (error_info != nullptr) {
            printf("on_query_static_quote_full_info error_id: %d, error_msg: %s\n",
                    error_info->error_id, error_info->error_msg);
            return;
        }
        for (uint32_t i = 0; i < data_count; ++i) {
            printf("security_full_info[%u]: exchange_index=%d, security_code=%s, security_name=%s, "
                          "security_type=%d, qualification_class=%d, is_registration=%d, is_VIE=%d, is_noprofit=%d, "
                          "is_weighted_voting_rights=%d, is_have_price_limit=%d, upper_limit_price=%.4f, "
                          "lower_limit_price=%.4f, pre_close_price=%.4f, price_tick=%.4f, bid_qty_upper_limit=%d, \n",
                    i,
                    (int)static_quote_full_infos[i].exchange_index,
                    static_quote_full_infos[i].security_code,
                    static_quote_full_infos[i].security_name,
                    (int)static_quote_full_infos[i].security_type,
                    (int)static_quote_full_infos[i].qualification_class,
                    static_quote_full_infos[i].is_registration,
                    static_quote_full_infos[i].is_VIE,
                    static_quote_full_infos[i].is_noprofit,
                    static_quote_full_infos[i].is_weighted_voting_rights,
                    static_quote_full_infos[i].is_have_price_limit,
                    static_quote_full_infos[i].upper_limit_price,
                    static_quote_full_infos[i].lower_limit_price,
                    static_quote_full_infos[i].pre_close_price,
                    static_quote_full_infos[i].price_tick,
                    static_quote_full_infos[i].bid_qty_upper_limit
            );
            printf("bid_qty_lower_limit=%d, bid_qty_unit=%d, ask_qty_upper_limit=%d, ask_qty_lower_limit=%d, "
                          "ask_qty_unit=%d, market_bid_qty_upper_limit=%d, market_bid_qty_lower_limit=%d, "
                          "market_bid_qty_unit=%d, market_ask_qty_upper_limit=%d, market_ask_qty_lower_limit=%d, "
                          "market_ask_qty_unit=%d, security_status=%d\n",
                    static_quote_full_infos[i].bid_qty_lower_limit,
                    static_quote_full_infos[i].bid_qty_unit,
                    static_quote_full_infos[i].ask_qty_upper_limit,
                    static_quote_full_infos[i].ask_qty_lower_limit,
                    static_quote_full_infos[i].ask_qty_unit,
                    static_quote_full_infos[i].market_bid_qty_upper_limit,
                    static_quote_full_infos[i].market_bid_qty_lower_limit,
                    static_quote_full_infos[i].market_bid_qty_unit,
                    static_quote_full_infos[i].market_ask_qty_upper_limit,
                    static_quote_full_infos[i].market_ask_qty_lower_limit,
                    static_quote_full_infos[i].market_ask_qty_unit,
                    static_quote_full_infos[i].security_status);
        }
    }

};

int main() {
    xlt_quote_config_t config = {
            ".", // 文件路径
            XLTLogLevel::LOG_DEBUG, // 日志基本
            64, // 内存池大小，单位MB
            {"192.168.17.22:6062"}, // 交易网关地址, 如"192.168.1.1:8080"
            "0.0.0.0",  ///< 本地网卡地址
            false,  ///< 是否使用EFVI
            false,  ///< 仅接收level1行情，如果false，则根据用户权限优先接收level2行情
            false   ///< 是否保序
    };
    MyQuoteSpi * my_spi = new MyQuoteSpi();
    QuoteApi * my_api = QuoteApi::create_quote_api();
    if (!my_api->initialize(&config)) {
        printf("Failed to initialize QuoteApi\n");
        return -1;
    }
    my_api->register_spi(my_spi);
    my_api->subscribe_all();
//    char subscribe_securitys[3][XLT_SECURITY_CODE_LEN] = {"000001", "000012", "118004"};
//    my_api->subscribe(subscribe_securitys, 3, XLTExchangeType::EXCHANGE_SH);

    auto result = my_api->login(1, account_name, password, pub_key_base64);

    if ( result > 0 ) {
        printf("Login request failed!!! error_id: %d\n",  result);
        return -1;
    }

    // 等待登录完成
    while (global_login_finished.load() == false) {
        usleep(1000);
    }

    // 登录失败
    if (!global_login_success.load()) {
        printf("Login failed!!!\n");
        return -1;
    }

    // 查询所有静态行情信息
    my_api->query_static_quote_full_info(2);

    while ( true) {
        usleep(3000*1000);
    }
    return 0;

}
