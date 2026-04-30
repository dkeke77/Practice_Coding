#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
	1167번 트리 지름 구하기 문제
	1번 코드를 더 개량하고자 했던 코드

	제일 문제로 꼽은건 방문 노드가 직전 노드와 연결됐는지 확인하기 위해 작성한 for문이었음
	이로 인해 시간 소요가 커진다고 판단해서 다른 방식으로 접근하고자 했음

	바로 분기가 발생할시, 현재 dist를 따로 스택에 저장하는 방법임
	그리고 트리의 끝에 도달했음을 알리는 bool을 따로 만듦
	이를 통해 만약 노드 방문 시, 직전 노드가 트리의 끝에 도달했었다면 지금 노드는 직전 분기로 회귀한 상황
	따라서 이전에 저장한 dist 스택에서 pop하여 현재 dist를 덮어씀

	이 방법을 통해 확실히 노드 회귀 부분에서 더 간략해졌음
	하지만 메모리는 더 많이 먹게 되었고, 실행시간은 거의 차이가 없었음
	이는 dist 스택이 컴퓨터 입장에선 예측하기가 어려워서 캐시 적중률이 떨어졌나봄
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
    stack<int> distStorage;
    vector<bool> isVisited(edges.size(),false);
    bool isReachedEnd = false;
	
	toVisit.push(start);
	while(!toVisit.empty())
	{
		int curNode = toVisit.top();
		toVisit.pop();
        isVisited[curNode] = true;
		
		// Get sum when branched
        if(isReachedEnd)
        {
            dist = distStorage.top();
            distStorage.pop();
            isReachedEnd = false;
        }

        int childCounter = 0;
		for (auto elem : edges[curNode])
		{
			if (!isVisited[elem.dest])
            {
                toVisit.push(elem.dest);
                childCounter++;
            }
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
        if (childCounter==0)
            isReachedEnd = true;
        else
        {
        for (int i=1; i<childCounter; i++)
            distStorage.push(dist);
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