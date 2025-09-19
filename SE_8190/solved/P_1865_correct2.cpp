#include <iostream>
#include <vector>
#include <queue>

/*
    백준 1865번 문제, 그래프의 음수 사이클 존재 여부를 묻는 문제
    벨만-포드 알고리즘을 묻는 문제임
    근데 SPFA라는 다른 방법도 있어서 그 방법도 써봄

    그런데 SPFA를 그대로 구현하면 이전 벨만-포드처럼 단절된 노드를 확인할 수 없음
    그래서 방문 큐에 모든 노드를 추가한채로 시작해야함
    그리고 생각보다 조기종료 적용한 벨만-포드보다 빠르진 않음

    그래도 데이크스트라처럼 범용적으로 쓸 수 있을거같음
    왜냐면 벨만-포드는 조기종료가 있더라도 불필요한 방문을 강제적으로 해야됨...
*/

#define INF 1e8
using namespace std;

struct Edge{int dest, weight;};

bool spfa(vector<vector<Edge>>& edges)
{
    vector<int> dist(edges.size(),INF);
    vector<int> counter(edges.size(),0);
    vector<bool> isInQueue(edges.size(), false);
    queue<int> toVisit;
    
    
    for(int i=1; i<edges.size(); i++)
    {
        toVisit.push(i);
        isInQueue[1] = true;
    }
    dist[1] = 0;

    while(!toVisit.empty())
    {
        int curNode = toVisit.front();
        toVisit.pop();
        isInQueue[curNode] = false;
        counter[curNode]++;

        if (counter[curNode] >= edges.size() || dist[curNode] < -INF)
            return true;

        for(auto edge : edges[curNode])
        {
            if (dist[curNode]+edge.weight < dist[edge.dest])
            {
                dist[edge.dest] = dist[curNode] + edge.weight;
                if(!isInQueue[edge.dest])
                {
                    toVisit.push(edge.dest);
                    isInQueue[edge.dest] = true;
                }
            }
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int test, N, M, W;
    int S, E, T;
    vector<vector<Edge>> edges;
    cin >> test;
    while(test--)
    {
        cin >> N >> M >> W;
        edges = vector<vector<Edge>>(N+1);
        for (int i=0; i<M; i++)
        {
            cin >> S >> E >> T;
            edges[S].push_back(Edge{E,T});
            edges[E].push_back(Edge{S,T});
        }

        for (int i=0; i<W; i++)
        {
            cin >> S >> E >> T;
            edges[S].push_back(Edge{E,-T});
        }

        if (spfa(edges))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}