#include <iostream>
#include <vector>

/*
    백준 1865번 문제, 그래프의 음수 사이클 존재 여부를 묻는 문제
    벨만-포드 알고리즘을 묻는 문제임

    그런데 한번 더 생각해봐야하는 부분이 존재함
    바로 특정 노드에서 방문할 수 있는 노드 중에 음수 사이클이 존재하는지가 아니라.
    그래프 전체 음수 사이클이 존재하는지를 묻는 것임
    그래서 원래는 현재 방문 노드가 INF면 다른 노드로 방문을 하지 않음
    그런데 현재 방문 노드가 다른 노드와 단절됐다면 다른 노드로 아예 방문이 불가능함
    이 때문에 다른 노드에 존재할 수 있는 음수 사이클을 찾을 수 없게 됨
    
    그리고 INF 크기를 무식하게 INT32_MAX로 잡아버리면 오버플로우가 발생하면서 정상적인 순회가 불가능해짐
    따라서 적당하게 크게 잡아버리는게 좋음

    그리고 업데이트 여부를 확인하는 변수를 추가하고, 업데이트가 없으면 조기 종료하도록 코드를 수정했는데,
    실행 시간이 28ms -> 16ms로 크게 줄어듦
*/

#define INF 1e8
using namespace std;

struct Edge
{
    int dest;
    int weight;
};

bool spfa(vector<vector<Edge>>& edges)
{
    vector<int> dist(edges.size(),INF);
    dist[1] = 0;
    bool isUpdated = false;

    for (int i=1; i<=edges.size(); i++)
    {
        isUpdated = false;
        for (int j=1; j<edges.size(); j++)
        {
            for(auto edge : edges[j])
            {
                if(dist[j] + edge.weight < dist[edge.dest])
                {
                    if (i==edges.size()) return true;
                    dist[edge.dest] = dist[j] + edge.weight;
                    isUpdated = true;
                }
            }
        }
        if (!isUpdated) break;
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