#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    수열을 입력받고, 그 수열에서 증가하는 부분수열 중 최대 길이를 알아내는 문제
    최대값을 구해하고 이전 값에 의해 영향을 받는다? -> 그냥 DP인거 밝히는중

    dp테이블은 그 숫자가 가능한 최대 수열 길이를 저장
    n번째 수열 원소에 대해, n번째 원소보다 n+i번째 원소가 크며
    dp에 저장된 n번째 원소의 최대 길이 + 1이 n+1번째 원소가 현재 구성가능한 최대 길이보다 크다면
    dp에 새로운 값을 저장

    이 방식은 O(N^2) 가량 소요되는데, GPT왈 O(NlogN) 방법이 있다고 함
    DP와 그리디를 섞은 방식인데 그건 correct2에서 소개함
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<int> dp(N,1);
    vector<int> seq(N,0);

    for(int i=0; i<N; i++)
    {
        cin >> seq[i];
    }

    for(int i=0; i<N-1; i++)
    {
        for(int j=i+1; j<N; j++)
        {
            if((seq[i] < seq[j]) && (dp[i]+1 > dp[j]))
                dp[j] = dp[i]+1;
        }
    }

    cout << *max_element(dp.begin(), dp.end());
}