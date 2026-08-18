#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    부분배열에서 한번만 등장할 수 있는건 양끝에 있는 원소들뿐만 아닌가?
    freq 구성하고, 양끝에 있는 원소들 중에 조건 맞는것 출력하면 될듯
    단, k가 n인 경우와 1인 경우를 따로 처리해줘야함
     ㄴ k==n인 경우, 모든 숫자가 한번만 등장하므로, 단순히 최댓값을 출력하면 됨
     ㄴ k==1인 경우, 모든 원소가 등장하므로, 그 중에서 freq가 1인 것을 찾으면 됨
    실행 결과, 0ms(100%), 30MB(over 92.86%)
*/

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        if (k == nums.size())
            return *max_element(nums.begin(), nums.end());
        
        vector<int> freq(51,0);

        for (const auto& num : nums)
            freq[num]++;
        
        if (k == 1)
        {
            int maxVal = -1;
            for (int i=1; i<=50; i++)
                maxVal = freq[i] == 1 ? max(maxVal, i) : maxVal;
            
            return maxVal;
        }
        else
        {
            int numL = freq[nums.front()] == 1 ? nums.front() : -1;
            int numR = freq[nums.back()] == 1 ? nums.back() : -1;

            return max(numL,numR);
        }
    }
};

int main()
{
    Solution s;

    return 0;
}