#include <iostream>>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
@성공3
    2개 배열을 이용하는 풀이를 사용해봄
     ㄴ 1번 파일에서 언급했던 Adjacency Mapping 방법
     ㄴ 해당 값을 가지는 제일 끝 인덱스를 저장하는 배열과 동일한 값이 직전에 어느 인덱스였는지 저장하는 배열
    또한 소수는 에라토스테네스의 체 방법을 이용해 미리 계산해두고 사용
     ㄴ 원래 풀이는 static inline을 사용하기에 C++14에선 불가능했으나, 조금 우회하는 방법을 사용하여 유사하게 구현함
    이 방법은 단순히 미리 계산해둔 소수표에 따라 소수를 판별함
    만약 소수라면 해당 소수의 배수로 인덱스 배열을 참조함
    그리고 직전 동일값 인덱스 배열을 통해, 동일한 값들에 대해서도 참조함
    
    처음에는 생각보다 속도가 안 나왔었는데, 2가지 원인이 있었음
    1) 텔레포트 후, valToIdx[i] = -1 누락
        이는 이전 풀이에서 pool에서 사용했던 노드들을 제거하는 것과 동일함
        이 때문에 방문했던 노드들을 불필요하게 순회하게 되었음
        다만 dist에 의해 이미 방문했던 노드들은 bfs에 추가되지 않았기에 오답이 나오는 상황은 없었음
        또한 이를 수정하여 개선된 성능은 미미했음
    2) 과도하게 큰 배열 사용
        매 케이스마다 사용하는 배열들을 너무 크게 할당했었음
         ㄴ 대표적으로 인덱스 배열
        때문에 큰 초기화 비용과 낮은 지역성이 발생했고, 성능 저하로 이어졌음
        따라서 배열의 크기들을 최댓값이나 nums 크기에 맞게 재설정해주었음
        이것으로 성능이 엄청나게 개선됐음
    수행 결과, 93ms(over 94.91%), 274MB(over 70.65%)가 나옴
    배열 크기 조정으로 인해 1549ms->93ms로 엄청나게 성능이 개선됐음
    nums 순회 중에 겸사겸사 최댓값을 구하는 것이 더 괜찮다고 생각했지만,
    그것보다 적절한 배열 크기를 할당하는 것이 더 중요했음
*/

class Solution {
public:
    static constexpr int MAX_VAL = 1e6;
    static constexpr int MAX_LEN = 1e5;
    static const vector<bool>& spf()
    {
        static const vector<bool> pv = []()
            {
                vector<bool> p(MAX_VAL+1,true);
                p[0] = false;
                p[1] = false;
                
                for (int i = 2; i <= 1000; ++i)
                {
                    if (p[i])
                    {
                        for (int j = i * i; j < MAX_VAL; j += i)
                        {
                            p[j] = false;
                        }
                    }
                }

                return p;
            }();

        return pv;
    }

    int minJumps(vector<int>& nums) {
        int maxValue = *max_element(nums.begin(), nums.end());

        vector<int> dist(nums.size(), MAX_VAL);
        vector<int> valToIdx(maxValue+1,-1);
        vector<int> prevSameNumIdx(nums.size(),-1);
        vector<bool> isVisited(maxValue+1,false);
        queue<int> toVisit;

        for (int i = 0; i < nums.size(); ++i)
        {
            prevSameNumIdx[i] = valToIdx[nums[i]];
            valToIdx[nums[i]] = i;
        }
        
        dist[0] = 0;
        toVisit.push(0);

        while(dist[nums.size()-1] == MAX_VAL && !toVisit.empty())
        {
            int curIdx = toVisit.front();
            int curDist = dist[curIdx];
            int curVal = nums[curIdx];
            toVisit.pop();

            if (spf()[curVal] && !isVisited[curVal])
            {
                isVisited[curVal] = true;
                for (int i = curVal; i <= maxValue; i += curVal)
                {
                    for (int j = valToIdx[i]; j != -1; j = prevSameNumIdx[j])
                    {
                        if (dist[j] > curDist+1)
                        {
                            dist[j] = curDist+1;
                            toVisit.push(j);
                        }
                    }
                    valToIdx[i] = -1;
                }
            }

            if (curIdx > 0 && dist[curIdx-1] > curDist+1)
            {
                dist[curIdx-1] = curDist+1;
                toVisit.push(curIdx-1);
            }
            if (curIdx < nums.size()-1 && dist[curIdx+1] > curDist+1)
            {
                dist[curIdx+1] = curDist+1;
                toVisit.push(curIdx+1);
            }
        }
        
        return dist[nums.size()-1];
    }
};

int main()
{
    Solution s;
    vector<int> v = {1,2,4,6};
    cout << s.minJumps(v) << endl;

    return 0;
}