## 要求

实现两个程序，write，read

- 在两个终端中分别运⾏write和read
- write将循环读终端输⼊，可输⼊空格，输⼊回车确定
- read进程将持续运⾏，感知到write输⼊的数据，就将该数据输出到屏幕上

## 实现效果

共享内存实现无关进程间的消息传递。注意 read() 调用一点要在本程序实现流程中，mutex lock 之前，并使用一个读缓存，否则输出端输出到屏幕有可能读不成功。

<img src="images/readme_pic/image-20220301134451649.png" alt="image-20220301134451649" style="zoom:67%;" />

<img src="images/readme_pic/image-20220301134545881.png" alt="image-20220301134545881" style="zoom:67%;" />



使用进程间mutex，一个条件变量，建立类似生产者消费者模式的程序。

