# 详细设计

matrix *matrixInit(int row, int col, int elem[])

初始化一个矩阵并获得其指针

```c++
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
```

matrix *matrixPlus(matrix *a, matrix *b)

矩阵相加

```c++
matrix *matrixPlus(matrix *a, matrix *b)
{
    if (a->row != b->row && a->col != b->col)
        return NULL;
    matrix *c = (matrix *)malloc(sizeof(matrix));
    初始化c内存,确定c行列数
    node *pa = a->elem, *pb = b->elem, *pc = c->elem;
    while ((pa - a->elem) < a->size && (pb - b->elem) < b->size)
    {
        if(pa的位置在pb之前)
            pa元素加入返回矩阵,pa++;
        else if(pa的位置在pb之后)
            pb元素加入返回矩阵,pb++;
        else if(两者位置相同)
            pa元素+pb元素的和加入返回矩阵,pa++,pb++;
    }
    将剩余的元素插入到返回矩阵中
    c->size = pc - c->elem;
    return c;
}
```

matrix *matrixMultiply(matrix *a, matrix *b)

矩阵相乘

```c++
matrix *matrixMultiply(matrix *a, matrix *b)
{
    if (a->col != b->row)
        return NULL;
    matrix *c = (matrix *)malloc(sizeof(matrix));
    初始化c内存,确定行列数
    node *p = c->elem;
    将b转置
    int apos[100];
    int bpos[100];
    确定各行开始的位置
    for (int i = 0; i < a->row; i++)
    {
        if (apos[i] != -1)
        {
            for (int j = 0; j < b->row; j++)
            {
                int sum = 0;
                if (bpos[j] != -1)
                {
                    获取两矩阵一行的元素
                    相乘后求和
                    if(sum!=0)
                        插入c矩阵
                }
            }
        }
    }
    matrix(b);
    return c;
}
```

void matrixPrint(matrix *m)

输出矩阵

```c++
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
```

void matrixFree(matrix *m)

释放矩阵内存

```c++
void matrixFree(matrix *m)
{
    free(m->elem);
    free(m);
}
```

matrix *matrixTrans(matrix *m)

矩阵转置

```c++
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
```

int *getRow(matrix *m, int row, node *p)

获取矩阵一行的元素

```c++
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
```

void workPlus()

处理矩阵相加的输入,判断是否满足条件,调用相加的函数

```c++
void workPlus()
{
    输入a,b矩阵的行列数和元素
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
```

void workMultiply()

处理矩阵相乘的输入,判断是否满足条件,调用相乘的函数

```c++
void workMultiply()
{
    输入a,b矩阵的行列数和元素
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
```
