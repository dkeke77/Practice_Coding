#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    top-down으로 모든 경우를 확인하는 것이 적절하다고 생각됨
    그런데 이미 확인했던 구간이 또 나올 여지가 크기 때문에 이전 결과를 캐싱하는 것이 좋다고 판단됨
    또한 구간의 합을 자주 구해야하므로 prefix sum을 쓰는 것도 좋을 것임
    실행 결과, 401ms(over 67.81%), 28MB(over 65.64%)
    의외로 TLE 없이 한번에 통과함
    bottom-up과 iterative하게 푸는 것도 가능하다고 보여짐
     ㄴ 각 인덱스에 대해서 길이가 2인 구간부터 n까지 늘려가면 될 것으로 보임
     ㄴ 개인적으론 이 방법이 더 빠를 것으로 생각됨
*/

class Solution {
public:
    int solve(const vector<int>& prefixSum, vector<vector<int>>& dp, int i, int j)
    {
        if (i == j)
            return 0;
        if (dp[i][j] > 0)
            return dp[i][j];
        
        int sum = prefixSum[j+1] - prefixSum[i];
        int maxVal = 0;
        for (int k=i; k<j; k++)
        {
            int sumL = prefixSum[k+1] - prefixSum[i];
            int sumR = sum - sumL;

            if (sumL == sumR)
            {
                maxVal = max(maxVal, sumL + solve(prefixSum, dp, i, k));
                maxVal = max(maxVal, sumR + solve(prefixSum, dp, k+1, j));
            }
            else if (sumL > sumR)
            {
                maxVal = max(maxVal, sumR + solve(prefixSum, dp, k+1, j));
            }
            else
            {
                maxVal = max(maxVal, sumL + solve(prefixSum, dp, i, k));
            }
        }
        dp[i][j] = maxVal;

        return maxVal;
    }

    int stoneGameV(vector<int>& stoneValue) {
        const int n = stoneValue.size();
        vector<int> prefixSum(n+1,0);
        for (int i=0; i<n; i++)
            prefixSum[i+1] = stoneValue[i] + prefixSum[i];

        vector<vector<int>> dp(n,vector<int>(n,0));

        return solve(prefixSum, dp, 0, n-1);
    }
};

int main()
{
    Solution s;

    return 0;
}