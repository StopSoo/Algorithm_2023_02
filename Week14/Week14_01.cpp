// Q. 점의 개수 N(<=100)을 입력 받고, N개의 점의 좌표 X, Y를 입력 받아 단순 폐쇄 경로 Poly[]를 생성하는 프로그램을 아래의 소스 코드를 이용해 작성하세요.
//    또한 단순 폐쇄 경로를 생성하는 과정에서 두 점 사이의 상대 각도 계산 횟수 및 각의 비교 횟수를 아래의 출력 예제에 맞춰 출력하시오.
//    (단, 수평각들을 정렬하는 알고리즘은 Heap Sort를 이용하고, 점의 X, Y 좌표는 100보다 작다고 가정한다.)
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int Nmax = 100;   // 다각형 내 최대 점 개수를 임의로 100으로 설정
struct point {
    char c; // 점 이름
    int x, y;   // 점 좌표
};
point polygon[Nmax];    // 다각형

// 두 점 사이의 상대 각도를 계산
float ComputeAngle(struct point p1, struct point p2, int& angleComputations){
    int dx, dy, ax, ay;
    float t;
    dx = p2.x - p1.x;   // x 변화율
    ax = abs(dx);
    dy = p2.y - p1.y;   // y 변화율
    ay = abs(dy);
    t = (ax+ay == 0) ? 0 : (float) dy / (ax+ay);
    if (dx < 0)
        t = 2 - t;
    else if (dy < 0)
        t = 4 + t;

    angleComputations += 1;
    return t * 90.0;
}

int main() {
    int N;  // 점의 개수
    int angleComputationCount = 0; // 수평각 계산 횟수
    int angleComparisons = 0;   // 각의 비교 횟수
    cin >> N;
    // 점 배열에 각 점들의 점 이름과 x, y 좌표값 입력 받기
    for (int i=0; i < N; i++) {
        cin >> polygon[i].c >> polygon[i].x >> polygon[i].y;
    }
    // 작성한 함수에 맞춰서 points 배열을 정렬 -> 오름차순으로 정렬
    sort(polygon, polygon+N, [](const point &a, const point &b) {
      return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    point pivot = polygon[0];    // x 값이 가장 작은 점을 pivot(기준점)으로 설정

    // points 배열을 pivot 관점 각도에 맞게 정렬
    sort(polygon + 1, polygon + N, [pivot, &angleComputationCount, &angleComparisons](const point &a, const point &b) {
        angleComparisons++;
        return ComputeAngle(pivot, a, angleComputationCount) < ComputeAngle(pivot, b, angleComputationCount);
    });

    cout << "다각형이 만들어지는 순서 : ";
    for (int i = 0; i < N; i++) {
        cout << polygon[i].c << " ";
    }
    cout << endl;

    cout << angleComputationCount << " (수평각 계산 횟수)" << endl;
    cout << angleComparisons << " (각의 비교 횟수)" << endl;

    return 0;
}