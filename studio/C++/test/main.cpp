#include <iostream>
#include <type_traits>
#include <fstream>

using namespace std;
int main(int arg, char *argv[])
{
    // 打开INI配置文件
    ifstream infile("config.ini");

    // 读取节名和节内容
    string section;
    string line;
    while (getline(infile, line)) {
        // 判断是否是节名
        if (line.substr(0, 1) == "[") {
            section = line.substr(1, line.length() - 2);
        } else {
            // 读取键值对
            int pos = line.find("=");
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);

            // 输出键值对
            cout << section << "." << key << " = " << value << endl;
        }
    }
    return 0;
}
