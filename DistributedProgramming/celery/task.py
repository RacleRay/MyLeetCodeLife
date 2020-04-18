from celery import Celery
import time

# $ pip install celery[Redis]
# $ celery worker -A task loglevel=debug  # 启动worker
broker = 'redis://172.17.0.6:6379'  # task send：消息中间件
backend = 'redis://172.17.0.6:6379' # results：计算结果存储


app = Celery('task_demo', broker=broker, backend=backend)

@app.task
def add(x, y):
    "functionName.delay()调度分配任务到worker。可通过functionName.ready()查看是否执行完毕"
    time.sleep(2)
    return x + y

"""
分布式爬虫

step1:

@app.task
def get_urls(url):
    pass
    send redis / result

@app.task
def get_page(url):
    pass
    send redis / page

@app.task
def page_parse(page):
    pass
    send mongodb / page_content


Master:
   定义逻辑，发送任务
"""



