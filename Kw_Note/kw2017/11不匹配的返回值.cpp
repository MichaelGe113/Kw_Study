传递给赋值运算符 = 的非常量对象
1.CL.ASSIGN.NON_CONST_ARG
CL.ASSIGN.NON_CONST_ARG 检查器查找将非常量对象传递给运算符 = 的类。
使用这种代码时，将无法表达某些语言结构。


赋值运算符 = 中返回的常量对象
2.CL.ASSIGN.RETURN_CONST
CL.ASSIGN.RETURN_CONST 检查器可查找包含赋值运算符的类，这些运算符返回常量引用。

赋值运算符 = 中返回的 void
3.CL.ASSIGN.VOID
CL.ASSIGN.VOID 检查器可查找包含赋值运算符的类，这些运算符返回 void。
漏洞代码示例
     class C{
//...
     public:
       C(int);
4      void operator=(const C&);
//...
     };
在此示例中，Klocwork 在第 4 行报告了一个 CL.ASSIGN.VOID 错误。
Klocwork 警告允许重新评估相应代码，避免出现设计限制。
修正代码示例
    class C{
//...
      C& operator=(const C&);
//...
    };


非void函数没有返回值
4.FUNCRET.GEN
FUNCRET.GEN 检查器会在没有 return 语句的非 void 函数中查找路径。


隐式返回 int 的非 void 函数没有返回值
5.FUNCRET.IMPLICIT
FUNCRET.IMPLICIT 检查器在没有 return 语句的隐式“int”函数中查找路径。
漏洞与风险
没有显式返回类型的函数应返回整数值。如果在没有 return 语句的情况下尝试读取返回代码，则不能进行初始化。
漏洞代码示例
   foo(char ** param){
     char * x = malloc(1);
     free(x);
     bar(&x);
5  }
Klocwork 标记了第 5 行，指出隐式“int”函数“foo”没有 return 语句。


非虚函数返回虚值
6.RETVOID.GEN
RETVOID.GEN 检查器查找那些非虚函数具有无返回值的明确返回语句的实例。
漏洞与风险
如果使用了返回的值，可能导致用到未初始化的内存。
漏洞代码示例
1  #include  <math.h>
2  #include  <stdio.h>
3  #define     OK    1
4  int func ()
5  {
6    return;
7  }
Klocwork 标记了代码中的第 6 行，在此 int 函数 func() 具有一个无返回值的返回语句。


隐式 int 函数返回虚值
7. RETVOID.IMPLICIT
RETVOID.IMPLICIT 检查器查找那些隐式 int 函数具有无返回值的明确返回语句的实例。


Void 函数返回值
8.VOIDRET
VOIDRET 检查器发现声明为 void 的函数返回了值。
