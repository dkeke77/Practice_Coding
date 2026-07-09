#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    우선 어떤 노드들이 같은 네트워크 내에 있는 빠르게 알기 위하여 Union-find를 적용하기로 함
    그런데 노드를 연결할때 모든 노드와 비교해보는 것은 비효율적임
    그래서 nums 배열에 대한 인덱스 배열을 정렬하여, 이를 기반으로 처리하는 것이 적절함
     ㄴ side effect로 path compression 등이 불필요지는 장점도 있음
    실행 결과, 92ms(over 12.88%), 229MB(over 36.16%)

    그런데 정렬되어있는 것이 nums가 아니라 queries로 착각하고 있었음
    따라서 굳이 정렬을 다시 수행할 필요가 없으며, 동시에 인덱스 배열 또한 불필요해짐
    실행 결과, 9ms(over 76.16%), 224MB(over 93.97%)

    또한 추가로 unions에 대한 초기화(자기자신을 union으로 설정)는 딱히 필요하지 않음도 식별함
    따라서 해당 과정을 없애고, union 구성 과정에서 이전 노드와 연결되지 않는다면 자기자신을 union으로 설정하도록 함
    실행 결과, 0ms(over 100%), 224MB(over 78.36%)
*/

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> unions(n,0);
        
        for (int i=1; i<n; i++)
        {
            if (nums[i]-nums[i-1] <= maxDiff)
                unions[i] = unions[i-1];
            else
                unions[i] = i;
        }

        vector<bool> result;
        result.reserve(queries.size());

        for (const auto& query : queries)
            result.push_back(unions[query[0]] == unions[query[1]]);

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}