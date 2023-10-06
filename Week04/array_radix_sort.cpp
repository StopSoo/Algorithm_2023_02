// Q. 정렬하려는 배열의 크기 N( 30000 > N >= 5000 )을 입력 받아, 문제 1번과 동일한 방법으로 데이터 A, 데이터 B, 데이터 C를 생성하고,
//    이 데이터 배열 A, B, C 각각에 대해 Bucket Sort 기반 Radix Sort를 이용해 오름차순으로 정렬시켜주는 프로그램을 작성하시오.
//    이 때, 정렬된 결과 뿐만 아니라 정렬 과정에서의 데이터비교 연산회수와 자료이동 연산회수 또한 아래의 입출력 예제와 같이 출력되어야 한다.
//    (버킷이 아닌 각 자리 숫자 단순 비교하여 Radix Sort 수행할 시 점수 없음)
#include <iostream>
#include <time.h>
using namespace std;

template <typename itemType>
struct node {
    itemType value;
    node* next;
};
 
typedef node<int>* node_pointer;    // itemType을 int로 가정하고 선언

node_pointer TABLE[10], x, z, temp; // TABLE : bucket

template <typename itemType>
void radixSort(itemType *a, int n, unsigned int &c, unsigned int &m) {
    // cipher : 입력 데이터의 자릿수
    // z : list의 끝을 확인하기 위한 노드 포인터 (NULL에 해당)
    /* radix_mod = 10 이면 radix는 a[j]의 일의 자리수
       radix_mod = 100 이면 radix는 a[j]의 십의 자리수
       => 버킷의 인덱스 */
    int i, j, cnt, radix, radix_mod = 10, cipher = 0;
    i = n;

    while(i > 0) {  // 입력 데이터의 자릿수 체크
        i = i / 10;
        cipher++;
    }

    for(i = 0; i < cipher; i++) {
        for(j = 0; j < n; j++) {
            cnt = 0;
            radix = (a[j] % radix_mod) / (radix_mod / 10);

            temp = new node<itemType>;
            temp->value = a[j];
            temp->next = z;
            if(TABLE[radix] == z) { // 값이 하나도 없다면
                TABLE[radix] = temp;
                m++;    // 자료 이동 연산
            } else {    // 값이 하나라도 있다면
                x = TABLE[radix];
                while(x->next != z) {   // 끝까지 가기
                    x = x->next;
                }
                x->next = temp;
                m++;    // 자료 이동 연산
            }
        }

        for(j = 0; j < 10; j++) {   // bucket 돌기
            if(TABLE[j] != z) {
                c++;    // 데이터 비교 연산
                x = TABLE[j];
                while(x != z) {
                    c++;    // 데이터 비교 연산
                    a[cnt++] = x->value;
                    m++;    // 자료 이동 연산
                    temp = x; // 메모리에서 노드를 삭제하기 위해 임시 저장
                    x = x->next;
                    delete temp; // 배열에 이미 넣은 노드를 메모리에서 삭제
                }
            }
            TABLE[j] = z;
            m++;    // 자료 이동 연산
        }
        radix_mod *= 10;
    }
}

int main() {
    // 1. 배열 A, B, C 만들기
    int N;  // 배열의 크기
    cin >> N;   // 사용자로부터 배열의 크기 입력 받기

    // 세 배열 생성 및 크기 동적 할당
    int *A = new int[N];
    int *B = new int[N];
    int *C = new int[N];
    int x, y;   // 랜덤 배열을 위한 인덱스

    for (int i = 0; i < N; i++) {   // 배열 B 초기화
        B[i] = i + 1;
    }
    srand((unsigned int)time(0));   // 배열 B 랜덤 배치를 위한 시드값 설정

    int value = N;
    for (int i = 0; i < N; i++) {   // 배열 A 초기화: 1부터 N까지 내림차순으로 push
        A[i] = value--;
    }
    for (int i = 0; i < N; i++) {   // 배열 B 재배치: 1부터 N까지의 숫자들이 "중복 없이" 랜덤하게 재배치된 데이터 배열
        while (true) {
            x = rand() % N;
            y = rand() % N;
            if (x != 0 && y != 0)   // 인덱스 0이 나오면 안되므로
                break;
        }

        swap(B[x], B[y]);
    }
    for (int i = 0; i < N; i++) {   // 배열 C 초기화: 1부터 N까지의 숫자들이 "중복을 허용"하며 랜덤하게 배치된 배열
        C[i] = rand() % N;
        while (C[i] == 0) { // 원소가 0일 경우 다시 설정
            C[i] = rand() % N;
        }
    }

    // 2. 배열 A, B, C에 대해 기수 정렬을 이용해 오름차순으로 정렬하기
    cout << "* Before Sorting *" << endl;
    cout << "A : ";
    for (int i = 0; i < 20; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    cout << "B : ";
    for (int i = 0; i < 20; i++) {
        cout << B[i] << " ";
    }
    cout << endl;
    cout << "C : ";
    for (int i = 0; i < 20; i++) {
        cout << C[i] << " ";
    }
    cout << endl;

    cout << "* After Sorting *" << endl;
    unsigned int compare_A = 0, move_A = 0;
    radixSort(A, N, compare_A, move_A);
    cout << "SortedData_A: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << A[i] << " ";
    }
    cout << endl;

    unsigned int compare_B = 0, move_B = 0;
    radixSort(B, N, compare_B, move_B);
    cout << "SortedData_B: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << B[i] << " ";
    }
    cout << endl;

    unsigned int compare_C = 0, move_C = 0;
    radixSort(C, N, compare_C, move_C);
    cout << "SortedData_C: ";
    for (int i = 0; i < 20; i++) {  // 정렬된 데이터들을 20개만 출력하기
        cout << C[i] << " ";
    }
    cout << endl;

    // 데이터 비교 연산 횟수와 자료 이동 연산 횟수 출력하기
    cout << "Compare_Cnt_A: " << compare_A << ", DataMove_Cnt_A: " << move_A << endl;
    cout << "Compare_Cnt_B: " << compare_B << ", DataMove_Cnt_B: " << move_B << endl;
    cout << "Compare_Cnt_C: " << compare_C << ", DataMove_Cnt_C: " << move_C << endl;

    // 메모리 해제
    delete [] A;
    delete [] B;
    delete [] C;
    return 0;
}

