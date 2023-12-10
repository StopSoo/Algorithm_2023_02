from collections import deque
import time

def bfs(graph, start, limit_distance):
    queue = deque([(start, [start], 0)])  # (현재 노드, 경로 리스트, 현재까지의 거리)

    max_nodes = ([], 0)  # (경로 리스트, 거리)
    visited = {}

    def state_hash(current, path):
        return current * 100 + hash(tuple(path))

    while queue:
        current, path, distance = queue.popleft()   # 큐에서 하나씩 빼서 값을 저장

        state = state_hash(current, path)
        if state in visited and visited[state] >= distance: # visited에 노드가 존재할 경우 pass
            continue

        visited[state] = distance

        if distance <= limit_distance and len(path) > len(max_nodes[0]):
            max_nodes = (path, distance)

        for neighbor, weight in graph[current].items():
            # 방문하지 않았고, 현재까지의 최대 거리보다 누적 거리가 크거나 같은 경우에만 큐에 추가
            if neighbor not in path and distance + weight <= limit_distance and distance + weight >= max_nodes[1]:
                queue.append((neighbor, path + [neighbor], distance + weight))

    return max_nodes

def find_max_nodes_within_distance(graph, start_node, limit_distance):
    return bfs(graph, start_node, limit_distance)

def do_bfs(limit_time):
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

    def weightMatrixToAdjList(matrix):
        return {i: {j + 1: weight for j, weight in enumerate(row) if weight != 0} for i, row in enumerate(matrix, start=1)}

    # 가중치 행렬을 기반으로 인접 리스트 생성
    adj_list = weightMatrixToAdjList(weight_matrix)

    # 시작 시간
    start_time = time.time()

    # 시작 노드
    start_node = 1
    # 제한 거리
    limit_distance = limit_time

    # bfs 함수 호출
    max_nodes = bfs(adj_list, start_node, limit_distance)

    # 종료 시간
    end_time = time.time()

    # 실행 시간 계산
    execution_time = end_time - start_time

    # 출력
    start_node_name = node_names[start_node]
    shortest_path_names = ' -> '.join([node_names[node] for node in max_nodes[0]])

    print(f"시작 노드 {start_node_name}에서 제한 거리 {limit_distance} 내에서의 최대 노드 방문 수: {len(max_nodes[0])}개")
    print(f"경로: {shortest_path_names}")
    print(f"총 거리: {max_nodes[1]}")

    # 실행 시간 출력
    if execution_time < 60:
        print(f"Execution Time: {execution_time:.2f}초")
    else:
        execution_time_in_minutes = execution_time // 60
        remaining_seconds = execution_time % 60
        print(f"Execution Time: {execution_time_in_minutes}분 {remaining_seconds:.2f}초")

do_bfs(40)