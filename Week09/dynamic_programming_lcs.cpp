// Q. 강의 자료의 LCS(Longest Commons Sequence) 찾기 문제와 의사코드를 참고하여, 다음을 각각 만족하는 동적알고리즘을 완성해보세요.
//    (1) 길이가 각각 m, n인 두 string입력에 대하여, b[i,j] 배열(화살표 기록에 사용함)을 사용하지 않고, O(m+n)시간에  LCS를 복구해낸다.
//    (2) 하향식 방법 (with memoization)을 사용하여 문제를 해결한다.
//    (3) 길이가 각각 m, n인 두 string 입력에 대하여, 크기가 최대 min(m, n)인 c[i,j] 배열(최대 LCS 값 기록에 사용함)을 사용하여 LCS의 길이를 찾는다.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> c; // 중복 계산 방지 배열
// LCS의 길이를 반환하는 함수
int LCS_Length(const string& X, const string& Y, int m, int n) {    // m : X의 길이 n: Y의 길이
    if (m == 0 || n == 0) {
        return 0;
    }
    // 결과가 이미 c에 저장되어 있는지 판별
    if (c[m][n] != -1) {
        return c[m][n];
    }

    if (X[m-1] == Y[n-1]) {
        c[m][n] = 1 + LCS_Length(X, Y, m - 1, n - 1);
    } else {
        int option1 = LCS_Length(X, Y, m - 1, n);
        int option2 = LCS_Length(X, Y, m, n - 1);
        c[m][n] = max(option1, option2);
    }
    return c[m][n];
}

// LCS 문자열을 찾는 함수
string FindLCS(const string& X, const string& Y, int m, int n) {    // m : X의 길이 n: Y의 길이
    if (m == 0 || n == 0) {
        return "";
    }
    // (1) 상향식 접근 방법에서 화살표 기록에 사용하는 b 배열을 사용하지 않음
    //     대체로 (m-1, n) 자리와 (m, n-1) 자리의 값을 서로 비교하여 더 큰 값이 있는 쪽으로 이동
    // (2) 하향식 접근 방법을 사용하기 위해 재귀 함수를 사용
    if (X[m - 1] == Y[n - 1]) {
        return FindLCS(X, Y, m - 1, n - 1) + X[m - 1];
    } else if (c[m - 1][n] > c[m][n - 1]) {
        return FindLCS(X, Y, m - 1, n);
    } else {
        return FindLCS(X, Y, m, n - 1);
    }
}

int main() {
    string X, Y;    // 두 문자열
    // 입력 받기
    getline(cin, X);
    getline(cin, Y);
    int m = X.length();
    int n = Y.length();

    // (3) LCS 값 기록에 사용할 2차원 배열, 크기는 (m+1)X(n+1)이다.
    // memo 배열 원소들을 -1로 초기화
    c.assign(m + 1, vector<int>(n + 1, -1));

    // 함수 실행 및 결과 출력
    int length = LCS_Length(X, Y, m, n);
    cout << "LCS 길이 : " << length << endl;

    string lcs = FindLCS(X, Y, m, n);
    cout << "LCS : " << lcs << endl;

    return 0;
}
