#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    그냥 순회하면서 값 더하면서 최댓값 기록하기
    실행 결과, 0ms(over 100%), 11MB(over 73.87%)
*/

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int maxH = 0;
        int alti = 0;

        for (const auto& g : gain)
        {
            alti += g;
            maxH = max(maxH, alti);
        }

        return maxH;
    }
};
int main()
{
    Solution s;

    return 0;
}