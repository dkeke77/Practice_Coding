#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
	1167번 트리 지름 구하기 문제
	1, 2번 코드에서 계속됐던 팔요한 weight를 찾기 위해 edges를 순회해야만 되는 것을 개선하고자 했음

	각 노드별 dist를 저장하는 벡터를 만듦
	다른 노드를 방문 예정 스택에 넣을때 dist에 (그 노드까지의 거리+현재 거리)를 기록
	이를 통해 필요한 weight를 찾기 위해 edges를 순회할 필요없이, 현재 간선을 확인하는 과정에서 자연스럽게 기록됨
	그리고 노드 방문 시엔 dist에서 현재 거리 데이터를 가져옴
	방문 여부는 bool 벡터로 관리

	제일 직관적이고 이해하기 쉬운 방법
	메모리를 2번 코드와는 특별히 많이 먹진 않음
	1번보다는 조금 더 먹음
	실행시간은 다른 방법들(72ms)에 비해 다소 느림(76ms)
	하지만 치명적이게 느리진 않으므로 좋은 구현이라고 생각함
	다른 dfs 문제에서도 이런 방식으로 구현하지 않을까 싶음
	또한 bfs로의 변경도 굉장히 단순함(방문예정노드를 stack에서 queue로 바꾸면 끝임)

	추가로 이걸 array로만 만들어보려다가 걍 포기함
	버그 잡기도 힘들고, 무엇보다 생각보다 성능적으로 큰 이점이 없음
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
	
	for (int i=0; i<N; i++)
	{
		cin >> v1;
		while(1)
		{
			cin >> v2;
			if (v2 == -1) break;
			cin >> weight;
			edges[v1].push_back(edge{v2,weight});
		}
	}
	
	result = DFS(edges, 1);
	result = DFS(edges, result.first);
	
	cout << result.second;

	return 0;
}