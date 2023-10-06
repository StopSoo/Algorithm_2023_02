// Q. 정렬하려는 배열의 크기 N(30000 > N >= 5000)을 입력 받아, 아래와 같은 세 가지 데이터 배열 A, B, C를 만들고,
//    이 데이터 배열 A, B, C 각각에 대해 Count Sort를 이용해 오름차순으로 정렬시켜주는 프로그램을 작성하시오.
//    이 때, 정렬된 결과 뿐만 아니라 정렬 과정에서의 데이터 비교 연산 회수와 자료 이동 연산 회수 또한 아래의 입출력 예제와 같이 출력되어야 한다.
#include <iostream>
#include <tuple>
#include <time.h>
using namespace std;

/* 전역 변수 선언부 */
typedef int itemType;
itemType *b, *sum;

/* 계수 정렬 선언부 */
itemType* CountSort(itemType *a, itemType *b, itemType *N, int n, unsigned int& c, unsigned int& m) {
    int i;
    for(i = 1; i <= n; i++) N[i] = 0;   // 초기화
    for(i = 1; i <= n; i++) {
        N[a[i]] = N[a[i]] + 1;  // 각 키의 개수 체크
    }
    for(i = 2; i <= n; i++) N[i] = N[i] + N[i-1];   // 키의 누적합
    for(i = n; i >= 1; i--) {   // 정렬 결과를 배열 b에 저장
        b[N[a[i]]] = a[i];
        for (int j = 0; j < abs(i - N[a[i]]); j++) m++;  // 움직인 인덱스 만큼 자료 이동 연산 체크
        N[a[i]] = N[a[i]] - 1;  // N 배열의 값을 조정
    }
    return b;
}

int main() {
    // 1. 배열 A, B, C 만들기
    int N;  // 배열의 크기
    cin >> N;   // 사용자로부터 배열의 크기 입력 받기

    // 세 배열 생성 및 크기 동적 할당 (인덱스 1부터 시작)
    int *A = new int[N+1];
    int *B = new int[N+1];
    int *C = new int[N+1];
    int x, y;   // 랜덤 배열을 위한 인덱스

    for (int i = 1; i <= N; i++) {   // 배열 B 초기화
        B[i] = i;
    }
    srand((unsigned int)time(0));   // 배열 B 랜덤 배치를 위한 시드값 설정

    int value = N;
    for (int i = 1; i <= N; i++) {   // 배열 A 초기화: 1부터 N까지 내림차순으로 push
        A[i] = value--;
    }
    for (int i = 1; i <= N; i++) {   // 배열 B 재배치: 1부터 N까지의 숫자들이 "중복 없이" 랜덤하게 재배치된 데이터 배열
        while (true) {
            x = rand() % N;
            y = rand() % N;
            if (x != 0 && y != 0)   // 인덱스 0이 나오면 안되므로
                break;
        }

        swap(B[x], B[y]);
    }
    for (int i = 1; i <= N; i++) {   // 배열 C 초기화: 1부터 N까지의 숫자들이 "중복을 허용"하며 랜덤하게 배치된 배열
        C[i] = rand() % N;
        while (C[i] == 0) { // 원소가 0일 경우 다시 설정
            C[i] = rand() % N;
        }
    }

    // 2. 배열 A, B, C에 대해 계수 정렬을 이용해 오름차순으로 정렬하기
    cout << "* Before Sorting *" << endl;
    cout << "A : ";
    for (int i = 1; i <= 20; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    cout << "B : ";
    for (int i = 1; i <= 20; i++) {
        cout << B[i] << " ";
    }
    cout << endl;
    cout << "C : ";
    for (int i = 1; i <= 20; i++) {
        cout << C[i] << " ";
    }
    cout << endl;

    // 전역 변수 초기화
    b = new itemType[N+1];    // 정렬 결과가 들어갈 최종 배열
    sum = new itemType[N+1];    // 원소 별 등장 횟수 기록 및 횟수 누적 값을 담을 배열

    cout << "* After Sorting *" << endl;
    unsigned int compare_A = 0, move_A = 0;
    int* countSortA = CountSort(A, b, sum, N, compare_A, move_A);
    cout << "SortedData_A: ";
    for (int i = 1; i <= 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << countSortA[i] << " ";
    }
    cout << endl;

    unsigned int compare_B = 0, move_B = 0;
    int* countSortB = CountSort(B, b, sum, N, compare_B, move_B);
    cout << "SortedData_B: ";
    for (int i = 1; i <= 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << countSortB[i] << " ";
    }
    cout << endl;

    unsigned int compare_C = 0, move_C = 0;
    int* countSortC = CountSort(C, b, sum, N, compare_C, move_C);
    cout << "SortedData_C: ";
    for (int i = 1; i <= 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << countSortC[i] << " ";
    }
    cout << endl;

    // 데이터 비교 연산 횟수와 자료 이동 연산 횟수 출력하기
    cout << "Compare_Cnt_A: " << compare_A << ", DataMove_Cnt_A: " << move_A << endl;
    cout << "Compare_Cnt_B: " << compare_B << ", DataMove_Cnt_B: " << move_B << endl;
    cout << "Compare_Cnt_C: " << compare_C << ", DataMove_Cnt_C: " << move_C << endl;

    // 메모리 해제
    delete [] A;
    delete [] B;
    delete [] C;
    return 0;
}

