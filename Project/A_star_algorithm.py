import random

# 부스 이용 시간 딕셔너리 (부스 번호: 부스 이용 시간)
timeWeight = {
    1: 1,
    2: 6,
    3: 2,
    4: 7,
    5: 4,
    6: 8,
    7: 9,
    8: 10,
    9: 5,
    10: 2,
    11: 3,
    12: 8,
    13: 4,
    14: 6,
    15: 9,
    16: 10,
    17: 7,
    18: 1,
    19: 8,
    20: 5
}

# 부스 간 이동 소요 시간
movingWeightMatrix = [
    [float('inf'), 4, 5, 2, 4, 3, 4, 5, 5, 3, 3, 5, 1, 2, 2, 5, 3, 2, 2, 2],
    [4, float('inf'), 3, 4, 3, 3, 4, 4, 5, 2, 1, 1, 5, 5, 5, 2, 2, 2, 1, 4],
    [5, 3, float('inf'), 3, 3, 1, 2, 1, 2, 2, 3, 4, 1, 4, 1, 3, 5, 2, 4, 5],
    [2, 4, 3, float('inf'), 1, 5, 4, 5, 2, 2, 2, 5, 2, 2, 4, 1, 2, 3, 2, 2],
    [4, 3, 3, 1, float('inf'), 2, 1, 4, 3, 4, 3, 1, 3, 3, 5, 2, 3, 3, 2, 3],
    [3, 3, 1, 5, 2, float('inf'), 5, 2, 5, 2, 5, 5, 2, 1, 2, 2, 3, 5, 5, 3],
    [4, 4, 2, 4, 1, 5, float('inf'), 1, 1, 4, 1, 3, 4, 1, 2, 2, 2, 1, 2, 3],
    [5, 4, 1, 5, 4, 2, 1, float('inf'), 3, 2, 2, 5, 1, 1, 5, 4, 4, 2, 3, 1],
    [5, 5, 2, 2, 3, 5, 1, 3, float('inf'), 4, 4, 3, 4, 1, 3, 3, 3, 3, 1, 4],
    [3, 2, 2, 2, 4, 2, 4, 2, 4, float('inf'), 1, 4, 3, 4, 1, 5, 1, 2, 1, 3],
    [3, 1, 3, 2, 3, 5, 1, 2, 4, 1, float('inf'), 3, 3, 1, 1, 3, 4, 3, 1, 5],
    [5, 1, 4, 5, 1, 5, 3, 5, 3, 4, 3, float('inf'), 2, 5, 5, 5, 4, 2, 1, 2],
    [1, 5, 1, 2, 3, 2, 4, 1, 4, 3, 3, 2, float('inf'), 4, 5, 5, 5, 2, 4, 2],
    [2, 5, 4, 2, 3, 1, 1, 1, 1, 4, 1, 5, 4, float('inf'), 1, 3, 1, 3, 5, 5],
    [2, 5, 1, 4, 5, 2, 2, 5, 3, 1, 1, 5, 5, 1, float('inf'), 3, 5, 3, 2, 1],
    [5, 2, 3, 1, 2, 2, 2, 4, 3, 5, 3, 5, 5, 3, 3, float('inf'), 3, 1, 3, 3],
    [3, 2, 5, 2, 3, 3, 2, 4, 3, 1, 4, 4, 5, 1, 5, 3, float('inf'), 3, 1, 4],
    [2, 2, 2, 3, 3, 5, 1, 2, 3, 2, 3, 2, 2, 3, 3, 1, 3, float('inf'), 5, 4],
    [2, 1, 4, 2, 2, 5, 2, 3, 1, 1, 1, 1, 4, 5, 2, 3, 4, 4, float('inf'), 2],
    [2, 4, 5, 2, 3, 3, 3, 1, 4, 3, 5, 2, 2, 5, 1, 3, 4, 4, 2, float('inf')]
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

# 인접 리스트 생성
resultAdjList = adjlist(movingWeightMatrix)
# print(resultAdjList)

# 사용자가 1번을 선택했을 때 실행되는 함수
def heuristic1(adjList, givenTime):
    route = []  # 최종 경로
    open = []
    close = set()
    totalWeight = 0  # g(n)
    expectedWeights = []  # h(n)
    expectedWeights.append(0) # 부스 번호 맞추기 위해 리스트의 크기를 21로 설정
    # 1 ~ 사용자가 입력한 시간의 절반 중 랜덤으로 h(n) 값 설정
    print('# h(n) 출력 :', end=' ')
    for i in range(20):
        expectedWeights.append(random.randrange(1, int(givenTime / 2)))
        print(expectedWeights[i], end=' ')
    print()
    print()

    # 시작 노드 설정: timeWeight 배열에서 최소값의 인덱스를 찾아서 사용 -> 부스 체험 시간이 가장 짧은 부스를 먼저 방문
    startNodeIndex = list(timeWeight.keys())[list(timeWeight.values()).index(min(timeWeight))]
    totalWeight += timeWeight[startNodeIndex] # 부스 이용 시간 누적
    open.append(startNodeIndex)
    route.append(startNodeIndex)  # 방문 부스 리스트에 첫 번쨰로 방문하는 부스 번호 추가
    print('사용자가 첫 부스로 \'' + str(startNodeIndex) + '\'번을 방문하였습니다.')
    print()
    close.add(startNodeIndex) # 첫 부스 방문 종료

    currentNode = timeWeight[startNodeIndex]  # 현재 노드 값 저장
    currentNodeIndex = startNodeIndex  # 현재 노드 인덱스 초기화
    while totalWeight <= givenTime and len(close) < len(adjList):
        compareValue = {}  # g(n) + h(n) 값을 비교하기 위함 (매번 초기화됨)
        neighbors = adjList[currentNodeIndex]
        for neighbor, weight in neighbors.items():
            if neighbor not in close:
                compareValue[neighbor] = totalWeight + timeWeight[neighbor] + weight + expectedWeights[neighbor] # g(n) + h(n)을 계산하여 저장
            else: # 이미 방문한 노드는 고려하지 않도록 설정
                compareValue[neighbor] = float('inf')
        print('g(n) + h(n):', compareValue)

        if not compareValue:
            break

        nextNode = min(list(compareValue.values()))  # g(n)+h(n)의 최소값 계산

        print('다음 부스로 이동하기 위해 가중치를 계산 중입니다.')
        print('g(n) + h(n)의 최소 값은', nextNode, '입니다.')

        nextNodeIndex = list(timeWeight.keys())[list(compareValue.values()).index(nextNode)]
        print('다음 부스는', nextNodeIndex, '입니다.')
        print()
        if (totalWeight + nextNode > givenTime):  # 시간 초과 시 종료
            print('다음 부스 이용 시 시간이 초과되어 다음 부스 이동을 보류합니다.')
            print()
            break

        open.append(nextNodeIndex)
        totalWeight += timeWeight[nextNodeIndex] + adjList[currentNodeIndex][nextNodeIndex] # (다음 부스로의 이동 시간 + 다음 부스 이용 시간) 누적 (수정했음! 확인해야 함!)
        route.append(nextNodeIndex) # 방문 부스 리스트에 다음 부스 번호 추가
        close.add(nextNodeIndex)  # 다음 부스 방문 종료
        currentNodeIndex = nextNodeIndex # 현재 노드를 nextNode로 변경
        print('현재 부스 \'' + str(currentNodeIndex) + '\'번을 이용 중입니다.')

    return route


# 사용자가 2번을 선택했을 때 실행되는 함수
def heuristic2(adjList):
    route = []  # 최종 경로
    open = []
    close = set()
    totalWeight = 0  # g(n)
    expectedWeights = []  # h(n)
    expectedWeights.append(0) # 부스 번호 맞추기 위해 리스트의 크기를 21로 설정
    # 1~20 중 랜덤으로 h(n) 값 설정
    print('# h(n) 출력 :', end=' ')
    for i in range(20):
        expectedWeights.append(random.randrange(1, 20))
        print(expectedWeights[i], end=' ')
    print()
    print()

    startNodeIndex = 1  # 시작 노드 설정: 1번 부스를 먼저 방문한다고 가정
    totalWeight += timeWeight[startNodeIndex] # 부스 이용 시간 누적
    open.append(startNodeIndex)
    route.append(startNodeIndex)  # 방문 부스 리스트에 첫 번쨰로 방문하는 부스 번호 추가
    print('사용자가 첫 부스로 \'' + str(startNodeIndex) + '\'번을 방문하였습니다.')
    print()
    close.add(startNodeIndex) # 첫 부스 방문 종료

    currentNode = timeWeight[startNodeIndex]  # 현재 노드 값 저장
    currentNodeIndex = startNodeIndex  # 현재 노드 인덱스 초기화
    while len(close) < len(adjList):  # 모든 부스를 다 돌 때까지 반복
        compareValue = {}  # g(n) + h(n) 값을 비교하기 위함 (매번 초기화됨)
        neighbors = adjList[currentNodeIndex]
        for neighbor, weight in neighbors.items():
            if neighbor not in close:
                compareValue[neighbor] = totalWeight + timeWeight[neighbor] + weight + expectedWeights[neighbor] # g(n) + h(n)을 계산하여 저장
            else: # 이미 방문한 노드는 고려하지 않도록 설정
                compareValue[neighbor] = float('inf')
        print('g(n) + h(n):', compareValue)

        if not compareValue:
            break

        nextNode = min(list(compareValue.values()))  # g(n)+h(n)의 최소값 계산

        print('다음 부스로 이동하기 위해 가중치를 계산 중입니다.')
        print('g(n) + h(n)의 최소 값은', nextNode, '입니다.')

        nextNodeIndex = list(timeWeight.keys())[list(compareValue.values()).index(nextNode)]
        print('다음 부스는', nextNodeIndex, '입니다.')
        print()

        open.append(nextNodeIndex)
        totalWeight += timeWeight[nextNodeIndex] + adjList[currentNodeIndex][nextNodeIndex]
        route.append(nextNodeIndex) # 방문 부스 리스트에 다음 부스 번호 추가
        close.add(nextNodeIndex)  # 다음 부스 방문 종료
        currentNodeIndex = nextNodeIndex # 현재 노드를 nextNode로 변경
        print('현재 부스 \'' + str(currentNodeIndex) + '\'번을 이용 중입니다.')

    return route, totalWeight




# 사용자 입력 파트
print('아래 두 가지 케이스 중 하나를 선택해주세요.')
ansCase = input('1. 주어진 시간 내 최대 개수의 부스 돌기  |  2. 모든 부스를 최소 시간 안에 돌기 : ')
if ansCase == '1':
    ansTime = int(input('주어진 시간을 입력해주세요(단위: 분) : '))
    route = heuristic1(resultAdjList, ansTime)
    print('사용자가 입력한 시간 내 이동할 수 있는 부스 경로는', route, '입니다.')
else:
    route, ansTime = heuristic2(resultAdjList)
    print('사용자가 최소 시간으로 모든 부스를 방문할 수 있는 부스 경로는', route, '입니다.')
    print('최소 시간은 ' + str(ansTime) + '분입니다.')