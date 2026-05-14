#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
@접근
    처음 temp에 저장해가며 자릿수 계산이 끝나는 시점에 결과값에 가산할까 생각했음
    하지만 이전 상태만 보는 것으로도 충분하기에 그렇게 구현함
    실행 결과, 0ms(over 100%), 10MB(over 87.00%)가 나옴

    거의 하드코딩에 코드 재사용성도 높아서 더 좋은 구조로 만들 수 있을 것으로 보임
    이를 함수로 따로 분리 및 일반화함
    현재 수가 바로 앞 수의 5배나 10배면, 그 수에 의해 현재 수가 감산됨
    이런 현상을 구현함
*/

class Solution {
public:
    int romanToInt(string s) {
        int result = 0;
        recentDigit = 0;

        for (const auto& c : s)
            result += calcRealNum(chTable.at(c));
        
        return result;
    }

private:
    const unordered_map<char,int> chTable =
    {
        {'I',1},
        {'V',5},
        {'X',10},
        {'L',50},
        {'C',100},
        {'D',500},
        {'M',1000}
    };
    int recentDigit = 0;
    int calcRealNum(int num)
    {
        int temp = num;
        if (recentDigit*5 == num || recentDigit*10 == num)
            temp -= recentDigit*2;

        recentDigit = num;
        return temp;
    }
};

int main()
{
    Solution s;

    cout << s.romanToInt("X");

    return 0;
}