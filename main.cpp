#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

void workPlus();
void workMultiply();

int main()
{
    int arg;
    do
    {
        cout << "请输入功能选项\n1.矩阵相加\n2.矩阵相乘\n0.结束程序\n选项:";
        cin >> arg;
        switch (arg)
        {
        case 1:
            workPlus();
            break;
        case 2:
            workMultiply();
            break;
        case 0:
            cout << "感谢使用\n";
            break;
        default:
            cout << "无效的选项\n";
            break;
        }
    } while (arg);
    return 0;
}

void workPlus()
{

}

void workMultiply()
{

}
