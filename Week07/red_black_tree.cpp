// Q. N(20000 >= N >= 1000)을 입력 받고 rand() 함수를 이용하여 N개의 중복되지 않는 난수로 이루어진 데이터 배열을 만들고,
//    BSTinsert()를 이용하여 앞서 생성한 N개의 데이터를 순서대로 삽입하여 이진 탐색트리 T1을 만들어라.
//    그리고 T1트리의 자료를 Inorder로 순회(Traversal)하면서 재배치시키고, 이를 입력으로 새로운 이진탐색 트리 T2와 Red-Black 트리 T3를 만드시오.
//    그리고, 각각의 트리를 초기 구축하는데 소요된 ‘키의 평균 비교 횟수’와 각각의 트리에서 랜덤한 100개의 자료들을 탐색(반드시 트리에 포함된 자료일 필요는 없음)하는데 소요된 ‘키의 평균 비교회수’를 구하고
//    아래의 출력 예제와 같이 출력하는 프로그램을 작성하시오.
//    또한, T2와 T3의 평균 비교 횟수를 이용해 Red-Black 트리의 탐색 성능에 대해 논의하시오.
//    (단, 삽입에 필요한 평균 비교 횟수는 각 자료 삽입을 위한 키의 비교 횟수 합계를 구한 다음에 전체 자료수 N으로 나누어서 계산함)
#include <iostream>
#include <set>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1
typedef int itemType;
typedef double infoType;
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
    void BSTinsert(itemType v, infoType info, int &compare);
    infoType BSTsearch(itemType v);
    void inorderTraversal(vector<itemType>& tree);   // 중위 순회 함수
};

void BST::BSTinsert(itemType v, infoType info, int &compare) {    // 삽입 함수
    node *newNode = new node(v, info, z, z);    // 새 노드 생성
    static node *temp = head;  // 노드 간 이동을 위한 노드, 삽입이 시작되면 head를 가리킴

    while (true) {
        compare++;
        if (head == nullptr) {  // 첫 삽입이라면 newNode를 head로 설정
            head = newNode;
            temp = head;
            return;
        } else {    // 이미 루트 노드가 존재한다면
            compare++;
            if (v < temp->key) {    // 찾고자 하는 값보다 루트 노드 값이 클 때
                compare++;
                if (temp->l == z) { // 왼쪽 노드가 NULL이라면
                    temp->l = newNode;  // 왼쪽에 새 노드 연결
                    return;
                }
                temp = temp->l; // 왼쪽 노드가 NULL이 아니라면 NULL일 때까지 왼쪽 노드로 이동
            } else {    // 찾고자 하는 값이 루트 노드 값보다 클 때
                compare++;
                if (temp->r == z) { // 오른쪽 노드가 NULL이라면
                    temp->r = newNode;  // 오른쪽에 새 노드 연결
                    return;
                }
                temp = temp->r; // 오른쪽 노드가 NULL이 아니라면 NULL일 때까지 오른쪽 노드로 이동
            }
        }
    }
}

infoType BST::BSTsearch(itemType v) {   // 탐색 함수
    static int compare = 0;    // 비교 횟수 변수
    node *current = head;   // head를 가리키고 직접 이동하는 노드

    while (current != z) {
        compare++;
        if (v == current->key) // 찾고자 하는 값을 찾았다면
            return compare;
        else if (v < current->key) // 찾고자 하는 값보다 현재 노드 값이 크다면 왼쪽 탐색
            current = current->l;
        else    // 찾고자 하는 값이 현재 노드 값보다 크다면 오른쪽 탐색
            current = current->r;
    }
    return compare;  // 비정상 종료
}

void BST::inorderTraversal(vector<itemType>& arr) {
    node *current = head;
    node *child;

    while (current != z) {
        if (current->l == z) {  // 현재 노드의 왼쪽 자식이 없을 때
            arr.push_back(current->key);   // key를 push
            current = current->r;
        } else {    // 현재 노드의 왼쪽 자식이 있다면
            child = current->l;
            while (child->r != z && child->r != current) {
                child = child->r;
            }

            if (child->r == z) {
                child->r = current;
                current = current->l;
            } else {
                child->r = z;
                arr.push_back(current->key);
                current = current->r;
            }
        }
    }
}

