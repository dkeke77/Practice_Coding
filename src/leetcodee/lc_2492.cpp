#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
@접근
    이전에 경유했던 엣지를 다시 경유하는 것이 가능하므로,
    1번 노드에서 도달 가능한 모든 엣지를 확인하며 그 최소를 구하면 됨
    실행 결과, 54ms(over 74.70%), 133MB(over 73.40%)

    다른 방법으로는 union-find를 사용할 수도 있음
*/

struct Edge
{
    int to;
    int cost;
};

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<Edge>> edges(n+1);

        for (const auto& r : roads)
        {
            edges[r[0]].push_back({r[1],r[2]});
            edges[r[1]].push_back({r[0],r[2]});
        }

        vector<bool> isVisited(n+1, false);
        queue<int> toVisit;

        toVisit.push(1);
        isVisited[1] = true;

        int minCost = edges[1][0].cost;

        while (!toVisit.empty())
        {
            auto visit = toVisit.front();
            toVisit.pop();

            for (const auto& e : edges[visit])
            {
                minCost = min(minCost, e.cost);
                if (!isVisited[e.to])
                {
                    isVisited[e.to] = true;
                    toVisit.push(e.to);
                }
            }
        }
        
        return minCost;
    }
};

int main()
{
    Solution s;

    return 0;
}