// Q. 다음 왼쪽 코드는 피보나치 수열을 구하는 재귀함수의 의사코드이다. 또한, 우측 코드는 피보나치 수열을 구하는 동적 알고리즘의 의사코드이다.
//    각 의사코드에 1 이상의 정수 n을 입력하였을 때 출력되는 call의 횟수를 각각 예측하는 프로그램을 작성해보세요.
#include <iostream>
using namespace std;

// 피보나치 수열을 구하는 재귀 함수
int fib(int n, int &count) {
    if (n == 1 or n ==2) {
        cout << "재귀-call" << endl;
        count++;    // 출력 횟수 증가
        return 1;
    } else {
        return fib(n-1, count) + fib(n-2, count);
    }
}

// 피보나치 수열을 구하는 동적 알고리즘을 가지는 함수
int fib(int n, int *f, int &count) {
    if (f[n] != 0)
        return f[n];
    else {
        if (n == 1 or n == 2)
            f[n] = 1;
        else {
            cout << "동적-call" << endl;
            count++;
            f[n] = fib(n-1, f, count) + fib(n-2, f, count);
        }
        return f[n];
    }
}
int memo_fib(int n, int& count) {
    int f[n+1];
    for (int i = 0; i < n+1; i++) {
        f[i] = 0;   // 0으로 초기화
    }
    return fib(n, f, count);
}

int main() {
    // 입력
    int n;
    int count_fib1 = 0, count_fib2 = 0;
    cin >> n;

    // 함수 실행
    fib(n, count_fib1);
    memo_fib(n, count_fib2);

    // 출력
    cout << "재귀 함수 : " << count_fib1 << ", 동적 알고리즘 : " << count_fib2 << endl;
    return 0;
}