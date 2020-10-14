#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

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
} matrix;

matrix *matrixInit(int row, int col, int elem[]);
matrix *matrixPlus(matrix *a, matrix *b);
matrix *matrixMultiply(matrix *a, matrix *b);

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

matrix *matrixInit(int row, int col, int elem[])
{
    int count = 0;
    matrix *ret = (matrix *)malloc(sizeof(matrix));
    ret->row = row;
    ret->col = col;
    ret->elem = (node *)malloc(sizeof(node) * row * col);
    for (int i = 0; i < row * col; i++)
    {
        if(elem[i]!=0)
        {
            ret->elem->val=elem[i];
            ret->elem->x=i/col;
            ret->elem->y=i%col;
            count++;
        }
    }
    ret->elem=(node*)realloc(ret->elem,sizeof(node)*count);
    return ret;
}

void workPlus()
{
}

void workMultiply()
{
}
