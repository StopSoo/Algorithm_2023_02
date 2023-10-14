// Q. N(10000 > N >= 100)을 입력받아 rand() 함수를 이용하여, 중복되는 값이 없는 N개의 난수를 생성하세요.
//    생성한 N개의 데이터를 생성된 순서대로 이진 탐색트리(Binary Search Tree)에 BSTinsert()를 통해 삽입하여 이진 탐색트리 T1을 만들어라.
//    그리고, BSTsearch()를 통해 이진 탐색트리 T1에서 랜덤한 100개의 자료들을 탐색하는데 소요된 ‘키의 평균 비교횟수’를 구하고,
//    아래의 출력 예제와 같이 출력하는 프로그램을 작성하시오.
#include <iostream>
#include <time.h>
using namespace std;

#define infoNIL 0
#define itemMIN -1

typedef int itemType;
typedef double infoType;

class BST {
private:
    struct node {
        itemType key; infoType info;
        struct node *l, *r;
        node(itemType k, infoType i, struct node *ll, struct node *rr)  // node 생성시 초기값 부여 가능
        { key = k; info = i; l = ll; r = rr; };
    };
    struct node *head, *z; // z : List의 끝을 대표하는 node pointer – NULL에 해당
public:
    BST(int max) {
        z = new node( 0, infoNIL, 0, 0);
        head = new node(itemMIN, infoNIL, z, z);
    }
    ~BST();
    infoType  BSTsearch(itemType v);
    void BSTinsert(itemType v, infoType info);
};
infoType BST::BSTsearch(itemType v) {
}
void BST::BSTinsert(itemType v, infoType info) {
}


int main() {
    int N;
    cin >> N;

    srand((unsigned int)time(0));   // 중복 없이 N개의 난수 생성을 위한 시드값 설정

}