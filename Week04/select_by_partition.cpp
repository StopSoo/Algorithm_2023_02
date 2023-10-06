// Q. n(> 10000)개의 양의 정수 자료를 랜덤 함수로서 발생하여, partition() 연산을 사용하여
// k번째 원소를 찾는 Select(a, l, r, k)을 사용해서 최소치, 최대치 및 중앙치를 찾고 비교연산 횟횟를 각각 출력하시오.
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
void select(itemType a[], int l, int r, int k, unsigned & c, unsigned & m)
{
    int j;
    if (l < r) {
        j = partition<int>(a, l, r, c, m);
        if (j > l + k - 1)
            select<int>(a, l, j-1, k, c, m);   // 왼쪽 배열 선택
        if (j < l + k - 1)
            select<int>(a, j+1, r, k - j + l - 1, c, m); // 오른쪽 배열 선택
    }
}

int main() {
    int N;  // 배열의 크기
    cin >> N;   // 사용자로부터 배열의 크기 입력 받기

    // 배열 생성 및 크기 동적 할당
    int *arr = new int[N];
    int x, y;   // 랜덤 배열을 위한 인덱스

    for (int i = 0; i < N; i++) {   // 배열 B 초기화
        arr[i] = i + 1;
    }
    srand((unsigned int)time(nullptr));   // 배열 B 랜덤 배치를 위한 시드값 설정

    int value = N;
    for (int i = 0; i < N; i++) {   // 배열 A 초기화: 1부터 N까지 내림차순으로 push
        arr[i] = value--;
    }
    for (int i = 0; i < N; i++) {   // 배열 B 재배치: 1부터 N까지의 숫자들이 "중복 없이" 랜덤하게 재배치된 데이터 배열
        while (true) {
            x = rand() % N;
            y = rand() % N;
            if (x != 0 && y != 0)   // 인덱스 0이 나오면 안되므로
                break;
        }
        swap(arr[x], arr[y]);
    }

    unsigned int compare = 0, move = 0;     // 데이터 비교 연산 횟수와 자료 이동 연산 횟수
    select<int>(arr, 0, N-1, 0, compare, move);
    cout << "최소치 : " << arr[0] << endl;
    cout << "최대치 : " << arr[N-1] << endl;
    cout << "중앙치 : " << arr[N/2] << endl;
    cout << "-----------------------------------" << endl;
    cout << "Compare_Cnt : " << compare << ", DataMove_Cnt : " << move << endl;

    // 메모리 해제
    delete [] arr;
    return 0;
}

