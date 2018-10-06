/* 已禁用的字符串串联函数调用 */
1.SV.BANNED.REQUIRED.CONCAT

/* 已禁用的复制函数调用 */
2.SV.BANNED.REQUIRED.COPY

/* 不安全的流读取函数 */
3.SV.BANNED.REQUIRED.GETS

/* 已禁用的字符串 IsBad 函数调用 */
4.SV.BANNED.REQUIRED.ISBAD

/* 已禁用的 sprintf 函数调用 */
5.SV.BANNED.REQUIRED.SPRINTF



某些 C/C++ 函数被视为是不安全的，因此“已禁用”这些函数。这些函数是：
    内存分配函数，如 alloca
    字符串串联函数，如 strcat 和 strncat
    字符串复制函数，如 strcpy 和 strncpy
    获取函数，如 gets 和 _getts
    isbad 函数，如 IsBadWritePtr
    数值转换函数，如 _iota 和 _itow
    OEM 转换函数，如 CharToOem
    路径函数，如 _splitpath 和 makepath
    扫描函数，如 scanf
    字符串打印函数，如 sprintf 和 snprintf
    字符串令牌化函数，如 strtok
漏洞与风险
    这些被禁止的函数大都是因为可能导致缓冲区溢出而被禁用。
    已禁用的函数的列表既包括 strcpy 和 strcat 之类的函数，也包括很多相对应的“n”函数，
    例如 strncpy 和 strncat。虽然经常推荐将“n”函数用于替换其匹配的非“n”函数，但是现
    在它们也被视为难以对溢出的缓冲区进行非空终止，而且缺少返回溢出错误的能力。





/*

*/
