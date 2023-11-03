// Q. Text String과 Pattern String을 입력 받아 1차원 배열에 저장하고,
//    Text String 에서 Pattern String을 모두 찾는 프로그램을 아래의 알고리즘 (Brute-Force, KMP, Rabin-Karp) 소스 코드를 참고하여 작성하세요.
//    또한 각각의 알고리즘이 수행한 문자 비교 횟수를 출력하세요.
//    Rabin-Karp 알고리즘의 경우 Horner의 연산 방법을 사용했을 때와 그렇지 않았을 때 *연산의 수행 횟수를 각각 출력하세요.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 패턴 문자열과 일치하는 시작점을 저장할 배열
vector<int> resultBS;
vector<int> resultKMP;
vector<int> resultRKYes;
vector<int> resultRKNo;
// 문자열 비교 횟수를 담을 변수
int compareBS = 0;
int compareKMP = 0;
int compareRKYes = 0;
int mulCountRK = 0;

void bruteSearch(string T, string P, int n, int m) {
    // T : text string, P : pattern string, n : T 사이즈, m : P 사이즈
    int i, j;
    for(i = 0; i <= n-m; i++) { // i : 비교를 시작하는 위치
        for (j = 0; j < m; j++) { // j : pattern에서 비교하는 위치
            compareBS++;
            if ( P[j] != T[i+j] ) break ;
        }

        if (j == m)
            resultBS.push_back(i);    // 시작점 위치를 result에 삽입
    }
}

int failure[10];
void fail(string P) {    // failure 배열 초기화 함수
    int j, n = P.size();
    failure[0] = -1;    // failure[0]은 무조건 -1을 가짐

    for (int i = 1; i < n; i++) {
        j = failure[i-1];

        while ((P[i] != P[j+1]) && (j >= 0)) {  // 일치할 때까지 반복
            j = failure[j];
        }

        if (P[i] == P[j+1]) // 일치하면
            failure[i] = j+1;
        else    // 일치하지 않으면
            failure[i] = -1;
    }
}

void kmpSearch(string T, string P) {
    // T : text string, P : pattern string
    int i = 0, j = 0;
    int lenS = T.size();   // text string의 길이
    int lenP = P.size();   // pattern string의 길이

    while (i < lenS) {
        while(j < lenP) {
            // 한 글자씩 비교
            compareKMP++;
            if (T[i] == P[j]) { // 패턴에서 한 글자와 문자열의 한 글자가 같다면
                i++;
                j++;
            } else if (j == 0)  // 패턴 첫 글자부터 다르다면
                i++;
            else    // 같은 부분이 있다면
                j = failure[j-1] + 1;
        }

        if (j == lenP) {    // 패턴의 마지막 문자까지 비교한다면
            resultKMP.push_back(i-lenP);    // 시작 위치를 배열에 넣기
            j = 0;  // 패턴 내 인덱스를 0으로 초기화
        }
    }

}

const int prime = 101;  // 소수
void rkSearchHornerYes(string T, string P) {
    // Horner 방법을 사용한 라빈 카프 알고리즘, 적절한 해시 사용
    // T : text string, P : pattern string
    int sizeT = T.length();
    int sizeP = P.length();
    int hashT = 0, hashP = 0, h = 1;
    // h 값 계산하기
    for (int i = 0; i < sizeP - 1; i++)
        h = (h * prime) % prime;
    // 해시 값 계산
    for (int i = 0; i < sizeP; i++) {
        hashT = (hashT * prime + T[i]) % prime;
        hashP = (hashP * prime + P[i]) % prime;
    }

    for (int i = 0; i <= sizeT - sizeP; i++) {
        if (hashT == hashP) {   // 해시 일치
            bool find = true;
            for (int j = 0; j < sizeP; j++) {
                compareRKYes++;
                if (T[i + j] != P[j]) { // 문자가 모두 일치하지 않는다면 실패
                    find = false;
                    break;
                }
            }
            if (find) {
                // 패턴 문자열과 같은 부분 문자열을 찾았다면 인덱스를 배열에 삽입
                resultRKYes.push_back(i);
            }
        }

        if (i < sizeT - sizeP) {    // 다음 부분 문자열에 대해 해시 값을 계산한 후 진행
            hashT = (prime * (hashT - T[i] * h) + T[i + sizeP]) % prime;
            if (hashT < 0) {
                hashT = (hashT + prime) % prime;
            }
        }
    }
}

void rkSearchHornerNo(string T, string P) {
    // Horner 방법을 사용하지 않은 라빈 카프 알고리즘, 적절한 해시 사용
    // T : text string, P : pattern string
    int sizeT = T.size();
    int sizeP = P.size();
    int hashT = 0, hashP = 0, power = 1;

    for (int i = 0; i <= sizeT - sizeP; i++) {
        if (i == 0) {
            for (int j = 0; j < sizeP; j++) {
                mulCountRK += 2;
                hashT = hashT + T[sizeT - 1 - j] * power;
                hashP = hashP + P[sizeP - 1 - j] * power;
                if (j < sizeP - 1)
                    power = power * 2;
            }
        } else {
            mulCountRK++;
            hashP = 2 * (hashP - T[i-1] * power) + T[sizeP - 1 + i];
        }
        if (hashT == hashP) {   // 해시 일치
            bool find = true;
            for (int j = 0; j < sizeP; j++) {
                if (T[i + j] != P[j]) { // 문자가 모두 일치하지 않는다면 실패
                    find = false;
                    break;
                }
            }
            if (find) {
                resultRKNo.push_back(i);
            }
        }
    }
}

int main() {
    // 입력
    string TS, PS;  // text string, pattern string -> 1차원 배열로 선언
    getline(cin, TS);
    getline(cin, PS);

    // 알고리즘 실행
    bruteSearch(TS, PS, TS.size(), PS.size());

    fail(PS);
    kmpSearch(TS, PS);

    rkSearchHornerYes(TS, PS);

    rkSearchHornerNo(TS, PS);

    // 출력
    cout << "Brute-Force : ";
    for (int e : resultBS) {
        cout << e << ", ";
    }
    cout << compareBS << endl;

    cout << "KMP : ";
    for (int e : resultKMP) {
        cout << e << ", ";
    }
    cout << compareKMP << endl;

    cout << "Rabin-Karp with Horner: ";
    for (int e : resultRKYes) {
        cout << e << ", ";
    }
    cout << compareRKYes << endl;

    cout << "Rabin-Karp without Horner: ";
    for (int e : resultRKNo) {
        cout << e << ", ";
    }
    cout << mulCountRK << endl;

    return 0;
}