```
// 启动一个储存item的server
go run ./rpcsupport/server/main.go --port=1234
// 启动多个worker，这里只是提供在本地不同端口的运行。实际提供多个物理机地址
go run ./rpcsupport/server/worker/server/main.go --port=9000
go run ./rpcsupport/server/worker/server/main.go --port=9001
go run ./rpcsupport/server/worker/server/main.go --port=9002
// 启动master的爬虫执行程序
go run main.go --item_host=":1234" --worker_hosts=":9000,:9001,:9002"
```



Request发送给分布式的worker节点

1. 通过goroutine，使用rpc客户端完成计算时间较长的部分

   - jsonrpc   [Used]

   - grpc

   - Thrift

2. 通过goroutine -> client -> (web/消息中间件) -> server -> goroutine完成分布式

   - docker/libchab
   - NATS streaming
   - gocircuit



### 分布式系统

1. 多个节点
   1. 容错性
   2. 可扩展性
   3. 固有分布性：地域、各模块负责人的分布性
2. 消息传递
   1. 节点有私有存储
   2. 易于开发
   3. 功能可扩展性
   4. 对比并行计算：多个程序同时计算一块数据，最后整合。分布式每一部分是可以计算不同的东西、不同的功能
      - REST
        - 特定api完成特定需要。**对外与用户通信**
      - RPC
        - 函数调用序列化，服务器反序列化执行函数。**master对分布式系统中的功能进行调用**，或者**模块内部之间，耦合度高的通信**
      - 中间件
        - message queue。**分布式系统内各服务器的数据传输**，或者**模块之间耦合度较低的通信**
3. 完成特定需求



#### 分布式与微服务

- 分布式：节点通信层面
- 微服务：模块划分层面，按业务划分模块，需要自动化测试、部署、服务发现。同一层面的架构为多层架构。





