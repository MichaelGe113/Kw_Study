/* 返回值被忽略 */
1.SV.RVT.RETVAL_NOTTESTED
检查返回值确保各项函数成功运行非常重要，因为忽略异常和错误条件
可能让攻击者有机会引入意外行为。
漏洞与风险
如果软件未经常检查不应发生的不寻常或异常条件，通常便会出现这些漏洞。
但是，攻击者可以使用这些条件来触发异常操作，引入不稳定性、错误行为或漏洞。
即使没有攻击，如果未检查返回值，运算中也可能使用不正确的数据，
这可能导致错误的程序流、损害数据完整性或应用程序故障。

缓解与预防
在处理异常案例时增加返回值和代码验证步骤，确保有相应的机制用于检查
和处理异常或意外条件。要确保代码已处理异常，可通过在低内存条件
下或使用不足的权限来运行程序，中断事务，或禁用与网络服务的连接性，由此确定错误条件。

漏洞代码示例
1  #include <pthread.h>
2
3  int foo() {
4      pthread_cond_t cond;
5      int res;
6      res = pthread_cond_init(&cond, NULL);
7      return 0;
8  }
Klocwork 在第 6 行生成了一个问题报告，指出“pthread_cond_init”的返回值未
与 0 进行比较。如果未检查返回值，可能发生意外的程序行为。

修正代码示例
1  #include <pthread.h>
2
3  int foo() {
4      pthread_cond_t cond;
5      int res;
6      res = pthread_cond_init(&cond, NULL);
7      if (res != 0) return 1;
8      return 0;
9  }


SV.RVT.RETVAL_NOTTESTED 检查器可为以下函数报告忽略的返回值代码：
    函数                           需检查的返回值
    socket	                         -1、0
    recv	                            0、-1
    pthread_mutex_destroy	            0
    pthread_mutex_lock               	0
    pthread_mutex_trylock	            0
    pthread_mutex_unlock	            0
    pthread_mutex_timedlock	          0
    pthread_mutex_getprioceiling    	0
    pthread_mutex_setprioceiling    	0
    pthread_cond_init	                0
    pthread_cond_destroy             	0
    pthread_cond_wait	                0
    pthread_cond_timedwait	          0
    pthread_cond_broadcast          	0
    pthread_rwlock_init	0
    pthread_rwlock_destroy	0
    pthread_rwlock_rdlock	0
    pthread_rwlock_tryrdlock	0
    pthread_rwlock_timedrdlock	0
    pthread_rwlock_wrlock	0
    pthread_rwlock_trywrlock	0
    pthread_rwlock_timedwrlock	0
    pthread_rwlock_unlock	0
    pthread_rwlockattr_init	0
    pthread_rwlockattr_destroy	0
    pthread_spin_init	0
    pthread_spin_destroy	0
    pthread_spin_lock	0
    pthread_spin_trylock	0
    pthread_spin_unlock	0
    pthread_barrier_init	0
    pthread_barrier_destroy	0
