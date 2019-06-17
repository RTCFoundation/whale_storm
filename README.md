# whale_storm分布式实时处理系统

简介：基于Hadoop与storm原理编写。基本分为分布式结点，底层通信系统，拓扑结构，高层次控制器，分布式远程过程的调用即高层次抽象元语等功能的设计与实现。

## 总体架构

Hadoop-->MapReduce![](https://github.com/writesky/a-new-start/blob/master/%E6%8D%95%E8%8E%B7.PNG?raw=true)          

##### Storm                                           

![](https://github.com/writesky/a-new-start/blob/master/%E6%8D%95%E8%8E%B71.PNG?raw=true)

whale_storm

![](https://github.com/writesky/a-new-start/blob/master/%E6%8D%95%E8%8E%B72.PNG?raw=true)

1. ###### Spout是消息源，拓扑结构中所有的数据都来消息源

2. Bolt是消息处理单元，负责接收来自消息源或数据处理单元的数据流，并对数据流进行逻辑处理

3. SpoutExecutor是一个线程，是消息的执行者，每个SouptExecutor负责执行一个消息源

4. BoltExecutor也是一个线程，是所有消息处理单元的执行者，每一个BoltExecutor负责执行一个消息处理单元

5. SpoutExecutor不停息的运行，而BoltExecutor只有在数据到来才启动

6. Manager是单个结点任务的管理者，负责创建执行器，与中心结点通信，并接收来自其他结点的数据，将这些数据分发到对应的Bolt中，让它处理

7. President是整个集群的中心结点，负责收集用户的请求，将用户定义的拓扑结构发送给正在运行的其他个Manager，也从Manager收集信息，了解结点情况，为每个Executor分配任务

   

从另一个角度来看

![](https://github.com/writesky/a-new-start/blob/master/%E6%8D%95%E8%8E%B73.PNG?raw=true)

​              ITask是抽象任务接口，IBolt和ISpout是分布式消息处理单元和消息源，Topology是由多个相互连接的消息处理单元和消息源组成，右侧是执行器，每个节点会定义一系列的执行器Executor，执行器分别为SpoutExcutor和BoltExecutor，分别执行不同任务，整个系统核心就是如何构建任务，并将任务同时分配到多个节点上同时运行，消息源与消息处理单元只是特定的抽象模型。

##########

现已实现

1. 系统编程接口设计
2. 服务器组件设计与实现
3. 管理服务设计与实现
