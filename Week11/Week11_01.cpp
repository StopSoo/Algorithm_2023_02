// Q. 첫 줄에는 정점의 개수, 간선의 개수, 탐색을 시작할 정점의 번호를 입력 받고, 다음 줄부터는 간선이 연결하는 두 정점의 번호가 주어진다.
//    즉, 각 정점은 1부터 정점의 개수까지의 서로 다른 자연수로 번호가 매겨진다고 가정한다.
//    그래프는 무방향 그래프라 가정한다. 이렇게 입력 받은 정보를 인접리스트 형태로 저장한 후,
//    DFS(Depth-First Search) 탐색한 결과와 BFS(Breadth-First Search)로 탐색한 결과를 각각 출력하는 프로그램을 작성하세요.
//    출력은 방문하는 정점의 번호를 순서대로 출력하면 됩니다.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool visited[100];    // 방문 배열

void DFS(vector<int> *list, int startNode) {
    visited[startNode] = true;  // 시작 노드 방문 체크
    cout << startNode << " ";

    for (int i = 0; i < list[startNode].size(); i++) {
        int next = list[startNode][i];
        if (!visited[next]) {
            DFS(list, next);
        }
    }
}

void BFS(vector<int> *list, int startNode) {
    vector<int> searchList; // 방문 결과 리스트
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);
    searchList.push_back(startNode);

    while (!q.empty()) {
        int current = q.front();    // 큐의 맨 앞 원소 반환
        q.pop();    // 큐의 맨 앞 원소 삭제

        for (int i = 0; i < list[current].size(); i++) {
            int next = list[current][i];
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
                searchList.push_back(next);
            }
        }
    }
    // 출력
    for (int i = 0; i < searchList.size(); i++)
        cout << searchList[i] << " ";
    cout << endl;
}

int main() {
    // 변수 선언과 입력
    int v, e, s;    // 정점 개수, 간선 개수, 탐색을 시작할 정점의 번호
    cin >> v >> e >> s;
    vector<int> list[v+1];    // 인접 리스트 선언 및 초기화
    for (int i = 0; i < e; i++) {
        int n1, n2;
        cin >> n1 >> n2;
        // 무방향 그래프이므로
        list[n1].push_back(n2);
        list[n2].push_back(n1);
    }
    // 함수 실행
    fill(visited, visited + v + 1, false);
    cout << "DFS : ";
    DFS(list, s);
    cout << endl;

    fill(visited, visited + v + 1, false);
    cout << "BFS : ";
    BFS(list, s);

    return 0;
}