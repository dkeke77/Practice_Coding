#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

/*
@접근
    어제 문제였던 부분배열 문제에서 동일 부분배열 재사용 금지가 추가된 문제임
    제약조건 또한 거의 동일하나, k가 최대 10^5번이라는 점이 핵심임
    따라서 pq와 bfs를 통한 상태공간 탐색이 주효할 것으로 생각됨
    그런데 다음 구간에서 현재 최대/최소를 버리게 되면, 새로운 최대/최소를 구해야함
    이 과정에서 구간 전체를 탐색해서 새로운 최대/최소를 탐색하는 것은 비효율적임
    그렇다면 세그먼트 트리를 이용해서 구간의 최대/최소를 탐색하는 것이 제일 적합하다고 생각됨

    세그먼트 트리 쿼리 과정에서 어려움이 있었음
    구간을 어떻게 탐색할지부터가 꽤 난관이었는데, 구간의 제일 왼쪽부터 제거해가는 방향으로 잡음
    이 때, 탐색된 구간은 정확하게 fit해야함
    처음 구현했던 로직은 제일 왼쪽에서 fit한 구간을 찾은 다음에, 구간의 시작점을 찾은 구간의 end+1로 이동함
    그리고 부모로 거슬러가며 새로운 시작점에 fit한 구간을 찾음
    하지만 이 방법은 사촌 노드를 계속 참조하게 될 수도 있고, 구현이 너무 복잡했음
    때문에 다른 관점을 생각해보았는데, dive/float 관점임
    먼저 수행하는 dive는 이전과 동일하게 제일 왼쪽에서 fit한 구간을 찾고 시작점을 옮김
    그리고 해당 시작점과 일치하는 최대 길이 구간을 만날때까지 float한다는 방향임
    하지만 float를 적절하게 구현하는 것은 꽤 어려운 일임
    동시에 매번 루트에서 탐색하더라도 균형 이진트리이기에 안정적으로 빠름
    따라서 dive까지만 수행하고 루트로 회귀하여 다음 구간을 찾는 것이 제일 적절함

    실행 결과, 548ms(over 70.97%), 205MB(over 66.13%)
    꽤 준수한 성능을 보여줌
    여기서 더 높은 성능을 확보하려면 아마 방문 확인용 해시를 다른 자료구조로 대체하는 것을 생각해볼 수 있으나,
    최대 2.5 * 10^9개의 bool을 보관하고 관리하기엔 부담스러움
     ㄴ bitset이 제일 적당해보이나, 구현하기 귀찮다!
    시간 복잡도는 O(nlogn + klogn) 정도로 생각됨
     ㄴ 초기 세그먼트 트리 구성에 2nlogn, 그리고 k번 구간을 방문하면서 세그먼트 트리를 탐색하기에 k*logn
     ㄴ 그런데 한번에 세그먼트 트리 탐색이 끝나지 않을 수 있기에 k*logn보다 클 수 있음
     ㄴ pq도 어느 정도 시간을 소요하겠지만, 정확히 얼마나 소요할지는 알기 어려움
    
    힌트에선 RMQ를 구성하는 것을 말하고, 상위 풀이에서는 희소 테이블(Sparse Table)을 구성하는 것으로 풀어냄
    단순히 최대/최소 쿼리용으로 사용할 수도 있고, 구간이 커짐에 따라 값도 단조 증가한다는 사실을 이용할 수도 있음
    희소 테이블 자체는 세그먼트 트리와 크게 다르진 않지만, 탐색 시 중복 배열 검사를 하지 않아도 된다는 장점이 있음
    하지만 희소 테이블이 공간복잡도는 더 많이 사용하게 됨
     ㄴ O(nlogn)이지만, 세그먼트 트리 방식은 O(n) (트리 8n, 해시 2k)
*/

struct Block
{
    int begin;
    int end;
    int minVal;
    int maxVal;

    long long val() const
    { return static_cast<long long>(maxVal - minVal); }

    bool operator<(const Block& other) const
    { return val() < other.val(); }
};

class Solution {
public:
    const vector<pair<int,int>> MOVE_SET = {{1,0}, {0,1}};

    const int SEG_TYPE_MIN = 0;
    const int SEG_TYPE_MAX = 1;

