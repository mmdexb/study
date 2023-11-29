import tkinter as tk
from tkinter import scrolledtext
import threading
import requests
import json
import geocoder
# 其他必要的导入...

# 您的核心函数...
# 示例：get_agriculture_advice() 和 answer_agriculture_question()

# 创建主窗口
root = tk.Tk()
root.title("农业人工智能助手")

# 创建文本区域显示结果
text_area = scrolledtext.ScrolledText(root, state='disabled', height=10)
text_area.pack(pady=10)

# 在单独的线程中执行长时间运行的任务
def threaded_task(func, *args):
    result = func(*args)
    text_area.config(state=tk.NORMAL)
    text_area.insert(tk.END, result + '\n')
    text_area.config(state=tk.DISABLED)

# 集成您的逻辑代码
def get_agriculture_advice():
    # ... 您的获取农业建议的代码 ...
    pass

def answer_agriculture_question():
    # ... 您的回答农业问题的代码 ...
    pass

# 创建按钮和事件
def on_advice_button_click():
    threading.Thread(target=threaded_task, args=(get_agriculture_advice,)).start()

def on_question_button_click():
    threading.Thread(target=threaded_task, args=(answer_agriculture_question,)).start()

advice_button = tk.Button(root, text="获取农业建议", command=on_advice_button_click)
advice_button.pack(pady=5)

question_button = tk.Button(root, text="提问农业问题", command=on_question_button_click)
question_button.pack(pady=5)

# 运行主循环
root.mainloop()
