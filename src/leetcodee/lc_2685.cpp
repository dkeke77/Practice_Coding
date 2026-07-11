#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    이 문제에 대해 2가지 풀이를 생각할 수 있음
    union-find와 bfs인데, 각각의 장단은 다음과 같음
    union-find
     ㄴ 추가 공간 n만을 요구하며 성능은 최소 e+n이 소모될 것임
     ㄴ 하지만 path compression과 같은 기법이 있어야 중복된 방문이 적을것
    bfs
     ㄴ 성능은 e+n만큼만 발생하며, 구현이 간단함
     ㄴ 하지만 추가 공간을 e만큼 요구함
    union-find를 많이 안 써봤으니 이번엔 union-find를 구현해보기로 함
    실행 결과, 2ms(over 99.06%), 117MB(over 98.43%)

    다른 풀이로는 각 노드의 엣지 개수가 (네트워크의 노드 개수 - 1)임을 이용하는 방법도 있는데,
    이 방법은 dfs/bfs로 각 노드를 방문하면서 엣지 개수를 확인하면 됨
     ㄴ 모든 노드가 동일한 엣지 개수를 가지는지, 그리고 순회 종료 후 그 엣지 개수가 위의 조건에 부합하는지 확인하면 될듯
*/

class Solution {
public:
    int unionFind(vector<int>& unions, int u)
    {
        while(unions[u] != u)
        {
            unions[u] = unions[unions[u]];
            u = unions[u];
        }

        return u;
    }
    void unionMerge(vector<int>& unions, vector<int>& unionSize, int head, int tail)
    {
        unions[tail] = head;
        unionSize[head] += unionSize[tail];
        unionSize[tail] = 0;
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        int answer = 0;
        vector<int> unions(n);
        vector<int> unionSize(n,1);
        vector<int> edgeCount(n,0);

        for (int i=0; i<n; i++)
            unions[i] = i;
        
        for (const auto& e : edges)
        {
            int u0 = unionFind(unions, e[0]);
            int u1 = unionFind(unions, e[1]);

            if (u0 != u1)
            {
                if (unionSize[u0] < unionSize[u1])
                    unionMerge(unions, unionSize, u1, u0);
                else
                    unionMerge(unions, unionSize, u0, u1);
            }
        }

        for (const auto& e : edges)
            edgeCount[unionFind(unions, e[0])]++;

        for (int i=0; i<n; i++)
        {
            int uSize = unionSize[i];
            if (uSize > 0)
            {
                int fullEdge = (uSize-1)*uSize/2;
                if (fullEdge == edgeCount[i])
                    answer++;
            }
        }

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}