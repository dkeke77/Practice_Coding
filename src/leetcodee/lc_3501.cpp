#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    우선 이전처럼 배열에서 0-1 블럭의 길이를 저장하고, 인접한 0블럭의 길이합 중 최대를 찾아야함
    하지만 그 구간이 고정적이지 않고, 경우엔 따라서 블럭을 잘라야할 수도 있음
    아무튼 구간의 최댓값을 빠르게 구해야하므로 세그먼트 트리를 떠올릴 수 있음
     ㄴ 잘리는 블럭이 1이라면 신경 쓸 필요 없음
     ㄴ 0이라면 그 블럭과 연관된 블럭들까지 구간에서 제외하고, 해당 블럭만 별도 처리하면 됨
    하지만 세그먼트 트리에 어떤 것을 저장할진 고민해봐야함

    아니면 trade 후보 배열에 대해 Sparse Table를 만드는건 어떰?
    온전한 블럭만 사용하는 구간만 빼내고, 해당 구간에 대해 RMQ 쿼리를 수행하고, 잘린 블럭만 따로 처리해서 최종 결과 도출
    그리고 1 총합에 해당 결과를 더하면 쿼리 결과 완료
    하지만 Sparse Table는 기본적으로 n^2 정도의 크기 배열을 필요로 하기 때문에, 현재 문제에선 적용하기 어려움
    따라서 어쩔 수 없이 세그먼트 트리를 통해 해결해야 할 것으로 보임

    이 문제를 풀기 위해선 2가지 자료구조를 병행해야 되는 것으로 판단됨
    0블럭들을 저장해놓은 배열과, 그 구간안에 정답 후보의 최댓값을 알려주는 세그먼트 트리
     ㄴ 정답 후보란 1블럭 앞뒤의 0블럭들의 길이 합
     ㄴ 트리는 0블럭의 배열 인덱스를 기준으로 구성
    트리 검색은 top-donw 방식으로 구현하다가 bottom-up 방식으로 바꿔서 구현함
     ㄴ width와 idx의 짝수 여부만 체크하면 되기에 구현이 더 간단함

    예상대로 양 끝단에 걸치는 0블럭의 처리가 곤란하였음
    따라서 양 끝단은 무조건 세그먼트 트리 검색에서 제외하고 별도로 계산하기로 함
    실행 결과, 171ms(over 40.76%), 253MB(over 99.59%)
    아무래도 양 끝단 처리이 복잡하기에 오래 걸리는 것으로 예상됨
    혹은 세그먼트 트리 관련 처리가 느린 것일 수도 있겠지만, 구축은 O(n)수준으로 효율적임
    검색은 작은 범위부터 시작하기에 다소 느릴 수도 있겠지만, 그 영향은 극히 미미할 것으로 생각됨

    다른 풀이에선 Sparse Table을 사용했는데, 사실 메모리 사용량에 대해 내가 잘못 생각했던 부분이 있었음
     ㄴ Sparse Table의 공간 복잡도는 O(logn*n)정도임
    아무튼 해당 풀이에선 0/1 블럭을 모두 저장하고, 정답 후보 또한 각 블럭에 대해 생성함
     ㄴ 1블럭이라면 인접 0블럭 길이 합, 0블럭이면 0
    위 정답 후보를 Sparse Table로 만듦
    그리고 각 인덱스가 어느 블럭에 속하는지 빠르게 알 수 있도록, 인덱스 배열에 블럭 번호를 적어서 이를 통해 접근함
     ㄴ 이 부분에서 시간 차이가 많이 났으리라 생각됨
     ㄴ 내 코드에선 매번 lower_bound을 2번하여 블럭의 위치를 식별하기 때문
    또한 이 풀이에서도 양끝단은 빼고 RMQ 쿼리를 수행함

    lower_bound의 대체가 성능 차이의 큰 원인이라고 분석했었고, 이에 따라 lower_bound를 인덱스 배열로 대체하였음
    개선 결과, 93ms(over 74.32%), 254MB(over 99.36%)
    예상대로 성능 차이는 반복된 lower_bound로 인한 것이었음
*/

struct Block
{
    int start;
    int length;

    int begin() const
    { return start; }
    int end() const
    { return start+length; }
};

class SegTree
{
public:
    SegTree(const vector<Block>& origin) : n(origin.size()-1)
    {
        int depth = 0;
        while((1<<depth) < n)
            depth++;
        maxDepth = depth;
        arr.resize((2<<depth) - 1);

        int startIdx = (1<<depth) - 1;
        for (int i=0; i<n; i++)
            arr[startIdx+i] = origin[i].length+origin[i+1].length;

        for (depth--; depth >= 0; depth--)
        {
            startIdx = (1<<depth) - 1;
            for (int i=0; i<(1<<depth); i++)
            {
                int idx = startIdx+i;
                arr[idx] = max(arr[idx*2+1],arr[idx*2+2]);
            }
        }
    }
    int query(int l, int r)
    {
        int result = 0;
        while(l <= r)
        {
            int idx = (1<<maxDepth)-1+l;
            int width = 1;

            while (l+(width<<1) <= r)
            {
                if (idx % 2 == 0) break;
                idx = (idx-1)/2;
                width <<= 1;
            }
            result = max(result, arr[idx]);
            
            l += width;
        }

        return result;
    }

private:
    vector<int> arr;
    const int n;
    int maxDepth;
};

class Solution {
public:
    
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        const int n = s.length();
        const int logn = ceil(log2(n));
        int countOne = s.front() == '1';
        int countZero = s.front() == '0';
        int bStart = 0;
        vector<Block> zeroes;
        zeroes.reserve(n/2);

        for (int i=1; i<n; i++)
        {
            if (s[i] != s[i-1])
            {
                if (s[i] == '0')
                    bStart = i;
                else
                {
                    zeroes.push_back({bStart,countZero});
                    countZero = 0;
                }
            }

            if (s[i] == '0')
                countZero++;
            else
                countOne++;
        }
        if (countZero > 0)
            zeroes.push_back({bStart,countZero});

        if (zeroes.size() < 2)
            return vector<int>(queries.size(), countOne);

        vector<int> quickLowerBound(n,zeroes.size());
        int blckPtr = zeroes.size()-1;
        for (int i=zeroes[blckPtr].end()-1; i>=0; i--)
        {
            if (blckPtr > 0 && zeroes[blckPtr-1].end()-1 == i)
                blckPtr--;
            quickLowerBound[i] = blckPtr;
        }
        SegTree segTr(zeroes);

        vector<int> result;
        result.reserve(queries.size());
        for (const auto& q : queries)
        {
            auto idxL = quickLowerBound[q[0]];
            auto idxR = quickLowerBound[q[1]];
            if (idxL == idxR)
            {
                result.push_back(countOne);
                continue;
            }
            int qResult = segTr.query(idxL+1,idxR-2);

            if (s[q[1]] == '1')
                idxR--;

            if (idxL < idxR)
            {
                if (idxL < zeroes.size()-1)
                {
                    int len0 = 0, len1 = 0;
                    len0 = zeroes[idxL].end() - max(q[0], zeroes[idxL].start);

                    if (idxL+1 == idxR)
                        len1 = min(q[1], zeroes[idxR].end()-1) - zeroes[idxR].start + 1;
                    else
                        len1 = zeroes[idxL+1].length;

                    qResult = max(qResult, len0+len1);
                }
                if (idxR > 0  && s[q[1]] == '0' && idxL+1 != idxR)
                    qResult = max(qResult, zeroes[idxR-1].length + (q[1]-zeroes[idxR].begin()+1));
            }

            result.push_back(countOne + qResult);
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}