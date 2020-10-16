#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

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
void matrixPrint(matrix *m);
void matrixFree(matrix *m);
matrix *matrixTrans(matrix *m);
int *getRow(matrix *m, int row, node *p);

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
    node *p = ret->elem;
    for (int i = 0; i < row * col; i++)
    {
        if (elem[i] != 0)
        {
            p->val = elem[i];
            p->x = i / col;
            p->y = i % col;
            p++;
            count++;
        }
    }
    ret->size = count;
    return ret;
}

void matrixPrint(matrix *m)
{
    int offset = 0;
    for (int i = 0; i < m->row; i++)
    {
        for (int j = 0; j < m->col; j++)
        {
            if (offset < m->size && m->elem[offset].x == i && m->elem[offset].y == j)
            {
                cout << m->elem[offset].val << " ";
                offset++;
            }
            else
            {
                cout << "0 ";
            }
        }
        cout << "\n";
    }
}

matrix *matrixPlus(matrix *a, matrix *b)
{
    if (a->row != b->row && a->col != b->col)
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
    c->size = pc - c->elem;
    //c->elem = (node *)realloc(c->elem, c->size+1);
    return c;
}

matrix *matrixTrans(matrix *m)
{
    matrix *ret = (matrix *)malloc(sizeof(matrix));
    ret->row = m->col;
    ret->col = m->row;
    ret->size = m->size;
    ret->elem = (node *)malloc(sizeof(node) * ret->col * ret->row);
    int num[100] = {0}, cpot[100] = {-1};
    for (int i = 0; i < m->size; i++)
        num[m->elem[i].y]++;
    cpot[0] = 0;
    for (int i = 1; i < m->col; i++)
        cpot[i] = cpot[i - 1] + num[i - 1];
    for (int i = 0; i < m->size; i++)
    {
        int col = m->elem[i].y, row = m->elem[i].x;
        ret->elem[cpot[col]].x = col;
        ret->elem[cpot[col]].y = row;
        ret->elem[cpot[col]].val = m->elem[i].val;
        cpot[col]++;
    }
    return ret;
}

void workPlus()
{
    int ar, ac;
    int br, bc;
    int *elema, *elemb;
    cout << "请输入矩阵A行数和列数(e.g. 3 3):";
    cin >> ar >> ac;
    elema = (int *)malloc(sizeof(int) * ar * ac);
    cout << "请输入矩阵A:\n";
    for (int i = 0; i < ar; i++)
        for (int j = 0; j < ac; j++)
            cin >> elema[i * ac + j];
    matrix *a = matrixInit(ar, ac, elema);
    free(elema);
    cout << "请输入矩阵B行数和列数(e.g. 3 3):";
    cin >> br >> bc;
    elemb = (int *)malloc(sizeof(int) * br * bc);
    cout << "请输入矩阵B:\n";
    for (int i = 0; i < br; i++)
        for (int j = 0; j < bc; j++)
            cin >> elemb[i * bc + j];
    matrix *b = matrixInit(br, bc, elemb);
    free(elemb);
    matrix *c = matrixPlus(a, b);
    if (c == NULL)
        cout << "不可相加: 行列数不相等\n";
    else
    {
        cout << "和矩阵为:\n";
        matrixPrint(c);
    }
    matrixFree(a);
    matrixFree(b);
    matrixFree(c);
    return;
}

int *getRow(matrix *m, int row, node *p)
{
    int *ret = (int *)malloc(sizeof(int) * m->col);
    for (int i = 0; i < m->col; i++)
        ret[i] = 0;
    while (p->x == row)
    {
        ret[p->y] = p->val;
        p++;
    }
    return ret;
}

matrix *matrixMultiply(matrix *a, matrix *b)
{
    if (a->col != b->row)
        return NULL;
    matrix *c = (matrix *)malloc(sizeof(matrix));
    c->size = 0;
    c->row = a->row;
    c->col = b->col;
    c->elem = (node *)malloc(sizeof(node) * c->col * c->row);
    node *p = c->elem;
    matrix *bTrans = matrixTrans(b);
    swap(bTrans, b);
    int apos[100];
    int bpos[100];
    memset(apos, -1, sizeof(apos));
    memset(bpos, -1, sizeof(bpos));
    for (int i = 0; i < a->size; i++)
        if (apos[a->elem[i].x] == -1)
            apos[a->elem[i].x] = i;
    for (int i = 0; i < b->size; i++)
        if (bpos[b->elem[i].x] == -1)
            bpos[b->elem[i].x] = i;
    for (int i = 0; i < a->row; i++)
    {
        if (apos[i] != -1)
        {
            for (int j = 0; j < b->row; j++)
            {
                int sum = 0;
                if (bpos[j] != -1)
                {
                    int *va = getRow(a, i, a->elem + apos[i]);
                    int *vb = getRow(b, j, b->elem + bpos[j]);
                    for (int k = 0; k < a->col; k++)
                        sum += va[k] * vb[k];
                    if (sum)
                    {
                        p->val = sum;
                        p->x = i;
                        p->y = j;
                        p++, c->size++;
                    }
                }
            }
        }
    }
    matrix(b);
    return c;
}

void workMultiply()
{
    int ar, ac;
    int br, bc;
    int *elema, *elemb;
    cout << "请输入矩阵A行数和列数(e.g. 3 3):";
    cin >> ar >> ac;
    elema = (int *)malloc(sizeof(int) * ar * ac);
    cout << "请输入矩阵A:\n";
    for (int i = 0; i < ar; i++)
        for (int j = 0; j < ac; j++)
            cin >> elema[i * ac + j];
    matrix *a = matrixInit(ar, ac, elema);
    free(elema);
    cout << "请输入矩阵B行数和列数(e.g. 3 3):";
    cin >> br >> bc;
    elemb = (int *)malloc(sizeof(int) * br * bc);
    cout << "请输入矩阵B:\n";
    for (int i = 0; i < br; i++)
        for (int j = 0; j < bc; j++)
            cin >> elemb[i * bc + j];
    matrix *b = matrixInit(br, bc, elemb);
    free(elemb);
    //matrix* c=matrixTrans(b);
    matrix *c = matrixMultiply(a, b);
    if (c == NULL)
        cout << "不可相乘: A列数不等于B行数\n";
    else
    {
        cout << "乘积矩阵为:\n";
        matrixPrint(c);
    }
    matrixFree(a);
    matrixFree(b);
    matrixFree(c);
    return;
}

void matrixFree(matrix *m)
{
    free(m->elem);
    free(m);
}
