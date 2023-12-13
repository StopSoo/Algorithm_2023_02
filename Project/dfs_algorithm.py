import time
import sys
## 메모이제이션 씀!!

def dfs(graph, current, visited, path, distance, max_nodes, limit_distance, memo):
    # 이미 방문한 상태인지 확인
    if (current, tuple(visited)) in memo:
        return memo[(current, tuple(visited))]

    # 제한된 거리 내에서 노드 개수가 더 큰 경로를 찾으면 max_node 업데이트
    if distance <= limit_distance and len(path) > max_nodes[0]:
        max_nodes[0] = len(path)
        max_nodes[1] = distance
        max_nodes[2] = path.copy()

    # 이웃 노드 탐색
    for neighbor in graph[current]: # 현재 노드의 이웃 노드 하나씩 순회
        if not visited[neighbor - 1] and distance + graph[current][neighbor] <= limit_distance:
            # 이웃 노드가 방문되지 않았고, 현재까지의 거리에 이웃 노드까지의 가중치를 더한 값이 제한 거리를 초과하지 않을 경우
            visited[neighbor - 1] = True # 노드 방문 표시
            path.append(neighbor) # 현재까지의 경로에 노드 추가
            # 메모이제이션을 활용하여 중복 계산 피하기
            dfs(graph, neighbor, visited, path, distance + graph[current][neighbor], max_nodes, limit_distance, memo)
            visited[neighbor - 1] = False
            path.pop()

    # 현재 상태의 결과를 메모이제이션에 저장
    memo[(current, tuple(visited))] = (max_nodes[0], max_nodes[1], max_nodes[2].copy())
    return memo[(current, tuple(visited))]

# 주어진 거리 제한 내에서 최대 노드 수를 찾음
def find_max_nodes_within_distance(graph, start_node, limit_distance, memo):
    visited = [False] * len(graph) # 방문 여부를 나타내는 리스트 초기화
    visited[start_node - 1] = True # 시작 노드를 방문했다고 표시
    path = [start_node] # 시작 노드를 경로에 추가
    max_nodes = [0, 0, []] # 최대 노드 수, 총 거리, 경로를 저장하는 리스트 초기화
    dfs(graph, start_node, visited, path, 0, max_nodes, limit_distance, memo) # DFS 함수 호출하여 최대 노드 수 찾기

    return max_nodes

