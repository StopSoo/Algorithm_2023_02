// Q. 2번 문제와 동일하게, N(10000 > N >= 100)을 입력 받아
//    rand() 함수를 이용하여 중복되지 않는 N개의 난수를 발생시킨 후, 이를 삽입하여 이진 탐색트리 T2을 만들어라.
//    그리고, 앞서 생성한 배열 데이터를 순서대로 10개씩 불러들인뒤, 그중 한 개를 랜덤하게 골라 삭제하는 프로그램을 아래의 BSTdelete() 코드를 완성하여 작성하시오.
//    또한, 위 방법을 통해 10개 이상의 자료들을 삭제하는 데 소요된 ‘키의 평균 비교횟수’를 구하고, 아래의 출력 예제와 같이 출력하는 프로그램을 작성하시오.
//    (단, 평균비교회수는 각 자료 삭제를 위한 키의 비교회수 합계를 구한 다음에 삭제한 자료수로 나누어서 계산함 )
#include <iostream>
#include <set>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

#define infoNIL 0
typedef int itemType;
typedef double infoType;

class BST {
private:
    struct node {
        itemType key;
        infoType info;
        struct node *l, *r;
        node(itemType k, infoType i, struct node *ll, struct node *rr) {  // node의 생성자
            key = k;
            info = i;
            l = ll;
            r = rr;
        };
    };
    // head : List의 시작 노드 포인터
    // z : List의 끝 노드 포인터 – NULL에 해당
    node *head, *z;

public:
    BST() {  // 생성자 -> 매개변수는 사용하지 않아 제거함
        z = new node( 0, infoNIL, nullptr, nullptr);
        head = nullptr; // 루트 노드는 없는 채로 시작
    }
    ~BST() {};    // 소멸자
    infoType BSTsearch(itemType v);
    void BSTinsert(itemType v, infoType info);
    void BSTdelete(itemType v);
};

infoType BST::BSTsearch(itemType v) {   // 탐색 함수
    static int compare = 0;    // 비교 횟수 변수

    while (head != z) {
        compare++;
        if (v == head->key) // 찾고자 하는 값을 찾았다면
            return compare;
        else if (v < head->key) // 찾고자 하는 값보다 현재 노드 값이 크다면 왼쪽 탐색
            head = head->l;
        else    // 찾고자 하는 값이 현재 노드 값보다 크다면 오른쪽 탐색
            head = head->r;
    }
    return compare;
}

void BST::BSTinsert(itemType v, infoType info) {    // 삽입 함수
    node *newNode = new node(v, info, z, z);    // 새 노드 생성
    static node *temp = head;  // 노드 간 이동을 위한 노드, 삽입이 시작되면 head를 가리킴

    while (true) {
        if (head == nullptr) {  // 첫 삽입이라면 newNode를 head로 설정
            head = newNode;
            temp = head;
            return;
        } else {    // 이미 루트 노드가 존재한다면
            if (v < temp->key) {    // 찾고자 하는 값보다 루트 노드 값이 클 때
                if (temp->l == z) { // 왼쪽 노드가 NULL이라면
                    temp->l = newNode;  // 왼쪽에 새 노드 연결
                    return;
                }
                temp = temp->l; // 왼쪽 노드가 NULL이 아니라면 NULL일 때까지 왼쪽 노드로 이동
            } else {    // 찾고자 하는 값이 루트 노드 값보다 클 때
                if (temp->r == z) { // 오른쪽 노드가 NULL이라면
                    temp->r = newNode;  // 오른쪽에 새 노드 연결
                    return;
                }
                temp = temp->r; // 오른쪽 노드가 NULL이 아니라면 NULL일 때까지 오른쪽 노드로 이동
            }
        }
    }
}

void BST::BSTdelete(itemType v) {   // 삭제 함수
    node* parent = nullptr;
    node* current = head;

    while (current != z && current->key != v) {
        parent = current;

        if (v < current->key)
            current = current->l;
        else
            current = current->r;
    }

    if (current == z) {
        // 삭제하려는 노드가 존재하지 않음
        return;
    }

    if (current->l == z && current->r == z) {
        // Case 1: 삭제하려는 노드가 리프 노드인 경우
        if (parent) {
            if (parent->l == current)
                parent->l = z;
            else
                parent->r = z;
        } else {
            head = z;
        }
        delete current;
    } else if (current->l == z || current->r == z) {
        // Case 2: 삭제하려는 노드가 자식 노드를 하나 가지고 있는 경우
        node* child = (current->l == z) ? current->r : current->l;
        if (parent) {
            if (parent->l == current)
                parent->l = child;
            else
                parent->r = child;
        } else {
            head = child;
        }
        delete current;
    } else {
        // Case 3: 삭제하려는 노드가 자식 노드를 둘 가지고 있는 경우
        node* successor = current->r;
        node* successorParent = current;
        while (successor->l != z) {
            successorParent = successor;
            successor = successor->l;
        }

        if (successorParent->l == successor)
            successorParent->l = successor->r;
        else
            successorParent->r = successor->r;

        current->key = successor->key;
        current->info = successor->info;
        delete successor;
    }
}

int main() {
    int N;
    cin >> N;

    srand((unsigned int)time(0));   // 중복 없이 N개의 난수 생성을 위한 시드값 설정

    set<int> uniqueValues;  // N개의 난수 생성을 위한 집합
    vector<int> values;
    // 중복되지 않는 N개 난수 생성
    while (uniqueValues.size() < N) {
        int value = rand() % 10000 + 1;    // 1 이상 10000 이하인 N개의 난수
        if (uniqueValues.find(value) == uniqueValues.end()) {   // value와 중복되는 값이 없을 때
            uniqueValues.insert(value);
            values.push_back(value);
        }
    }
    // 이진 탐색 트리 생성
    BST T2;
    for (int value: values) {
        T2.BSTinsert(value, infoNIL);
    }

    // 10개씩 불러와 그 중 한 개를 랜덤하게 골라 삭제
    int index = 0;
    int randomIndex;
    while (index < N) {
        randomIndex = rand() % 10;  // 랜덤 인덱스 추출
        T2.BSTdelete(values[index + randomIndex]);  // 해당 값에 대해 삭제 함수 실행
        index += 10;    // 다음 10개 숫자 세트로 넘어감
    }


//    int totalCompare = 0;    // 총 비교횟수를 담을 변수
//    for (int i = 0; i < 100; i++) {
//        int randIndex = rand() % N; // 인덱스를 랜덤으로 선택하고
//        int searchNumber = values[randIndex];   // 해당 인덱스의 값을 탐색 값으로 설정
//        totalCompare += T2.BSTsearch(searchNumber); // 탐색하는 데 걸린 비교 횟수를 총 비교 횟수 변수에 더함
//    }
//
//    double averageCompare = (double)totalCompare / 100.0;   // 평균 비교 횟수 계산
//    cout << averageCompare << " (T2의 평균 비교 횟수)" << endl;
    return 0;
}