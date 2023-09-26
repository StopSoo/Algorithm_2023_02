// Q. 정렬하려는 배열의 크기 N(> 10000)을 입력 받아, 문제 1번과 동일한 방법으로 데이터 A와 데이터 B를 생성하고,
//    이 데이터 배열 A, B 각각에 대해 Shell Sort를 이용해 오름차순으로 정렬시켜주는 프로그램을 작성하시오.
//    이 때, 정렬된 결과 뿐만 아니라 정렬 과정에서의 데이터 비교 연산 회수와 자료 이동 연산 회수 또한 아래의 입출력 예제와 같이 출력되어야 한다.
#include <iostream>
#include <time.h>
#include <tuple>
using namespace std;

// 쉘 정렬 함수
template <typename itemType>
tuple<itemType, itemType> shellSort(itemType a[], int n) // 정렬하려는 배열, 배열의 크기
{
    int i, j, h;
    itemType temp;
    h = 1;  // 부분 배열 내 원소들이 떨어진 거리 초기화
    int compare = 0, move = 0;  // 데이터 비교 횟수, 자료 이동 횟수
    while (h < n / 3) {
        h = 3 * h + 1;
    }
    do {
        for (i = h; i < n; i++)
        {
            temp = a[i];
            j = i;
            compare++;  // 데이터 비교 횟수 증가
            while (a[j-h] > temp)
            {
                a[j] = a[j-h];
                move++; // 자료 이동 횟수 증가
                j -= h;
                if (j < h-1)
                    break;
                compare++;  // 데이터 비교 횟수 증가
            }
            a[j] = temp;
            move++; // 자료 이동 횟수 증가
        }
        h = h / 2;  // 부분 배열 내 거리 재설정
    } while (h > 0);

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

    // 2. 배열 A와 B에 대해 쉘 정렬을 이용해 오름차순으로 정렬하기
    tuple<int, int> result = {};
    result = shellSort(A, N);   // 연산 횟수 튜플 받기
    int compare_A = get<0>(result); // 배열 A의 데이터 비교 연산 횟수 받기
    int move_A = get<1>(result);    // 배열 A의 자료 이동 연산 횟수 받기
    cout << "SortedData A: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << A[i] << " ";
    }
    cout << endl;

    result = shellSort(B, N);   // 연산 횟수 튜플 받기
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
