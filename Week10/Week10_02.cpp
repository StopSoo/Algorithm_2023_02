// Q. 위 문제에서 정리한 방법을 토대로 Bruteforce 방법의 비교 횟수가 Divide-and-Conquer 방법의 비교횟수보다 작거나 같아지는 가장 큰 입력 배열의 크기 n을 구하세요.
//    이를 토대로 Divide-and-Conquer 방법을 적용한 recursive 알고리즘에서 base case가 n보다 작거나 같을 때는 Bruteforce 방식을 사용하도록 수정된 방법을 작성해보세요.
//    이후, 이 방법과 기존 Divide-and-Conquer 방법의 필요 비교 횟수를 입력 크기 N에 대한 그래프로 정리하여 비교해보세요.
#include <iostream>
#include <time.h>
using namespace std;

void bfFindSubarray(int *A, int N, int &s, int&e, int& c) {
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
}

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

// 수정된 방법
void editedMethod(int *A, int low, int high, int &compare) {
    tuple<int, int, int, int> left, right, cross = {};
    int lLow, lHigh, lSum, rLow, rHigh, rSum, cLow, cHigh, cSum;

    compare++;
    if (low == high)
        return;

    int mid = (low + high)/2;
    left = findMaxSubarray(A, low, mid, compare);
    right  = findMaxSubarray(A, mid+1, high, compare);
    cross = findMaxCrossingSubarray(A, low, mid, high, compare);
    lLow = get<0>(left); lHigh = get<1>(left); lSum = get<2>(left);
    rLow = get<0>(right); rHigh = get<1>(right); rSum = get<2>(right);
    cLow = get<0>(cross); cHigh = get<1>(cross);  cSum = get<2>(cross);

    if (lSum >= rSum && lSum >= cSum) {
        compare++;
        return;
    }
    else if (rSum >= lSum && rSum >= cSum) {
        compare++;
        return;
    }
    else {
        compare++;
        return;
    }
}

int main() {
    // 사용자 입력
    int N;
    cin >> N;
    // 변수 선언
    int start, end, bfCompare = 0, DaQCompare = 0, dpCompare = 0;
    // 배열 A 선언 및 초기화
    int *A = new int[1000];
    srand((unsigned int)time(0));   // 배열 A 랜덤 배치를 위한 시드값 설정
    for (int i = 0; i < 10000; i++) {   // 배열 A 재배치: -50부터 50까지의 숫자들이 랜덤하게 재배치된 데이터 배열
        A[i] = rand() % 100 - 50;
    }
    // bf 비교 횟수 <= daq 비교 횟수인 가장 큰 입력 배열 크기 n 구하기
    int whatIsMaxN = 0;
    for (int i = 1; i < 1000; i++) {
        bfFindSubarray(A, i, start, end, bfCompare);
        tuple<int, int, int, int> DaQ = findMaxSubarray(A, 0, i-1, DaQCompare);
        // 확인용 출력
        if (bfCompare <= DaQCompare) {
            cout << i << " : " << "bfCompare : " << bfCompare << ", DaQCompare : " << DaQCompare << endl;
            whatIsMaxN = i;
        } else
            break;
    }
    cout << "N의 최댓값 : " << whatIsMaxN << endl ;

    // base case가 n보다 작거나 같을 때는 bf 방식을 사용하도록 수정
    int editedCompare = 0;
    tuple<int, int, int, int> editedResult;
    if (N <= whatIsMaxN)
        bfFindSubarray(A, N, start, end, editedCompare);
    else
        editedMethod(A, 0, N, editedCompare);

    cout << "수정된 방법의 비교 횟수 : " << editedCompare << endl;
    return 0;
}