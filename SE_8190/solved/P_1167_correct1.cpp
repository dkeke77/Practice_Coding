#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
	1167번 트리 지름 구하기 문제
	플로이드 적용하려다 실패하고 DFS를 적용하기로 함
	풀이법은 사실 GPT한테 스포당해서 구현에 더 중점을 두고 풀어봄

	단순히 탐색만 하는 DFS가 아닌 dest를 관리해야 하고,
	특히 부모쪽 노드로 회귀하는 경우에는 dist를 예전 값으로 어떻게 돌려야할지가 제일 큰 고민이었음

	이 코드에서는 스택을 2개 이용하여, 방문예정 노드말고도 방문했던 노드도 저장하게 함
	그리고 매 노드 방문 시마다, 제일 최근에 방문한 노드와 지금 노드가 이어져 있는지 확인함
	만약 이어져 있지 않다면, 이어진 노드가 나올때까지 방문했던 노드 스택을 pop
	pop하면 dist에서 그 노드의 weight를 빼버림

	이 방식은 노드 정보만 저장하기 때문에 dist에 weight를 더하거나 빼고 싶을때 복잡해짐
	edges에서 현재 노드와 dest가 이어진 간선을 순회해서 찾아야됨
	때문에 반복문이 지나치게 많아진 느낌이 있음
	그런데 이 방식은 생각보다 빠르고, 동시에 메모리도 제일 적게 먹음
	GPT 의견으로는 컴파일 과정에서 최적화가 더 잘 됐거나,
	혹은 실행과정에서 컴퓨터가 예상하기 쉽기 때문에 캐시 적중률이 높았던 걸로 보임
	loop unroll이라는 개념도 언급했는데 따로 더 공부해볼 것
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
	int w = 0;
	int maxNode = start;
	stack<int> toVisit;
	stack<pair<int,int>> visited;
	
	toVisit.push(start);
	visited.push(make_pair(start,0));
	while(!toVisit.empty())
	{
		int curNode = toVisit.top();
		toVisit.pop();
		
		// Trace backward
		bool isConnected = false;
		while(!isConnected && visited.top().first != curNode)
		{
			for(auto elem : edges[curNode])
			{
				if(visited.top().first==elem.dest)
				{
					isConnected = true;
					break;
				}
			}
			if (!isConnected)
			{
				dist -= visited.top().second;
				visited.pop();
			}
		}
		
		for (auto elem : edges[curNode])
		{
			if (elem.dest != visited.top().first)
				toVisit.push(elem.dest);
			else
			{
				w = elem.weight;
				dist += w;
				
				if (dist > maxDist)
				{
					maxDist = dist;
					maxNode = curNode;
				}
			}
		}
		visited.push(make_pair(curNode,w));
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