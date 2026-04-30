#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
	1967번 트리 지름 구하기 문제
	1, 2번 코드에서 계속됐던 팔요한 weight를 찾기 위해 edges를 순회해야만 되는 것을 개선하고자 했음

    1167번 코드 복붙해서 입출력쪽만 다듬음
    입력범위부터 더 작아서 굉장히 쉬웠음
*/

struct edge
{
	int dest;
	int weight;
};

pair<int,int> DFS(vector<vector<edge>>& edges, int start)
{
	int dist = 0;
    int maxDist = 0;
	int maxNode = start;
	stack<int> toVisit;
    vector<bool> isVisited(edges.size(),false);
    vector<int> distVec(edges.size(),0);
	
	toVisit.push(start);
	while(!toVisit.empty())
	{
		int curNode = toVisit.top();
		toVisit.pop();
        isVisited[curNode] = true;
		
		dist = distVec[curNode];
        if(maxDist < dist)
        {
            maxDist = dist;
            maxNode = curNode;
        }

		for (auto elem : edges[curNode])
		{
			if (!isVisited[elem.dest])
            {
                toVisit.push(elem.dest);
                distVec[elem.dest] = dist + elem.weight;
            }
		}
	}
	return make_pair(maxNode,maxDist);
}

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

	int N, v1, v2, weight;
	pair<int,int> result;
	cin >> N;
	vector<vector<edge>> edges(N+1);
	
	for (int i=0; i<N-1; i++)
	{
		cin >> v1 >> v2 >> weight;
		edges[v1].push_back(edge{v2,weight});
        edges[v2].push_back(edge{v1,weight});
	}
	
	result = DFS(edges, 1);
	result = DFS(edges, result.first);
	
	cout << result.second;

	return 0;
}