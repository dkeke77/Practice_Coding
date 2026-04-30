#include <iostream>
#include <vector>

using namespace std;

/*
    피보나치 수열에 대해 재귀호출 방식으로 구할때 f(N)에서 몇번의 f(0)과 f(1)이 나올까 묻는 문제
    직관적으로 dp로 풀 수 있어, dp를 적용하여 풀음

    근데 처음에 풀땐 인덱스 이슈로 인해 굳이 안해도 될 0,1 예외처리를 했었는데
    인덱스 처리 제대로 하고 예외처리는 없앰
    그리고 처음엔 매번 dp를 새로 구성했는데 사실 그럴 필요는 없음
    dp를 지우지말고 유지하면서, dp 테이블 내에 정답이 존재한다면 바로 출력하고, 없다면 그때 확장을 하는 방식으로 함

    근데 gpt가 보기엔 더 개선할 여지가 있다고 하던데
    문제에선 n이 크지 않으니 vector말고 배열 쓰라는 얘기도 했고
    또 0이 나온 횟수는 f(n-1)고 1이 나온 횟수는 f(n)라서 dp 테이블을 굳이 2개 만들 필요는 없다고 함
    근데 굳이 구현해볼 필요는 없어 보여서 스킵
*/

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

    vector<int> dp0({1,0});
    vector<int> dp1({0,1});

    int iter, target;
    cin >> iter;

    while(iter--)
    {
        cin >> target;

        if(dp0.size() <= target)
        {
            for(int i=dp0.size(); i<=target; i++)
            {
                dp0.push_back(dp0[i-2]+dp0[i-1]);
                dp1.push_back(dp1[i-2]+dp1[i-1]);
            }
        }

        cout << dp0[target] << " " << dp1[target] << '\n';
    }

    return 0;
}