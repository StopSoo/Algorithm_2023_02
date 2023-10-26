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

class BST {
private:
    struct node {
        itemType key;
        infoType info;
        struct node *l, *r;
        node(itemType k, infoType i, struct node *ll, struct node *rr) {
            key = k;
            info = i;
            l = ll;
            r = rr;
        };
    };
    node *head, *z;

public:
    BST() {
        z = new node(0, infoNIL, nullptr, nullptr);
        head = nullptr;
    }
    ~BST() {};
    infoType BSTinsert(itemType v, infoType info);
    infoType BSTsearch(itemType v);
    void inorderTraversal(vector<itemType>& tree);
};

infoType BST::BSTinsert(itemType v, infoType info) {
    node *newNode = new node(v, info, z, z);
    static node *temp = head;
    int compare = 0;    // 비교 횟수

    while (true) {
        compare++;
        if (head == nullptr) {
            head = newNode;
            break;
        } else {
            compare++;
            if (v < temp->key) {
                compare++;
                if (temp->l == z) {
                    temp->l = newNode;
                    break;
                }
                temp = temp->l;
            } else {
                compare++;
                if (temp->r == z) {
                    temp->r = newNode;
                    break;
                }
                temp = temp->r;
            }
        }
    }
    delete newNode;
    delete temp;
    return compare;
}

infoType BST::BSTsearch(itemType v) {
    int compare = 0;    // 비교 횟수
    node *current = head;

    while (current != z) {
        compare++;
        if (v == current->key)
            return compare;
        else if (v < current->key)
            current = current->l;
        else
            current = current->r;
    }
    return compare;
}

void BST::inorderTraversal(vector<itemType>& arr) { // 중위 순회
    node *current = head;
    node *child;

    while (current != z) {
        if (current->l == z) {
            arr.push_back(current->key);
            current = current->r;
        } else {
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

    srand((unsigned int)time(0));

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
    double initialCompareT1 = 0;
    for (int value : values) {
        initialCompareT1 += T1.BSTinsert(value, infoNIL);
    }

    vector<itemType> sortedData;
    T1.inorderTraversal(sortedData);

    BST T2;
    double initialCompareT2 = 0;
    for (int value : sortedData) {
        initialCompareT2 += T2.BSTinsert(value, infoNIL);
    }

    RBtree T3;
    double initialCompareT3 = 0;
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