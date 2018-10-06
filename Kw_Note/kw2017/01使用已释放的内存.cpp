 // (c++)
/* 由于缺失运算符而释放已释放的内存 */
1.CL.FFM.ASSIGN
/* 应定义运算符 = */
class C
{
// ...
      C& operator=(const C& src){
        if (&src == this) return *this;
        delete[] data;
        data = new char[10];
        memcpy(data, src.data, 10);
        return *this;
     }
// ...
};

/* 由于缺失复制构造函数而释放已释放的内存 */
2.CL.FFM.COPY
/* def 深拷贝构造函数 */
class C
{
//  ...
  C(const C& src){
    data = new char[10];
    memcpy(data, src.data, 10);
  }
//  ...
};

/* 由于缺少自赋值检查而释放已释放的内存 */
3.CL.SELF-ASSIGN
漏洞代码示例 1
1  class Pencil {
2  };
3  class Box {
4  public:
5      Box& operator=(const Box& rhs) {
6          count = rhs.count;
7          delete x;
8          x = new Pencil(*rhs.x);
9      }
10 private:
11    int count;
12    Pencil *x;
13 };
在此示例中，未对运算符 = 中是否存在自赋值进行检查。如果发生自赋值，第 7 行
的 delete 运算符会从参数“rhs”（作为“this”的别名进行操作）中删除成员“x”，
导致第 8 行复制构造函数中使用的内存破坏。
修正：参考Line:9


/* 由于在赋值运算中进行浅层复制而释放已释放的内存 */
4.CL.SHALLOW.ASSIGN

/* 由于复制构造函数中的浅层复制而释放已释放的内存 */
5.CL.SHALLOW.COPY


函数返回局部变量的地址
6.LOCRET.ARG (通过函数形参返回)


函数在全局变量中返回局部变量的地址
7.LOCRET.GLOB


函数在返回值中返回局部变量的地址
8.LOCRET.RET


可能取消引用指向已释放内存的指针
9.UFM.DEREF.MIGHT
  #include <stdlib.h>

  int *foo(int t) {
      int *x = malloc(1);
      if (!t) {
          free(x); //问题1
      }
      *x = t;      //问题2
      return x;
 }


取消引用指向已释放内存的指针
10.UFM.DEREF.MUST


已释放内存可能再次被释放
11.UFM.FFM.MIGHT

已释放内存再次被释放
12.UFM.FFM.MUST


可能返回指向已释放内存的指针
13.UFM.RETURN.MIGHT

返回指向已释放内存的指针
14.UFM.RETURN.MUST


可能使用已被释放的内存
15.UFM.USE.MIGHT

使用了已释放内存
16.UFM.USE.MUST



https://wiki.sei.cmu.edu/confluence/display/c/MEM30-C.+Do+not+access+freed+memory
