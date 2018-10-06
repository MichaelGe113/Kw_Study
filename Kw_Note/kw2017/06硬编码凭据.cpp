/* 硬编码凭据的使用（密码和用户名） */
1.HCC
漏洞与风险
使用硬编码凭据使攻击者能够从可执行文件提取凭据并绕过身份验证。
硬编码凭据会产生可能很难检测和修复的重大风险。
漏洞代码示例 2
1   #include <string>
2
3   bool connectToServer(const std::string &userAndPassword)
4   {
5     if (userAndPassword == "alice:s3cr3t")
6       return true;
7     return false;
8   }
在此示例中，Klocwork 将在第 5 行报告一个缺陷，指出用户凭据与硬编码值进行了比较。

修正代码示例 2
在此修正示例中，Klocwork 不再报告缺陷。
1   #include <string>
2
3   namespace database
4   {
5     bool checkServerCredentials(const std::string &userAndPassword);
6   }
7
8   bool connectToServer(const std::string &userAndPassword)
9   {
10    return database::checkServerCredentials(userAndPassword);
11  }

/* 硬编码凭据的使用（密码） */
2.HCC.PWD

/* 硬编码凭据的使用（用户名） */
3.HCC.USER
