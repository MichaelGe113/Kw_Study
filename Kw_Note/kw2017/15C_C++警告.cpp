可能错误的指针缩放
1.CWARN.ALIGNMENT
在 C 和 C++ 中，由于数学运算隐式缩放的方式，可能意外指向错误的内存。
CWARN.ALIGNMENT 检查器可搜索指针可能未正确对齐的实例。
漏洞代码示例
1 int buffer[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
2 int test1() {
3 char *temp = (char *)buffer;
4 int res = (int) (*(temp+6));
5 return res;
6 }
在此示例中，Klocwork 在第 4 行发布了一个 CWARN.ALIGNMENT 警告，
因为可能存在指针缩放错误的情况。在此行中，“res”可能打算获得
数组“buffer”的第七个元素，但是将 6 添加到变量“temp”中只会增加
6 个字节。在本例中，整数值提取自“buffer”第三个元素的中间。

修正代码示例
1 int buffer[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
2 int test1() {
3 char *temp = (char *)buffer;
4 int res = *((int*)temp+6);
5 return res;
6 }
在该修正代码示例中，通过编码可清楚知道，
“res”指“buffer”的第七个元素。
