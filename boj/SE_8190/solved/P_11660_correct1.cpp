#include <iostream>
#include <vector>

using namespace std;

/*
    N*N 표에 숫자들이 적혀있고, 지정해주는 사각형 범위에 있는 숫자들의 합을 구하는 문제
    누적합이니 DP라는 느낌이 들었고 DP 문제가 맞았음
    혼자서 발상하고 푸는 것에 초점을 맞추는 데 노력해봄

    우선 표를 입력 받으면서 세로부분의 합을 누적해감
    그리고 지정된 사각형 범위에서 열 범위만큼 세로합을 전부 합산함
    이때, 사각형의 최하단만 신경쓰면 됨
    그리고 사각형 상단 위쪽의 값을 합산된 결과에서 빼주면 결과가 나옴

    하지만 정석적으로 푸는 방법이 여러 방면에서 더 좋음...
    정석적으로 푸는 방법은 세로합이 아니라 (1,1)을 기준으로 사각형 누적합을 저장하는거임
    처음엔 기준이 (1,1)이 아니라면 비포함되는 영역을 빼다가 좌상단쪽에서 중복으로 빼기가 발생할 것을 염려했음
    하지만 그냥 중복으로 빼진만큼 더하면 되는거였음,,,
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

    int N,M,input;
    cin >> N >> M;
    vector<vector<int>> dp(N,vector<int>(N,0));
    
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            cin >> input;
            if (i == 0)
                dp[i][j] = input;
            else
                dp[i][j] = dp[i-1][j] + input;
        }
    }

    Coord c1, c2;
    int sum, isYZero;

    while(M--)
    {
        sum = 0;
        cin >> c1.x >> c1.y >> c2.x >> c2.y;

        if (c1.x == 1)
        {
            for (int j = c1.y-1; j<c2.y; j++)
                sum += dp[c2.x-1][j];
        }
        else
        {
            for (int j = c1.y-1; j<c2.y; j++)
            {
                sum += dp[c2.x-1][j];
                sum -= dp[c1.x-2][j];
            }
        }

        cout << sum << '\n';
    }
}