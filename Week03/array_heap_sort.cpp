// Q. 다음에 주어진 프로그램을 참고해서 N(>10000)개의 정수를 발생하여 heapsort()를 구현하여 실습하고,
//    키의 비교 연산 횟수를 헤아려서 출력하고 비교하시오.
//    단,  heapsort()를  구현하기 위해서 class PQ에 정의된 연산 MakeHeap()은 별도로 구현하며, 필요한 사항은 임의로 정한다.
#include <iostream>
#include <algorithm>
using namespace std;

template <typename itemType>
class PQ {
private:
    itemType *a;    // 배열
    int N;  // 배열의 크기
    int comparisons; // 비교 연산 횟수

public:
    PQ(int max) {   // 생성자
        a = new itemType[max+1];
        N = max+1;
        comparisons = 0;

        // 배열 초기화
        cout << "배열의 원소를 입력 : " << endl;
        for (int i=1; i < N; ++i) {
            cin >> a[i];
        }
        a[0] = 0;   // 인덱스 0번쨰 원소 사용 안 함
    }
    ~PQ() {     // 소멸자
        delete [] a;
    }

    itemType* getA() {  // a에 대한 getter
        return a;
    }

    void MakeHeap(int Root, int LastNode) {     // 클래스 내장 함수이므로 매개변수 a 삭제
        int Parent = Root;
        int RootValue = a[Root];
        int LeftSon = 2 * Parent;
        int RightSon = LeftSon + 1;
        int Son;
        while (LeftSon <= LastNode) {
            comparisons++;
            if (RightSon <= LastNode && a[LeftSon] < a[RightSon]) {
                comparisons++;
                Son = RightSon;     // child 중 큰것올 골라 son에 넣음
            }
            else {
                comparisons++;
                Son = LeftSon;
            }

            comparisons++;
            if (RootValue < a[Son]) {   // 루트 값보다 Son 값이 크면
                a[Parent] = a[Son];     // Son을 위로 올림
                Parent = Son;           // Son이 parent 가 됨
                LeftSon = Parent * 2;   // child 다시 지정
                RightSon = LeftSon + 1;
            } else break;
        }
        a[Parent] = RootValue;
    }

    int getComparisons() {
        return comparisons;
    }

    friend void heapsort(PQ<int>& item, int N);
};

void heapsort(PQ<int>& item, int N) {
    int i;
    for (i = N/2; i >= 1; i--)
        item.MakeHeap(i-1, N);
    for (i = N; i >= 1; i--) {
        swap(item.a[0], item.a[i]);
        item.MakeHeap(0, i-1);
    }
}

int main() {
    int N;  // 힙의 크기
    cin >> N;

    PQ<int> item(N);    // 클래스 객체이자 배열 생성

    heapsort(item, N);

    cout << "비교 연산 횟수 : " << item.getComparisons() << endl;

    return 0;
}

