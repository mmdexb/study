import requests
import json

#调用高德api

url = "https://restapi.amap.com/v3/weather/weatherInfo?"
city = "370211"
extensions = "all"
output = "json"
key = "e4446083c70b225d4a78fc245649e583"

params = {
    "city": city,
    "extensions": extensions,
    "output": output,
    "key": key
}

response = requests.get(url, params=params)
data = response.json()

# 将数据保存到 JSON 文件
with open("weather_data.json", "w") as file:
    json.dump(data, file)

# 从 JSON 文件加载数据为字典对象
with open("weather_data.json", "r") as file:
    data = json.load(file)

first_cast = data['forecasts'][0]['casts'][0]

# 将提取的数据作为新的变量
day_weather = first_cast['dayweather']
night_weather = first_cast['nightweather']
day_temp = first_cast['daytemp']
night_temp = first_cast['nighttemp']
day_wind = first_cast['daywind']
night_wind = first_cast['nightwind']
day_power = first_cast['daypower']
night_power = first_cast['nightpower']

print("今日天气:")
print("白天天气:", day_weather)
print("夜晚天气:", night_weather)
print("白天温度:", day_temp)
print("夜晚温度:", night_temp)
print("白天风向:", day_wind)
print("夜晚风向:", night_wind)
print("白天风力:", day_power)
print("夜晚风力:", night_power)

from datetime import datetime

def get_season(month):
    if 3 <= month <= 5:
        return "春季"
    elif 6 <= month <= 8:
        return "夏季"
    elif 9 <= month <= 11:
        return "秋季"
    else:
        return "冬季"

# 获取当前日期
current_date = datetime.now()

# 提取年、月、日
current_year = current_date.year
current_month = current_date.month
current_day = current_date.day

# 判断季节
current_season = get_season(current_month)

# 打印结果
print(f"今天是{current_year}年{current_month}月{current_day}日，属于{current_season}。")

#制作内容

propmt="假设你是农业专家，你需要根据我给你的季节，地理位置特征，白天天气，夜晚天气，白天温度,夜晚温度,白天风向,夜晚风向,白天风力,夜晚风力,这几个参数，你需要综合这几个参数，为今天的农业生产提出切实可靠的建议,请注意，你应该综合考虑季节，地理特征，气象信息，你的建议需要充实，可靠，切合实际，并且考虑全面，考虑到全部的因素对农业的影响。"
LocPo="土壤类型多样，包括沿海地区的沙质土壤和内陆地区的黏土质地,位于黄海沿岸，黄岛区受到海洋调节影响，气候较为温和。四季分明，夏季相对温暖，冬季较为寒冷,地形包括沿海平原和一些内陆丘陵地带"
var="当前季节:" + current_season + "\n白天天气:" + day_weather + "\n夜晚天气:" + night_weather + "\n白天温度:" + day_temp + "\n夜晚温度:" + night_temp + "\n白天风向:" + day_wind + "\n夜晚风向:" + night_wind + "\n白天风力:" + day_power + "\n夜晚"
hans=propmt+var
'''
# 替换为你的 API 密钥
api_key = "sk-FAS4inga85jqlgxSimdJiKbjq4XjmEiptcpuN8VOeXThzwl1"

# 请求的 URL
url = "https://api.chatanywhere.com.cn/v1/chat/completions"

# 请求头
headers = {
    "Content-Type": "application/json",
    "Authorization": f"Bearer {api_key}"
}

# 请求体
data = {
    "model": "gpt-3.5-turbo",
    "messages": [{"role": "user", "content": hans}],
    "temperature": 0.7
}

# 发送 POST 请求
response = requests.post(url, headers=headers, json=data)


# 提取出其中的message中的content和stop reson作为新变量
completion_data = response.json()

# 获取message中的content和finish_reason
content = completion_data['choices'][0]['message']['content']
finish_reason = completion_data['choices'][0]['finish_reason']

# 打印新的变量
print("新的变量:")
print("生成的内容:", content)
print("停止原因:", finish_reason)

'''

import SparkApi
#以下密钥信息从控制台获取
appid = "214c1dad"     #填写控制台中获取的 APPID 信息
api_secret = "NTE2ZDc5ZWUxMDA3ZmYxNDIxNDA2MGFi"   #填写控制台中获取的 APISecret 信息
api_key ="c2d5988bb69048db0b287c4f3600be2c"    #填写控制台中获取的 APIKey 信息

#用于配置大模型版本，默认“general/generalv2”
#domain = "general"   # v1.5版本
domain = "generalv2"    # v2.0版本
#云端环境的服务地址
#Spark_url = "ws://spark-api.xf-yun.com/v1.1/chat"  # v1.5环境的地址
Spark_url = "ws://spark-api.xf-yun.com/v2.1/chat"  # v2.0环境的地址


text =[]

# length = 0

def getText(role,content):
    jsoncon = {}
    jsoncon["role"] = role
    jsoncon["content"] = content
    text.append(jsoncon)
    return text

def getlength(text):
    length = 0
    for content in text:
        temp = content["content"]
        leng = len(temp)
        length += leng
    return length

def checklen(text):
    while (getlength(text) > 8000):
        del text[0]
    return text
    


if __name__ == '__main__':
    text.clear
    while(1):
        Input = hans
        question = checklen(getText("user",Input))
        SparkApi.answer =""
        print("",end = "")
        SparkApi.main(appid,api_key,api_secret,Spark_url,domain,question)
        getText("assistant",SparkApi.answer)
        break
        


