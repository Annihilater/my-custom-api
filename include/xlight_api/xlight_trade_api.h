#pragma once

#include "xlight_trade_struct.h"

/**
 * @class XLIGHT::API::TraderSpi
 * @brief 交易接口响应类
 */
namespace xlight {
    namespace api {
        class TradeSpi {
        public:
            virtual ~TradeSpi() = default;
            /**
             * @brief 断线通知
             * 用户断线之后需要重新调用login方法，建立连接并登录
             * @param session_id 会话ID。
             */
            virtual void on_disconnect(uint64_t session_id) {};

            /**
             * @brief 登录回调
             * @param session_id 本次登录生成的会话ID。如果登录失败则为0。
             * @param error_info 登录请求发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误。
             * @param request_id 此消息响应函数对应的请求ID
             */
            virtual void on_login(uint64_t session_id, xlt_error_info_t *error_info, uint64_t request_id) {};

            /**
             * @brief 处理订单状态通知
             *
             * 本函数用于接收订单状态通知，并根据通知内容进行相应处理。此为一个虚函数，旨在被子类重载以实现具体的处理逻辑。
             *
             * @param session_id 会话ID。
             * @param order_status_notice 包含订单状态信息的通知对象指针。该对象包含了与订单状态相关的信息，如订单ID、状态代码等。
             */
            virtual void on_order_status_notice(uint64_t session_id, xlt_order_status_notice_t *order_status_notice){};

            /**
             * @brief 申报拒绝响应
             *
             * 此函数用于处理来自交易系统的申报拒绝响应。
             *
             * @param session_id 会话ID。
             * @param order_response 申报拒绝响应数据指针。
             */
            virtual void on_order_reject(uint64_t session_id, xlt_order_reject_t *order_reject) {};

            /**
             * @brief 申报响应和撤单成功响应
             *
             * 此函数用于处理来自交易系统的申报响应和撤单成功响应。
             *
             * @param session_id 会话ID。
             * @param order_response 申报响应和撤单成功响应响应数据指针。
             */
            virtual void on_order_response(uint64_t session_id, xlt_order_response_t* order_response) {};


            /**
             * @brief 撤单失败通知
             *
             * 此函数用于处理来自交易系统的撤单失败通知。
             * @param session_id 会话ID。
             * @param order_cancel_fail 撤单失败通知数据指针。
             */
            virtual void on_order_cancel_fail(uint64_t session_id, xlt_order_cancel_fail_t *order_cancel_fail) {};

            /**
             * @brief 成交回报通知
             *
             * 此函数用于处理来自交易系统的成交回报通知。
             *
             * @param session_id 会话ID。
             * @param trade_report 成交回报通知数据指针。
             */
            virtual void on_trade_report(uint64_t session_id, xlt_trade_report_t *trade_report) {};

            /**
             * @brief 测试心跳响应
             * @param session_id
             * @param sequence
             * @param msg
             * @param timestamp
             */
            virtual void
            on_test_pong(uint64_t session_id, uint64_t sequence, uint32_t msg_len, char *msg, uint64_t timestamp) {};

//            /**
//             * @brief 原始订单执行报告（需用户自行解码）
//             *
//             * 此函数用于接收原始的订单执行报告。报告内容包括但不限于订单状态、执行细节等。
//             * 由于报告是原始形式，因此需要用户自行解码以获取具体信息。
//             *
//             * @param session_id 会话ID。
//             * @param platform_type 交易网关平台类型，用于区分回报类型。
//             * @param report 报告数据的指针，具体内容依赖于报告类型，需用户自行解码。
//             */
//            virtual void on_raw_report(uint64_t session_id, XLTExchangePlatformType platform_type, void *report) {};

            /**
             * @brief 持仓变动推送，当持仓发生变化时，会推送给用户。
             * @param session_id 会话id，登录时得到
             * @param positions 持仓列表，个数由data_count决定
             * @param data_count 持仓个数
             */
            virtual void on_positions(uint64_t session_id, xlt_position_info_t positions[], uint32_t data_count) {};

