import requests
import json
import geocoder
import xml.etree.ElementTree as ET
while(1):
    print("嗨，我是您的农业人工智能助手，输入1，我可以为您提供今日的农业建议；输入2，您可以向我提问农业问题;输入0退出程序")
    option=0
    option=int(input())

    if option==1:
        #调用高德api
        key = " "
        city=""
        #查询citycode
        def get_location():
            try:
                # 尝试获取GPS信息
                g = geocoder.ip('me')

                if g.ok:
                    # 如果成功获取GPS信息，返回地理位置信息
                    return f"{g.city}, {g.state}, {g.country}"
                else:
                    # 如果GPS不可用，尝试获取IP地址的地理位置信息
                    g = geocoder.ip('me')
                    if g.ok:
                        return f"地理位置: {g.city}, {g.state}, {g.country}"
                    else:
                        return "无法获取地理位置信息"
            except Exception as e:
                return f"发生错误: {str(e)}"

        location = get_location()

        #获取acode

        url = f"https://restapi.amap.com/v3/geocode/geo?address={location}&output=json&key={key}"
        response = requests.get(url)

        if response.status_code == 200:
            # 解析JSON响应
            data = json.loads(response.text)
            adcode = data["geocodes"][0]["adcode"]
            formatted_address = data["geocodes"][0]["formatted_address"]

            city = adcode
            adr=formatted_address

            print("adcode:", city)
            print("您目前的位置是:",adr)
        else:
            print("请求失败:", response.status_code)





        #查询天气
        url = "https://restapi.amap.com/v3/weather/weatherInfo?"
        extensions = "all"
        output = "json"
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

        propmt="假设你是一名农业专家，你需要根据我给你的季节，地理，白天天气，夜晚天气，白天温度,夜晚温度,白天风向,夜晚风向,白天风力,夜晚风力这些因素，分析本地的在目前情况下的土壤墒情，并依据土壤墒情和气象信息提供切实可靠的农业生产建议。请注意，你的建议应当紧紧围绕着我所提供的地理，气象信息与你提供的土壤墒情，你的建议应当充实丰富，具有实践意义与高度的可用性。"
        LocPo=" "
        var="当前季节:" + current_season + "\n白天天气:" + day_weather + "\n夜晚天气:" + night_weather + "\n白天温度:" + day_temp + "\n夜晚温度:" + night_temp + "\n白天风向:" + day_wind + "\n夜晚风向:" + night_wind + "\n白天风力:" + day_power + "\n夜晚"
        hans=propmt+var

        #调用大语言模型
        import SparkApi
        appid = " "    
        api_secret = " "   
        api_key =" "    
        domain = "generalv3" 

        Spark_url = "ws://spark-api.xf-yun.com/v3.1/chat"  


        text =[]

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
    if option==2:
        ques=""
        print("请输入你的问题，比如玉米叶发黄是什么原因，如何防治？  ：")
        ques=input()
        
        #调用大语言模型
        import SparkApi
        appid = "214c1dad"    
        api_secret = "NTE2ZDc5ZWUxMDA3ZmYxNDIxNDA2MGFi"   
        api_key ="c2d5988bb69048db0b287c4f3600be2c"    
        domain = "generalv3" 

        Spark_url = "ws://spark-api.xf-yun.com/v3.1/chat"  


        text =[]

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
                Input = ques
                question = checklen(getText("user",Input))
                SparkApi.answer =""
                print("",end = "")
                SparkApi.main(appid,api_key,api_secret,Spark_url,domain,question)
                getText("assistant",SparkApi.answer)
                break
    if option==0:
        quit()



