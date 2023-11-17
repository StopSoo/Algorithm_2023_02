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
    int sum;    // subarray 원소들의 합
    int result = 0; // maximum subarray의 원소들의 합

    for (int i = 0; i < N; i++) {
        sum = 0;
        for (int j = i; j < N; j++) {
            c++;    // 비교 횟수
            sum += A[j];
            if (result < sum) {
                result = sum;
                s = i;
                e = j;
            }
            if (result < sum + A[j+1]) {
                result = sum + A[j+1];
                s = i;
                e = j+1;
            }
        }
    }
    return result;
}

// 방법 2
tuple<int, int, int, int> findMaxCrossingSubarray(int *A, int low, int mid, int high, int &compare) {
    int leftSum = -1;
    int sum = 0;
    int maxLeft;
    for (int i = mid; i >= low; i--) {
        sum += A[i];
        if (sum > leftSum) {
            compare++;
            leftSum = sum;
            maxLeft = i;
        }
    }

    int rightSum =  -1;
    sum = 0;
    int maxRight;
    for (int j = mid + 1; j <= high; j++) {
        sum += A[j];
        if (sum > rightSum) {
            compare++;
            rightSum = sum;
            maxRight = j;
        }
    }
    return {maxLeft, maxRight, leftSum + rightSum, compare};
}

tuple<int, int, int, int> findMaxSubarray(int *A, int low, int high, int &compare) {
    tuple<int, int, int, int> left, right, cross = {};
    int lLow, lHigh, lSum, rLow, rHigh, rSum, cLow, cHigh, cSum;

    compare++;
    if (low == high)
        return {low, high, A[low], compare};

    int mid = (low + high)/2;
    left = findMaxSubarray(A, low, mid, compare);
    right  = findMaxSubarray(A, mid+1, high, compare);
    cross = findMaxCrossingSubarray(A, low, mid, high, compare);
    lLow = get<0>(left); lHigh = get<1>(left); lSum = get<2>(left);
    rLow = get<0>(right); rHigh = get<1>(right); rSum = get<2>(right);
    cLow = get<0>(cross); cHigh = get<1>(cross);  cSum = get<2>(cross);

    if (lSum >= rSum && lSum >= cSum) {
        compare++;
        return {lLow, lHigh, lSum, compare};
    }
    else if (rSum >= lSum && rSum >= cSum) {
        compare++;
        return {rLow, rHigh, rSum, compare};
    }
    else {
        compare++;
        return {cLow, cHigh, cSum, compare};
    }
}

// 방법 3
tuple<int, int, int, int> dpFindSubarray(int *A, int size, int &compare) {
    int maxEnd = A[0];
    int maxSum = A[0];
    int start = 0;
    int end = 0;
    int tempStart = 0;

    for (int i = 1; i < size; i++) {
        compare++;
        if (maxEnd > 0) {
            maxEnd += A[i];
        } else {
            maxEnd = A[i];
            tempStart = i;
        }

        if (maxEnd > maxSum) {
            compare++;
            maxSum = maxEnd;
            start = tempStart;
            end = i;
        }
    }

    return {start, end, maxSum, compare};
}

int main() {
    int N;
    cin >> N;
    // 변수 선언
    int start, end, bfCompare = 0, DaQCompare = 0, dpCompare = 0;
    // 배열 A 선언 및 초기화
    int *A = new int[N];
    srand((unsigned int)time(0));   // 배열 A 랜덤 배치를 위한 시드값 설정
    for (int i = 0; i < N; i++) {   // 배열 A 재배치: -50부터 50까지의 숫자들이 랜덤하게 재배치된 데이터 배열
        A[i] = rand() % 100 - 50;
        cout << A[i] << " ";
    }
    cout << endl;

    // 함수 실행
    int bfSum = bfFindSubarray(A, N, start, end, bfCompare);
    tuple<int, int, int, int> DaQ = findMaxSubarray(A, 0, N-1, DaQCompare);
    tuple<int, int, int, int>dpResult = dpFindSubarray(A, N, dpCompare);

    // 출력
    cout << "Bruteforce 결과 :\t\t\tsubarray 위치 = [" << start << ", " << end;
    cout << "],\t\t 합 = " << bfSum << ",\t\t비교횟수 = " << bfCompare << endl;

    cout << "Divide-and-Conquer 결과 :\tsubarray 위치 = [" << get<0>(DaQ) << ", " << get<1>(DaQ);
    cout << "],\t\t 합 = " << get<2>(DaQ) << ",\t\t비교횟수 = " << DaQCompare << endl;

    cout << "Dynamic Programming 결과 :\tsubarray 위치 = [" << get<0>(dpResult) << ", " << get<1>(dpResult);
    cout << "],\t\t 합 = " << get<2>(dpResult) << ",\t\t비교횟수 = " << dpCompare << endl;

    return 0;
}