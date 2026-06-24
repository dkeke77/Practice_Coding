#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    balloon 각 철자별로 카운팅을 하고, 각 철자가 특정 치 이상이면 카운트
    실행 결과, 0ms(over 100%), 9MB(over 64.87%)
    
*/

bool isAbleToBalloon(vector<int>& letterCount)
{
    return (
        letterCount[0] >=1 &&
        letterCount[1] >=1 &&
        letterCount[2] >=2 &&
        letterCount[3] >=2 &&
        letterCount[4] >=1
    );
}

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        int result = 0;
        vector<int> letterCount(5,0);

        for (const auto& c : text)
        {
            if (c == 'b')
                letterCount[0]++;
            else if (c == 'a')
                letterCount[1]++;
            else if (c == 'l')
                letterCount[2]++;
            else if (c == 'o')
                letterCount[3]++;
            else if (c == 'n')
                letterCount[4]++;

            if (isAbleToBalloon(letterCount))
            {
                result++;
                letterCount[0] -= 1;
                letterCount[1] -= 1;
                letterCount[2] -= 2;
                letterCount[3] -= 2;
                letterCount[4] -= 1;
            }
        }

        return result;
    }
};
int main()
{
    Solution s;

    return 0;
}