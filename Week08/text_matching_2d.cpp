// Q. 2차원 배열의 Text String 과  2차원 배열의 Pattern String을 이용하여  Text String 에서 Pattern String을 모두 찾는 프로그램을 Brute-Force, Rabin-Karp를 이용하여 작성하세요.
//    이하 입력에 대해 각각의 알고리즘이 수행한 문자 비교 횟수를 출력하세요.
//    또한, Rabin-Karp 알고리즘에서 랜덤 값들을 가지는 Text_String[][]=(100x100)에 대해 q의 값을 10, 100, 1000, 10000으로 변화시키면서 비교횟수를 출력한 후, 이를 그래프 형태로 정리해보세요.
//    [단, Text_String[][]=(100x100)은 모두 ‘A’로 구성되어 있고, Pattern_String[][]=(10x10)로서 마지막 문자인 p[9][9]=’B’ 이고, 나머지는 모두 ‘A’로 하는 배열을 이용하시오.]

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
using namespace std;

const int TEXT_SIZE = 100;
const int PATTERN_SIZE = 10;

// 문자열 비교 횟수를 담을 변수
int compareBS = 0;
int compareRK = 0;

void bruteSearch(vector<vector<char>>& T, vector<vector<char>>& P, int n, int m) {
    // T : text string, P : pattern string, n : T 사이즈, m : P 사이즈
    for (int i = 0; i <= n - m; i++) {
        for (int j = 0; j <= n - m; j++) {
            int k, l;
            for (k = 0; k < m; k++) {
                for (l = 0; l < m; l++) {
                    compareBS++;
                    if (P[k][l] != T[i + k][j + l]) {
                        break;
                    }
                }
                if (l < m)
                    break;
            }
        }
    }
}

int prime = 101;
// 해쉬 구하기 함수
int hashFunc(vector<vector<char>>& arr, int r, int c, int m) {
    int hash = 0;
    for (int i = r; i < r + m; i++) {
        for (int j = c; j < c + m; j++) {
            hash = (hash * prime + arr[i][j]) % prime;
        }
    }
    return hash;
}

void rkSearch(vector<vector<char>>& T, vector<vector<char>>& P, int n, int m) {
    int textHash = hashFunc(T, 0, 0, m);
    int patternHash = hashFunc(P, 0, 0, m);
    int h = 1;

    for (int i = 0; i < m - 1; i++) {
        h = (h * prime) % prime;
    }

    for (int i = 0; i <= n - m; i++) {
        for (int j = 0; j <= n - m; j++) {
            if (textHash == patternHash) {
                int k, l;
                bool match = true; // 패턴 문자열과 일치하는지 여부를 나타내는 변수
                for (k = 0; k < m; k++) {
                    for (l = 0; l < m; l++) {
                        compareRK++;
                        if (P[k][l] != T[i + k][j + l]) {
                            match = false;
                            break;
                        }
                    }
                    if (!match) break;
                }
                if (match) {
                    compareRK++;
                }
            }
            if (j < n - m) {
                textHash = (prime * (textHash - T[i][j] * h) + T[i][j + m]) % prime;
                if (textHash < 0) {
                    textHash = (textHash + prime) % prime;
                }
            }
        }
        if (i < n - m) {
            int newHash = 0;
            for (int j = 0; j < m; j++) {
                newHash = (newHash * prime + T[i + m][j]) % prime;
            }
            textHash = newHash;
        }
    }
}

// q값에 따라 랜덤 소수 구하기 함수
default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
bool isPrime(int n) {   // 소수 구하기 함수
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int generateRandomPrime(int q) {
    // 범위 내 랜덤 소수 구하는 함수
    uniform_int_distribution<int> distribution(q);
    while (true) {
        int candidate = distribution(generator);
        if (isPrime(candidate)) {
            return candidate;
        }
    }
}

int main() {
    // text string, pattern string -> 2차원 배열로 선언 및 문제의 조건대로 초기화
    vector<vector<char>> TS(TEXT_SIZE, vector<char>(TEXT_SIZE, 'A'));
    vector<vector<char>> PS(PATTERN_SIZE, vector<char>(PATTERN_SIZE, 'A'));
    PS[PATTERN_SIZE - 1][PATTERN_SIZE - 1] = 'B';

    // brute force algorithm
    bruteSearch(TS, PS, TS.size(), PS.size());
    cout << "Brute-Force : " << compareBS << endl;

    // rabin-karp algorithm
    int qValues[] = {10, 100, 1000, 10000};
    for (int q : qValues) {
        compareRK = 0;
        prime = generateRandomPrime(q); // q에 따라 prime 설정하기
        rkSearch(TS, PS, TEXT_SIZE, PATTERN_SIZE);
        cout << "Rabin-Karp (q = " << q << ") : " << compareRK << endl;
    }

    return 0;
}