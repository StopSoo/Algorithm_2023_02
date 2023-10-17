// Q. 2번 문제와 동일하게, N(10000 > N >= 100)을 입력 받아
//    rand() 함수를 이용하여 중복되지 않는 N개의 난수를 발생시킨 후, 이를 삽입하여 이진 탐색트리 T2을 만들어라.
//    그리고, 앞서 생성한 배열 데이터를 순서대로 10개씩 불러들인뒤, 그중 한 개를 랜덤하게 골라 삭제하는 프로그램을 아래의 BSTdelete() 코드를 완성하여 작성하시오.
//    또한, 위 방법을 통해 10개 이상의 자료들을 삭제하는 데 소요된 ‘키의 평균 비교 횟수’를 구하고, 아래의 출력 예제와 같이 출력하는 프로그램을 작성하시오.
//    (단, 평균 비교 횟수는 각 자료 삭제를 위한 키의 비교회수 합계를 구한 다음에 삭제한 자료수로 나누어서 계산함 )
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
    void BSTinsert(itemType v, infoType info);
    infoType BSTdelete(itemType v);
};

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

infoType BST::BSTdelete(itemType v) {   // 삭제 함수
    node* parent = nullptr; // 삭제하려는 노드의 부모 노드
    node* target = head;    // 삭제하려는 노드, 처음엔 head로 초기화
    static int compare = 0;    // 비교 횟수 변수

    // 삭제하려는 값인 v 값과 일치하는 노드를 찾을 때까지 탐색
    compare++;
    while (target != z && target->key != v) { // 노드 리스트 끝에 도달하거나 v 값 노드를 찾으면 종료
        parent = target;

        compare++;
        if (v < target->key)
            target = target->l;
        else
            target = target->r;
    }
    // 삭제하려는 노드가 존재하지 않는다면
    compare++;
    if (target == z) {
        return compare;
    }

    // 1) 삭제하려는 노드가 리프 노드인 경우
    if (target->l == z && target->r == z) {
        compare++;
        if (parent) {   // 부모 노드가 존재할 때
            compare++;
            if (parent->l == target)    // 부모의 왼쪽 자식이 삭제하려는 노드라면 왼쪽을 연결 해제
                parent->l = z;
            else    // 부모의 오른쪽 자식이 삭제하려는 노드라면 오른쪽을 연결 해제
                parent->r = z;
        } else {    // 부모 노드가 존재하지 않을 때
            head = z;
        }
        delete target;  // 삭제하려는 노드 삭제
    } // 2) 삭제하려는 노드가 자식 노드를 하나만 가지고 있는 경우
    else if (target->l == z || target->r == z) {
        compare += 2;   // 위 if문을 거쳤기 때문에 2번으로 체크
        // 삭제하려는 노드의 자식 노드를 저장
        node* child = (target->l == z) ? target->r : target->l;

        if (parent) {   // 부모 노드가 존재할 때
            compare++;
            if (parent->l == target)    // 부모 노드의 왼쪽 노드가 삭제하려는 노드일 경우
                parent->l = child;  // 해당 노드에 child를 저장
            else    // 부모 노드의 오른쪽 노드가 삭제하려는 노드일 경우
                parent->r = child;  // 해당 노드에 child를 저장
        } else {    // 부모 노드가 존재하지 않을 때
            head = child;
        }
        delete target;  // 삭제하려는 노드 삭제
    } // 3) 삭제하려는 노드가 자식 노드를 둘 다 가지고 있는 경우
    else {
        compare += 3;   // if문을 모두 거쳤기 때문에 3번으로 체크
        // 일반적으로 삭제할 노드의 후임자는 삭제하려는 노드의 오른쪽 서브 트리에서 가장 작은 값을 가진 노드 (!)
        node* successor = target->r;    // l, r 중 target 자리에 올 노드를 임의로 r로 설정
        node* successorParent = target; // 후임자 노드의 부모 노드는 target
        // 삭제하려는 노드의 오른쪽 서브 트리에서 가장 작은 값을 찾고 successor에 넣는 과정
        while (successor->l != z) {
            compare++;
            successorParent = successor;
            successor = successor->l;
        }
        compare++;
        if (successorParent->l == successor)    // successor가 부모 노드의 왼쪽 자식일 때
            successorParent->l = successor->r;  // 원래 자신의 자리에 자신의 오른쪽 자식 노드를 저장
        else    // successor가 부모 노드의 오른쪽 자식일 때
            successorParent->r = successor->r;  // 원래 자신의 자리에 자신의 오른쪽 자식 노드를 저장
        // target 노드를 successor 노드로 변경
        target->key = successor->key;
        target->info = successor->info;
        delete successor;   // successor 노드는 원래의 target 노드 자리로 옮겨졌으므로 successor 노드 삭제
    }
    return compare;
}

int main() {
    int N;
    cin >> N;
    if (N % 10 != 0) {  // 10의 배수를 입력하지 않으면 10개씩 불러올 수 없기 때문에 예외 처리
        cout << "10의 배수를 입력하세요." << endl;
        return 0;
    }

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
    int totalCompare = 0;    // 총 비교횟수를 담을 변수
    int randomIndex;
    int deleteNumCount = 0;     // 삭제한 자료 수를 담을 변수
    while (index < N) {
        randomIndex = rand() % 10;  // 랜덤 인덱스 추출
        totalCompare += T2.BSTdelete(values[index + randomIndex]);  // 해당 값에 대해 삭제 함수 실행
        deleteNumCount++;   // 삭제한 자료 수 체크
        index += 10;    // 다음 10개 숫자 세트로 넘어감
    }
    double averageCompare = (double)totalCompare / (double)deleteNumCount;   // 평균 비교 횟수 계산
    cout << averageCompare << " (T2의 평균 비교 횟수)" << endl;
    return 0;
}