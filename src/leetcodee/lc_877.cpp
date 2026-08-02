#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    어제 풀었던 문제와 거의 동일함
    따라서 이전과 같이 bottom-up DP로 풀 수 있음
     ㄴ 첫번째 원소에서부터 하나씩 붙여나가는 방식
    그리고 이전과는 다르게 손실 기준으로 데이터를 구성했음
    양쪽이 번갈아가며 자신의 손실을 dp에 저장하도록 함
    그리고 마지막에 넣었던 플레이어에 따라 dp[0]의 값을 판별하도록 함
    실행 결과, 3ms(over 38.73%), 11MB(over 46.05%)

    그런데 이 문제의 경우는 굉장히 간결하게 풀 수도 있음
    이 문제에서 배열의 길이는 무조건 짝수인데, 이로 인해 처음 숫자를 고르는 플레이어는 반드시 이길 수밖에 없음
    왜냐하면 배열의 길이가 짝수라면 그 배열의 짝수/홀수번째 숫자를 전부 선택할 수 있음
    즉, 처음 고르는 플레이어가 그 중 유리한 것을 선택하면 무조건 이김
    당연하게도 이는 0ms임
*/

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        const int n = piles.size();
        vector<int> dp(n,0);

        for (int i=0; i<n; i++)
            dp[i] = piles[i];
        
        for (int len=1; len<n; len++)
        {
            for (int i=0; i<n-len; i++)
                dp[i] = max(piles[i+len]-dp[i], piles[i]-dp[i+1]);
        }

        if (n % 2 == 0)
            return dp[0] > 0;
        else
            return -dp[0] > 0;
    }
};

int main()
{
    Solution s;

    return 0;
}