#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

/*
@접근
    이전 문제에서 약간 변형되어, 임의의 두 노드 간의 경우의수를 구하는 문제임
    따라서 이전 문제의 풀이를 기반으로 구현하면 될 것으로 보임
    하지만 쿼리가 최대 10^5인 점, 그리고 부모 쪽으로 역행해야 도달하는 경우도 있단 점이 관건임
    전자의 조건 때문에 매번 dfs를 수행하는 것은 불가능함
    그러나 후자의 조건은 매번 탐색을 요구하고 있음
    단순하게 생각하면 사이클이 없는 그래프에서 노드 간 거리 구하기 문제임
     ㄴ 모든 거리는 1
    
    부모로 역행하는 방식을 생각해보는건 어떨까
    우선 더 깊은 쪽의 노드를 상대와 동일한 깊이까지 부모로 이동하고, 그 이후로 양쪽 모두 부모로 이동
    만약 양쪽 모두 부모가 동일하다면 루프 종료하고 현재까지 이동횟수로 정답 생성...
    이를 위해선 모든 노드를 먼저 탐색해둘 필요가 있음
     ㄴ 모든 노드에 대한 깊이 정보가 필요하기 때문
    그런데 부모로 회귀하는 과정에서, 최악의 경우엔 모든 노드를 계속 방문해야 하는 경우도 있음
     ㄴ 트리가 1줄로 이어진 형태이고, root와 leaf를 쿼리하는 경우
     ㄴ 위와 같은 케이스로 모든 쿼리가 채워진 경우라면 10^10로 TLE 확정임
    예상대로 TLE이 발생했지만, 방식 자체는 맞다고 판단됨
    따라서 한번에 하나씩 부모로 돌아가는 것이 아닌 크게 움직일 필요가 있음
    그렇다면 각 노드별로 자신의 부모부터 조상까지 저장하도록 하고, 어디까지 일치하는지 벡터끼리 비교하면 됨
    이는 바이너리하게 검사할 수 있으므로 훨씬 빠름
     ㄴ 두 노드의 깊이를 맞추기 위해 이동하는 것도 생략할 수 있음
    그러나 이 방법은 MLE이 발생함
     ㄴ 생각해보니 2*10^10라서 좀 많이 빡셀듯...
    
    결국 힌트를 보고 binary lifting이라는 개념을 알게 됨
    각 노드에 대해 부모, 조부모, 고조부모... 이런식으로 2^n번째 조상을 저장하는 방식임
    이를 이용하면 첫번째 구상했던 이동 로직을 더 빠르게 구현할 수 있을 것
     ㄴ 이 때문에 depth 정보가 필요할 것
    실행결과, 371ms(over 72.22%), 376MB(over 67.78%)
    
    여기서 성능을 더 개선하려면 조상 테이블을 고정으로 할당해놓고 재사용하는 방법이 있음
     ㄴ 초기화는 노드 1에 대해서만 수행하고, 순회하면서 알아서 초기화되도록 하면 됨
     ㄴ 알아서 초기화되게 하려면 조상 중에 0이 나와도 break하지 않으면 됨
    하지만 이 정도의 성능이라면 충분히 좋다고 판단하기에 특별히 개선하진 않을 것
*/

class Solution {
public:
    int toVisit[100'000];
    int stkPtr = 0;

    int answers[100'001];
    int answerPtr = 2;

    int getAnswer(int depth)
    {
        answers[0] = 0;
        answers[1] = 1;

        if (depth >= answerPtr)
        {
            for (answerPtr; answerPtr<=depth; ++answerPtr)
                answers[answerPtr] = (answers[answerPtr-1] << 1) % 1'000'000'007;
        }

        return answers[depth];
    }

    int log2Int(int a)
    {
        int result = 0;
        while(a > 1)
        {
            a >>= 1;
            result++;
        }
        return result;
    }
    
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        const int m = edges.size();
        const int n = queries.size();
        const int log2M = log2Int(m+2)+1;

        vector<vector<int>> adjVec(m+2);
        vector<int> depth(m+2);
        vector<vector<int>> ancestor(m+2,vector<int>(log2M,0));
        vector<int> result;
        result.reserve(n);
        
        for (const auto& e : edges)
        {
            adjVec[e[0]].push_back(e[1]);
            adjVec[e[1]].push_back(e[0]);
        }

        toVisit[stkPtr++] = 1;
        depth[1] = 0;

        while(stkPtr > 0)
        {
            auto curNode = toVisit[--stkPtr];
            auto& curNodeParent = ancestor[curNode][0];

            for (const auto& adjNode : adjVec[curNode])
            {
                if (adjNode != curNodeParent)
                {
                    depth[adjNode] = depth[curNode]+1;
                    ancestor[adjNode][0] = curNode;

                    for (int i=1; i<log2M; ++i)
                    {
                        int nextAnc = ancestor[ancestor[adjNode][i-1]][i-1];
                        if (nextAnc != 0)
                            ancestor[adjNode][i] = nextAnc;
                        else
                            break;
                    }

                    toVisit[stkPtr++] = adjNode;
                }
            }
        }
        
        for (const auto& query : queries)
        {
            int dist = 0;
            auto node1 = query[0];
            auto node2 = query[1];

            if (depth[node1] > depth[node2])
                swap(node1, node2);
            
            int diff = depth[node2] - depth[node1];
            int ancPtr = 0;
            dist += diff;

            while(diff)
            {
                if (diff & 1)
                    node2 = ancestor[node2][ancPtr];

                ancPtr++;
                diff >>= 1;
            }

            if (node1 == node2)
            {
                result.push_back(getAnswer(dist));
                continue;
            }

            int node1Depth = depth[node1];

            for (int i=log2M-1; i>=0; --i)
            {
                if (ancestor[node1][i] != ancestor[node2][i])
                {
                    node1 = ancestor[node1][i];
                    node2 = ancestor[node2][i];
                }
            }

            dist += (node1Depth-depth[node1]+1)*2;

            result.push_back(getAnswer(dist));
        }

        return result;
    }
};
int main()
{
    Solution s;

    return 0;
}