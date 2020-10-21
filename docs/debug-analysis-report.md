# 调试分析报告

## 遇到的问题

矩阵初始化数据丢失

```c++
     ret->row = row;
     ret->col = col;
     ret->elem = (node *)malloc(sizeof(node) * row * col);
+    node *p = ret->elem;
     for (int i = 0; i < row * col; i++)
     {
         if (elem[i] != 0)
         {
-            ret->elem->val = elem[i];
-            ret->elem->x = i / col;
-            ret->elem->y = i % col;
+            p->val = elem[i];
+            p->x = i / col;
+            p->y = i % col;
+            p++;
             count++;
         }
     }
     ret->elem = (node *)realloc(ret->elem, sizeof(node) * count);
     ret->size = count;
     return ret;
 }
```

# 时空复杂度

|函数|T(n)|M(n)|
|--|--|--|
|matrixFree|O(1)|O(1)|
|matrixInit|O(xy)|O(xy)|
|matrixPlus|O(xy)|O(xy)|
|matrixMultiply|O(n^3)|O(xy)|
|matrixPrint|O(xy)|O(1)|
|matrixTrans|O(y+n)|O(xy)|
|getRow|O(y)|O(y)|
|workPlus|O(xy)|O(xy)|
|workMultiply|O(n^3)|O(xy)|

