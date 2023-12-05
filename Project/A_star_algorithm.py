import random

# 부스 체험 시간 배열
timeWeight = [1, 6, 2, 7, 4, 8, 9, 10, 5, 2, 3, 8, 4, 6, 9, 10, 7, 1, 8, 5]
# 부스 방문 여부 체크 배열
isVisited = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

# 부스 간 이동 소요 시간
movingWeightMatrix = [
    [0, 4, 5, 2, 4, 3, 4, 5, 5, 3, 3, 5, 1, 2, 2, 5, 3, 2, 2, 2],
    [4, 0, 3, 4, 3, 3, 4, 4, 5, 2, 1, 1, 5, 5, 5, 2, 2, 2, 1, 4],
    [5, 3, 0, 3, 3, 1, 2, 1, 2, 2, 3, 4, 1, 4, 1, 3, 5, 2, 4, 5],
    [2, 4, 3, 0, 1, 5, 4, 5, 2, 2, 2, 5, 2, 2, 4, 1, 2, 3, 2, 2],
    [4, 3, 3, 1, 0, 2, 1, 4, 3, 4, 3, 1, 3, 3, 5, 2, 3, 3, 2, 3],
    [3, 3, 1, 5, 2, 0, 5, 2, 5, 2, 5, 5, 2, 1, 2, 2, 3, 5, 5, 3],
    [4, 4, 2, 4, 1, 5, 0, 1, 1, 4, 1, 3, 4, 1, 2, 2, 2, 1, 2, 3],
    [5, 4, 1, 5, 4, 2, 1, 0, 3, 2, 2, 5, 1, 1, 5, 4, 4, 2, 3, 1],
    [5, 5, 2, 2, 3, 5, 1, 3, 0, 4, 4, 3, 4, 1, 3, 3, 3, 3, 1, 4],
    [3, 2, 2, 2, 4, 2, 4, 2, 4, 0, 1, 4, 3, 4, 1, 5, 1, 2, 1, 3],
    [3, 1, 3, 2, 3, 5, 1, 2, 4, 1, 0, 3, 3, 1, 1, 3, 4, 3, 1, 5],
    [5, 1, 4, 5, 1, 5, 3, 5, 3, 4, 3, 0, 2, 5, 5, 5, 4, 2, 1, 2],
    [1, 5, 1, 2, 3, 2, 4, 1, 4, 3, 3, 2, 0, 4, 5, 5, 5, 2, 4, 2],
    [2, 5, 4, 2, 3, 1, 1, 1, 1, 4, 1, 5, 4, 0, 1, 3, 1, 3, 5, 5],
    [2, 5, 1, 4, 5, 2, 2, 5, 3, 1, 1, 5, 5, 1, 0, 3, 5, 3, 2, 1],
    [5, 2, 3, 1, 2, 2, 2, 4, 3, 5, 3, 5, 5, 3, 3, 0, 3, 1, 3, 3],
    [3, 2, 5, 2, 3, 3, 2, 4, 3, 1, 4, 4, 5, 1, 5, 3, 0, 3, 1, 4],
    [2, 2, 2, 3, 3, 5, 1, 2, 3, 2, 3, 2, 2, 3, 3, 1, 3, 0, 5, 4],
    [2, 1, 4, 2, 2, 5, 2, 3, 1, 1, 1, 1, 4, 5, 2, 3, 4, 4, 0, 2],
    [2, 4, 5, 2, 3, 3, 3, 1, 4, 3, 5, 2, 2, 5, 1, 3, 4, 4, 2, 0]
]
movingWeightMatrix_len = len(movingWeightMatrix)

# 부스 간 이동 소요 시간 행렬을 기반으로 인접 리스트를 생성하여 반환
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

resultAdjList = adjlist(movingWeightMatrix)
print(resultAdjList)

# 휴리스틱 함수 - 시간 내에 최대 개수의 부스 돌기
# def heuristic(adjList, givenTime):
#   route = []  # 최종 경로
#   open = []
#   close = set()
#   totalWeight = 0  # g(n)
#   expectedWeights = []  # h(n)
#   # 1 ~ 사용자가 입력한 시간의 절반 중 랜덤으로 h(n) 값 설정
#   print('# h(n) 출력 :', end=' ')
#   for i in range(20):
#     expectedWeights.append(random.randrange(1, int(givenTime / 2)))
#     print(expectedWeights[i], end=' ')
#   print()
#   print()

#   while totalWeight <= givenTime and len(close) < len(adjList):
#     nowNodeIndex = min(range(len(timeWeight)), key=lambda i: timeWeight[i])
#     neighbors = adjList[nowNodeIndex + 1]
#     print('neighbors : ', neighbors)

#     compareValue = {}  # g(n) + h(n) 값을 비교하기 위함
#     for neighbor, weight in neighbors.items():
#       if neighbor not in close:
#         compareValue[neighbor] = weight + expectedWeights[neighbor - 1]
#     print('compareValue : ', compareValue)

#     if not compareValue:
#       break

#     nextNode = min(compareValue, key=compareValue.get)
#     open.append(nextNode)
#     totalWeight += timeWeight[nextNode - 1] + movingWeightMatrix[nowNodeIndex][nextNode - 1]
#     route.append(nextNode)
#     close.add(nextNode)
#     isVisited[nextNode - 1] = 1
#     print('현재 부스 \'' + str(nextNode) + '\'번을 이용 중입니다.')

#   return route

# route = heuristic(resultAdjList, 30)
# print(route)

# 시작 노드가 timeWeight의 최소값을 가지는 노드
def heuristic(adjList, givenTime):
    route = []  # 최종 경로
    open = []
    close = set()
    totalWeight = 0  # g(n)
    expectedWeights = []  # h(n)
    # 1 ~ 사용자가 입력한 시간의 절반 중 랜덤으로 h(n) 값 설정
    print('# h(n) 출력 :', end=' ')
    for i in range(20):
        expectedWeights.append(random.randrange(1, int(givenTime / 2)))
        print(expectedWeights[i], end=' ')
    print()
    print()

    # 시작 노드 설정: timeWeight 배열에서 최소값의 인덱스를 찾아서 사용
    startNodeIndex = timeWeight.index(min(timeWeight))
    open.append(startNodeIndex + 1)  # Adjusting index to start from 1
    current_node = startNodeIndex + 1

    while totalWeight <= givenTime and len(close) < len(adjList):
        neighbors = adjList[current_node]
        print('neighbors : ', neighbors)

        compareValue = {}  # g(n) + h(n) 값을 비교하기 위함
        for neighbor, weight in neighbors.items():
            if neighbor not in close:
                compareValue[neighbor] = weight + expectedWeights[neighbor - 1]
        print('compareValue : ', compareValue)

        if not compareValue:
            break

        nextNode = min(compareValue, key=compareValue.get)
        open.append(nextNode)
        totalWeight += timeWeight[nextNode - 1] + movingWeightMatrix[current_node - 1][nextNode - 1]
        route.append(nextNode)
        close.add(nextNode)
        current_node = nextNode
        isVisited[nextNode - 1] = 1
        print('현재 부스 \'' + str(nextNode) + '\'번을 이용 중입니다.')

    return route

route = heuristic(resultAdjList, 30)
print(route)