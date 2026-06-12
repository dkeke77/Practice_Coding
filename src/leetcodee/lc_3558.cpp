#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

/*
@접근
    최대 깊이 d의 노드에 도달하는 d개의 엣지를 지나야함
    그리고 이 노드말고도 다른 노드가 깊이 d에 있다면, k개의 엣지를 공유하는 경우도 생각해야됨
    따라서 k+j=d라고 하면... case(k) * case(j) * case(j)로 계산해야하는 것
    이를 정리하면 경로들을 추출하고, 경로 중 중복되는 부분을 독립된 경로로 분리하고, 다른 경로들에서 해당 부분을 제거해야됨
    그리고 각 경로들의 경우의수를 곱하면 됨
    경우의 수는 조합을 통해 구할 수도 있지만 dp를 쓰는 것이 적절해보임
     ㄴ 1,2, 각각 n/2개와 (n-1)/2개를 순서 상관없이 배치하는 문제
     ㄴ 2n 타일링 문제에서 봤던 것처럼 홀수 케이스
    
    문제를 너무 복잡하게 생각했음
    단순히 제일 깊은 노드 하나만 선택하여 처리하면 됨
    그 경우엔 깊이 d에 대해, 2^(d-1)개 경우의수가 발생함
     ㄴ 전체 경우의수는 2^d이고, 여기서 짝수와 홀수가 정확히 절반씩 있음
        ㄴ 가중치가 1 혹은 2이기 때문에 0에 대해서는 생각할 필요가 없음
     ㄴ 따라서 홀수가 되는 경우의수는 그의 절반인 2^(d-1)
    실행 결과, 330ms(over 37.50%), 348MB(over 34.21%)

@개선
    보다 성능을 더 올리기 위해 여러 개선을 적용해봄
    먼저 stack을 int 배열과 인덱스 포인터로 대체함
    그 결과, 312ms(over 42.76%), 345MB(over 37.50%)
    그리고 매번 2^n-1를 계산하는 것이 아니라 정답을 캐싱하도록 함
    그 결과, 273ms(over 77.63%), 325MB(over 88.82%)
     ㄴ 성능은 적지 않게 개선된 것을 보아, 매번 계산하는 것이 비용이 은근히 들었던 걸로 보임
     ㄴ 그리고 의외로 메모리를 크게 줄일 수 있었는데, for문으로 누적되는 임시 데이터들 때문으로 보임
    이 이상 줄이려면 puring이나 다른 접근법을 시도해야한다고 생각됨
    하지만 puring을 하기엔, 현재 노드가 더 유망한지 파악하기 어렵고 그 효과도 덜할 것으로 생각됨
     ㄴ 무조건 제일 깊은 노드까지 가야지만 알 수 있고, 남은 노드 개수를 기준으로 puring하는 것은 효과가 미미할 것으로 생각됨
    혹은 인접리스트 구성을 더 나은 방법을 적용할 수 있을지도 모름
*/

class Solution {
public:
    pair<int,int> toVisit[100'000];
    int stkPtr = 0;

    int answers[100'001];
    int answerPtr = 2;
    
    int assignEdgeWeights(vector<vector<int>>& edges) {
        answers[0] = 0;
        answers[1] = 1;

        const int n = edges.size();
        int result = 1;
        int maxDepth = 0;
        vector<vector<int>> adjVec(n+2);
        vector<bool> isVisited(n+2,false);
        
        for (const auto& e : edges)
        {
            adjVec[e[0]].push_back(e[1]);
            adjVec[e[1]].push_back(e[0]);
        }

        toVisit[stkPtr++] = {1,0};
        isVisited[1] = true;

        while(stkPtr > 0)
        {
            auto curNode = toVisit[--stkPtr];

            for (const auto& adjNode : adjVec[curNode.first])
            {
                if (!isVisited[adjNode])
                {
                    isVisited[adjNode] = true;
                    toVisit[stkPtr++] = {adjNode,curNode.second+1};
                    maxDepth = max(maxDepth,curNode.second+1);
                }
            }
        }

        if (maxDepth >= answerPtr)
        {
            for (answerPtr; answerPtr<=maxDepth; ++answerPtr)
                answers[answerPtr] = (answers[answerPtr-1] << 1) % 1'000'000'007;
        }

        return answers[maxDepth];
    }
};

int main()
{
    Solution s;

    return 0;
}