class RBtree {
private:
    struct node {
        itemType key, tag;
        infoType info;
        struct node *l, *r;
        node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr) {
            key = k;
            info = i;
            tag = t;
            l = ll;
            r = rr;
        }
    };
    struct node *head, *tail, *x, *p, *g, *gg, *z;

public:
    RBtree() {  // 생성자
        z = new node(0, infoNIL, black, 0, 0);
        z->l = z;
        z->r = z;
        tail = z;
        head = new node(itemMIN, infoNIL, black, z, z);
    }

    itemType insert(itemType k, infoType info) {
        int compare = 0;
        x = head;
        p = head;
        g = head;

        while (x != z) {
            compare++;
            gg = g;
            g = p;
            p = x;

            compare++;
            x = (k < x->key) ? x->l : x->r;

            compare += 2;
            if (x->l->tag && x->r->tag)
                split(k);
        }
        x = new node(k, info, red, z, z);

        compare++;
        if (k < p->key)
            p->l = x;
        else
            p->r = x;

        split(k);
        head->r->tag = black;

        return compare;
    }

    void split(itemType k) {
        x->tag = red;
        x->l->tag = black;
        x->r->tag = black;
        if (p->tag) {
            g->tag = red;
            if (k < g->key != k < p->key)
                p = rotate(k, g);
            x = rotate(k, gg);
            x->tag = black;
        }
    }

    struct node *rotate(itemType k, struct node *y) {
        struct node *high, *low;
        high = (k < y->key) ? y->l : y->r;

        if (k < high->key) {
            low = high->l;
            high->l = low->r;
            low->r = high;
        } else {
            low = high->r;
            high->r = low->l;
            low->l = high;
        }

        if (k < y->key)
            y->l = low;
        else
            y->r = low;

        return low;
    }

    infoType search(itemType k) {
        int compare = 0;    // 비교 횟수
        node *current = head;

        while (current != z) {
            compare++;
            if (k == current->key)
                return compare;
            else if (k < current->key)
                current = current->l;
            else
                current = current->r;
        }
        return compare;
    }
};

int main() {
    int N;
    cin >> N;

    srand((unsigned int)time(0));   // 랜덤 값 seed 설정

    set<int> uniqueValues;
    vector<int> values;
    while (uniqueValues.size() < N) {
        int value = rand() % 10000 + 1;
        if (uniqueValues.find(value) == uniqueValues.end()) {
            uniqueValues.insert(value);
            values.push_back(value);
        }
    }

    BST T1;
    int initialCompareT1 = 0;
    for (int value : values) {
        T1.BSTinsert(value, infoNIL, initialCompareT1);
    }

    vector<itemType> sortedData;
    T1.inorderTraversal(sortedData);    // 중위 순회

    BST T2;
    int initialCompareT2 = 0;
    for (int value : sortedData) {
        T2.BSTinsert(value, infoNIL, initialCompareT2);
    }

    RBtree T3;
    int initialCompareT3 = 0;
    for (itemType value : sortedData) {
        initialCompareT3 += T3.insert(value, infoNIL);
    }

    double searchCompareT1 = 0;
    double searchCompareT2 = 0;
    double searchCompareT3 = 0;
    for(int i = 0; i < 100; i++) {
        int randIndex = rand() % N;
        int searchNumber = values[randIndex];
        searchCompareT1 += T1.BSTsearch(searchNumber);
        searchCompareT2 += T2.BSTsearch(searchNumber);
        searchCompareT3 += T3.search(searchNumber);
    }


    cout << (double)initialCompareT1 / N << " (T1의 구축 시 평균 비교 횟수)"<< endl;
    cout << (double)initialCompareT2 / N << " (T2의 구축 시 평균 비교 횟수)"<< endl;
    cout << (double)initialCompareT3 / N << " (T3의 구축 시 평균 비교 횟수)"<< endl;

    double averageCompareT1 = searchCompareT1 / 100.0;
    double averageCompareT2 = searchCompareT2 / 100.0;
    double averageCompareT3 = searchCompareT3 / 100.0;
    cout << averageCompareT1 << " (T1의 평균 탐색 비교 횟수)" << endl;
    cout << averageCompareT2 << " (T2의 평균 탐색 비교 횟수)" << endl;
    cout << averageCompareT3 << " (T3의 평균 탐색 비교 횟수)" << endl;

    return 0;
}