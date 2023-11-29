import geocoder

def get_location():
    try:
        # 尝试获取GPS信息
        g = geocoder.ip('me')

        if g.ok:
            # 如果成功获取GPS信息，返回地理位置信息
            return f"地理位置: {g.city}, {g.state}, {g.country}"
        else:
            # 如果GPS不可用，尝试获取IP地址的地理位置信息
            g = geocoder.ip('me')
            if g.ok:
                return f"地理位置: {g.city}, {g.state}, {g.country}"
            else:
                return "无法获取地理位置信息"
    except Exception as e:
        return f"发生错误: {str(e)}"

if __name__ == "__main__":
    location = get_location()
    print(location)
