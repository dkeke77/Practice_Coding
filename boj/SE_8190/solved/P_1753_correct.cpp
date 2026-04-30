#include <iostream>
#include <vector>
#include <stack>
#include <queue>

/*
    1753번, 방향그래프에서의 데이크스트라 알고리즘 문제
    첫 구현에선 stack으로 방문예정노드를 구현했는데 이게 문제였음
    왜냐면 나중에 걸러질 가능성이 높은 노드를 먼저 방문할 수도 있었음
    때문에 불필요한 방문이 더 많이 할 수 있음
    따라서 최소힙으로 구현하는 것이 옳은 구현임
    남겨질 가능성이 높은 노드를 먼저 방문하기 때문에 더 효율적임

    그리고 문제에서 두 노드간에 간선이 중복될 수 있음을 시사했는데,
    처음에는 최소 비용 간선만 남도록 처리를 했음
    이 때문에 지나치게 시간이 오래 걸리는 문제가 발생함
    방문예정노드를 stack으로 했다면 필수적인 처리였겠지만 최소힙에선 불필요함
    어차피 제일 짧은 간선으로 방문하고, 긴 간선은 나중에 방문을 시도할때 이전 결과에 의해 알아서 막혀버림
    즉, 굳이 신경쓸 필요가 없었다
*/

using namespace std;

struct Edge
{
    int dest;
    int weight;

    bool operator>(const Edge& other) const
    {
        return weight > other.weight;
    }
};

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int V, E, start;
    int v1, v2, w;
    cin >> V >> E >> start;
    vector<vector<Edge>> edges(V+1);
    vector<int> dist(V+1, -1);
    priority_queue<Edge, vector<Edge>, greater<Edge>> toVisit;

    for(int i=0; i<E; i++)
    {
        cin >> v1 >> v2 >> w;
        edges[v1].push_back(Edge{v2,w});
    }

    toVisit.push(Edge{start,0});
    dist[start] = 0;
    while(!toVisit.empty())
    {
        int curNode = toVisit.top().dest;
        int curDist = toVisit.top().weight;
        toVisit.pop();

        if(dist[curNode] < curDist) continue; 

        for (auto &elem : edges[curNode])
        {
            if (dist[elem.dest] == -1 || dist[elem.dest] > curDist + elem.weight)
            {
                dist[elem.dest] = curDist + elem.weight;
                toVisit.push(Edge{elem.dest,curDist + elem.weight});
            }                
        }
    }

    for (int i=1; i<=V; i++)
    {
        if (dist[i] == -1)
            cout << "INF\n";
        else
            cout << dist[i] << '\n';
    }

    return 0;
}