#include <vector>
#include <iostream>

using namespace std;

/*
@풀이
    단순하게 prefix sum 만들고, suffix sum을 만들면서 처리하면 됨
    2n이므로 O(n)
    실행 결과, 0ms(over 100%), 15NMB(over 63.06%)
    처음 시작하고 prefix sum을 구하는 과정에선 suffix sum을 알 수 없고, 이는 그 반대 경우 또한 동일함
    그러나 반환해야하는 값은 두 값을 모두 알고 있어야만 구할 수 있음
    따라서 무조건 2번 이상 순회해야만 답을 구할 수 있음
*/

class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        const int n = nums.size();
        vector<int> result(n,0);

        for(int i=1; i<n; ++i)
            result[i] += result[i-1] + nums[i-1];

        int rSum = 0;
        for(int i=n-2; i>=0; --i)
        {
            rSum += nums[i+1];
            result[i] = abs(result[i] - rSum);
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}