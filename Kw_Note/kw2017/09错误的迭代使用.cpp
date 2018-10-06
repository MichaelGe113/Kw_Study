无效迭代器
1.ITER.CONTAINER.MODIFIED

漏洞代码示例
1   void foo(list<int>& cont, int x)
2   {
3     list<int>::iterator i;
4     for (i = cont.begin(); i != cont.end(); i++)
5     {
6       if (*i == x)
7         cont.erase(i);
8     }
9   }

在该示例中，函数应该移除列表“cont”中所有等于“x”的元素。
然而，调用“cont.erase(i)”会使迭代器“i”失效，这样“i”的后续增量就会成为无效操作。

修正代码示例
1   void foo(list<int>& cont, int x)
2   {
3     list<int>::iterator i;
4     for (i = cont.begin(); i != cont.end();)
5     {
6       if (*i == x)
7         i =cont.erase(i);
8       else i++;
9     }
10   }


可取消引用末端迭代器
2.ITER.END.DEREF.MIGHT

漏洞代码示例

1   #include <set>
2   using namespace std;
3   int foo(set<int>& cont)
4   {
5     set<int>::iterator i = cont.begin();
6     if (*i < 100)
7       return *i;
8     return 100;
9   }
如果该示例中的容器“cont”为空，则迭代器“i”的值将等于 cont.end()。
在该案例中，取消引用“i”无效，并会生成未定义的结果。

修正代码示例
1   int foo(set<int>& cont)
2   {
3     set<int>::iterator i = cont.begin();
4     if ( (i != cont.end()) && (*i < 100) )
5       return *i;
6     return 100;
7   }


取消引用末端迭代器
3.ITER.END.DEREF.MUST

漏洞代码示例
1   #include <set>
2   using namespace std;
3   int foo(set<int>& cont)
4   {
5     int x = 0;
6     set<int>::iterator i;
7     for (i = cont.begin(); i != cont.end(); i++)
8     {
9       x += *i;
10       if (x > 100)
11        break;
12     }
13     x += *i;
14     return x;
15   }
    如果在该示例中，第 9 行没有发生循环中断，则迭代器“i”的值将在循环后等于 cont.end()。
在该案例中，取消引用“i”无效，并会生成未定义的结果。(若没有执行break)

修正代码示例
1   int foo(set<int>& cont)
2   {
3     int x = 0;
4     set<int>::iterator i;
5     for (i = cont.begin(); i != cont.end(); i++)
6     {
7       x += *i;
8       if (x > 100)
9         break;
10     }

11     if (i != cont.end())
12      x += *i;
13     return x;
14   }


迭代器含有不适当的容器对象
4.ITER.INAPPROPRIATE.MULTIPLE
漏洞代码示例
1   #include <set>
2   using namespace std;
3
4
5   void foo(set<int>& cont1, set<int>& cont2, set<int>& cont3)
6   {
7       set<int>::iterator i = cont1.find(100);
8       set<int>::iterator j = cont2.find(200);
9       cont3.insert(i, j);
10  }
11
12  int main()
13  {
14      return 0;
13  }
在该示例中，迭代器“i”和迭代器“j”分别被分配到“cont1”和“cont2”，它们用于
指定“cont3”的范围，这会生成未定义的结果。Klocwork 针对第 9 行报告
ITER.INAPPROPRIATE.MULTIPLE。



迭代器含有不适当的容器对象
5.ITER.INAPPROPRIATE.MULTIPLE
ITER.INAPPROPRIATE 检查器标记迭代器被分配到一个容器并结合其他容器使用的实例。
漏洞代码示例
1   void foo(set<int>& cont1, set<int>& cont2)
2   {
3     set<int>::iterator i = cont1.find(100);
4     if (i != cont1.end())
5       cont2.erase(i);
6   }
在该示例中，迭代器“i”被分配到容器“cont1”，然后却错误地与“cont2”一起使用，
这会生成未定义的结果。

修正代码示例
1   void foo(set<int>& cont1, set<int>& cont2)
2   {
3     set<int>::iterator i = cont1.find(100);
4     if (i != cont1.end())
5   {
6       i = cont2.find(100);
7       if (i != cont2.end())
8       cont2.erase(i);
9   }
