// Q. 3번과 동일한 문제를 해결하지만 최악시간 복잡도가 O(N)이 되도록 하는 Select_N(a, l, r, k)을 사용해서 최소치, 최대치 및 중앙치를 찾고 비교연산 회수를 각각 출력하시오.
//    1번 문제에서 만든 데이터 A, B, C에 대해 이를 수행해보고 3번과 결과가 크게 달라지는 때를 하나 골라서 이를 제출하시면 됩니다.
#include <iostream>
#include <time.h>
using namespace std;

template <typename itemType>
void swap(itemType a[], int x, int y) {
    itemType temp;
    temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

template <typename itemType>
int partition(itemType a[], int l, int r, unsigned &c, unsigned &m) {
    int i, j;
    itemType v;

    if (l < r) {
        v = a[l];
        i = l;
        j = r + 1;
        for (;;) {
            while (a[++i] < v) {    // pivot보다 작다면 왼쪽 포인터를 계속 오른쪽으로 이동
                c++;    // 데이터 비교 연산
            }
            while (a[--j] > v) {    // pivot보다 크다면 오른쪽 포인터를 계속 왼쪽으로 이동
                c++;    // 데이터 비교 연산
            }
            if (i >= j)     // 포인터가 서로 엇갈리면 반복문 중단
                break;
            swap(a, i, j);  // i번째 원소와 j번째 원소 교환
            m++;    // 자료 이동 연산
        }
        swap(a, j, l);
        m++;    // 자료 이동 연산

        return j;
    }
}

template <typename itemType>
itemType select_N(itemType a[], int l, int r, int k, unsigned& c, unsigned& m)
{
    if (l == r) return a[l];

    int pivot = partition<int>(a, l, r, c, m);
    int rank = pivot - l + 1;

    if (k == rank) {
        return a[pivot];
    } else if (k < rank) {
        return select_N(a, l, pivot - 1, k, c, m);
    } else {
        return select_N(a, pivot + 1, r, k - rank, c, m);
    }
}

int main() {
    int N;  // 배열의 크기
    cin >> N;   // 사용자로부터 배열의 크기 입력 받기

    // 1. 세 배열 생성 및 크기 동적 할당
    int *A = new int[N];
    int *B = new int[N];
    int *C = new int[N];
    int x, y;   // 랜덤 배열을 위한 인덱스

    for (int i = 0; i < N; i++) {   // 배열 B 초기화
        B[i] = i + 1;
    }
    srand((unsigned int)time(0));   // 배열 B 랜덤 배치를 위한 시드값 설정

    int value = N;
    for (int i = 0; i < N; i++) {   // 배열 A 초기화: 1부터 N까지 내림차순으로 push
        A[i] = value--;
    }
    for (int i = 0; i < N; i++) {   // 배열 B 재배치: 1부터 N까지의 숫자들이 "중복 없이" 랜덤하게 재배치된 데이터 배열
        while (true) {
            x = rand() % N;
            y = rand() % N;
            if (x != 0 && y != 0)   // 인덱스 0이 나오면 안되므로
                break;
        }

        swap(B[x], B[y]);
    }
    for (int i = 0; i < N; i++) {   // 배열 C 초기화: 1부터 N까지의 숫자들이 "중복을 허용"하며 랜덤하게 배치된 배열
        C[i] = rand() % N;
        while (C[i] == 0) { // 원소가 0일 경우 다시 설정
            C[i] = rand() % N;
        }
    }

    // 2. 배열 A, B, C에 대해 3번과 동일한 문제 해결
    // 배열 상태 확인
    cout << "* Before Sorting *" << endl;
    cout << "A : ";
    for (int i = 0; i < 20; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    cout << "B : ";
    for (int i = 0; i < 20; i++) {
        cout << B[i] << " ";
    }
    cout << endl;
    cout << "C : ";
    for (int i = 0; i < 20; i++) {
        cout << C[i] << " ";
    }
    cout << endl << endl;

    unsigned int compare_A = 0, move_A = 0;
    cout << "A - 최소치 : " << select_N<int>(A, 0, N-1, 0, compare_A, move_A) << endl;
    cout << "A - 최대치 : " << A[N-1] << endl;
    cout << "A - 중앙치 : " << A[N/2] << endl;
    cout << "-----------------------------------" << endl;
    cout << "Compare_Cnt_A : " << compare_A << ", DataMove_Cnt_A : " << move_A << endl << endl;

    unsigned int compare_B = 0, move_B = 0;
    cout << "B - 최소치 : " << select_N<int>(B, 0, N-1, 0, compare_B, move_B) << endl;
    cout << "B - 최대치 : " << select_N<int>(B, 0, N-1, N-1, compare_B, move_B) << endl;
    cout << "B - 중앙치 : " << select_N<int>(B, 0, N-1, N/2, compare_B, move_B) << endl;
    cout << "-----------------------------------" << endl;
    cout << "Compare_Cnt_B : " << compare_B << ", DataMove_Cnt_B : " << move_B << endl << endl;

    unsigned int compare_C = 0, move_C = 0;
    cout << "C - 최소치 : " << select_N<int>(C, 0, N-1, 0, compare_C, move_C) << endl;
    cout << "C - 최대치 : " << select_N<int>(C, 0, N-1, N-1, compare_C, move_C) << endl;
    cout << "C - 중앙치 : " << select_N<int>(C, 0, N-1, N/2, compare_C, move_C) << endl;
    cout << "-----------------------------------" << endl;
    cout << "Compare_Cnt_C : " << compare_C << ", DataMove_Cnt_C : " << move_C << endl << endl;

    // 메모리 해제
    delete [] A;
    delete [] B;
    delete [] C;
    return 0;
}

