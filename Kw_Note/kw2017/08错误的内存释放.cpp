/* 使用不相符的函数释放内存 */
1.CL.FMM
漏洞代码示例
1    class C{
2      Data *data;
3    public:
4      C(){  data = new Data[2];}
5      ~C(){  delete data;}
6    };

1    #include <iostream>
2    using namespace std;
3    class Data
     {
4     public:
5      Data(){ cout << "Constructing Data at " << (void *)this << endl;}
6      ~Data() {cout << "Destroying Data at " << (void *)this << endl;}
7     };
//...
8    int main(){
9      C c;
10      return 1;
11    }

Output:
Constructing Data at 0x602018
Constructing Data at 0x602019
Destroying Data at 0x602019
在此示例中，构造函数使用数组版本的运算符“new”，析构函数使用标量“delete”。
即使构造函数中分配的所有内存都将在析构函数中释放，也只会调用“Data”的一个析构函数。

修正代码示例
1    class C{
//...
2      ~C(){  delete[] data;}
//...
3    };


/* 可能使用不匹配函数释放内存 */
2.FMM.MIGHT

/* 使用不匹配函数释放内存 */
3.FMM.MUST


/* 可能释放非堆内存 */
4.FNH.MIGHT

/* 释放非堆内存 */
5.FNH.MIGHT


/* 可能释放未分配内存 */
6.FUM.GEN.MIGHT

/* 释放未分配内存 */
7.FUM.GEN.MUST



缓解与预防
确保使用相应的分配器和释放器对，如下表所示：

分配器	                               释放器
malloc()、calloc()、realloc()	        free
运算符 new()	                         运算符 delete()
运算符 new[]()	                       运算符 delete[]()
位置 new()	                          析构函数
