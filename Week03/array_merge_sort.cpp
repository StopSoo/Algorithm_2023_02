// Q. 정렬하려는 배열의 크기 N(> 10000)을 입력 받아, 문제 1번과 동일한 방법으로 데이터 A와 데이터 B를 생성하고,
//    이 데이터 배열 A, B 각각에 대해 Merge Sort를 이용해 오름차순으로 정렬시켜주는 프로그램을 작성하시오.
//    이 때, 정렬된 결과 뿐만 아니라 정렬 과정에서의 데이터 비교 연산 회수와 자료 이동 연산 회수 또한 아래의 입출력 예제와 같이 출력되어야 한다.
#include <iostream>
#include <tuple>
#include <time.h>
using namespace std;

// 합병 정렬 함수
template <typename itemType>
tuple<int, int> merge(itemType a[], int l, int mid, int r, int& c, int& m) {
    int i, j, k, n;
    i = l;
    j = mid + 1;
    k = l;  // 합병 정렬 배열의 인덱스
    n = sizeof(a) / sizeof(itemType);   // 배열 a의 사이즈 체크
    int compare_sum = 0, move_sum = 0;

    itemType* sorted = new itemType[n]; // 합병 정렬 결과를 담을 배열

    while (i <= mid && j <= r) {
        compare_sum++;  // 데이터 비교 연산
        if (a[i] <= a[j]) { // 양쪽 배열 원소 중 왼쪽 원소가 더 작거나 같다면
            sorted[k++] = a[i++];   // 합병 정렬 배열에 왼쪽 원소 대입
        } else {    // 오른쪽 원소가 더 작다면
            sorted[k++] = a[j++];   // 합병 정렬 배열에 오른쪽 원소 대입
        }
        move_sum++; // 자료 이동 연산
    }

    if (i > mid)    // 왼쪽 배열을 합병 정렬 배열에 모두 넣었다면
        for (n = j; n <= r; n++) {   // 오른쪽 배열의 모든 원소를 합병 정렬 배열에 대입
            sorted[k++] = a[n];
            move_sum++; // 자료 이동 연산
        }
    else            // 오른쪽 배열을 합병 정렬 배열에 모두 넣었다면
        for (n = i; n <= mid; n++) { // 왼쪽 배열의 모든 원소를 합병 정렬 배열에 대입
            sorted[k++] = a[n];
            move_sum++; // 자료 이동 연산
        }

    for (n=l; n<=r; n++) {  // 정렬된 배열을 위치에 맞게 배열 a에 다시 대입
        a[n] = sorted[n];
    }

    delete [] sorted;
    return {compare_sum, move_sum};
}

template <typename itemType>
void mergesort(itemType a[], int l, int r, int& c, int&m) {
    int mid;
    tuple<int, int> result;
    if (l < r) {
        mid = (l + r) / 2;
        mergesort(a, l, mid, c, m);   // 앞 부분 정렬
        mergesort(a, mid+1, r, c, m); // 뒷 부분 정렬
        result = merge(a, l, mid, r, c, m); // 두 배열 합병
        // 데이터 비교 연산 횟수, 자료 이동 연산 횟수를 변수에 담기
        c += get<0>(result);
        m += get<1>(result);
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

    // 2. 배열 A와 B에 대해 합병 정렬을 이용해 오름차순으로 정렬하기
    int compare_A = 0, move_A = 0;
    mergesort(A, 0, N-1, compare_A, move_A);
    cout << "SortedData A: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << A[i] << " ";
    }
    cout << endl;

    int compare_B = 0, move_B = 0;
    mergesort(B, 0, N-1, compare_B, move_B);
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

