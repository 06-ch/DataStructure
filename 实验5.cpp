#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char DataType;

typedef struct LinkStack {
    DataType data;
    struct LinkStack* next;
} LinkStack;


LinkStack* InitStack() {
    LinkStack* S = (LinkStack*)malloc(sizeof(LinkStack));
    S->next = NULL;
    return S;
}


bool IsEmpty(LinkStack* S) {
    return S->next == NULL;
}


void Push(LinkStack* S, DataType x) {
    LinkStack* p = (LinkStack*)malloc(sizeof(LinkStack));
    p->data = x;
    p->next = S->next;
    S->next = p;
}


bool Pop(LinkStack* S, DataType* e) {
    if (IsEmpty(S)) return false;
    LinkStack* p = S->next;
    *e = p->data;
    S->next = p->next;
    free(p);
    return true;
}


bool GetTop(LinkStack* S, DataType* e) {
    if (IsEmpty(S)) return false;
    *e = S->next->data;
    return true;
}

bool BracketMatch(const char* str) {
    LinkStack* stack = InitStack();
    bool flag = true;
    int i = 0;

    while (str[i] != '\0' && flag) {
        char ch = str[i];
        char topElem;

        if (ch == '(' || ch == '[' || ch == '{') {
            Push(stack, ch);
        }
        else if (ch == ')') {
            if (!IsEmpty(stack) && GetTop(stack, &topElem) && topElem == '(') {
                Pop(stack, &topElem);
            }
            else {
                flag = false;
            }
        }
        else if (ch == ']') {
            if (!IsEmpty(stack) && GetTop(stack, &topElem) && topElem == '[') {
                Pop(stack, &topElem);
            }
            else {
                flag = false;
            }
        }
        else if (ch == '}') {
            if (!IsEmpty(stack) && GetTop(stack, &topElem) && topElem == '{') {
                Pop(stack, &topElem);
            }
            else {
                flag = false;
            }
        }
        i++;
    }

    bool result = IsEmpty(stack) && flag;

    
    char temp;
    while (!IsEmpty(stack)) {
        Pop(stack, &temp);
    }
    free(stack);

    return result;
}

int main() {
    if (BracketMatch("{()[]}")) printf("∆•≈‰\n");
    else printf("≤ª∆•≈‰\n");

    if (BracketMatch("(){]")) printf("∆•≈‰\n");
    else printf("≤ª∆•≈‰\n");

    return 0;
}