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
    int size;
} matrix;

matrix *matrixInit(int row, int col, int elem[]);
matrix *matrixPlus(matrix *a, matrix *b);
matrix *matrixMultiply(matrix *a, matrix *b);
void matrixPrint(matrix* m);

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
        if (elem[i] != 0)
        {
            ret->elem->val = elem[i];
            ret->elem->x = i / col;
            ret->elem->y = i % col;
            count++;
        }
    }
    ret->elem = (node *)realloc(ret->elem, sizeof(node) * count);
    ret->size = count;
    return ret;
}

matrix *matrixPlus(matrix *a, matrix *b)
{
    if (a->row == b->row && a->col == b->col)
        return NULL;
    matrix *c = (matrix *)malloc(sizeof(matrix));
    c->row = a->row;
    c->col = a->col;
    c->elem = (node *)malloc(sizeof(node) * c->row * c->col);
    node *pa = a->elem, *pb = b->elem, *pc = c->elem;
    while ((pa - a->elem) < a->size && (pb - b->elem) < b->size)
    {
        if (pa->x == pb->x && pa->y == pb->y)
        {
            pc->val = pa->val + pb->val;
            pc->x = pa->x;
            pc->y = pa->y;
            pc++, pa++, pb++;
        }
        else if (pa->x < pb->x || (pa->x == pb->x && pa->y < pb->y))
        {
            pc->val = pa->val;
            pc->x = pa->x;
            pc->y = pa->y;
            pc++, pa++;
        }
        else
        {
            pc->val = pb->val;
            pc->x = pb->x;
            pc->y = pb->y;
            pc++, pb++;
        }
    }
    while ((pa - a->elem) < a->size)
    {
        pc->val = pa->val;
        pc->x = pa->x;
        pc->y = pa->y;
        pc++, pa++;
    }
    while ((pb - b->elem) < b->size)
    {
        pc->val = pb->val;
        pc->x = pb->x;
        pc->y = pb->y;
        pc++, pb++;
    }
    c->size=pc-c->elem;
    c->elem=(node*)realloc(c->elem,c->size);
    return c;
}

void workPlus()
{
    int ar,ac;
    int br,bc;
    int* elema,*elemb;
    cout<<"请输入矩阵A行数和列数(e.g. 3 3):";
    cin>>ar>>ac;
    elema=(int*)malloc(sizeof(int)*ar*ac);
    cout<<"请输入矩阵A:\n";
    for(int i=0;i<ar;i++)
        for(int j=0;j<ac;j++)
            cin>>elema[i*ac+j];
    matrix* a=matrixInit(ar,ac,elema);
    free(elema);
    cout<<"请输入矩阵B行数和列数(e.g. 3 3):";
    cin>>br>>bc;
    cout<<"请输入矩阵B:\n";
    for(int i=0;i<br;i++)
        for(int j=0;j<bc;j++)
            cin>>elema[i*bc+j];
    matrix* b=matrixInit(br,bc,elemb);
    free(elemb);
    matrix* c=matrixPlus(a,b);
    if(c==NULL)
        cout<<"不可相加: 行列数不相等\n";
    else
    {
        cout<<"和矩阵为:\n";
        matrixPrint(c);
    }
}

void workMultiply()
{
}
