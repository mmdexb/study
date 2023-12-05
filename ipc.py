import socket
import requests
from datetime import datetime

# 获取当前系统时间
def get_current_time():
    return datetime.now().strftime("%Y-%m-%d %H:%M:%S")

import psutil

# 获取无线局域网适配器 WLAN 的 IPv4 地址
def get_wlan_ip():
    try:
        interfaces = psutil.net_if_addrs()
        wlan_info = interfaces.get('WLAN', [])  # 替换 'WLAN' 为你的无线适配器名称
        for info in wlan_info:
            if info.family == socket.AF_INET:
                return info.address
    except Exception as e:
        print(f"获取无线局域网适配器IPv4地址失败：{e}")
        return None

# 更新Cloudflare DNS解析记录
def update_dns_record(api_token, zone_id, record_id, new_ip):
    url = f"https://api.cloudflare.com/client/v4/zones/{zone_id}/dns_records/{record_id}"
    headers = {
        "Content-Type": "application/json",
        "X-Auth-Email": "1367072295@qq.com",  # 请在此处填入你的Cloudflare邮箱
        "Authorization": f"Bearer {api_token}",
    }
    data = {
        "content": new_ip,
        "name": "test1.linuschen.ink",  # 修改为你的记录名称
        "type": "A",
        "proxied": False,
        "comment": get_current_time(),  # 使用当前系统时间作为 commit 内容
        "ttl": 60,
    }

    try:
        response = requests.put(url, headers=headers, json=data)
        if response.status_code == 200:
            print("DNS记录更新成功")
        else:
            print(f"DNS记录更新失败，HTTP状态码：{response.status_code}")
            print(response.text)
    except Exception as e:
        print(f"发生异常：{e}")

if __name__ == "__main__":
    # 请替换为你的Cloudflare API信息
    api_token = "KJV2m6IrDnPLow3QjNXd_qzmQCnakUD0umL8uExD"
    zone_id = "52313f05013baafb68caca26431039f8"
    record_id = "9b76dfc52bfb7c348120367acf9a321a"  # 可以通过调用Cloudflare API获取

    # 获取内网IP地址
    wlan_ip = get_wlan_ip()

    if wlan_ip:
        print(f"无线局域网适配器 WLAN 的IPv4地址: {wlan_ip}")

        # 更新Cloudflare DNS解析记录
        update_dns_record(api_token, zone_id, record_id, wlan_ip)
    else:
        print("无法获取无线局域网适配器 WLAN 的IPv4地址")