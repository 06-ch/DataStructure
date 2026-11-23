#include<iostream>
using namespace std;
typedef int Datatype;
struct SeqQueue {
	int front;
	int rear;
	int maxsize;
	Datatype* elements;
};
void InitQueue(SeqQueue& Q, int size = 24) {
	Q.maxsize = size;
	Q.elements = new Datatype[Q.maxsize];
	Q.front = 0;
	Q.rear = 0;
}
bool IsEmpty(SeqQueue Q) {
	return Q.front == Q.rear;
}
bool IsFull(SeqQueue Q) {
	return (Q.rear + 1) % Q.maxsize == Q.front;
}
bool EnQueue(SeqQueue& Q, Datatype x) {
	if (IsFull(Q)) {
		cout << "[错误]顺序队列已满,入队失败!" << endl;
		return false;
	}
	Q.elements[Q.rear] = x;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	return true;
}
bool DeQueue(SeqQueue& Q, Datatype& x) {
	if (IsEmpty(Q)) {
		cout << "[错误]顺序队列为空,出队失败!" << endl;
		return false;
	}
	x = Q.elements[Q.front + 1] % Q.maxsize;
	return true;
}
bool GetFront(SeqQueue Q, Datatype& x) {
	if (IsEmpty(Q)) {
		cout << "[错误]顺序队列为空,获取队首失败!" << endl;
		return false;
	}
	x = Q.elements[Q.front];
	return true;
}
struct Node {
	Datatype data;
	Node* next;
};
struct LinkQueue {
	Node* front;
	Node* rear;
};
void InitLinkQueue(LinkQueue& Q) {
	Node* head = new Node;
	head->next = nullptr;
	Q.front = head;
	Q.rear = head;
}
bool IsEmptyLink(LinkQueue Q) {
	return Q.front == Q.rear;
}
void EnQueueLink(LinkQueue& Q, Datatype x) {
	Node* newNode = new Node;
	newNode->data = x;
	newNode->next = nullptr;
	Q.rear->next = newNode;
	Q.rear = newNode;
}
bool DeQueueLink(LinkQueue& Q, Datatype& x) {
	if (IsEmptyLink(Q)) {
		cout << "[错误]链队列为空,出队失败!" << endl;
		return false;
	}
	Node* p = Q.front->next;
	x = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) {
		Q.rear = Q.front;
	}
	delete p;
	return true;
}
bool GetFrontLink(LinkQueue Q, Datatype& x) {
	if (IsEmptyLink(Q)) {
		cout << "[错误]链队列为空,获取队首失败!" << endl;
		return false;
	}
	x = Q.front->next->data;
	return true;
}
int main() {
	Datatype val;
	cout << "测试顺序队列" << endl;
	SeqQueue sq;
	InitQueue(sq);
	cout << "1.入队 10,20,30" << endl;
	EnQueue(sq, 10);
	EnQueue(sq, 20);
	EnQueue(sq, 30);
	GetFront(sq, val);
	cout << "2,当前队首元素:" << val << endl;
	DeQueue(sq, val);
	cout << "3,出队元素:" << val << endl;
	GetFront(sq,val);
	cout << "4,出队后新队首:" << val << endl;
	cout << "\n测试链队列" << endl;
	LinkQueue lq;
	InitLinkQueue(lq);

	cout << "1,入队 100, 200" << endl;
	EnQueueLink(lq, 100);
	EnQueueLink(lq, 200);
	GetFrontLink(lq, val);
	cout << "2,当前队列队首:" << val << endl;
	DeQueueLink(lq, val);
	cout << "3,出队元素:" << val << endl;
	DeQueueLink(lq, val);
	cout << "4,再次出队元素:" << val << endl;
	cout << "5,尝试空队列出队(触发报错):" << endl;
	DeQueueLink(lq, val);
	return 0;
}