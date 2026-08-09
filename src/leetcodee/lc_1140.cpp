#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    예전에 stone game 3를 풀었던 것처럼 비슷한 느낌으로 접근해보자
    각 플레이어의 득실을 계산하기보단, 각 인덱스에 도달했을때 기대할 수 있는 최대 점수로 따져보자
    이 때, 각 인덱스에 도달했을때, 얼마만큼의 길이를 사용할 수 있는지도 중요한 상태임
    따라서 dp는 몇개를 가져갔는지를 같이 기록해야함
    dp[i][j]라고 할때, i를 piles의 인덱스, j를 해당 인덱스부터 몇개를 가져갈 것인지라고 하자
    그러면 dp[i][j] = sum(piles[i]~piles[i+j-1]) - max(dp[i+j][1]~dp[i+j][2*j])과 같은 꼴일것
     ㄴ 항의 앞쪽은 이번에 획득할 이익이고, 뒷쪽은 이번 선택을 인해 상대가 얻을 이익을 의미
     ㄴ 그리고 상대가 1~2*j개중에서 제일 이익이 되는 것을 고른다고 생각
     ㄴ 이 과정에서 매번 max를 찾는 것은 비효율적이지만, n이 작으므로 일단은 나이브하게 구현해도 될듯
    이를 뒤->앞 순으로 진행
    그리고 마지막으로 얻은 dp[0]의 최적값은 실제 점수가 아닌, 상대와의 점수 차임
    따라서 실제 값은 (sum(piles) + dp[0])/2임
     ㄴ dp[0]는 상대와의 점수 차임으로, score1 - score2임
     ㄴ 그리고 sum(piles)는 score1 + score2이므로, 이 둘을 더하면 2*score1임
    
    문제에서 M과 X에 대한 설명이 난해했기에 잘못 해석했는데, M_next = max(M,X)이므로, M은 줄어들지 않음
    즉, M이 4일때 X를 3으로 한다고 하여도 M이 3으로 줄어들지 않고 4로 유지됨
    위 접근은 다음 M이 X로 바뀌는 경우에 유효함
    따라서 몇개를 고르느냐가 아닌, M을 갱신하며 전파해야함
     ㄴ 현재 고른 개수에 따라 M을 갱신
    이는 재귀로 표현하기 편하기에 재귀를 사용하여 구현함
    이미 방문한 상태는 다시 처리하기보단, 저장해뒀다가 재방문 시 재사용하는 것이 더 효율적임
    실행 결과, 11ms(over 54.67%), 14MB(over 55.90%)
*/

class Solution {
public:
    int buildDP(vector<int>& piles, vector<vector<int>>& dp, int i, int M)
    {
        const int n = piles.size();
        if (i >= n) return 0;

        int& result = dp[i][M];
        if (result > INT32_MIN)
            return result;

        int sum = 0;
        for (int j=0; j<2*M; j++)
        {
            if (i+j >= n) break;
            sum += piles[i+j];
            result = max(result, sum - buildDP(piles, dp, i+j+1, max(j+1,M)));
        }

        return result;
    }

    int stoneGameII(vector<int>& piles) {
        const int n = piles.size();
        int allSum = 0;

        for (const auto& p : piles)
            allSum += p;

        if (n <= 2)
            return allSum;

        vector<vector<int>> dp(n,vector<int>(n+1,INT32_MIN));

        return (allSum + buildDP(piles, dp, 0, 1)) / 2;
    }
};

int main()
{
    Solution s;

    return 0;
}