#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    문자열의 각 연속된 1에 대해, 인접한 0의 개수를 기록하는 방향
    그리고 그 0의 개수가 최대인 것을 선택하면 그것이 곧 정답이지 않을까 생각함
    실행 결과, 33ms(over 95.04%), 55MB(over 76.13%)
*/

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int countOne = 0;
        int countZeroFront = 0;
        int countZeroBack = 0;
        int maxZero = 0;
        char prevCh = '1';

        for (const auto& c : s)
        {
            if (c == '0')
                countZeroBack++;
            else
            {
                if (prevCh != c)
                {
                    if (countZeroFront > 0)
                        maxZero = max(maxZero, countZeroFront+countZeroBack);
                    countZeroFront = countZeroBack;
                    countZeroBack = 0;
                }
                countOne++;
            }
            prevCh = c;
        }
        if (countZeroFront > 0 && countZeroBack > 0)
            maxZero = max(maxZero, countZeroFront+countZeroBack);
        
        return countOne + maxZero;
    }
};

int main()
{
    Solution s;

    return 0;
}