    inline long long makeKey(int begin, int end) const
    { return end * 50'001LL + begin; }

    void buildSegTree(const vector<int>& nums, vector<int>& segTree, const int SEG_TYPE)
    {
        for (int i=0; i<nums.size(); ++i)
        {
            int begin = 0;
            int end = nums.size()-1;
            int index = 0;

            while(begin != end)
            {
                int mid = (begin + end) / 2;
                if (i <= mid)
                {
                    end = mid;
                    index = 2*index + 1;
                }
                else
                {
                    begin = mid+1;
                    index = 2*index + 2;
                }
            }
            segTree[index] = nums[i];
            index = (index-1) / 2;

            if (SEG_TYPE == SEG_TYPE_MIN)
            {
                while(index > 0)
                {
                    int childL = 2*index + 1;
                    int childR = 2*index + 2;
                    segTree[index] = min(segTree[childL], segTree[childR]);
                    index = (index-1) / 2;
                }
                segTree[index] = min(segTree[2*index+1], segTree[2*index+2]);
            }
            else if (SEG_TYPE == SEG_TYPE_MAX)
            {
                while(index > 0)
                {
                    int childL = 2*index + 1;
                    int childR = 2*index + 2;
                    segTree[index] = max(segTree[childL], segTree[childR]);

                    index = (index-1) / 2;
                }
                segTree[index] = max(segTree[2*index+1], segTree[2*index+2]);
            }
        }
    }

    int queryBlockMinMax(vector<int>& segTree, const int blckBegin, const int blckEnd, const int SEG_TYPE)
    {
        int nextBegin = blckBegin;
        int result = 0;

        if (SEG_TYPE == SEG_TYPE_MIN)
            result = 1e9;
        
        while(nextBegin <= blckEnd)
        {
            int begin = 0;
            int end = segTree.size() / 4 - 1;
            int index = 0;
            
            // dive
            while(nextBegin != begin)
            {
                int mid = (begin + end) / 2;
                if (nextBegin <= mid)
                {
                    end = mid;
                    index = 2*index + 1;
                }
                else
                {
                    begin = mid+1;
                    index = 2*index + 2;
                }
            }
            while (end > blckEnd)
            {
                end = (begin + end) / 2;
                index = 2*index + 1;
            }

            if (SEG_TYPE == SEG_TYPE_MIN)
                result = min(result, segTree[index]);
            else if (SEG_TYPE == SEG_TYPE_MAX)
                result = max(result, segTree[index]);
            nextBegin = end+1;
        }

        return result;
    }

    long long maxTotalValue(vector<int>& nums, int k) {
        const int n = nums.size();
        long long result = 0;

        vector<int> minSegTree(4*n,nums.front());
        vector<int> maxSegTree(4*n,nums.front());
        buildSegTree(nums, minSegTree, SEG_TYPE_MIN);
        buildSegTree(nums, maxSegTree, SEG_TYPE_MAX);
        
        int gMin = nums.front();
        int gMax = nums.front();

        unordered_set<long long> isVisited;
        priority_queue<Block> toVisit;
        toVisit.push({0, n-1, minSegTree.front(), maxSegTree.front()});

        while(!toVisit.empty())
        {
            auto curBlock = toVisit.top();
            toVisit.pop();
            k--;
            result += curBlock.val();

            if (k > 0)
            {
                if (curBlock.begin == curBlock.end) continue;

                for (const pair<int,int>& mv : MOVE_SET)
                {
                    int nextBegin = curBlock.begin + mv.first;
                    int nextEnd = curBlock.end - mv.second;
                    int nextBlockKey = makeKey(nextBegin, nextEnd);
                    if (isVisited.find(nextBlockKey) == isVisited.end())
                    {
                        isVisited.insert(nextBlockKey);
                        
                        int lMin = curBlock.minVal;
                        int lMax = curBlock.maxVal;
                        int valToPop = 0;

                        if (mv.first)
                            valToPop = nums[curBlock.begin];
                        else if (mv.second)
                            valToPop = nums[curBlock.end];

                        if (valToPop == lMin)
                            lMin = queryBlockMinMax(minSegTree, nextBegin, nextEnd, SEG_TYPE_MIN);
                        else if (valToPop == lMax)
                            lMax = queryBlockMinMax(maxSegTree, nextBegin, nextEnd, SEG_TYPE_MAX);

                        toVisit.push({nextBegin, nextEnd, lMin, lMax});
                    }
                }
            }
            else
                break;
        }

        return result;
    }
};

int main()
{
    Solution s;

    vector<int> v;

    //s.maxTotalValue(v,1);

    return 0;
}