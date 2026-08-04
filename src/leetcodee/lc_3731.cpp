#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    freq 구하면서 최대/최소도 같이 구하고,
    그 범위를 다시 순회하면서 freq가 0인 케이스를 배열에 push_back
    n+range보다 작게 해결할 순 없을 것으로 보임
     ㄴ 어떤 숫자를 보는 순간에 최대/최소인지 바로 알 수가 없음
     ㄴ 그리고 안 보인 숫자가 나중에도 안 보일지 확신할 수 없음
    실행 결과, 0ms(over 100%), 33MB(over 43.06%)
*/

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> freq(101,0);
        int minVal = nums[0];
        int maxVal = nums[0];

        for (const auto& num : nums)
        {
            freq[num]++;
            minVal = min(minVal, num);
            maxVal = max(maxVal, num);
        }
        
        vector<int> result;
        result.reserve((maxVal - minVal + 1) - nums.size());
        for (int i=minVal+1; i<maxVal; i++)
        {
            if (freq[i] == 0)
                result.push_back(i);
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}