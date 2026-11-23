#include <iostream>
#include <cstring>
#include <iomanip> 

using namespace std;

// 定义联系人结构体
struct Contact
{
    char name[50]; // 联系人姓名
    char phone[12]; // 联系人电话
    struct Birthday // 联系人生日
    {
        int year;  // 年
        int month; // 月
        int day;   // 日
    } birthday;
    int age; // 联系人年龄
};

// 定义通讯录结点结构体
struct Node
{
    Contact data; // 联系人信息
    Node* next;   // 指向下一个结点的指针
};

/*函数功能：初始化一个空的通讯录链表
* 函数形参:无
* 函数返回值：返回一个空的通讯录链表头指针，Node* 类型
*/
Node* InitAddressBook()
{
    Node* head = new Node;
    if (head == NULL)
        cout << "内存分配失败！" << endl;
    else
        head->next = NULL;
    return head;
}

/*函数功能：输入单个联系人信息
* 函数形参：无
* 函数返回值：返回联系人信息，Contact 类型
*/
Contact InputContact()
{
    Contact data;
    cout << "请输入联系人姓名：";
    cin >> data.name;
    cout << "请输入联系人电话：";
    cin >> data.phone;
    cout << "请输入联系人生日（年 月 日）：";
    cin >> data.birthday.year >> data.birthday.month >> data.birthday.day;
    cout << "请输入联系人年龄：";
    cin >> data.age;
    return data;
}

/*函数功能：输出单个联系人信息
* 函数形参：联系人信息 Contact data
* 函数返回值：无，void 类型
*/
void OutputContact(Contact data)
{
    cout << left << setw(12) << data.name
        << setw(15) << data.phone
        << data.birthday.year << "年" << data.birthday.month << "月" << data.birthday.day << "日\t"
        << data.age << "岁" << endl;
}

/*函数功能：输出通讯录中所有联系人信息
* 函数形参：通讯录链表头指针 Node* head
* 函数返回值：无，void 类型
*/
void OutputAddressBook(Node* head)
{
    Node* node = head->next;
    if (node == NULL) {
        cout << "暂无联系人信息！" << endl;
        return;
    }

    cout << left << setw(12) << "姓名" << setw(15) << "电话" << "生日\t\t年龄" << endl;
    cout << "----------------------------------------------------" << endl;

    while (node) {
        OutputContact(node->data);
        node = node->next;
    }
}

/*函数功能：采用尾插法创建一个通讯录链表
* 函数形参：通讯录链表头指针 Node* head，联系人信息 Contact data
* 函数返回值：创建成功返回 true，否则返回 false，bool 类型
*/
bool CreateAddressBookTail(Node* head, Contact data)
{
    static Node* tail = head;
    Node* node = new Node;
    if (node == NULL)
    {
        cout << "内存分配失败！" << endl;
        return false;
    }
    node->data = data;
    node->next = NULL;
    tail->next = node;
    tail = node;
    return true;
}

/*函数功能：按姓名查找通讯录中指定联系人信息
* 函数形参：通讯录链表头指针 Node* head，联系人姓名 char name[]
* 函数返回值：查找成功，返回地址，否则返回空，Node* 类型
*/
Node* SearchContactByName(Node* head, char* name)
{
    Node* node = head->next;
    while (node) {
        if (strcmp(node->data.name, name) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}

/*函数功能：查找指定联系人的前驱结点
* 函数形参：通讯录链表头指针 Node* head，指定联系人地址 Node* target
* 函数返回值：查找成功，返回前驱，否则返回空，Node* 类型
*/
Node* SearchPreNode(Node* head, Node* target)
{
    for (Node* pre = head; pre->next != NULL; pre = pre->next) {
        if (pre->next == target)
            return pre;
    }
    return NULL;
}

/*函数功能：删除指定联系人
* 函数形参：通讯录链表头指针 Node* head，指定联系人 Node* target
* 函数返回值：删除成功，返回 true，否则返回 false，bool 类型
*/
bool DeleteContact(Node* head, Node* target)
{
    Node* pre = SearchPreNode(head, target);
    if (pre)
    {
        pre->next = target->next;
        delete target;
        return true;
    }
    return false;
}

/*函数功能：在指定联系人的后面插入一个新的联系人
* 函数形参：通讯录链表头指针 Node* head，指定联系人地址 Node* target，联系人信息 Contact data
* 函数返回值：插入成功，返回 true，否则返回 false，bool 类型
*/
bool InsertContactAfter(Node* head, Node* target, Contact data)
{
    Node* node = new Node;
    if (node) {
        node->data = data;
        node->next = target->next;
        target->next = node;
        return true;
    }
    return false;
}

int main()
{
    Node* head = InitAddressBook();
    int choice;
    char searchName[50];
    Contact newContact;
    Node* targetNode = NULL;

    while (true)
    {
        cout << "\n========== 通讯录管理系统 ==========" << endl;
        cout << "1. 批量建立通讯录链表 (尾插)" << endl;
        cout << "2. 在某联系人后插入" << endl;
        cout << "3. 查询联系人" << endl;
        cout << "4. 删除联系人" << endl;
        cout << "5. 显示所有联系人" << endl;
        cout << "0. 退出程序" << endl;
        cout << "====================================" << endl;
        cout << "请输入您的选择：";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int n;
            cout << "请输入要添加的联系人数量：";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "\n--- 录入第 " << i + 1 << " 个联系人 ---" << endl;
                newContact = InputContact();
                CreateAddressBookTail(head, newContact);
            }
            break;
        }
        case 2:
        {
            char targetName[50];
            cout << "请输入要在哪位联系人之后插入 (输入姓名)：";
            cin >> targetName;
            targetNode = SearchContactByName(head, targetName);

            if (targetNode != NULL) {
                cout << "请输入新联系人信息：" << endl;
                newContact = InputContact();
                if (InsertContactAfter(head, targetNode, newContact)) {
                    cout << "插入成功！" << endl;
                }
            }
            else {
                cout << "未找到该联系人，无法插入。" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "请输入要查询的联系人姓名：";
            cin >> searchName;
            targetNode = SearchContactByName(head, searchName);
            if (targetNode != NULL) {
                OutputContact(targetNode->data);
            }
            else {
                cout << "查无此人！" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "请输入要删除的联系人姓名：";
            cin >> searchName;
            targetNode = SearchContactByName(head, searchName);
            if (targetNode != NULL) {
                if (DeleteContact(head, targetNode)) {
                    cout << "删除成功！" << endl;
                }
            }
            else {
                cout << "没有找到该联系人。" << endl;
            }
            break;
        }
        case 5:
        {
            OutputAddressBook(head);
            break;
        }
        case 0:
            cout << "退出系统。" << endl;
            return 0;
        default:
            cout << "输入有误，请重新输入！" << endl;
            break;
        }
    }
    return 0;
}