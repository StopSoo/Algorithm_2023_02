// Q. N(>500) 개의 물건들이 선반에 일렬로 놓여져 있다고 가정하자. 이 물건들을 무게 기준으로 오름차순으로 정렬시킬 때 이동되는 물건들의 무게 합을 최소로 만들고자 한다.
//    예를 들어, 무게가 5와 3인 두 개의 물건 위치를 서로 바꾸는 경우, 무게가 가벼운 것을 먼저 내려 놓고, 무거운 것을 빈 자리로 이동시킨 뒤, 내려놓았던 가벼운 것을 다시 무거운 것이 있었던 빈 자리로 이동시키는 방법 (총 이동된 물건들의 무게 합 = 3+5+3 =11)이
//    무거운 물건을 먼저 내려 놓는 방법 (총 이동된 물건들의 무게 합 = 5+3+5 =13) 에 비해 보다 효율적일 것이다.
//    이러한 이동 물건들의 무게 합 최소화 전략이 반영될 수 있도록 앞의 3번 문제에서 작성한 Bubble Sort 함수 프로그램을 수정해 작성하고, 어떻게 수정하였는지 설명하시오.
//    또한, N의 값을 입력 받은 뒤 Insertion Sort, 수정된 Bubble Sort, Shell Sort 각각에 대해 아래 입출력 예제와 같이 이동된 물건들의 무게 합을 출력해주는 프로그램을 작성하시오.
#include <iostream>
using namespace std;

// 버블 정렬 함수
int Bubble(int sorted, int *a)  // 정렬 여부, 값을 비교하고자 하는 배열의 포인터
{
    int temp;   // 임시 변수
    if (*a > *(a+1)) {    // 앞에 있는 원소 값이 뒤에 있는 원소 값보다 크면 swap
        temp = *a;
        *a = *(a+1);
        *(a+1) = temp;
        sorted = false;
    }
    return sorted;  // 정렬 여부 반환
}

int bubbleSort(int *a, int n)    // 정렬하고자 하는 배열, 배열의 크기
{
    int i, j, Sorted;   // 제어 변수, 정렬 여부 변수
    Sorted = false; // 정렬 여부
    int total_weight = 0;   // 물건들의 무게의 합
    while (!Sorted) {
        Sorted = true;
        for (i = 0; i < n; i++) {
            if (i == n-1) {     // 마지막 원소까지 정렬하면 반복문 종료
                Sorted = true;
                break;
            }
            for (j = 0; j < n-i-1; j++) {
                Sorted = Bubble(Sorted, &a[j]);
                if (Sorted == false) {  // 정렬이 되었다면
                    // 이동되는 물건들의 최소 무게 합을 총 무게 합에 더해준다.
                    total_weight += (min(a[j], a[j+1])*2 + max(a[j], a[j+1]));
                }
            }
        }
    }
    return total_weight;
}

// 삽입 정렬 함수
int insertion(int *a,  int n)    // 매개변수 : 배열, 배열의 크기
{
    int i, j;   // 제어 변수
    int v;  // 타겟 물건
    int total_weight = 0;   // 물건들의 무게의 합
    for (i = 1; i < n; i++)
    {
        v = a[i];
        for (j = i-1; j >=0; j--) {
            if (a[j] > v) {
                // swap 개념인데 ... 수정 필요 !!
                a[j+1] = a[j];
                // 이동되는 물건들의 최소 무게 합을 총 무게 합에 더해준다.
                // 삽입 정렬이어도 두 물건씩 서로 바꾼다는 전제 하에 !
                total_weight += (min(a[j], v)*2 + max(a[j], v));
            } else break;
        }
    }
    return total_weight;
}

// 쉘 정렬 함수
int shellSort(int *a, int n) // 정렬하려는 배열, 배열의 크기
{
    int i, j, h;
    int temp;
    h = 1;  // 부분 배열 내 원소들이 떨어진 거리 초기화
    int total_weight = 0;   // 물건들의 무게의 합
    while (h < n / 3) {
        h = 3 * h + 1;
    }
    do {
        for (i = h; i < n; i++)
        {
            temp = a[i];
            j = i;
            while (a[j-h] > temp)
            {
                a[j] = a[j-h];
                j -= h;
                if (j < h-1)
                    break;
            }
            a[j] = temp;
        }
        h = h / 2;  // 부분 배열 내 거리 재설정
    } while (h > 0);

    return total_weight;
}

int main() {
    // N을 입력 받고 N개의 물건들의 무게를 담는 배열 만들기
    int N;  // 배열의 크기
    cin >> N;   // 사용자로부터 배열의 크기 입력 받기

    // 배열 생성 및 동적 할당
    int *arr = new int[N];
    for (int i = 0; i < N; i++) {   // 배열 arr를 물건의 무게로 초기화
        arr[i] = N - (i + 1) + 1;
    }

    // 무게 합에 대한 정렬 별 변수 선언
    int total_weight_bubble;   // 버블 정렬 - 물건들의 무게의 최종 합
    int total_weight_insertion;   // 버블 정렬 - 물건들의 무게의 최종 합
    int total_weight_shell;   // 버블 정렬 - 물건들의 무게의 최종 합

    // 배열 arr에 대해 정렬 별 계산
    total_weight_bubble = bubbleSort(arr, N);
    total_weight_insertion = insertion(arr, N);
    total_weight_shell = shellSort(arr, N);

    // 이동된 물건들의 무게 합을 각각의 정렬에 대해 출력하기
    cout << "Insertion Sort : " <<  total_weight_insertion << endl;
    cout << "Bubble Sort : " <<  total_weight_bubble << endl;
    cout << "Shell Sort : " <<  total_weight_shell << endl;

    // 메모리 해제
    delete [] arr;
    return 0;
}