            /**
             * @brief 资金变动推送，当资金发生变化时，会推送给用户。
             * @param session_id 会话id，登录时得到
             * @param assets 资金账户列表
             * @param data_count 资金账户个数
             */
            virtual void on_assets(uint64_t session_id, xlt_asset_info_t assets[], uint32_t data_count) {};

            /**
             * @brief 持仓查询响应
             * @param session_id 会话id，登录时得到
             * @param request_id 此消息响应函数对应的请求ID
             * @param positions 本次响应返回的持仓列表，个数由data_count决定
             * @param data_count 本次响应返回的持仓个数
             * @param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
             * @param error_info 查询账户持仓发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
             * @remark 一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
             */
            virtual void on_query_positions(uint64_t session_id, uint64_t request_id, xlt_position_info_t positions[],
                                            uint32_t data_count, bool is_last, xlt_error_info_t *error_info) {};

            /**
             * @brief 请求查询资金账户响应
             * @param session_id 会话id，登录时得到
             * @param request_id 此消息响应函数对应的请求ID
             * @param assets 查询到的资金账户列表情况，个数由data_count决定
             * @param data_count 本次响应返回的持仓个数
             * @param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
             * @param error_info 查询资金账户发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
             * @remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
             */
            virtual void on_query_assets(uint64_t session_id, uint64_t request_id, xlt_asset_info_t asset[],
                                         uint32_t data_count, bool is_last, xlt_error_info_t *error_info) {};

            /**
             * @brief 订单查询响应
             * @param session_id 会话id，登录时得到
             * @param request_id 此消息响应函数对应的请求ID
             * @param order_infos 本次响应返回的订单信息，个数由data_count决定
             * @param data_count 本次响应返回的数据条数
             * @param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
             * @param error_info 查询订单时发生错误时，返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
             * @remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
             */
            virtual void on_query_orders(uint64_t session_id, uint64_t request_id, xlt_order_info_t order_infos[],
                                         uint32_t data_count, bool is_last, xlt_error_info_t *error_info) {};

            /**
             * @brief 分页请求查询报单响应
             * @param session_id 会话id，登录时得到
             * @param request_id 此消息响应函数对应的请求ID
             * @param order_infos 本次响应返回的订单信息，个数由data_count决定
             * @param data_count 本次响应返回的数据条数
             * @param req_count 分页请求的最大数量
             * @param order_sequence 分页请求的当前回报数量
             * @param query_reference 当前响应最后一条报单信息所对应的查询索引，需要记录下来，在进行下一次分页查询的时候需要用到
             * @param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
             * @param error_info 查询报单时发生错误时，返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
             * @remark 当order_sequence为0，表明当次查询没有查到任何记录，当is_last为true时，如果order_sequence等于req_count，那么表示还有报单，可以进行下一次分页查询，如果不等，表示所有报单已经查询完毕。一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线。
             */
            virtual void on_query_orders_by_page(uint64_t session_id, uint64_t request_id, xlt_order_info_t
            order_infos[], uint32_t data_count, int64_t req_count, int64_t order_sequence, int64_t query_reference,
            bool is_last, xlt_error_info_t *error_info) {};

            /**
             * @brief 订单明细查询响应
             * @param session_id 会话id，登录时得到
             * @param request_id 此消息响应函数对应的请求ID
             * @param order_details 本次响应返回的流水明细，个数由data_count决定
             * @param data_count 本次响应返回的数据条数
             * @param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
             * @param error_info 订单明细查询发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
             * @remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
             */
            virtual void on_query_order_detail(uint64_t session_id, uint64_t request_id, xlt_order_detail_t
            order_details[], uint32_t data_count, bool is_last, xlt_error_info_t *error_info) {};

            /**
             * @brief 查询超时回调
             * @param session_id 会话id，登录时得到
             * @param request_id 超时请求ID
             */
            virtual void on_request_timeout(uint64_t session_id, uint64_t request_id){};
        };
    }
}

/**
 * @class XLIGHT::API::TraderApi
 * @brief 交易接口类
 */
