#include <iostream>
#include <string>
using namespace std;

void bruteSearch(char *t, char *p, int n, int m) {
    // t : text string, p : pattern string, n : t 사이즈, m : p 사이즈
    int i, j;
    for(i = 0; i <= n-m; i++) { // i : 비교를 시작하는 위치
        for (j = 0; j < m; j++) { // j : pattern에서 비교하는 위치
            if ( p[j] != t[i+j] ) break ;
        }
        if (j == m)
            cout << "패턴이 텍스트의 " << i << "번째부터 나타남" << endl;
    }
}

void kmpSearch(char *t, char *p) {
    // t : text string, p : pattern string
}

void rkSearch(char *t, char *p) {
    // 라빈 카프 알고리즘, 적절한 해시 사용
    // t : text string, p : pattern string
}

int main() {
    string TS, PS;  // text string, pattern string -> 1차원 배열로 선언

}