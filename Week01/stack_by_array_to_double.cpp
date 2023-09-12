// Q. 다음은 배열을 이용하는 스택(Stack1)의 구현 및 응용 예이다.
//    다양한 입력 데이터에 대해 아래 프로그램을 실행해보고, 어떤 기능을 하는 프로그램인지 생각해보세요.
//    정수가 아닌 double 입력에 대해 결과가 나오게 하려면 어떻게 수정해야 합니까?
#include <iostream>
using namespace std;

template <typename itemType>
class Stack1 {
private:
    itemType *stack; 	// 스택
    int p;	// 스택으로 구현된 배열의 인덱스
public:
    // 클래스의 생성자
    // stack을 디폴트 매개변수 값인 100 크기의 배열로 초기화하고, 배열의 인덱스 p를 0으로 초기화
    Stack1(int max=100) { stack = new itemType[max]; p = 0; }
    ~Stack1() { delete stack; }	// 클래스의 소멸자
    inline void push (itemType v) { stack[p++] = v; } // 현재 스택 인덱스에 값을 넣고 인덱스에 1 추가
    inline itemType pop() { return stack[--p]; } // 현재 스택 인덱스 값을 1 감소시키고 해당 인덱스 원소를 반환
    inline int empty() { return !p; } // 스택이 비어 있으면 true를, 비어 있지 않으면 false를 반환
};

int main() {
    char c;    // 사용자가 입력한 문자
    Stack1<double> acc(50); // 최대 크기 50의 배열 변수
    double x;    // 스택에 들어갈 원소를 담을 변수
    while ((c = cin.get()) != '\n') {    // 사용자가 입력한 문자가 개행 문자가 아닌 동안 반복
        x = 0;
        while (c == ' ')    // 받아온 문자 c가 ‘ ’이면 다음 문자를 받아옴
            cin.get(c);
        if (c == '+')    // ‘+’가 들어오면 스택의 윗부분부터 첫 번째 원소와 두 번째 원소를 더해서 x에 대입
            x = acc.pop() + acc.pop();
        if (c == '*')    // ‘*’가 들어오면 스택의 윗부분부터 첫 번째 원소와 두 번째 원소를 곱해서 x에 대입
            x = acc.pop() * acc.pop();
        while (c >= '0' && c <= '9') {    // c가 문자 ‘0’~’9’일 때
            x = 10 * x + (c - '0');    // c를 숫자로 바꾸고 해당 수식을 적용하며 x를 업데이트
            int n = 1;  // 소수점 아래 자릿수 체크
            if ((c = cin.get()) == '.') {   // 다음 문자를 받아왔는데 .일 경우
                while ((c = cin.get()) != ' ') {    // 한 수가 끝나기 전까지
                    x = x + pow(0.1, n) * (c-'0');  // 소수점 아래 자릿수를 만들어줌
                    n++;    // 자릿수 1 증가
                }
            }
        }
        acc.push(x); // 배열(스택) acc에 x를 삽입
    }
    cout << acc.pop() << '\n'; // 계산된 최종 결과를 배열(스택)에서 빼내 출력
}
