#include <iostream>
#include <vector>

/*
    1932번 문제.
    숫자로 이루어진 삼각형의 맨 위에서 왼쪽/오른쪽 대각선을 선택하며 내려올때, 그 누적합의 최대를 묻는 문제
    너무 DP같아서 DP스타일로 풀었고, 실제로 정답이었음

    처음엔 이전 결과중 최댓값을 저장할 벡터를 따로 만들었으나,
    오른쪽->왼쪽으로 벡터를 순회하니 그럴 필요가 없어졌음
    그래서 for문과 벡터 각각 하나를 없앨 수 있었음
*/

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N, input, maxVal = 0;
    cin >> N;
    vector<int> tri(N+2,0);

    for(int i=1; i<=N; i++)
    {
        for(int j=i; j>=1; j--)
        {
            cin >> input;
            tri[j] = input + max(tri[j-1],tri[j]);
            if (i==N && maxVal < tri[j])
                maxVal = tri[j];
        }
    }
    cout << maxVal;

    return 0;
}