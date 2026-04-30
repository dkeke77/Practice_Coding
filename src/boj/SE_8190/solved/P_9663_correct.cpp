#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
    유명한 N-Queen 문제
    일반적인 백트래킹을 이용하여 해결함
    가지치기를 잘 하는 것이 알다시피 중요한 관건임
    가지치기를 안하면 O(N!)가 나와서 컴퓨터 터짐

    한 행씩 진행하며 퀸을 놓는다고 생각하고
    이전 배치들을 참고해서 배치 불가능한 곳을 mask에 표기
    그리고 표기된 곳을 피해서 새로 퀸을 배치하고 stack에 push
*/

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int N;
	cin >> N;
	vector<int> queen(N,-1);
	vector<bool> mask(N,false);
	stack<vector<int>> dfs;
	int result = 0;
	
	for(int i=0; i<N; i++)
	{
		queen[0] = i;
		dfs.push(queen);
	}
	
	int curHeight;
	while(!dfs.empty())
	{
		fill(mask.begin(),mask.end(),false);
	
		queen = dfs.top();
		dfs.pop();
	
        curHeight = -1;
		for(int i=0; i<N; i++)
		{
			if (queen[i] == -1)
            {
                curHeight = i;
				break;
            }
		}
	
		if(curHeight == -1)
		{
			result++;
            continue;
		}
	
		for(int i=0; i<curHeight; i++)
		{
			mask[queen[i]] = true;
			int diagL = queen[i]-(curHeight-i);
			int diagR = queen[i]+(curHeight-i);
	
			if (diagL >= 0)
				mask[diagL] = true;
			if (diagR < N)
				mask[diagR] = true;
		}
	
		for(int i=0; i<N; i++)
		{
			if (!mask[i])
			{
				queen[curHeight] = i;
				dfs.push(queen);
			}
		}
	}
	
	cout << result;
	
	return 0;
}