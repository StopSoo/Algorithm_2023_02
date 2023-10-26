// Q. N(20000 > N >= 1000)을 입력 받고 rand() 함수를 이용하여 서로 다른 N개의 난수를 발생시켜 데이터 배열에 중복되는 값이 없도록 만들고,
//    그 배열 값을 1번 문제에서 작성한 Red-Black 트리 T3와 Hash  Table에 각각 삽입해보세요.
//    이 때, Hash Table의 크기 M은 이하 규칙에 따라 설정.
//    Red-Black 트리 T3와 Hash Table를 초기 구축하는데 소요된 ‘키의 평균 비교회수’와
//    Red-Black트리 T3와 Hash Table에서 100개의 자료들을 탐색하는데 소요된 ‘키의 평균 비교회수’를 구하고, 아래의 출력 예제와 같이 출력하는 프로그램을 작성하시오.
//    또한, T3와 Hash Table의 평균 비교회수를 이용해 Hashing 방법의 탐색 성능에 대해 논의하시오.
//    [단, Hash Table 크기 M은 11, 101, 1009로 정하고, Hash함수는 Division Method (HashValue=Key mod M)로,
//    충돌 해결 방법은 Chaining 방법을 이용해 각각 프로그램을 작성하시오.]
#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>

using namespace std;

#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1
typedef int itemType;
typedef double infoType;

class RBtree {
private:
    struct node {
        itemType key, tag;
        infoType info;
        struct node* l, * r;
        node(itemType k, infoType i, itemType t, struct node* ll, struct node* rr) {
            key = k;
            info = i;
            tag = t;
            l = ll;
            r = rr;
        }
    };
    struct node* head, * tail, *x, *p, *g, *gg, *z;

public:
    RBtree() {
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

    struct node* rotate(itemType k, struct node* y) {
        struct node* high, * low;
        high = (k < y->key) ? y->l : y->r;

        if (k < high->key) {
            low = high->l;
            high->l = low->r;
            low->r = high;
        }
        else {
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
        int compare = 0;
        node* current = head;

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

// 해시 테이블
class HashTable {
private:
    int M;
    vector<list<itemType>> table;

public:
    HashTable(int size) : M(size) {
        table.resize(M);
    }

    void insert(itemType key) {
        int hashValue = key % M;
        table[hashValue].push_back(key);
    }

    infoType search(itemType key) {
        int hashValue = key % M;
        int compare = 0;

        for (const auto& value : table[hashValue]) {
            compare++;
            if (value == key)
                return compare;
        }

        return compare;
    }
};

int main() {
    int N;
    cin >> N;

    srand(static_cast<unsigned int>(time(0)));

    set<itemType> uniqueValues;
    vector<itemType> values;

    while (uniqueValues.size() < N) {
        itemType value = rand() % 10000 + 1;
        if (uniqueValues.find(value) == uniqueValues.end()) {
            uniqueValues.insert(value);
            values.push_back(value);
        }
    }

    RBtree T3;
    HashTable hashTable11(11);
    HashTable hashTable101(101);
    HashTable hashTable1009(1009);

    double initialCompareT3 = 0;
    double initialCompareHashTable11 = 0;
    double initialCompareHashTable101 = 0;
    double initialCompareHashTable1009 = 0;

    for (itemType value : values) {
        initialCompareT3 += T3.insert(value, infoNIL);
        initialCompareHashTable11 += hashTable11.search(value);
        initialCompareHashTable101 += hashTable101.search(value);
        initialCompareHashTable1009 += hashTable1009.search(value);
    }

    double searchCompareT3 = 0;
    double searchCompareHashTable11 = 0;
    double searchCompareHashTable101 = 0;
    double searchCompareHashTable1009 = 0;

    for (int i = 0; i < 100; i++) {
        int randIndex = rand() % N;
        itemType searchNumber = values[randIndex];

        searchCompareT3 += T3.search(searchNumber);
        searchCompareHashTable11 += hashTable11.search(searchNumber);
        searchCompareHashTable101 += hashTable101.search(searchNumber);
        searchCompareHashTable1009 += hashTable1009.search(searchNumber);
    }

    cout << "T3의 구축 시 평균 비교 횟수 : " << (initialCompareT3 / N) << endl;
    cout << "Hash Table 크기가 11인 경우의 구축 시 평균 비교 횟수 : " << (initialCompareHashTable11 / N) << endl;
    cout << "Hash Table 크기가 101인 경우의 구축 시 평균 비교 횟수 : " << (initialCompareHashTable101 / N) << endl;
    cout << "Hash Table 크기가 1009인 경우의 구축 시 평균 비교 횟수 : " << (initialCompareHashTable1009 / N) << endl;

    cout << "T3의 평균 비교 횟수 : " << (searchCompareT3 / 100.0) << endl;
    cout << "Hash Table 크기가 11인 경우의 평균 비교 횟수 : " << (searchCompareHashTable11 / 100) << endl;
    cout << "Hash Table 크기가 101인 경우의 평균 비교 횟수 : " << (searchCompareHashTable101 / 100) << endl;
    cout << "Hash Table 크기가 1009인 경우의 평균 비교 횟수 : " << (searchCompareHashTable1009 / 100) << endl;

    return 0;
}
