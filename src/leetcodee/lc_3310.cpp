#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
@접근
    문제 설명이 굉장히 난해한데, 어떤 노드의 하위 노드는 전부 위험으로 간주함
    그리고 그 위험 노드를 제거한 결과를 반환하는 것이 목표인데,
    위험 노드그룹이 다른 정상 노드와 연결된다면 제거하지 않음
    즉, 같은 네트워크에 정상 노드가 하나라도 있으면 제거하지 않음
    따라서 위험 노드를 네트워크에 전파하고, 정상 노드를 전파하고 나서 위험 노드를 없애면 됨
    bfs 2번 사용해서 풀어낼 수도 있고, union-find도 고려할만 해보임
     ㄴ 그런데 union-find는 상위 노드가 2개 이상인 케이스와 순환 그래프인 케이스가 있으므로 사용하기 어려워보임
    그리고 bfs를 2번 하더라도 상위 노드가 2개 이상이며, 그 중 한 상위 노드의 서브네트워크에 정상 노드가 없는 경우를 처리하진 못함
    따라서 bfs를 통해 위험노드를 전파하고, 정상노드중에서 위험노드가 하위인 노드가 있다면 모든 위험을 무시하는 방법을 사용
     ㄴ 위험노드 근원은 1개뿐이므로 위험노드 네트워크 또한 1개이므로 이 방법이 가능함
    실행 결과, 173ms(over 70.34%), 297MB(over 90.69%)

*/

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> edges(n);
        vector<bool> suspicious(n);

        for (const auto& invocation : invocations)
            edges[invocation[0]].push_back(invocation[1]);
        
        queue<int> toVisit;
        toVisit.push(k);
        suspicious[k] = true;
        while(!toVisit.empty())
        {
            auto curr = toVisit.front();
            toVisit.pop();

            for (const auto& next : edges[curr])
            {
                if (suspicious[next]) continue;

                suspicious[next] = true;
                toVisit.push(next);
            }
        }

        vector<int> result;
        result.reserve(n);
        for (int i=0; i<n; i++)
        {
            if (suspicious[i]) continue;
            
            for (const auto& next : edges[i])
            {
                if (suspicious[next])
                {
                    for (int i=0; i<n; i++)
                        result.push_back(i);
                    return result;
                }
            }
        }

        for (int i=0; i<n; i++)
        {
            if (!suspicious[i])
                result.push_back(i);
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}