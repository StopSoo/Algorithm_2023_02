// Q. 점의 개수 N(<=100)과 양의 정수 m(<N)을 입력 받은 후,
//    각 점의 좌표 X, Y(정수이며, 0에서 100까지의 값을 지닌다)를 랜덤하게 생성한 후 (단, 동일한 좌표를 지니는 점은 존재하지 않도록 생성한다),
//    각 점마다 그 점을 제외하고 가장 가까운 점 m개를 연결하여 그래프 (V, E)를 생성한다.
//    이후, 이 그래프에서 1번째 점과 N번째 점 사이의 최단 거리 및 그 경로를 출력하는 프로그램을 작성하세요.
//    단, 두 점 사이를 잇는 경로가 없는 경우에는 없다고 출력한다.
//    m을 1부터 시도해보면서 1번과 N번 점이 연결될 확률이 약 50% 이상이 되기 위해서는 어느 정도의 m이 필요한가 구해보세요.
//    정확한 답을 구할 필요는 없고, 실험적으로 살펴보면 됩니다.
//    이러한 m에 대해, N을 늘려가며, 그래프를 생성하는데 걸린 시간과 최단경로를 찾기 위해 걸린 시간(두 점 사이의 경로가 있는 경우)을 그래프로 정리하세요.
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <queue>
#include <stack>

using namespace std;

struct Point {  // 점
    int x, y;
    // 좌표가 (x, y) 값을 가지므로 operator overriding 진행
    bool operator < (const Point& other) const {
        return (x < other.x) || ((x == other.x) && (y < other.y));
    }
    bool operator == (const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
};

struct Edge {   // 간선
    int u, v, weight;
};

bool operator < (const Edge& a, const Edge& b) {
    return a.weight > b.weight;
}

int calculateDistance(const Point& p1, const Point& p2) {   // 두 점 사이의 거리를 계산
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

pair<int, vector<int>> findShortestPath(const vector<vector<int>>& graph, int start, int end) {
    int N = graph.size();
    vector<int> dist(N, INT_MAX);
    vector<int> parent(N, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        // 마지막 원소일 경우
        if (u == end) {
            // 경로 재구성하기
            stack<int> path;
            int curr = end;
            while (curr != -1) {
                path.push(curr);
                curr = parent[curr];
            }
            // 최종 경로 구성
            vector<int> resultPath;
            while (!path.empty()) {
                resultPath.push_back(path.top());
                path.pop();
            }
            return {dist[u], resultPath};
        }
        // 최단 거리 찾기
        for (int v = 0; v < N; ++v) {
            if (graph[u][v] != -1 && dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    // 경로가 없을 경우
    return {-1, {}};
}

int main() {
    // 랜덤 설정
    srand(time(nullptr));

    int N, m;
    cout << "점의 개수와 양의 정수를 입력하세요 : ";
    cin >> N >> m;

    set<Point> uniquePoints;    // 좌표가 중복되는 일 없이 점을 생성
    while (uniquePoints.size() < N) {
        uniquePoints.insert({rand() % 101, rand() % 101});
    }

    vector<Point> points(uniquePoints.begin(), uniquePoints.end());

    // 그래프 생성
    vector<vector<int>> graph(N, vector<int>(N, -1));
    for (int i = 0; i < N; ++i) {
        vector<Edge> edges;
        for (int j = 0; j < N; ++j) {
            if (i != j) {
                int weight = calculateDistance(points[i], points[j]);   // 두 점 사이의 거리를 계산
                edges.push_back({i, j, weight});
            }
        }
        sort(edges.begin(), edges.end(), less<Edge>()); // 간선을 오름차순으로 정렬
        for (int j = 0; j < min(m, N - 1); ++j) {
            graph[i][edges[j].v] = edges[j].weight;
        }
    }
    // 가장 짧은 경로 찾기
    auto result = findShortestPath(graph, 0, N - 1);

    // 출력
    if (result.first == -1) {   // 경로가 없을 경우 (예외 처리)
        cout << "경로가 존재하지 않습니다." << endl;
    } else {
        cout << "최단 거리는 " << result.first << "입니다." << endl;
        cout << "최단 경로는 ";
        for (int node : result.second) {
            cout << node << " ";
        }
        cout << "입니다." << endl;
    }

    return 0;
}

