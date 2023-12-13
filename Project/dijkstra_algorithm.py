import heapq
import time

def do_dijkstra():
    INF = int(1e9)  # 무한을 의미하는 값으로 10억

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

    # weight_matrix를 원하는 크기로 자르기
    matrix_len = 20  # 적절한 크기로 설정
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


    # 다익스트라 알고리즘 : 시작 노드에서 모든 노드로의 최단 거리를 계산하는 함수
    def dijkstra(graph, start, memo, visited):
        if start in memo:
            return memo[start]

        # distance 딕셔너리 초기화
        distance = {node: INF for node in graph}
        distance[start] = 0

        q = [(0, start)]  # (거리, 노드)를 저장하는 우선 순위 큐

        while q: # 큐에 남아있는 노드가 없으면 끝
            current_dist, current_node = heapq.heappop(q) # 탐색할 노드와 거리 가져옴

            if distance[current_node] < current_dist:  # 기존에 있는 거리보다 길다면 고려할 필요성 없음
                continue

            visited |= 1 << (current_node - 1)  # 노드 방문 표시

            for neighbor, weight in graph[current_node].items():
                new_distance = current_dist + weight # 노드를 경유할 때 거리
                if new_distance < distance[neighbor]: # 알고 있는 거리보다 작으면
                    distance[neighbor] = new_distance # 새로 갱신
                    heapq.heappush(q, (new_distance, neighbor)) # 다음 인접 거리를 계산 하기 위해 큐에 삽입

        memo[start] = distance
        return distance


    # 백트래킹을 이용한 최단 경로 구하기
    def backtrack(graph, current, visited, path, distance, min_distance, min_path, memo):
        # 모든 노드를 방문한 경우
        if all(visited):
            # 현재까지의 경로가 찾은 최소 거리보다 짧으면 업데이트
            if distance < min_distance[0]:
                min_distance[0] = distance
                min_path[0] = path[:]
            return

        # 가지치기: 현재까지의 거리가 이미 찾은 최소 거리보다 크면 중단
        if distance >= min_distance[0]:
            return

        # 메모이제이션을 활용하여 중복 계산 최소화
        if tuple(visited) in memo:
            if distance >= memo[tuple(visited)]:
                return

        memo[tuple(visited)] = distance

        for neighbor in graph[current]:
            # 방문하지 않은 노드인 경우
            if not visited[neighbor - 1]:
                visited[neighbor - 1] = True
                path.append(neighbor)

                # 새로운 거리 계산
                new_distance = distance + graph[current][neighbor]
                # 재귀 호출을 통해 다음 노드로 이동
                backtrack(graph, neighbor, visited, path, new_distance, min_distance, min_path, memo)

                # 백트래킹: 방문한 상태를 원래대로 돌림
                visited[neighbor - 1] = False
                path.pop()

    # 가중치 행렬을 기반으로 인접 리스트 생성
    adj_list = adjlist(weight_matrix)

    # 시작 노드
    start_node = 1

    # 시작 시간
    start_time = time.time()

    # 시작 노드에서 모든 노드를 한 번씩 방문하는 경우의 최단 경로 계산
    for end_node in range(2, matrix_len+1):
        if end_node != start_node:
            # 시작 노드에서 각 노드로의 최단 거리 계산
            memo = {}
            visited = 0  # 모든 비트가 0으로 초기화
            distance_from_start = dijkstra(adj_list, start_node, memo, visited)

            # 백트래킹을 통해 최단 경로 찾기
            visited = [False] * matrix_len
            visited[start_node - 1] = True
            path = [start_node]
            min_time = [INF]
            min_path = [[]]
            backtrack(adj_list, start_node, visited, path, 0, min_time, min_path, memo)

    # 종료 시간
    end_time = time.time()

    # 실행 시간 계산
    execution_time = end_time - start_time

    # 결과 출력
    print(f"시작 노드 {node_names[start_node]}에서 모든 노드를 경유할 때의 최단 경로 및 거리")
    print("최단 경로:")
    for i, node_index in enumerate(min_path[0]):
        print(node_names[node_index], end="")
        # 마지막 요소가 아닌 경우에만 -> 출력
        if i < len(min_path[0]) - 1:
            print(" -> ", end="")
    print()

    print(f"최소 시간: {min_time[0]}")

    # 실행 시간 출력
    if execution_time < 60:
        print(f"Execution Time: {execution_time:.5f}초")
    else:
        execution_time_in_minutes = execution_time // 60
        remaining_seconds = execution_time % 60
        print(f"Execution Time: {int(execution_time_in_minutes)}분 {int(remaining_seconds)}초")

    