def do_dfs(limit_time, memo):
    # 동아리 정보
    node_names = {
        1: "DUSSA (통계조사연구회)",
        2: "동국대학교 교지 편집 위원회",
        3: "FC 엘레펜테",
        4: "그리고그림",
        5: "ROTC",
        6: "프론티어",
        7: "렛츠무드",
        8: "기무회",
        9: "카페인",
        10: "LOTUS",
        11: "젊은새이웃",
        12: "ODC",
        13: "음샘",
        14: "손짓사랑회",
        15: "동굴탐험연구회",
        16: "MECS",
        17: "선무부",
        18: "페인터즈",
        19: "코티스트",
        20: "AJAX"
    }

    # 가중치 행렬
    # 인접 리스트를 만들기 위한 가중치 행렬
    origin_weight_matrix = [
        [0, 5, 6, 3, 5, 4, 5, 6, 6, 4, 4, 6, 2, 3, 3, 6, 4, 3, 3, 3],
        [10, 0, 9, 10, 9, 9, 10, 10, 11, 8, 7, 7, 11, 11, 11, 8, 8, 8, 7, 10],
        [7, 5, 0, 5, 5, 3, 4, 3, 4, 4, 5, 6, 3, 6, 3, 5, 7, 4, 6, 7],
        [9, 11, 10, 0, 8, 12, 11, 12, 9, 9, 9, 12, 9, 9, 11, 8, 9, 10, 9, 9],
        [8, 7, 7, 5, 0, 6, 5, 8, 7, 8, 7, 5, 7, 7, 9, 6, 7, 7, 6, 7],
        [11, 11, 9, 13, 10, 0, 13, 10, 13, 10, 13, 13, 10, 9, 10, 10, 11, 13, 13, 11],
        [13, 13, 11, 13, 10, 14, 0, 10, 10, 13, 10, 12, 13, 10, 11, 11, 11, 10, 11, 12],
        [15, 14, 11, 15, 14, 12, 11, 0, 13, 12, 12, 15, 11, 11, 15, 14, 14, 12, 13, 11],
        [10, 10, 7, 7, 8, 10, 6, 8, 0, 9, 9, 8, 9, 6, 8, 8, 8, 8, 6, 9],
        [5, 4, 4, 4, 6, 4, 6, 4, 6, 0, 3, 6, 5, 6, 3, 7, 3, 4, 3, 5],
        [6, 4, 6, 5, 6, 8, 4, 5, 7, 4, 0, 6, 6, 4, 4, 6, 7, 6, 4, 8],
        [13, 9, 12, 13, 9, 13, 11, 13, 11, 12, 11, 0, 10, 13, 13, 13, 12, 10, 9, 10],
        [5, 9, 5, 6, 7, 6, 8, 5, 8, 7, 7, 6, 0, 8, 9, 9, 9, 6, 8, 6],
        [8, 11, 10, 8, 9, 7, 7, 7, 7, 10, 7, 11, 10, 0, 7, 9, 7, 9, 11, 11],
        [11, 14, 10, 13, 14, 11, 11, 14, 12, 10, 10, 14, 14, 10, 0, 12, 14, 12, 11, 10],
        [15, 12, 13, 11, 12, 12, 12, 14, 13, 15, 13, 15, 15, 13, 13, 0, 13, 11, 13, 13],
        [10, 9, 12, 9, 10, 10, 9, 11, 10, 8, 11, 11, 12, 8, 12, 10, 0, 10, 8, 11],
        [3, 3, 3, 4, 4, 6, 2, 3, 4, 3, 4, 3, 3, 4, 4, 2, 4, 0, 6, 5],
        [10, 9, 12, 10, 10, 13, 10, 11, 9, 9, 9, 9, 12, 13, 10, 11, 12, 12, 0, 10],
        [7, 9, 10, 7, 8, 8, 8, 6, 9, 8, 10, 7, 7, 10, 6, 8, 9, 9, 7, 0]
    ]

    matrix_len = 20  # 적절한 크기로 설정

    # 가중치 행렬을 원하는 크기로 자르기
    weight_matrix = [row[:matrix_len] for row in origin_weight_matrix[:matrix_len]]

    def weight_matrix_to_adj_list(matrix):
        graph = {}
        for i in range(len(matrix)):
            # 노드 이름을 1, 2, 3, ...으로 부여
            node = i + 1
            neighbors = {}
            for j in range(len(matrix[i])):
                if matrix[i][j] != 0:
                    # 인접한 노드도 숫자로 부여
                    neighbor = j + 1
                    weight = matrix[i][j]
                    neighbors[neighbor] = weight
            graph[node] = neighbors
        return graph

    # 가중치 행렬을 기반으로 인접 리스트 생성
    adj_list = weight_matrix_to_adj_list(weight_matrix)

    # 시작 시간
    start_time = time.time()

    # 시작 노드
    start_node = 1
    # 제한 거리
    limit_distance = limit_time

    # 최대 노드 수를 방문하는 함수 호출
    max_nodes = find_max_nodes_within_distance(adj_list, start_node, limit_distance, memo)

    # 종료 시간
    end_time = time.time()

    # 실행 시간 계산
    execution_time = end_time - start_time

    # 결과 출력
    start_node_name = node_names[start_node]
    shortest_path_names = ' -> '.join([node_names[node] for node in max_nodes[2]])

    print(f"시작 노드 {start_node_name}에서 제한 거리 {limit_distance} 내에서의 최대 노드 방문 수 : {max_nodes[0]}개")
    print(f"경로: {shortest_path_names}")
    print(f"총 거리: {max_nodes[1]}")

    # 실행 시간 출력
    if execution_time < 60:
        print(f"Execution Time: {execution_time:.5f}초")
    else:
        execution_time_in_minutes = execution_time // 60
        remaining_seconds = execution_time % 60
        print(f"Execution Time: {int(execution_time_in_minutes)}분 {int(remaining_seconds)}초")
