#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

/*
@접근
    먼저 인접 리스트를 구성하면서 offline인 노드가 포함되는 엣지는 제외
    단순하게 다익스트라를 쓸 수도 있겠지만 이 문제에서 쓰긴 어려움
     ㄴ 최소경로가 아닌 목적지까지 갈 수 있는 여러 경로를 따져야 하기 때문
    그렇다면 dfs로 모든 경로를 확인해보기?
     ㄴ 비순환 그래프이므로 무한루프에 빠질 위험은 없음
    하지만 예상대로 TLE이 발생함

    힌트1를 보니, 매개변수 탐색을 이용하면 된다는 점을 확인했음
    따라서 dfs 시, 비용의 하한을 탐색해가며 하한의 최대를 찾아내면 되는것
     ㄴ 큰 하한일수록 달성하기 어려움
    그러나 TLE이 발생했는데, 높은 확률로 dfs 탐색때문일것
    따라서 문제의 태그에서 일러준 다익스트라를 이용하면 될것
    그런데 계속 TLE이 발생하길래 확인해보니, 두 노드 사이에 간선이 여러 개일 수 있었음
    하지만 무조건 간선의 최솟값만 저장해선 없음
     ㄴ 최솟값보다 큰 값이 정답일 수도 있기 때문
    따라서 모든 간선을 저장해야만 함
    그래서 기존 Edge 구조체에 비용을 int가 아닌 set<int>에 저장하게 함
    그리고 비용 저장 과정에서 기존에 추가했던 노드라면 해당 노드 원소에 찾아가 set에 새로운 비용을 insert하게 함
    실행 결과, 840ms(over 19.76%), 391MB(over 33.59%)

    속도가 느린 것은 아무래도 set 때문임
    이 부분에 대해 최적화를 진행한다면 더 빨라질 여지가 많음
     ㄴ 이전처럼 모든 간선을 노드 구분없이 저장하고, 방문 시 동일 노드에 대한 처리를 별도로 하기
     ㄴ 혹은 set를 벡터로 대체하기
    그래서 해당 노드의 모든 간선을 순회한 다음에 노드 방문을 1번만 하도록 하였음
     ㄴ 반복된 방문을 방지
    실행 결과, 456ms(over 37.98%), 413MB(over 22.09%)
    여기에 몇가지 최적화를 추가하면 아마 더 빨라질 여지가 더 있지만, 굳이 더 하진 않겠음

    DAG이기 떄문에 위상정렬을 사용할 수도 있음
    미리 위상정렬을 수행하여 토폴로지를 만들어두고, 해당 토폴로지를 순회함
    이 떄, 모든 간선을 처리한 뒤에 무조건 방문이 시행되므로 다익스트라보다 빠를 여지가 큼
*/

struct Edge
{
    Edge(int a, int b) : to(a), cost(b) {}
    int to;
    int cost;
};

struct VisitNode
{
    int idx;
    long long cost;

    bool operator<(const VisitNode& other) const
    { return cost < other.cost; }
};

bool dijkstra(const vector<vector<Edge>>& adj, int lowBound, long long k)
{
    const int n = adj.size();
    vector<long long> dist(n, LLONG_MAX);
    dist[0] = 0;

    priority_queue<VisitNode> pq;
    pq.push({0,0});

    while(!pq.empty())
    {
        auto visit = pq.top();
        pq.pop();

        set<int> nextNode;
        for (const auto& e : adj[visit.idx])
        {
            if (e.cost < lowBound) continue;

            long long newCost = visit.cost + static_cast<long long>(e.cost);
            if (newCost > k) continue;

            if (newCost < dist[e.to])
            {
                dist[e.to] = newCost;
                nextNode.insert(e.to);
            }
        }

        for (const auto& nxt : nextNode)
            pq.push({nxt,dist[nxt]});

        if (dist[n-1] <= k)
            return true;
    }

    if (dist[n-1] > k)
        return false;
    else
        return true;
}

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k)
    {
        const int n = online.size();
        int result = -1;
        vector<vector<Edge>> adj(n);
        vector<int> costs;
        costs.reserve(edges.size());

        int start = 1'000'000'000;
        int end = 0;
        bool existValidPath = false;

        for (const auto& e : edges)
        {
            if (online[e[0]] && online[e[1]])
            {
                adj[e[0]].push_back(Edge(e[1], e[2]));
                start = min(start, e[2]);
                end = max(end, e[2]);
            }
        }
    
        while(start < end)
        {
            int mid = (start + end + 1) / 2;
            
            bool passed = dijkstra(adj, mid, k);

            if (passed)
            {
                start = mid;
                existValidPath = true;
            }
            else
                end = mid-1;
        }
        
        if (existValidPath)
            return start;
        else
        {
            bool passed = dijkstra(adj, start, k);
            if (passed)
                return start;
            else
                return -1;
        }
    }
};


int main()
{
    Solution s;

    return 0;
}