// Q. 양의 정수 N을 입력 받은 후, 랜덤한 정수로 이루어진 크기 N의 정수 배열을 생성하세요.
//    이후 이 배열에서 다음 세 가지 방법을 각각 이용하여 maximum subarray의 위치, 그 subarray가 포함하는 정수의 합, 그리고 사용된 비교 횟수를 출력하는 프로그램을 작성하세요.
//    단, 동일한 합을 지니는 maximum subarray가 여러 개 존재할 때는 그 중에서 가장 왼쪽에서 시작하고, 시작점이 같다면 길이가 더 짧은 것이 출력되도록 하세요.
//    방법1. 모든 subarray에 대해 값을 조사하여 비교하는 Brute-force 방법
//    방법2. Divide-and-Conquer방식을 이용한 방법
//    방법3. Dynamic programming (동적 프로그래밍) 방식을 이용한 방법 (Hint: 강의자료 26페이지 참고)
//    N의 크기를 늘려가며 각 방법에서 사용된 비교 횟수를 측정하고, 각 방법의 차이가 잘 나타나도록 결과를 그래프로 정리하세요.
#include <iostream>
#include <time.h>
using namespace std;
// 방법 1
int bfFindSubarray(int *A, int N, int &s, int&e, int& c) {
    int sum = 0;    // subarray 원소들의 합
    int result = 0; // maximum subarray의 원소들의 합

    for (int i = 0; i < N; i++) {
        sum = 0;
        for (int j = i; j < N; j++) {
            c++;    // 비교 횟수
            sum += A[j];
            if (result < sum + A[j+1]) {
                result = sum + A[j+1];
                s = i;
                e = j+1;
            }
        }
    }
    return result;
}

int main() {
    int N;
    cin >> N;

    int start, end, compare = 0;
    int *A = new int[N];
    int x, y;   // 인덱스
    for (int i = 0; i < N; i++) {   // 배열 A 초기화
        A[i] = -1 * (N/2) + i;
    }
    srand((unsigned int)time(0));   // 배열 A 랜덤 배치를 위한 시드값 설정
    for (int i = 1; i <= N; i++) {   // 배열 A 재배치: 1부터 N까지의 숫자들이 "중복 없이" 랜덤하게 재배치된 데이터 배열
        x = rand() % N;
        y = rand() % N;
        swap(A[x], A[y]);
    }


    // 함수 실행
    int bfSum = bfFindSubarray(A, N, start, end, compare);


    // 출력
    for (int i = 0; i < N; i++)
        cout << A[i] << " ";
    cout << endl;
    cout << "Bruteforce 결과 :\t\tsubarray 위치 = [" << start << ", " << end;
    cout << "],\t\t 합 = " << bfSum << ",\t\t비교횟수 = " << compare << endl;


    return 0;
}