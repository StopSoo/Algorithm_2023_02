// Q. 임의의 점 Z의 좌표 값과 단순 폐쇄 경로 생성을 위한 N개의 점의 좌표 값들을 입력 받고,
//    해당 점이 단순 폐쇄 경로 Poly[] 내부에 존재하는 점인가를 판단해주는 프로그램을 구현하세요.
//    이 때, 아래의 입출력 예제에 맞춰 출력하세요.
#include <iostream>
using namespace std;

const int Nmax = 100;   // 다각형 내 최대 점 개수를 임의로 100으로 설정
struct point {
    char c; // 점 이름
    int x, y;   // 점 좌표
};
point polygon[Nmax];    // 다각형

// 점 Z가 단순 폐쇄 경로 안에 있는지의 여부를 반환하는 함수
bool isInsideConvexHull(point z, int N) {
    int intersections = 0;

    for (int i = 0; i < N; i++) {
        point p1 = polygon[i];
        point p2 = polygon[(i + 1) % N];

        if ((p1.y > z.y) != (p2.y > z.y) && z.x < p1.x + (p2.x - p1.x) * (z.y - p1.y) / (p2.y - p1.y)) {
            intersections++;
        }
    }
    // 교차점의 개수가 홀수라면 점 Z는 다각형 내부에 있는 것 !
    return intersections % 2 == 1;
}

int main() {
    int N;  // 점의 개수
    point z;
    cin >> N >> z.x >> z.y;
    // 점 배열에 각 점들의 점 이름과 x, y 좌표값 입력 받기
    for (int i=0; i < N; i++) {
        cin >> polygon[i].c >> polygon[i].x >> polygon[i].y;
    }

    bool isInside = isInsideConvexHull(z, N);   // 다각형 내부에 점 z가 있는지 여부를 반환

    cout << "다각형이 만들어지는 순서 : ";
    for (int i = 0; i < N; i++) {
        cout << polygon[i].c << " ";
    }
    cout << endl;

    cout << (isInside ? "True" : "False") << endl;
    return 0;
}