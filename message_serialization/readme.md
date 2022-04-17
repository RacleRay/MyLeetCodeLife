使用boost asio写简单聊天C/S程序，用三种序列化方式练习：

- boost serialization：只能在C++写的Client和Server之间传递
- json：效率低一点，但灵活简单
- Protobuf：效率高，简洁易用



makefile 默认使用 -D_PROTO 即Protobuf方式，进行通信。

-D_JSON 和 -D_ARCHIVE 对应其他两种方式。



建立连接后，Client端输入

```
BindName yourname
```

注册后，输入

```
Chat 发送的消息
```

进行信息发送



