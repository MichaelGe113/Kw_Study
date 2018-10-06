资源泄露
1.RH.LEAK
RH.LEAK 检查器查找这样的实例：所有与之前获得但并未释放的
资源相关的描述符都丢失了。

漏洞与风险
有多种资源受限的情况，并且如果资源没有正确地释放，那么在
下一次尝试访问时，它将不可用。
漏洞代码示例
1  #include <stdio.h>

2  int foo (const char *name) {
3      FILE *f = fopen(name, "r");
4       //...//
5      if (some_error) return 1;
6       //...//
7      fclose(f);
8      return 0;
9  }
Klocwork 标记了第 5 行的代码，表示资源可能丢失。



不安全的资源处理 - 分配和释放
2.SV.INCORRECT_RESOURCE_HANDLING.URH
SV.INCORRECT_RESOURCE_HANDLING.URH 检查器会标记出请求可能已经
被释放的资源的情况。检查器会分析以下 POSIX 资源，以查找错误的资源处理：
    标准输入/输出资源：文件描述符、文件以及管道流
    X/开放式系统接口 (XSI) 资源：消息、信号灯，以及共享内存
    实时资源：消息队列、信号灯、共享内存、已指定类型的内存对象、进程派生、时钟以及计时器
    线程资源：线程、互斥、条件变量、障碍、读取/写入锁定对象以及旋转锁定对象
    套接字
    跟踪



不安全的资源处理 - 状态检查
3.SV.INCORRECT_RESOURCE_HANDLING.WRONG_STATUS
