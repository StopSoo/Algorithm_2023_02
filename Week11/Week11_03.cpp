// Q. 2번 문제와 동일하게 양의 정수 N과 실수 확률값 p(0<p<1) 입력에 대해 그래프를 생성하는데, 행렬의 각 원소가 p의 확률로 1부터 10 사이의 랜덤한 자연수가 되고,
//    1-p의 확률로 inf값(적절히 설정)을 가지도록 합니다. 이후, 이를 최소한의 간선만 추가하여 하나의 연결 그래프로 변경하세요.
//    이후, 이 그래프에 대해 Minimum Spanning Tree를 출력하는 Prim의 알고리즘을 작성하세요. 단, 그래프의 정점 수 V, 간선 수 E에 대해, 실행시간이 Θ(E⋅logV) 혹은 Θ(E⋅logE) 가 되도록 작성해야 합니다.
//    간선의 수를 변화해가며 실행시간을 측정한 후, 이를 정리하여 보고서에 그래프(예, x축은 E, y축은 실행시간) 형태로 작성하세요.
// 공부하고 다시 풀어보기 (!)
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>

using namespace std;

// 간선 정보 구조체
struct Edge {
    int src, dest, weight;
};

// 우선순위 큐를 위한 비교 연산자 정의
struct Compare {
    bool operator()(const Edge& e1, const Edge& e2) {
        return e1.weight > e2.weight;  // 가중치가 낮은 것이 우선순위가 높음
    }
};

// 그래프 클래스 정의
class Graph {
private:
    int V;  // 정점의 수
    vector<vector<int>> adjacencyMatrix;  // 인접 행렬
public:
    Graph(int vertices)
    : V(vertices) {
        // 인접 행렬 초기화
        adjacencyMatrix.resize(V, vector<int>(V, INT_MAX));
    }

    // 간선 추가 함수
    void addEdge(int src, int dest, int weight) {
        adjacencyMatrix[src][dest] = weight;
        adjacencyMatrix[dest][src] = weight;
    }

    // Prim의 알고리즘 구현
    void primMST() {
        vector<bool> inMST(V, false);  // 최소 신장 트리에 포함된 정점 여부
        priority_queue<Edge, vector<Edge>, Compare> pq;  // 최소 힙

        // 임의의 시작 정점 선택
        int startVertex = 0;
        inMST[startVertex] = true;

        // 선택한 정점에 연결된 모든 간선을 우선순위 큐에 추가
        for (int i = 0; i < V; ++i) {
            if (adjacencyMatrix[startVertex][i] != INT_MAX) {
                Edge edge = {startVertex, i, adjacencyMatrix[startVertex][i]};
                pq.push(edge);
            }
        }

        cout << "Minimum Spanning Tree (Prim's Algorithm):" << endl;

        int edgeCount = 0;
        auto start_time = chrono::high_resolution_clock::now();

        // 간선을 선택하여 최소 신장 트리를 구성
        while (!pq.empty() && edgeCount < V - 1) {
            Edge currentEdge = pq.top();
            pq.pop();

            // 선택한 간선의 도착 정점이 이미 최소 신장 트리에 포함되어 있으면 스킵
            if (inMST[currentEdge.dest]) {
                continue;
            }

            // 간선 출력
            cout << "(" << currentEdge.src + 1 << " " << currentEdge.dest + 1 << ") ";
            edgeCount++;

            // 현재 간선의 도착 정점을 최소 신장 트리에 추가
            inMST[currentEdge.dest] = true;

            // 새로 추가된 정점에 연결된 간선을 우선순위 큐에 추가
            for (int i = 0; i < V; ++i) {
                if (adjacencyMatrix[currentEdge.dest][i] != INT_MAX && !inMST[i]) {
                    Edge edge = {currentEdge.dest, i, adjacencyMatrix[currentEdge.dest][i]};
                    pq.push(edge);
                }
            }
        }

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

        cout << "\n실행 시간: " << duration.count() << " microseconds" << endl;
    }
};

int main() {
    int N, weight;
    double p;
    cin >> N >> p;

    // 그래프 생성
    Graph graph(N);

    // 인접 행렬 생성
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (rand() / static_cast<double>(RAND_MAX) < p) {
                // p의 확률로 1부터 10 사이의 랜덤한 자연수, 1-p의 확률로 INT_MAX
                weight = (rand() % 10) + 1;
                graph.addEdge(i, j, weight);
            }
        }
    }
    // Minimum Spanning Tree 출력
    graph.primMST();

    return 0;
}
