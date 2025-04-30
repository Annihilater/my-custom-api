#pragma once

#include <cstdint>
#include "netinet/in.h"

namespace x1 {
namespace base {

class McRecv {
public:
    /**
     * @brief 析构函数
     */
    virtual ~McRecv() = default;

    /**
     * @brief 查询订阅IP
     * @return IP地址，大端格式
     */
    uint32_t local_ip() const { return local_ip_; }

    /**
     * @brief 设置订阅IP
     * @param local_ip IP地址，大端格式
     */
    void set_local_ip(uint32_t local_ip) { local_ip_ = local_ip; }

    /**
     * @brief 添加组播地址，支持在线修改
     * @param mc_addr 组播地址
     * @return
     */
    virtual bool add_mc_addr(sockaddr_in mc_addr) = 0;

    /**
     * @brief 删除组播地址，支持在线修改
     * @param mc_addr 组播地址
     * @return
     */
    virtual bool del_mc_addr(sockaddr_in mc_addr) = 0;

    /**
     * @brief 初始化
     * @return
     */
    virtual bool initialize() = 0;

    /**
     * @brief
     * @return
     */

    /**
     * @brief 接收组播包，非阻塞
     * @param len 接收数据长度
     * @return 返回数据地址，空表示没有数据
     */
    virtual void* recv(int &len) = 0;

protected:

    // 最大支持组播个数
    static const int MAX_MC_ADDR_CNT = 16;

    // 组播订阅IP
    uint32_t local_ip_ = 0;

    // 组播地址
    sockaddr_in mc_addrs[MAX_MC_ADDR_CNT] = { 0 };

    // 实际组播地址个数
    int mc_addr_cnt = 0;
};

}

}
