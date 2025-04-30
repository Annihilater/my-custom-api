#pragma once
#include "xlt_api_quote_define.h"

namespace x1{
/**
 * @brief 行情回调类
 */
class QuoteSpi
{
public:
    /**
     * @brief 登录请求响应
     * @param request_id 请求ID
     * @param success 登录是否成功
     * @param error_info 如果登录失败，返回的错误信息
     */
    virtual void on_login(uint64_t request_id, bool success, xlt_error_info_t *error_info) {};

    /**
     * @brief 快照行情通知
     * @param market_data 行情数据
     */
    virtual void on_market_data(xlt_market_data_t *market_data) {};

    /**
     * @brief 逐笔行情通知
     * @param tbt_data  逐笔数据
     */
    virtual void on_tick_by_tick(xlt_tick_by_tick_t* tbt_data){};

    /**
     * @brief 查询全量静态行情信息响应
     * @param request_id 请求ID
     * @param static_quote_full_infos 本次响应返回的全量静态行情信息列表，个数由data_count决定
     * @param data_count 本次响应返回的数据个数
     * @param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
     * @param error_info 查询发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
     * @remark 一个查询请求可能对应多个响应，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
     */
    virtual void on_query_static_quote_full_info(uint64_t request_id,
                                                 xlt_static_quote_full_info_t static_quote_full_infos[],
                                                 uint32_t data_count, bool is_last, xlt_error_info_t *error_info) {};

    /**
     * @brief 查询超时回调
     * @param request_id 超时请求ID
     */
    virtual void on_request_timeout(uint64_t request_id){};

    virtual ~QuoteSpi()=default;

};

/**
 * @brief 行情订阅接口类
 */
class QuoteApi
{
public:

    /**
     * @brief 创建QuoteApi
     * @return 创建出的QuoteApi
     */
    static QuoteApi *create_quote_api();

    /**
     * @brief 初始化API，登录之前必须调用此函数，只能初始化一次
     * @param config 配置信息
     * @return 初始化是否成功
     */
    virtual bool initialize(xlt_quote_config_t *config) = 0;

    /**
     * 注册回调接口
     * @brief 注册回调接口
     * @param spi 派生自行情响应类的实例，请在登录之前设定
     */
    virtual void register_spi(QuoteSpi *spi) = 0 ;

    /**
     * 用户登录请求
     * @brief 用户登录请求
     * @param request_id 请求ID，用于标识请求，on_login异步响应时会带回
     * @param account_name   登录账号
     * @param password  密码
     * @param pub_key 用于标识用户的公钥(长度64字节)，用户开户时申请得到
     * @return “0”表示请求发送成功，非"0"表示请求发送失败
     * @remark 此函数为异步请求，需要等待on_login响应
     */
    virtual int login(uint64_t request_id, const char *account_name, const char *password, const char *pub_key) = 0;

    /**
     * 用户登出同步阻塞请求
     * @brief 用户登出同步阻塞请求
     * @return “0”表示登出成功，非"0"表示登出失败
     * @remark 此函数为同步阻塞式，不需要异步等待登录成功，当函数返回即可进行后续操作
     */
    virtual int logout() = 0;

    /**
     * @brief 订阅全市场行情
     */
    virtual void subscribe_all() = 0;

    /**
     * @brief 取消订阅全市场行情
     */
    virtual void unsubscribe_all() = 0;

    /**
     * @brief 订阅指定市场指定证券代码的行情
     * @param security_code 证券代码数组
     * @param count 证券代码数量
     * @param exchange_index 交易所代码
     */
    virtual void subscribe(char (*security_code)[CONST_STR_SECURITY_CODE_LEN], int count, ExchangeIndex exchange_index) = 0;

    /**
     * @brief 取消订阅指定市场指定证券代码的行情
     * @param security_code 证券代码数组
     * @param count 证券代码数量
     * @param exchange_index 交易所代码
     */
    virtual void unsubscribe(char (*security_code)[CONST_STR_SECURITY_CODE_LEN], int count, ExchangeIndex exchange_index)
    = 0;

    /**
     * @brief 获取当前交易日。只有登录成功后,才能得到正确的交易日。
     * @return 返回日期，格式为。YYYYMMDD
     */
    virtual uint32_t get_trading_day() = 0;

    /**
     * @brief 查询全量静态行情信息
     * @param request_id 请求ID
     * @return "0"表示查询发送成功，非"0"表示请求失败
     * @remark 此函数为异步请求，需要等待on_login响应
     */
    virtual int query_static_quote_full_info(uint64_t request_id) = 0;

protected:
    virtual ~QuoteApi(){};

};
}

