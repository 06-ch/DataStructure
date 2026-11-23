#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define LIST_MAXSIZE 50
typedef int ElemType;

typedef struct
{
    ElemType data[LIST_MAXSIZE];
    int length;
} SqList;

void InitSqList(SqList* L)
{
    L->length = 0;
}

void CreateSqList(SqList* L, int n)
{
    int i;
    if (n < 0 || n > LIST_MAXSIZE)
    {
        printf("输入元素个数不合法！\n");
        return;
    }
    L->length = n;
    printf("请输入%d个元素：", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &L->data[i]);
    }
}

bool SqListEmpty(SqList* L)
{
    if (L->length == 0)
        return true;
    return false;
}

int SqListLength(SqList* L)
{
    return L->length;
}


void PrintSqList(SqList* L)
{
    int i;
    if (SqListEmpty(L))
    {
        printf("顺序表为空！\n");
        return;
    }
    printf("顺序表：");
    for (i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}
bool GetElem(SqList* L, int pos, ElemType* e)
{
    if (pos < 1 || pos > L->length)
        return false;
    *e = L->data[pos - 1];
    return true;
}

int LocateSeqElem(SqList* L, ElemType val)
{
    int i;
    for (i = 0; i < L->length; i++)
    {
        if (L->data[i] == val)
        {
            return i + 1;
        }
    }
    return 0;
}

int BinarySearch(SqList* L, ElemType val)
{
    int low, high, mid;
    low = 1;
    high = L->length;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (L->data[mid - 1] == val)
            return mid;
        else if (L->data[mid - 1] < val)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;
}


bool ListInsert(SqList* L, int pos, ElemType e)
{
    int i;
    if (pos < 1 || pos > L->length + 1)
    {
        printf("插入位置错误\n");
        return false;
    }
    if (L->length >= LIST_MAXSIZE)
    {
        printf("顺序表已满\n");
        return false;
    }
    
    for (i = L->length; i >= pos; i--)
    {
        L->data[i] = L->data[i - 1];
    }
    L->data[pos - 1] = e;
    L->length++;
    return true;
}


bool ListDeletePos(SqList* L, int pos, ElemType* e)
{
    int i;
    if (pos < 1 || pos > L->length)
    {
        printf("删除位置错误\n");
        return false;
    }
    *e = L->data[pos - 1];
    for (i = pos; i <= L->length - 1; i++)
    {
        L->data[i - 1] = L->data[i];
    }
    L->length--;
    return true;
}

void ListDeleteAllVal(SqList* L, ElemType val)
{
    int i, count = 0;
    for (i = 0; i < L->length; i++)
    {
        if (L->data[i] != val)
        {
            L->data[count++] = L->data[i];
        }
    }
    L->length = count;
}

int main(void)
{
    SqList L;
    InitSqList(&L);
    int op, n, pos, ret;
    ElemType x, e;
    while (1)
    {
        printf("\n====顺序表操作菜单====\n");
        printf("1.创建顺序表\n");
        printf("2.判断是否为空\n");
        printf("3.求表长度\n");
        printf("4.输出顺序表\n");
        printf("5.取指定位置元素\n");
        printf("6.顺序查找元素\n");
        printf("7.二分查找元素\n");
        printf("8.指定位置插入元素\n");
        printf("9.删除指定位置元素\n");
        printf("10.删除全部指定值元素\n");
        printf("0.退出程序\n");
        printf("请输入操作序号：");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("输入元素个数：");
            scanf("%d", &n);
            CreateSqList(&L, n);
            break;
        case 2:
            if (SqListEmpty(&L))
                printf("顺序表是空表\n");
            else
                printf("顺序表非空\n");
            break;
        case 3:
            printf("当前顺序表长度：%d\n", SqListLength(&L));
            break;
        case 4:
            PrintSqList(&L);
            break;
        case 5:
            printf("输入位置pos：");
            scanf("%d", &pos);
            if (GetElem(&L, pos, &e))
                printf("第%d号元素 = %d\n", pos, e);
            else
                printf("位置非法\n");
            break;
        case 6:
            printf("输入要查找的值：");
            scanf("%d", &x);
            ret = LocateSeqElem(&L, x);
            if (ret != 0)
                printf("顺序查找：元素在第%d位\n", ret);
            else
                printf("顺序查找：未找到\n");
            break;
        case 7:
            printf("输入要查找的值：");
            scanf("%d", &x);
            ret = BinarySearch(&L, x);
            if (ret != 0)
                printf("二分查找：元素在第%d位\n", ret);
            else
                printf("二分查找：未找到（表必须有序）\n");
            break;
        case 8:
            printf("输入插入位置pos、插入元素x：");
            scanf("%d%d", &pos, &x);
            if (ListInsert(&L, pos, x))
                printf("插入成功\n");
            break;
        case 9:
            printf("输入删除位置pos：");
            scanf("%d", &pos);
            if (ListDeletePos(&L, pos, &e))
                printf("删除成功，被删元素=%d\n", e);
            break;
        case 10:
            printf("输入要删除的值：");
            scanf("%d", &x);
            ListDeleteAllVal(&L, x);
            printf("已删除所有值为%d的元素\n", x);
            break;
        case 0:
            printf("程序结束\n");
            return 0;
        default:
            printf("输入无效，请重新选择\n");
        }
    }
}