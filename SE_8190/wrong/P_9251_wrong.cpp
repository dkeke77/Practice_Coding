#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/*
    LCS 길이 찾는 문제
    DP 쓰는게 정석이라던데 난 걍 dfs 써봄
    시간복잡도 N^2 정도 나올거라고 생각했고, 10^3가 최대이니 10^6로 널널하게 통과할 수 있을거라고 생각했음
    근데 시간 초과로 실패함

    우선 이중 벡터 접근과 max 계산을 매번 하기 때문에 느림
    이런 스타일로 짜면 캐시 적중률이 낮다고 함
    왜냐면 2차원배열 행을 건너뛰며 접근을 하면 계속 메모리 접근 간격이 커짐
    C++은 행을 우선으로 저장하는 것에서 비롯되는 문제
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    stack<pair<int,int>> dfs;
    vector<vector<int>> tb;
    string s1,s2;
    int curDepth, curIndex;
    int maxDepth = -1;

    cin >> s1 >> s2;

    vector<int> temp;
    for(int i=0; i<s1.size(); i++)
    {
        temp.clear();

        for(int j=0; j<s2.size(); j++)
        {
            if(s1[i]==s2[j])
                temp.push_back(j);
        }

        if(temp.size() > 0)
            tb.push_back(temp);
    }

    for(int i=0; i<tb.size(); i++)
    {
        if (int(tb.size())-i<=maxDepth)
            break;

        for(auto elem:tb[i])
            dfs.push({elem,i});
        
        while(!dfs.empty())
        {
            curIndex = dfs.top().first;
            curDepth = dfs.top().second;
            maxDepth = max(maxDepth, curDepth);
            dfs.pop();

            if(curDepth < tb.size()-1)
            {
                for(auto elem : tb[curDepth+1])
                {
                    if (elem > curIndex)
                        dfs.push({elem,curDepth+1});
                }
            }
                
        }
    }

    cout << maxDepth+1;

    return 0;
}