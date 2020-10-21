# 概要设计

相加: 用双指针法将三元表组相应元素相加  
相乘: 将第二个矩阵转置后,每次从两个矩阵获取一行相乘后求和

## 数据结构类型定义

```c++
typedef struct MatrixNode
{
    int val;
    int x;
    int y;
} node;

typedef struct Matrix
{
    int col;
    int row;
    node *elem;
    int size;
} matrix;
```

## 主程序流程

```c++
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
        cout << "\n";
    } while (arg);
    return 0;
}
```

## 函数调用关系

main()调用workPlus()和workMultiply(),workPlus()调用matrixInit(),matrixPlus(),matrixFree(),workMultiply()调用matrixInit(),matrixMultiply(),matrixFree(),matrixMultiply()调用matrixTrans(),getRow()
