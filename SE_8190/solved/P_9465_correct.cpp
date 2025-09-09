#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

/*
    스티커를 떼는 문제
    근데 뜯으면서 주변 스티커까지 손상되므로 모든 스티커를 뗄 수는 없음
    이 때, 뗀 스티커들 가치 총합의 최대값은?

    나는 행동을 3가지로 정의함 -> 윗줄 뗌, 아랫줄 뗌, 아무것도 안함
    이 행동에 따라 배열을 순회하며 dp 테이블을 채우고 최대값을 찾음

    근데 다른 풀이를 보니 아무것도 안하는 행동은 따로 정의할 필요는 없었음
    아무것도 안한 경우를 보려면 그저 전전 인덱스를 참조하면 됐음
    그러나 실행시간이 엄청 큰 영향을 주진 않았음 (4ms 가량)

    그리고 c스타일 배열에서 처음으로 stl array를 써봤는데 4ms 정도 실행시간이 증가함
    rolling DP를 적용해서 메모리 사용량을 더 깎아내는 것도 좋은 방법일듯
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int cases, cols;
    cin >> cases;
    
    while(cases--)
    {
        cin >> cols;
        vector<array<int,2>> sticker(cols);
        vector<array<int,3>> dp(cols);

        // Input & Init
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<cols; j++)
                cin >> sticker[j][i];
        }
        dp[0][0] = sticker[0][0];
        dp[0][1] = sticker[0][1];
        dp[0][2] = 0;

        // Travel
        for (int i=1; i<cols; i++)
        {
            dp[i][0] = max(dp[i-1][1],dp[i-1][2]) + sticker[i][0];
            dp[i][1] = max(dp[i-1][0],dp[i-1][2]) + sticker[i][1];
            dp[i][2] = max(dp[i-1][0],dp[i-1][1]);
        }
        cout << *max_element(dp[cols-1].begin(),dp[cols-1].end()) << '\n';
    }

    return 0;
}

