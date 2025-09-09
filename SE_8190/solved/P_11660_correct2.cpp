#include <iostream>
#include <vector>

using namespace std;

/*
    N*N 표에 숫자들이 적혀있고, 지정해주는 사각형 범위에 있는 숫자들의 합을 구하는 문제
    
    정석적으로 2D 누적합 방식으로 풀음
*/

struct Coord
{
    int x,y;
};


int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N,M,input,tempSum;
    cin >> N >> M;
    vector<vector<int>> dp(N,vector<int>(N,0));
    
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            tempSum = 0;
            cin >> input;
            if ((i==0) && (j==0))
                dp[i][j] = input;
            else if (i==0)
                dp[i][j] = dp[i][j-1] + input;
            else if (j==0)
                dp[i][j] = dp[i-1][j] + input;
            else
                dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + input;
        }
    }

    Coord c1, c2;
    while(M--)
    {
        cin >> c1.x >> c1.y >> c2.x >> c2.y;

        if ((c1.x == 1) && (c1.y == 1))
            cout << dp[c2.x-1][c2.y-1] << '\n';
        else if (c1.x == 1)
            cout << dp[c2.x-1][c2.y-1] - dp[c2.x-1][c1.y-2] << '\n';
        else if (c1.y == 1)
            cout << dp[c2.x-1][c2.y-1] - dp[c1.x-2][c2.y-1] << '\n';
        else
            cout << dp[c2.x-1][c2.y-1] - dp[c2.x-1][c1.y-2] - dp[c1.x-2][c2.y-1] + dp[c1.x-2][c1.y-2] << '\n';
    }
}