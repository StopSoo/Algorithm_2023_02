// Q. N(10000 > N >= 100)을 입력받아 rand() 함수를 이용하여, 중복되는 값이 없는 N개의 난수를 생성하세요.
//    생성한 N개의 데이터를 생성된 순서대로 이진 탐색트리(Binary Search Tree)에 BSTinsert()를 통해 삽입하여 이진 탐색트리 T1을 만들어라.
//    그리고, BSTsearch()를 통해 이진 탐색트리 T1에서 랜덤한 100개의 자료들을 탐색하는데 소요된 ‘키의 평균 비교횟수’를 구하고,
//    아래의 출력 예제와 같이 출력하는 프로그램을 작성하시오.
#include <iostream>
#include <set>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

#define infoNIL 0
#define itemMIN -1
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
    BST(int max) {  // 생성자
        z = new node( 0, infoNIL, nullptr, nullptr);
        head = new node(itemMIN, infoNIL, z, z);
    }
    ~BST() {    // 소멸자
        delete z;
        delete head;
    };
    infoType  BSTsearch(itemType v);
    void BSTinsert(itemType v, infoType info);
};

infoType BST::BSTsearch(itemType v) {
    int compare = 0;
    while (head != z) {
        compare++;
        if (v == head->key)
            return compare;
        else if (v < head->key)
            head = head->l;
        else
            head = head->r;
    }
    return compare;
}

void BST::BSTinsert(itemType v, infoType info) {
    node* newNode = new node(v, info, z, z);
    while (true) {
        if (v < head->key) {
            if (head->l == z) {
                head->l = newNode;
                return;
            }
            head = head->l;
        } else {
            if (head->r == z) {
                head->r = newNode;
                return;
            }
            head = head->r;
        }
    }
}


int main() {
    int N;
    cin >> N;

    srand((unsigned int)time(0));   // 중복 없이 N개의 난수 생성을 위한 시드값 설정
    set<int> uniqueValues;
    vector<int> values;
    // 중복되지 않는 N개 난수 생성
    while (uniqueValues.size() < N) {
        int value = rand() % 100000 + 1;    // 1 이상 100000 이하인 N개의 난수
        if (uniqueValues.find(value) == uniqueValues.end()) {
            uniqueValues.insert(value);
            values.push_back(value);
        }
    }
    // 이진 탐색 트리
    BST tree(N);
    for (int value: values) {
        tree.BSTinsert(value, infoNIL);
    }

    double totalCompare = 0;
    for (int i = 0; i < 100; i++) {
        int randIndex = rand() % N;
        int searchNumber = values[randIndex];
        totalCompare += tree.BSTsearch(searchNumber);
    }
    double averageCompare = totalCompare / 100.0;

    cout << averageCompare << " (T1의 평균 비교 횟수)" << endl;
    return 0;
}