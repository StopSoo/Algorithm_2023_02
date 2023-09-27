// Q. 다음에 주어진 프로그램을 참고해서 N(>10000)개의 정수를 발생하여 heapsort ()를 구현하여 실습하고,
//    키의 비교 연산 회수를 헤아려서 출력하고 비교하시오.
//    단,  heapsort()를  구현하기 위해서 class PQ에 정의된 연산 MakeHeap() 은 별도로 구현하며, 필요한 사항은 임의로 정한다.
#include <iostream>
#include <algorithm>
using namespace std;

template <typename itemType>
class PQ {
private:
    itemType *a;
    int N;

public:
    PQ(int max) { // 생성자
        a = new itemType[max];
        N = max;    // 배열의 크기
    }
    ~PQ() {     // 소멸자
        delete [] a;
    }
    itemType* getA() {  // a에 대한 getter
        return a;
    }
    void MakeHeap(temType a[], int Root, int LastNode) {
        // 1. 배열 초기화
        cout << "배열의 원소를 입력(배열의 크기는 입력한 값-1)" << endl;
        a[0] = 0;
        for (int i=1; i < N; i++) {
            cin >> a[i];
        }

        // 확인용 출력
        for (int i = 0; i < N; i++) {
            cout << a[i] << " ";
        }
        cout << endl;

        // 2. 힙 생성
        int root = a[1];
        int lastNode = a[N-1];
        int parent, leftSon, rightSon, son, rootValue;
        parent = root;
        rootValue = a[root];
        leftSon = parent * 2 + 1;
        rightSon = leftSon + 1;

        while (leftSon <= lastNode) {
            if (rightSon <= lastNode && a[leftSon] < a[rightSon])
                son = rightSon; // child 중에 큰 것을 골라 son에 넣음
            else son = leftSon;

            if (rootValue < a[son]) {   // root 값보다 son 값이 크다면
                a[parent] = a[son];
                parent = son;   // son이 parent가 됨
                leftSon = parent * 2 + 1;   // child를 수정
                rightSon = leftSon + 1;
            } else break;
        }

        a[parent] = rootValue;
    }

    friend void heapsort(itemType a[], int N);
};

template <typename itemType>
void heapsort(PQ<int> item, int N) {
    int i;

    for (i = N/2; i >= 1; i--)
        MakeHeap(item.getA(), i-1, N-1);  // 정렬할 배열을 힙으로 변환

    // 확인용 출력
    for (int i = 0; i < N; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    for (i = N-1; i >= 1; i--) {
        swap(a, 0, i);          // 힙의 최대 값을 제거하고
        MakeHeap(a, 0, i-1);    // 남은 원소로 다시 힙 재정비
    }
}

int main() {
    int N;  // 힙의 크기
    cin >> N;

    PQ<int> item(N); // 클래스 객체이자 배열 생성
    item.MakeHeap();
    heapsort(item, N);

    // 정렬된 배열 출력
    cout << "힙 정렬 결과:" << endl;
    for (int i = 1; i < N; i++) {
        cout << item.getA()[i] << " ";
    }
    cout << endl;

    return 0;

}

