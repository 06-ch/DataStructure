#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

struct Stack {
    int top;
    int maxsize;
    DataType* elements;
};

Stack* initStack(int max) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->elements = (DataType*)malloc(sizeof(DataType) * max);
    s->top = -1;
    s->maxsize = max;
    return s;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == s->maxsize - 1;
}

void push(Stack* s, DataType x) {
    if (isFull(s)) return;
    s->top++;
    s->elements[s->top] = x;
}

DataType pop(Stack* s) {
    if (isEmpty(s)) return -1;
    DataType x = s->elements[s->top];
    s->top--;
    return x;
}

DataType getTop(Stack* s) {
    if (isEmpty(s)) return -1;
    return s->elements[s->top];
}

void convertBase(int number, int base) {
    Stack* s = initStack(100);

    if (number == 0) {
        printf("0\n");
        return;
    }

    while (number > 0) {
        push(s, number % base);
        number = number / base;
    }

    while (!isEmpty(s)) {
        printf("%d", pop(s));
    }
    printf("\n");
}

int main() {
    Stack* s = initStack(5);
    push(s, 10);
    push(s, 20);
    push(s, 30);

    printf("%d\n", getTop(s));
    printf("%d\n", pop(s));
    printf("%d\n", pop(s));
    printf("%d\n", getTop(s));

    convertBase(10, 2);
    convertBase(255, 8);

    return 0;
}