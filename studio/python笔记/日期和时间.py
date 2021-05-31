#对日期和时间操作有三个模块
import datetime
import time
import calendar

#获取程序执行的时间
before = time.time()
fun()
after = time.time()
after - before

#获取当前的时间并转为字符串
#必须导入datetime中datetime类
from datetime import datetime
str(datetime.now())

#指定格式输出 ‘2019-02-24 ** 16:56:55’
datetime.now().strftime('%Y-%m-%d ** %H:%M:%S')

#字符串时间转化为时间
time.strptime('2015-08-01 23:59:59', '%Y-%m-%d %H:%M:%S')

#转化为秒
time.mktime(time)

#增加时间
from datetime import timedelta
theDay = datetime.now().date()
target = theDay+timedelta(days=120)
