// Q. 정렬하려는 배열의 크기 N (> 10000) 을 입력 받아, 아래와 같은 두 가지 데이터 배열 A와 B를 만들고,
//    이 데이터 배열 A와 B 각각에 대해 Quick Sort를 통해 오름차순으로 정렬시켜주는 프로그램을 작성하시오.
//    이 때, 정렬된 결과 뿐만 아니라 정렬 과정에서의 데이터 비교 연산회수와 자료 이동 연산회수 또한 아래의 입출력 예제와 같이 출력되어야 한다.
#include <iostream>
#include <tuple>
#include <time.h>
using namespace std;

// 퀵 정렬 함수
template <typename itemType>
inline void swap(itemType a[], int i, int j)
{
    itemType t = a[i];
    a[i] = a[j];
    a[j] = t;
}

template <typename itemType>
tuple<int, itemType, itemType> partition(itemType a[], int l, int r) {
    int i, j;
    itemType v;
    int64_t compare = 0, move = 0;  // 데이터 비교 횟수, 자료 이동 횟수 -> N이 커서 자료형을 int에서 int_64로 변경

    compare++;  // 데이터 비교 연산
    if (r > l) {    // right > left
        v = a[l];
        i = l;
        j = r+1;
        for (;;) {
            while (a[++i] < v) { compare++; };    // 데이터 비교 연산
            compare++;  // while문을 빠져나왔을 때의 데이터 비교 연산 횟수
            while (a[--j] > v) { compare++; };    // 데이터 비교 연산
            compare++;  // while문을 빠져나왔을 때의 데이터 비교 연산 횟수
            if (i >= j) break;
            swap(a, i, j);
            move += 3; // 자료 이동 연산
        }
        swap(a, j, l);
        move += 3;  // 자료 이동 연산
    }
    return {j, compare, move};
}

template <typename itemType>
tuple<int, int> quicksort(itemType a[], int l, int r, int& compare_sum, int& move_sum) {
    int  j;
    tuple<int, int, int> result;
    if (r > l) {
        result = partition(a, l, r);
        j = get<0>(result); // 인덱스
        compare_sum += get<1>(result);  // 데이터 비교 연산 횟수 누적
        move_sum += get<2>(result); // 자료 이동 연산 횟수 누적
        quicksort(a, l, j-1, compare_sum, move_sum);
        quicksort(a, j+1, r, compare_sum, move_sum);
    }
    return {compare_sum, move_sum};
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

    // 2. 배열 A와 B에 대해 퀵 정렬을 이용해 오름차순으로 정렬하기
    int compare_sum = 0, move_sum = 0;
    tuple<int, int> result = {};
    result = quicksort(A, 0, N-1, compare_sum, move_sum);   // 연산 횟수 튜플 받기
    int compare_A = get<0>(result); // 배열 A의 데이터 비교 연산 횟수 받기
    int move_A = get<1>(result);    // 배열 A의 자료 이동 연산 횟수 받기
    cout << "SortedData A: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << A[i] << " ";
    }
    cout << endl;

    result = quicksort(B, 0, N-1, compare_sum, move_sum);   // 연산 횟수 튜플 받기
    int compare_B = get<0>(result); // 배열 B의 데이터 비교 연산 횟수 받기
    int move_B = get<1>(result);    // 배열 B의 자료 이동 연산 횟수 받기
    cout << "SortedData B: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << B[i] << " ";
    }
    cout << endl;

    // 데이터 비교 연산 횟수와 자료 이동 연산 횟수 출력하기
    cout << "Compare_Cnt_A: " << compare_A << ", DataMove_Cnt_A: " << move_A << endl;
    cout << "Compare_Cnt_B: " << compare_B << ", DataMove_Cnt_B: " << move_B << endl;

    // 메모리 해제
    delete [] A;
    delete [] B;
    return 0;
}

