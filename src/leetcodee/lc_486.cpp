#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    일단 현재의 선택이 최적이 아닌 경우가 있기 때문에, 단순 그리디로는 접근할 수 없음
     ㄴ 2번 예시처럼, 제일 낮은 1을 선택해야 상대에게 233을 넘겨주지 않을 수 있음
    따라서 이런 문제는 모든 경우의 수를 따져볼 필요가 있음
    마침 길이가 20이기에 2^20로 확인할 수 있지만, 각 플레이어가 이상한 플레이를 하는 경우도 포함될 수 있음
    그런 경우까지도 정답으로 인정해주는지가 의문임
    다른 방법으로는 DP가 있는데, 어떤걸 상태로 할지가 문제
    기본 틀은 2차원 DP로 풀되, 각 셀의 상태는 플레이어들의 점수로 하자
    그리고 각 셀의 의미는 DP[i][j]는 남은 배열이 i~j인 상태를 의미
    이에 따라 DP[i][j]에서 다음 상태는 DP[i+1][j]와 DP[i][j+1]로 전이하며, 전이된 값들중 최대를 기록
    이것도 사실 이상한 플레이들을 하는 경우를 배제시키진 못함

    다른 풀이를 본 결과, 이 접근은 틀린 것은 아니었으나 반대로 수행했어야했음
    즉, 첫 상태를 [0,n-1]에서 시작하는 것이 아닌, [i,i]에서부터 [0,n-1]로 복원해나가는 것이 해법이었음
    위 방식대로면 마지막 상태 [i,i]에서부터 숫자를 하나 택하고, 이를 배열에 붙이는 것으로 생각할 수 있음
    다시 정리하며느 어떤 상태 [i,j]를 만들기 위해 앞의 원소와 뒤의 원소 중 어느 것을 붙일지 선택하는 문제가 되는 것
    이를 통해 이상한 풀이는 자연스럽게 배제되고, 서로가 최적으로 행동한 결과만이 하나 남게 됨
    실행 결과, 1ms(over 46.17%), 11MB(over 11.20%)
    서로의 점수차만 기록하게 하고, 1차원 DP로 줄인다면 성능과 메모리 양쪽 모두 개선될 여지가 있으나 굳이 하지는 않음

    다른 풀이로는, 재귀를 이용하여 min-max 알고리즘과 같이 트리를 구성하는 방법도 있음
    각 재귀는 배열의 왼쪽/오른쪽 중 하나를 선택하고, 남은 구간에 대한 선택을 재귀적으로 요청함
    그리고 depth에 맞는 플레이어의 입장에서 이익이 되는 것을 반환함
    이를 통해 각 플레이어 입장에서 최적인 결과를 하나를 위와 마찬가지로 얻을 수 있음
    사실 유심히 보면 큰 아이디어자체는 크게 다르지 않음을 알 수 있음
*/

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        const int n = nums.size();
        if (n <= 2)
            return true;

        vector<vector<vector<int>>> dp(n,vector<vector<int>>(n,vector<int>(2,0)));
        int turn = n-1;
        for (int i=0; i<n; i++)
            dp[i][i][turn%2] = nums[i];
        
        
        for (turn--; turn>=0; turn--)
        {
            int intv = n-1-turn;
            for (int i=0; i<=turn; i++)
            {
                // Pick left
                const auto& left = dp[i+1][i+intv];
                const auto& right = dp[i][i+intv-1];
                if (left[(turn+1)%2] < right[(turn+1)%2])
                {
                    dp[i][i+intv] = left;
                    dp[i][i+intv][turn%2] += nums[i];
                }
                else
                {
                    dp[i][i+intv] = right;
                    dp[i][i+intv][turn%2] += nums[i+intv];
                }
                
            }
        }

        return dp[0][n-1][0] >= dp[0][n-1][1];
    }
};
int main()
{
    Solution s;

    return 0;
}