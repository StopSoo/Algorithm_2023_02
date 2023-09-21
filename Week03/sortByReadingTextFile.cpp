// Q. 아래의 내용을 포함한 datafile.txt라는 Text 파일(문자 데이터 파일)을 파일 입력을 이용해 읽어 들이고,
//    읽어들인 Text 파일을 특수 문자와 공백을 기준으로 단어(word)로 분리한 뒤, 각 단어의 빈도 수를 구하도록 하시오.
//    그 뒤, 우선 빈도 수를 기준으로 내림차순 정렬하고, 만약 빈도 수가 같은 경우에는 Strcmp를 이용해서 단어의 ASCII코드 값을 기준으로 오름차순 정렬한 결과를 아래의 출력 예제와 같이 출력하는 프로그램을 작성하시오.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
using namespace std;

int main() {
    string line;    // 파일에서 읽어온 문장을 저장할 string 변수 선언
    list<string> words; // 구분한 단어들을 저장할 리스트 선언
    ifstream file("Week03/datafile.txt");  // 파일 읽어오기 -> 경로 수정할 것
    if (file.is_open()) {
        // 1. 파일에 저장되어 있는 텍스트를 불러와서 한 문장씩 받아 공백으로 구분 후 리스트에 저장
        while (getline(file, line)) {   // file에서 한 문장씩 받아와 string 변수 line에 저장
            stringstream ss(line);
            string word;
            while (ss >> word) words.push_back(word);   // 공백으로 문자열 구분
        }

        // 2. 리스트에 저장된 문자열들을 하나씩 불러와 특수문자 제거 후 리스트에 저장
        list<string>::iterator iter;    // 반복자 생성
        for (iter = words.begin(); iter != words.end(); iter++) {   // 리스트를 처음부터 끝까지 돌면서
            if ((*iter).find('.') != string::npos) {    // find : 해당 문자가 위치한 인덱스를 반환
                *iter = (*iter).substr(0, (*iter).find('.'));
            }
            if ((*iter).find(',') != string::npos) {
                *iter = (*iter).substr(0, (*iter).find(','));
            }
            if ((*iter).find('/') != string::npos) {
                words.push_back((*iter).substr(0, (*iter).find('/')));
                *iter = (*iter).substr((*iter).find('/')+1, (*iter).length()-((*iter).find('/')+1));
            }
        }
        // 확인용 출력
        for (iter = words.begin(); iter != words.end(); iter++) {
            cout << *iter << endl;
        }

        // 3. 단어의 빈도수 구하기

        file.close();   // 파일 닫기
    } else {
        cout << "파일을 열 수 없습니다.";
        return 1;
    }

    return 0;
}