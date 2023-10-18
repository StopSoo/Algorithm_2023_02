// Q. 다음은 스택(Stack) 기반의 수식 트리의 응용 예이다.
//    아래의 소스코드를 참고하여, 후위 표기 수식 입력 데이터를 이용해 수식 트리에 자료를 저장하고
//    중위 순회(Inorder Traversal) 방식으로 트리를 순회한 결과를 출력하시오.
//    입력 데이터: A B C - D E * * F + *
#include <iostream>
using namespace std;

struct treeNode {
    char info;
    treeNode *l, *r;
};

treeNode *x, *z;

void visit(treeNode *t) // 방문한 노드의 값 출력
{
    cout << t->info << " ";
}

void traverse(treeNode *t)  // 순회 함수
{
    if (t != z)
    {
        traverse(t->l); // 왼쪽 순회
        visit(t);
        traverse(t->r); // 오른쪽 순회
    }
}

template <typename itemType>
class Stack {
private:
    itemType *stack;
    int p;
    int max_size;

public:
    Stack(int max = 100) {    // 생성자
        stack = new itemType[max];
        p = 0;  // 인덱스
        max_size = max; // 스택 사이즈
    };

    ~Stack(){   // 소멸자
        delete [] stack;
    };

    inline void push(itemType v) {  // 스택에 원소를 삽입
        if (p < max_size)
            stack[p++] = v;
    };

    inline itemType pop(){  // 스택의 최상단 원소를 반환
        if (p > 0)
            return stack[--p];
        return nullptr;
    };

    inline int empty(){ // 스택이 비어 있는지 여부를 반환
        return !p;
    };
};

int main() {
    char c;
    Stack<treeNode*> stack(50);
    // 후위 표기 수식을 트리로 구성
    z = new treeNode;
    z->l = z;
    z->r = z;

    while ((c= cin.get()) != '\n') // 받아 온 한 문자가 개행 문자가 아닐 때까지 반복
    {
        while(c == ' ') // 받아 온 한 문자가 공백 문자일 경우
            cin.get(c); // 다음 문자 받아 오기
        x = new treeNode;
        x->info = c;
        x->l = z;
        x->r = z;
        if (c == '+' || c == '*' || c == '-') { // 받아 온 한 문자가 연산자일 경우
            x->r = stack.pop(); // 첫 번째로 뺀 수를 r에 넣기
            x->l = stack.pop(); // 두 번째로 뺸 수를 l에 넣기
        }
        stack.push(x);
    }

    traverse(stack.pop());  // 연산된 값에 대해 중위 순회 함수 실행
    cout << endl;

    delete z;   // 메모리 해제
    return 0;
}

