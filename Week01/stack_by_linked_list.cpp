// Q. 포인터를 이용하는 스택(Stack2) 자료구조를 완성하고, 이를 통해 후위(postfix) 표기의 수식을 계산해주는 프로그램을 작성하세요.
//    단, + 와 * 뿐만 아니라 – 와 / 까지도 연산이 가능해야 한다.
#include <iostream>
using namespace std;

template <typename itemType>
class Stack2 {
private:
    struct node {
        itemType key;
        struct node *next;
    };
    struct node *head;
public:
    Stack2() {    // 생성자
        head = new node;
        head->next = NULL;
    }
    ~Stack2() {     // 소멸자 (모든 노드들의 메모리 해제)
        while (head) {
            node *temp;
            temp = head;
            head = head->next;
            delete temp;
        }
        delete head;
    }
    void push (itemType value) {
        node *new_node = new node;  // 새로운 노드 생성
        node *temp; // 임시 노드 생성 -> head 대신 위치 설정
        new_node->key = value;  // key에 입력 받은 값 대입

        if (head->next == NULL) {   // head 후 첫 노드일 경우
            head->next = new_node;  // new_node를 head의 next로 연결
            new_node->next = NULL;  // new_node이 next를 NULL로 초기화
            return;
        } else {
            temp = head->next;  // temp 노드를 head->next로 초기화
            while (temp->next != NULL) {    // 끝까지 이동
                temp = temp->next;
            }
            temp->next = new_node;  // 연결 리스트의 끝에 새로운 노드 삽입
            new_node->next = NULL;
        }
    }

    itemType pop() {    // stack의 마지막 원소 반환
        node *temp; // 임시 노드 생성 -> head 대신 위치 설정
        node *prev;
        itemType key;
        if (head->next != NULL) {   // 노드가 1개가 아니라면
            temp = head->next;
            while (temp->next != NULL) {    // 맨 끝으로 간다.
                prev = temp;
                temp = temp->next;
            }
            key = temp->key;
            prev->next = temp->next;
            delete temp;
            return key;
        }
        return head->key;
    }

    int empty() {   // stack이 비어 있는지 여부를 반환
        head->next == NULL ? true : false;
    }
};

int main() {
    char c; // 사용자가 입력한 문자
    Stack2<double> stack;
    double x;  // 스택에 들어갈 원소를 담을 변수

    while ((c = cin.get()) != '\n') {
        x = 0;
        while (c == ' ')
            cin.get(c);
        if (c == '+') { x = stack.pop() + stack.pop(); }
        if (c == '-') { x = abs(stack.pop() - stack.pop()); }
        if (c == '*') { x = stack.pop() * stack.pop(); }
        if (c == '/') {
            int a = stack.pop();
            int b = stack.pop();
            x = double(max(a, b)) / double(min(a, b));
        }
        while (c >= '0' && c <= '9') {
            x = 10 * x + (c - '0');
            int n = 1;
            if ((c = cin.get()) == '.') {
                while ((c = cin.get()) != ' ') {
                    x = x + pow(0.1, n) * (c - '0');
                    n++;
                }
            }
        }
        stack.push(x);
    }
    cout << stack.pop() << '\n';
}
