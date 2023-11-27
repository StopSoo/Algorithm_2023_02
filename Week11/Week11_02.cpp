// Q. 양의 정수 N과 실수 확률값 p(0<p<1)를 입력 받은 후, 이를 통해, 행렬의 각 원소를 p의 확률로 1,  1-p의 확률로 0으로 생성하는 N x N 인접 행렬을 생성하세요.
//    단, 인접 행렬은 반드시 대칭 행렬이 되도록 생성해야 합니다 (즉, i행 j열의 원소 = j행 i열의 원소).
//    이후 이 인접 행렬을 1번에서 사용한 인접 리스트 형태로 변환한 후 그래프가 총 몇 개의 연결 성분으로 이루어져 있는가를 출력하는 프로그램을 작성하세요.
//    [Hint. 위에서 작성한 DFS 혹은 BFS출력을 이용하면, 한 연결 그래프에 포함된 점들을 모두 얻을 수 있습니다.]
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

vector<vector<int>> makeMatrix(int N, double p);
tuple<vector<vector<int>>, int> makeAdjList(vector<vector<int>> M, int N);

int main() {
    int N, count;
    double p;
    tuple<vector<vector<int>>, int> result = {};
    cin >> N >> p;

    vector<vector<int>> adjMatrix = makeMatrix(N, p);   // 인접 행렬 생성
    // 확인용 출력
    cout << "* 인접 행렬 *" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    result = makeAdjList(adjMatrix, N);
    vector<vector<int>> adjList = get<0>(result);
    count = get<1>(result);  // 인접 행렬을 인접 리스트로 변환해서 얻은 연결 성분 개수 값

    cout << "연결 성분의 개수 : " << count << endl;

    return 0;
}

// 대칭 행렬 생성 함수
vector<vector<int>> makeMatrix(int N, double p) {
    vector<vector<int>> M(N, vector<int>(N, 0));
    srand(time(0));

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            // 대칭행렬에서 주대각선에 있는 원소들은 모두 0이다.
            if (i == j) {
                M[i][j] = 0;
                continue;
            }
            // 행렬 원소의 값을 p의 확률로 1, 1-p의 확률로 0으로 설정
            if (rand() / static_cast<double>(RAND_MAX) < p) {
                M[i][j] = 1;
                M[j][i] = 1;
            }
        }
    }
    return M;
}

tuple<vector<vector<int>>, int> makeAdjList(vector<vector<int>> M, int N) {
    vector<vector<int>> list(N);
    int count = 0;  // 연결 성분 개수 체크

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (M[i][j]) {
                list[i].push_back(j);
                list[j].push_back(i);
                count++;
            }
        }
    }
    // 확인용 출력
    cout << "* 인접 리스트 *" << endl;
    for (int i = 0; i < N; i++) {
        cout << i << " : ";
        for (int j = 0; j < list[i].size(); j++) {
            cout << list[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return {list, count};
}