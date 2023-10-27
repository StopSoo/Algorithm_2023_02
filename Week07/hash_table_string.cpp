// Q. N (20000 > N >= 1000)을 입력 받아 임의의 문자열 N개를 생성하고 (각 문자열의 길이는 100 이하라고 가정),
//    강의 자료 5페이지의 Hash 함수 두 개(implementation1, implementation3)와 본인이 Java hashCode를 참고하여 정의한 Hash를 각각 이용해 Hash Table에 삽입해보세요.
//    각 경우, Hash Table의 크기에 따라 hash 출력 값을 수정해주어야 합니다.
//    Hash Table 크기 M = N/2, 충돌은 Chaining 방법으로 해결하세요.
//    각 방법에서 임의로 100개의 데이터를 검색할 때 필요한 비교 횟수를 출력하는 프로그램을 작성하고, 각 방법의 탐색 성능에 대해 논의해보세요.
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

class HashTable {
private:
    int tableSize;
    vector<list<string>> table;

    int getNextPrime() {
        int primeNumbers[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        return primeNumbers[tableSize % 10];
    }

public:
    HashTable(int size)
        : tableSize(size) {
        table.resize(tableSize);
    }

    void insert(string &value, int hashCode) {
        table[hashCode].push_back(value);
    }

    int hashCode1(string input) {
        return input.length() % tableSize;
    }

    int hashCode3(string input) {
        int output = 1;
        for (char c : input) {
            int nextPrime = getNextPrime();
            output *= pow(nextPrime, static_cast<int>(c));
        }
        return static_cast<int>(pow(getNextPrime(), input.length())) % tableSize;
    }

    int myHashCode(string input) {
        int hashCode = 0;
        int prime = 31;
        for (char c : input) {
            hashCode = (hashCode * prime) + static_cast<int>(c);
        }
        return hashCode % tableSize;
    }

    int search(string &value, int hashCode) {
        int compare = 0;
        for (string& item : table[hashCode]) {
            compare++;
            if (item == value)
                return compare;
        }
        return compare;
    }
};

int main() {
    int N;
    cin >> N;

    HashTable hashTable1(N/2);
    HashTable hashTable3(N/2);
    HashTable myHashTable(N/2);

    srand(time(0));

    for (int i=0; i < N; i++) {
        string randomString = "string" + to_string(i);  // 랜덤 문자열 만들기
        int hashCode1 = hashTable1.hashCode1(randomString);
        int hashCode3 = hashTable3.hashCode3(randomString);
        int myHashCode = myHashTable.myHashCode(randomString);
        hashTable1.insert(randomString, hashCode1);
        hashTable3.insert(randomString, hashCode3);
        myHashTable.insert(randomString, myHashCode);
    }

    // 임의로 100개의 데이터 검색 및 비교 회수 출력
    int totalCompare1 = 0;
    int totalCompare3 = 0;
    int totalmyCompare = 0;

    for (int i = 0; i < 100; i++) {
        std::string searchString = "string" + std::to_string(rand() % N);

        int hashCode1 = hashTable1.hashCode1(searchString);
        int compare1 = hashTable1.search(searchString, hashCode1);
        totalCompare1 += compare1;

        int hashCode3 = hashTable3.hashCode3(searchString);
        int compare3 = hashTable3.search(searchString, hashCode3);
        totalCompare3 += compare3;

        int myHashCode = myHashTable.myHashCode(searchString);
        int myCompare = myHashTable.search(searchString, myHashCode);
        totalmyCompare += myCompare;
    }

    cout << "implementation1의 평균 비교 횟수 : " << static_cast<double>(totalCompare1) / 100.0 << endl;
    cout << "implementation3의 평균 비교 횟수 : " << static_cast<double>(totalCompare3) / 100.0 << endl;
    cout << "myHashCode의 평균 비교 횟수 : " << static_cast<double>(totalmyCompare) / 100.0 << endl;
    return 0;
}
