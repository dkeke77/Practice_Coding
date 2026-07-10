#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    이전 문제와 다른 점이 있다면 최소 몇개의 노드를 거쳐야 목표 노드까지 갈 수 있느냐를 반환해야함
    따라서 두 노드 사이에 몇개의 노드를 경유해야 하는지 알 수 있어야함
    노드 a,b에 대해, 각각 n1, n2를 nums로써 가진다고 가정하자... (n1<n2)
    그러면 n2-n1 <= maxDiff라면 n1~n2 사이의 모든 노드는 a와 b에 직접 연결되어있음이 보장됨
    따라서 각 노드는 한번에 도달 가능한 제일 먼 노드만 저장하는 것으로 정보를 압축할 수 있음
    그리고 보다 구현을 간편하게 하기 위하여, n1<n2 방향으로만 탐색하도록 하는 편이 좋다고 생각됨

    위 방법대로만 구현하고 TLE이 발생했지만 이는 충분히 예상했던 결과임
    왜냐하면 힌트에서 binary lifting을 언급했기 때문임
    만약 maxDiff가 1이고, nums가 1씩 증가하는 형태로 데이터가 들어온다면,
    매 쿼리마다 최악의 경우 n이 발생하며, 이는 n*q으로 이어짐
    따라서 binary lifting를 통해 빠르게 탐색할 필요가 있음

    실행 결과, 357ms(over 31.58%), 390MB(over 38.16%)
    그리고 쿼리 루프를 더 간략화할 수 있기에 적용했음
    실행 결과, 346ms(over 36.84%), 390MB(over 38.16%)
    결과를 보면 알 수 있듯, 쿼리 루프 간소화는 성능에 영향을 주진 않음
     ㄴ 가독성만 더 나아졌음

     그런데 다른 풀이를 보니, farestNode의 구성 순서가 차이가 있었음
     ㄴ 내 코드의 경우엔 node,step 순이면, 다른 풀이는 step,node 순서임
    해당 순서로 바꾼 결과, 166ms(over 60.53%), 330MB(over 67.11%)
    꽤나 의외의 결과인데, 한 노드의 1개 이상의 step을 보고 이동하기 때문에 step들의 지역성이 높은 편이 캐시 히트에 유리하다고 생각했음
    하지만 실제 결과는 이런 추측과는 정반대로 나왔음
    아무래도 binary lifting 과정에서 발생하는 비용보다 farestNode 구성에 소모하는 비용이 더 컸던 것으로 보임
    farestNode 구성에서는 node들의 지역성이 높은 편이 더 유리함
     ㄴ binary lifting에서는 logn번 farestNode를 sparse하게 참조하기 때문에 캐시 히트를 높여도 그 효과가 크지 않을 것이라고 생각됨
     ㄴ 반면, farestNode 구성에서는 같거나 이전 step의 node들을 사용하기 때문에 이들의 지역성을 높게 하는 편이 캐시 친화적임
*/

class Solution {
public:
    int ceiledLog2(int n)
    {
        int temp = 1;
        int count = 0;
        while(temp < n)
        {
            count++;
            temp <<= 1;
        }

        return count;
    }

    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries)
    {
        const int logn = ceiledLog2(n);
        vector<int> result;
        result.reserve(queries.size());
        vector<int> sortedIdx(n);
        vector<vector<int>> farestNode(logn,vector<int>(n,-1));

        for (int i=1; i<n; i++)
            sortedIdx[i] = i;

        sort(sortedIdx.begin(), sortedIdx.end(), [&nums](int a, int b){ return nums[a] < nums[b]; });

        int ptr = 0;
        for (int i=0; i<n-1; i++)
        {
            ptr = max(ptr,i);
            while(ptr < n-1)
            {
                if (nums[sortedIdx[ptr+1]] - nums[sortedIdx[i]] <= maxDiff)
                    ptr++;
                else
                    break;
            }

            if (i < ptr)
                farestNode[0][sortedIdx[i]] = sortedIdx[ptr];
        }

        for (int i=1; i<logn; i++)
        {
            for (int j=0; j<n; j++)
            {
                if (farestNode[i-1][j] == -1)
                    continue;
                
                farestNode[i][j] = farestNode[i-1][farestNode[i-1][j]];
            }
        }

        for (const auto& query : queries)
        {
            if (query[0] == query[1])
            {
                result.push_back(0);
                continue;
            }

            int curr = query[0];
            int target = query[1];
            int dist = 0;

            if (nums[curr] > nums[target])
                swap(curr,target);

            for (int step = logn-1; step>=0; step--)
            {
                if (farestNode[step][curr] != -1)
                {
                    if (nums[farestNode[step][curr]] < nums[target])
                    {
                        dist += (1<<step);
                        curr = farestNode[step][curr];
                    }
                }
            }

            if (nums[target] - nums[curr] <= maxDiff)
                result.push_back(dist+1);
            else
                result.push_back(-1);
        }

        return result;
    }
};
int main()
{
    Solution s;

    return 0;
}