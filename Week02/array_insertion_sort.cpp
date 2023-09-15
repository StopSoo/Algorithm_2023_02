// Q. 정렬하려는 배열의 크기 N ( >10000 ) 을 입력 받아, 아래와 같은 두 가지 데이터 배열 A와 B를 만들고,
//    이 데이터 배열 A와 B 각각에 대해 Insertion Sort를 통해 오름차순으로 정렬시켜주는 프로그램을 작성하시오.
//    이 때, 정렬된 결과 뿐만 아니라 정렬 과정에서의 데이터 비교 연산 횟수와 자료 이동 연산 횟수 또한 아래의 입출력 예제와 같이 출력되어야 한다.

#include <iostream>
#include <time.h>
using namespace std;

// 삽입 정렬 함수
template <typename itemType>
tuple<itemType, itemType> insertion(itemType a[],  int n)    // 매개변수 : 배열, 배열의 크기
{
    int i, j;
    itemType v;
    int compare = 0, move = 0;  // 데이터 비교 횟수, 자료 이동 횟수
    for (i = 1; i < n; i++)
    {
        v = a[i];
        for (j = i-1; j >=0; j--) {
            compare++;  // 데이터 비교 발생
            if (a[j] > v) {
                a[j+1] = a[j];
                move++; // 자료 이동 발생
            } else break;
        }
        a[j+1] = v;
    }

    return {compare, move}; // 데이터 비교 횟수, 자료 이동 횟수 반환
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

    // 2. 배열 A와 B에 대해 삽입 정렬을 이용해 오름차순으로 정렬하기
    tuple<int, int> result = {};
    result = insertion(A, N);   // 연산 횟수 튜플 받기
    int compare_A = get<0>(result); // 배열 A의 데이터 비교 연산 횟수 받기
    int move_A = get<1>(result);    // 배열 A의 자료 이동 연산 횟수 받기
    cout << "SortedData A: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << A[i] << " ";
    }
    cout << endl;

    result = insertion(B, N);   // 연산 횟수 튜플 받기
    int compare_B = get<0>(result); // 배열 B의 데이터 비교 연산 횟수 받기
    int move_B = get<1>(result);    // 배열 B의 자료 이동 연산 횟수 받기
    cout << "SortedData B: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << B[i] << " ";
    }
    cout << endl;

    cout << "Compare_Cnt_A: " << compare_A << ", DataMove_Cnt_A: " << move_A << endl;
    cout << "Compare_Cnt_B: " << compare_B << ", DataMove_Cnt_B: " << move_B << endl;

    // 메모리 해제
    delete [] A;
    delete [] B;
    return 0;
}