namespace xlight {
    namespace api {
        class TradeApi {
        public:
            /**
             * 创建交易api实例，只能创建一次
             * @brief 创建实例
             * @return 返回交易接口实例
             */
            static TradeApi *create_trade_api();

            /**
             * @brief 初始化API，登录之前必须调用此函数，只能初始化一次
             * @param config 配置信息
             * @return 初始化是否成功
             */
            virtual bool initialize(xlt_trade_config_t * config) = 0;

            /**
             * 注册回调接口
             * @brief 注册回调接口
             * @param spi 派生自交易响应类的实例，请在登录之前设定
             */
            virtual void register_spi(TradeSpi *spi) = 0;

            /**
             * 用户登录请求
             * @brief 用户登请求
             * @param client_id 客户端标识ID
             * @param account_name 帐号
             * @param password 交易密码
             * @param pub_key 用于标识用户的公钥(长度64字节)，用户开户时申请得到
             * @param biz_type 业务类型ID（暂未启用）
             * @param request_id 用于用户定位请求响应的ID，由用户自定义
             * @param resume_type 数据（订单回报等）重传方式，默认值为XLTResumeType::RESUME
             * @param start_sequence 恢复时的起始序列号，默认值为0，当resume_type为XLTResumeType::SPECIFY时有效
             * @return 查询请求发送是否成功，"0"表示成功，非"0"表示出错，此时用户可以调用get_last_error()来获取错误信息。
             */
            virtual int login(uint16_t client_id, const char *account_name, const char *password, const char *pub_key,
                              uint32_t biz_type,
                              uint64_t request_id, XLTResumeType resume_type = XLTResumeType::RESUME, uint64_t
                              start_sequence = 0) = 0;

            /**
             * 登出请求
             * @brief 登出请求
             * @param session_id 会话id，登录时得到
             * @return "0"表示成功，非"0"表示出错，此时用户可以调用get_last_error()来获取错误信息。
             */
            virtual int logout(uint64_t session_id) = 0;

            /**
             * @brief 测试心跳请求
             * @param session_id
             * @param sequence
             * @param msg
             * @return
             */
            virtual int test_ping(uint64_t session_id, uint64_t sequence, uint32_t msg_len) = 0;

            /**
             * @brief 获取当前交易日。只有登录成功后,才能得到正确的交易日。
             * @return 返回日期，格式为。YYYYMMDD
             */
            virtual uint32_t get_trading_day() = 0;
//
//            /**
//             * @brief 获取错误信息
//             * @return 错误信息
//             */
//            virtual xlt_error_info_t get_last_error() = 0;
//
            /**
             * 报单录入请求，所有业务统一报单接口，根据业务类型字段区分不同业务。
             * Xlight接收订单后，会在报单响应函数on_order_reject、on_order_response中返回订单状态,
             * 之后所有的成交明细会在on_trade_report中返回，当订单到达终止状态会触发订单状态结束响应。
             * @brief 委托
             * @param order 委托信息
             * @param session_id   资金账户对应的session_id，登录时得到
             * @param algo_order_id 如果是普通交易账号填0；如果是算法厂商，则填写母单ID。
             * @return 返回系统生成的订单ID，如果为‘0’表示订单发送失败，非"0"表示订单发送成功，用户需要记录下返回的order_xid，它保证一个交易日内唯一，不同的交易日不保证唯一性。
             */
            virtual uint64_t insert_order(uint64_t session_id, xlt_order_insert_info_t *order,  uint64_t
            algo_order_id = 0) = 0;

            /**
             * 撤单请求。
             * 如果撤单成功，会在报单响应函数on_order_response里返回原单部撤或者全撤的消息，
             * 如果不成功，会在on_order_reject、on_order_cancel_error响应函数中返回错误原因。
             * @brief 撤单
             * @param cancel_info   撤单信息
             * @param session_id    会话id，登录时得到
             * @param algo_order_id 如果是普通交易账号填0；如果是算法厂商，则填写母单ID。
             * @return  撤单在xLight系统中的ID,如果为‘0’表示撤单发送失败，非"0"表示撤单发送成功，用户需要记录下返回的order_cancel_xid，它保证一个交易日内唯一，不同的交易日不保证唯一性。
             */
            virtual uint64_t
            cancel_order(uint64_t session_id, xlt_order_cancel_info_t *cancel_info, uint64_t algo_order_id = 0) = 0;

