虚拟内存泄漏
1.CL.MLK.VIRTUAL
CL.MLK.VIRTUAL。在这种情况下，如果程序损坏了某个指针，且该指针指向某个派生类型
对象的向上转换的基本类型，则将不会调用该派生类型的析构函数。


赋值运算符中的内存泄漏
2.CL.MLK.ASSIGN
这是一个类级别 (CL) 检查器，可告知运算符 = 中可能发生的内存泄漏情况。
当构造函数中执行动态内存分配的一个类覆盖运算符 = 中的相应指针，
而没有提前释放内存和/或对适当引用计数器进行递减操作时，Klocwork
将报告 CL.MLK.ASSIGN。这可能导致内存

析构函数中的内存泄漏泄漏。
3.CL.MLK
CL.MLK 基于 Scott Meyer 的第 6 项：使用析构函数中指针成员的“delete”。
如果构造函数中执行动态内存分配的一个类未在析构函数中释放该内存，
并可能导致内存泄漏，这时 Klocwork 将报告 CL.MLK。


不一致的内存释放
4.FREE.INCONSISTENT
有时，如果释放的内存不一致，则会导致内存泄露。因此，需要确保在函数的所有
路径上释放内存。FREE.INCONSISTENT 检查器会标记直接或通过一系列的
取消引用和域操作访问内存，然后在函数的一个路径而不在其他路径上释放内存的情况。
通常在错误情况下或会话意外中断时会发生该问题。
漏洞代码示例
  void my_free(char *p, int flag) {
      if (flag == 17) {
          p = 0;
          return;
      }
      if (flag == 34) {
          return;
      }
9     free(p);
 }


内存可能泄漏
5.MLK.MIGHT
程序未释放之前分配的内存，并且此时在某些路径上对动态内存的引用可能丢失。
示例 1
  void foobar(int i)
  {
    char* p = new char[10];
    if(i) {
5     p = 0;
    }
    delete[] p;
  }
Klocwork 针对第 5 行生成内存泄漏报告，表明存储在“p”中并通过
第 3 行的函数“new[]”进行分配的动态内存可能在第 5 行丢失。


内存泄漏
6.MLK.MUST


内存可能泄漏
7.MLK.RET.MIGHT
当内存被分配至函数和从函数返回（取决于具体的条件），但未分配到任何变量时，
将报告 MLK.RET.MIGHT 问题。被分配的内存在此时丢失。
示例 1
1  void* alloc_data(void* pool)
2  {
3    if (pool) {
4       return pool_alloc(pool, 10);
5    } else {
6       return malloc(10);
7    }
8  }
9
10  void foo(void* pool)
11  {
12    alloc_data(pool);
13  }
Klocwork 生成内存泄漏报告，表明可能是通过函数“alloc_data”所分配的动态内存在第 12 行丢失。


内存泄漏
8.MLK.RET.MUST
当被分配的内存从函数返回，但未分配到任何变量时，将报告 MLK.RET.MUST 问题。
被分配的内存在此时丢失
漏洞代码示例
1  void* alloc_data()
2  {
3    return malloc(10);
4  }
5
6  void foo()
7  {
8    alloc_data();
9  }
Klocwork 生成内存泄漏报告，表明通过函数“alloc_data”所分配的动态内存在第 8 行丢失。

修正代码示例
 1  void* alloc_data()
2  {
3    return malloc(10);
4  }
5
6  void foo()
7  {
8    void* ptr = alloc_data();
9    free(ptr);
10  }
