import sys
import time

def do_floydwarhall():
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

    # weight_matrix를 원하는 크기로 자르기
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

    # 가중치 행렬을 기반으로 인접 리스트 생성
    def adjlist(matrix):
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

    def floyd_warshall(matrix):
        for k in range(matrix_len):
            for i in range(matrix_len):
                for j in range(matrix_len):
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j])

    # 가중치 행렬을 기반으로 인접 리스트 생성
    adj_list = adjlist(weight_matrix)

    # 시작 시간
    start_time = time.time()

    # 플로이드-워셜 알고리즘 적용
    floyd_warshall(weight_matrix)

    # 시작 노드
    start_node = 1

    # 시작 노드 DUSSA (통계조사연구회)에서 모든 노드를 한 번씩 방문하는 경우의 최단 거리 및 거리 합 계산
    total_time = 0

    # Set the end_node to the last node to visit all nodes
    end_node = matrix_len

    print(f"시작 노드 {node_names[start_node]}에서 모든 노드를 경유할 때의 최단 경로 및 거리")

    print("최단 경로:")
    path = [start_node]
    current_node = start_node

    for _ in range(end_node - 1):  # Iterate only once, visiting all nodes
        next_node = min((neighbor for neighbor in adj_list[current_node] if neighbor not in path), key=lambda x: weight_matrix[current_node - 1][x - 1])
        path.append(next_node)
        current_node = next_node

    for i, node_index in enumerate(path):
        print(node_names[node_index], end="")
        if node_index != path[-1]:
            print(" -> ", end="")
            edge_weight = weight_matrix[path[i] - 1][path[i + 1] - 1]
            total_time += edge_weight
    print(f"\n최소 시간: {total_time}")

    # 종료 시간
    end_time = time.time()

    # 실행 시간 계산
    execution_time = end_time - start_time

    # 실행 시간 출력
    if execution_time < 60:
        print(f"Execution Time: {execution_time:.5f}초")
    else:
        execution_time_in_minutes = execution_time // 60
        remaining_seconds = execution_time % 60
        print(f"Execution Time: {int(execution_time_in_minutes)}분 {int(remaining_seconds)}초")
