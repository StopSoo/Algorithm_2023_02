// Q. 정렬하려는 배열의 크기 N(> 10000)을 입력 받아, 문제 1번과 동일한 방법으로 데이터 A와 데이터 B를 생성하고,
//    이 데이터 배열 A, B 각각에 대해 Bubble Sort를 이용해 오름차순으로 정렬시켜주는 프로그램을 작성하시오.
//    이때, 정렬된 결과뿐만 아니라 정렬 과정에서의 데이터비교 연산회수와 자료이동 연산회수 또한 아래의 입출력 예제와 같이 출력되어야 한다.

#include <iostream>
#include <time.h>
using namespace std;

// 버블 정렬 함수
template <typename itemType>
int Bubble(int sorted, itemType *a, int n)  // 정렬 여부, 값을 비교하고자 하는 배열
{
    int temp;
    if ( *(a-1) > *a ) {    // 앞에 있는 원소 값이 뒤에 있는 원소 값보다 크면 swap
        temp = *(a-1);
        *(a-1) = *a;
        *a = temp;
        sorted = false;
    }
    return sorted;
}

template <typename itemType>
void bubbleSort(itemType a[], int n)    // 정렬하고자 하는 배열, 배열의 크기
{
    int i, Sorted;
    Sorted = false;
    while ( !Sorted ) {
        Sorted = true;
        for ( i=1; i<n; i++ )
            Sorted = Bubble( Sorted, &a[i], n );
    }
}

int main() {
    // 1. 배열 A와 B 만들기
    int N;  // 배열의 크기
    cin >> N;   // 사용자로부터 배열의 크기 입력 받기

    // 두 배열 생성 및 크기 동적 할당
    int *A = new int[N];
    int *B = new int[N];
    int x, y;   // 인덱스
    for (int i = 0; i < N; i++) {   // 배열 B 초기화
        B[i] = i+1;
    }
    srand((unsigned int)time(0));   // 배열 B 랜덤 배치를 위한 시드값 설정

    int value = N;
    for (int i = 0; i < N; i++) {   // 배열 A 초기화: 1부터 N까지 내림차순으로 push
        A[i] = value--;
    }
    for (int i = 0; i < N; i++) {   // 배열 B 재배치: 1치터 N까지의 숫자들이 랜덤하게 재배치된 데이터 배열
        x = rand() % N;
        y = rand() % N;
        swap(B[x], B[y]);
    }
    // 임시
    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << B[i] << " ";
    }
    cout << endl;



    // 메모리 해제
    delete [] A;
    delete [] B;
    return 0;
}