            /**
             * @brief 请求查询投资者持仓
             * @param session_id 会话id，登录时得到
             * @param request_id 用于用户定位查询响应的ID，由用户自定义
             * @param security_code 需要查询持仓的合约代码，可以为空，表示查询全市场，如果不为空，请不带空格
             * @param exchange_index 需要查询持仓的合约所在市场，默认为0。market不指定或者为非0的其他非有效值情况下，可能由于证券代码沪深2个市场有重复，而导致查询不到所需的持仓。如果想正确查询指定持仓，请指定market
             * @param algo_order_id 如果是普通交易账号填0；如果是算法厂商，则填写母单ID。
             * @return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用get_last_error()来获取错误信息
             * @remark 该方法如果用户提供了合约代码，则会查询此合约的持仓信息，如果合约代码为空，则默认查询所有持仓信息。
             */
            virtual int query_positions(uint64_t session_id, uint64_t request_id, char *security_code,
                                        XLTExchangeIndex exchange_index, uint64_t algo_order_id = 0) = 0;

            /**
             * @brief 请求查询资产
             * @param session_id 会话id，登录时得到
             * @param request_id 用于用户定位查询响应的ID，由用户自定义
             * @param algo_order_id 如果是普通交易账号填0；如果是算法厂商，则填写母单ID。
             * @return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用get_last_error()来获取错误信息
             */
            virtual int query_assets(uint64_t session_id, uint64_t request_id, uint64_t algo_order_id = 0) = 0;

            /**
             * @brief 请求查询订单
             * @param session_id 会话id，登录时得到
             * @param request_id 用于用户定位查询响应的ID，由用户自定义
             * @param order_query_param 需要查询的订单相关筛选条件，其中xid如果不为0，则只查询指定订单，否则根据后续条件进行查询：
             * 其中证券代码可以为空，则默认所有存在的证券代码，如果不为空，请不带空格,
             * 其中起始时间格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点，结束时间格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
             * @param algo_order_id 如果是普通交易账号填0；如果是算法厂商，则填写母单ID。
             * @return 查询请求发送是否成功，"0"表示成功，非"0"表示出错，此时用户可以调用get_last_error()来获取错误信息
             */
            virtual int query_orders(uint64_t session_id, uint64_t request_id, const xlt_order_query_param_t
            *order_query_param, uint64_t algo_order_id = 0) = 0;

            /**
             * @brief 分页请求查询报单
             * @param session_id 会话id，登录时得到
             * @param request_id 用于用户定位查询响应的ID，由用户自定义
             * @param query_param 需要分页查询订单的条件，如果第一次查询，那么query_param.reference填0
             * @param algo_order_id 如果是普通交易账号填0；如果是算法厂商，则填写母单ID。
             * @return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用get_last_error()来获取错误信息
             * @remark 该方法支持分页查询，注意用户需要记录下最后一笔查询结果的reference以便用户下次查询使用
             */
            virtual int query_orders_by_page(uint64_t session_id, uint64_t request_id,
                                             xlt_order_query_by_page_param_t *page_query_param, uint64_t algo_order_id = 0) = 0;

            /**
             * @brief 根据委托编号请求查询订单明细
             * @param session_id 会话id，登录时得到
             * @param request_id 用于用户定位查询响应的ID，由用户自定义
             * @param order_xid 需要查询的订单编号，即委托成功时返回的order_xid
             * @param algo_order_id 如果是普通交易账号填0；如果是算法厂商，则填写母单ID。
             * @return 查询是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用get_last_error()来获取错误信息
             * @remark 此函数查询出的结果可能对应多个查询结果响应
             */
            virtual int query_order_details(uint64_t session_id, uint64_t request_id, uint64_t order_xid, uint64_t algo_order_id = 0) = 0;

        protected:
            virtual ~TradeApi() = default;
        };
    }
}

