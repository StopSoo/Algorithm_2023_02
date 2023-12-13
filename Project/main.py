import os
import dfs_algorithm, bfs_algorithm , A_star_algorithm
import floydwarshall_algorithm, dijkstra_algorithm

print("아래 두 가지 케이스 중 하나를 선택해주세요.")
x = int(input("1. 주어진 시간 내 최대 개수의 부스 돌기 | 2. 모든 부스를 최소 시간 안에 돌기 : "))

def main():
    if x == 1:
        limit_time = int(input("제한 시간을 입력해주세요: "))
        print("\n[ DFS ]")
        memo={}
        dfs_algorithm.do_dfs(limit_time,memo)

        print("\n\n[ A* ]")
        A_star_algorithm.do_a_star(limit_time, 1)

        print("\n[ BFS ]")
        bfs_algorithm.do_bfs(limit_time)        

    elif x == 2:
        print("\n[ Floyd-Warshall ]")
        floydwarshall_algorithm.do_floydwarhall()

        print("\n\n[ A* ]")
        A_star_algorithm.do_a_star(0, 2)
        
        print("\n[ Dijkstra + Priority Queue + BackTracking ]")
        dijkstra_algorithm.do_dijkstra()

if __name__ == "__main__":
    main()