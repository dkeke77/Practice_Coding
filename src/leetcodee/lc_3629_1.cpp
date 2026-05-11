#include <iostream>>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
@접근
    뒤로 한칸 움직이는 동작 때문에 DP처럼 선형적인 접근은 불가능
    따라서 BFS를 적용하는 것이 적절하다고 판단됨
    최소거리라서 빠르게 끝낼 수도 있고,
    한 셀에 여러 개의 노드가 동시에 존재하지 않기에 메모리 사용이 극심하진 않을 것으로 예상됨

    뒤로 텔레포트하는 행위는 이득이 없으므로 하는 것으로 생각됨
    따라서 앞으로 텔레포트, 앞뒤 한칸 이동만 하는 것으로 고려...

    그런데 뒤로 텔레포트해야 통과하는 케이스 발견
     ㄴ 텔레포트로 한참 앞으로 이동해버렸다면, 뒤쪽의 많은 셀들은 미방문 상태 -> 텔레포트를 이용하여 뒤로 가는 것이 더 나음

    소수 해시 버킷을 만들면서 문제가 발생함..
     ㄴ 최대 9600개 가량의 소수가 존재함
     ㄴ 그런데 소수 해시 버킷은 O(p*n)이기에 약 9.6*10^8의 시간복잡도가 발생함
     ㄴ 따라서 20000번만 버킷 루프를 돌아도 TLE 발생

@성공1
    BFS를 사용하며, 노드 탐색 도중 이동 규칙에 앞/뒤 노드와 텔레포트를 처리하도록 하였음
    그런데 모든 수를 매번 텔레포트 가능한지 확인하는 것은 비효율적이고, 이를 해결하는 것을 목표로 하였음
    우선 소수 해시를 일부 정리하도록 하였음
    만약 해당 소수가 1번만 등장하는데, 최댓값의 절반보다 크다면 -> 해당 소수로 텔레포트 가능한 수는 없음
    위 규칙에 따라서 유망하지 않은 소수를 먼저 지우도록 하였음
    또한 모든 수에 대해 텔레포트 후보를 순회하기 보다, 텔레포트할 수 있는 수를 미리 정리하도록 하였음
     ㄴ 이를 pool이라고 함
    pool은 비소수들중에서 텔레포트할 수 있는 것들만 모아둔 것임
    BFS 순회 중 소수인 노드를 만난다면, 해당 소수의 인덱스들을 추가하고,
    그리고 pool을 순회하며 텔레포트할 수 있는 대상들을 추가함
    추가된 것들과 이미 방문했던 노드들을 pool에서 제외함
    이 때, pool의 크기를 조정하는 연산은 비용이 적지 않으므로, 재사용될 데이터만 앞으로 보내고 이들의 개수만 갱신하도록 함

    그런데 계속 TLE이 나왔는데, 원인은 pool 정리 로직에 있었음
    pool 정리 로직이 그 비용이 얻는 이익보다 적었던 것이 원인으로 보임
    애시당초, 텔레포트할 수 있는 노드를 탐색하는 행동은 어차피 BFS에서 수행되므로 동일한 일을 2번 하는 것과 같아짐
    이를 막기 위해 각 소수별로 노드를 정리하는 것이 아닌, 텔레포트 가능한 노드를 발견하면 루프 조기 종료하도록 하였음
    그러나 테스트 케이스를 분석한 결과, 조기 종료되는 시점은 상당히 늦다는 사실을 발견함
    즉, p*(p-n)에 근접하는 반복이 발생하였기에 TLE이 발생하였던 것
    pool의 크기를 100배 넘게 줄이기에 나중 과정에선 실효성 있을 것으로 보이나, 전체에 대한 검사 자체가 너무 무거웠음

    해당 연산을 제외한 결과, 2747ms(over 5.00%), 186MB(over 91.00%)가 나옴

@성공2
    다른 풀이에서는 각 값이 어느 인덱스에 있는지 저장하는 방식을 사용함
     ㄴ 이 풀이에서는 동일한 숫자가 나올 시, 기존 인덱스를 별도의 배열에 저장하고 새로운 인덱스로 덮어씀
     ㄴ 동일한 수들의 인덱스에 대한 연결 리스트를 배열에 집어넣었다고 이해하면 됨
     ㄴ 이를 해당 풀이 저자는 Adjacency Mapping라고 함
     ㄴ 또한 소수는 에라토스테네스의 체 방법을 이용해 미리 계산해둠
    위 풀이 중 값에 대한 인덱스를 저장하는 배열을 적용해봄

    그 결과, 1927ms(over 5.00%), 319MB(over 52.31%)가 나옴
    약 800ms 정도의 성능 향상을 확인하였으나, 메모리는 약 2배 정도 사용하게됨
    또한 여전히 성능이 평균보다 아래임
    그리고 소수가 아닌 동일한 수들에 대한 대처가 안됨
     ㄴ 테스트 케이스에선 이러한 경우가 없어 통과한 것으로 보임
    따라서 해당 풀이에서 사용했던 Adjacency Mapping를 사용해야 이런 문제를 예방할 수 있음
    
    추가로 에라토스테네스의 체 방법으로 미리 소수를 계산해두는 방식도 적용해봄
     ㄴ 해당 방식은 C++17 이상에서만 사용 가능함
     ㄴ static inline 변수이기 때문...
    그 결과, 1634ms(over 5.65%), 323MB(over 51.56%)가 나옴
    유의미한 성능 향상이 있었으나, 여전히 평균에는 한참 떨어져있음
    따라서 핵심적인 성능 저하의 원인은 아님
    
*/

class Solution {
public:
    int minJumps(vector<int>& nums) {
        const int DIST_INIT_VLAUE = 1e6;

        vector<int> dist(nums.size(), DIST_INIT_VLAUE);
        vector<int> pool;
        queue<int> toVisit;
        unordered_map<int,vector<int>> primeIdx;

        vector<int> valToIdx(DIST_INIT_VLAUE+1,-1);

        int maxValue = 0;
        int poolEnd = 0;

        for (int i = 0; i < nums.size(); ++i)
        {
            maxValue = max(maxValue, nums[i]);
            valToIdx[nums[i]] = i;
            if (nums[i] == 1) continue;

            if (isPrime(nums[i]))
            {
                primeIdx[nums[i]].push_back(i);
            }
            // else
            //     pool.push_back(i);
        }

        for (auto it = primeIdx.begin(); it != primeIdx.end();)
        {
            if (it->first > maxValue/2 && it->second.size() < 2)
                it = primeIdx.erase(it);
            else
                ++it;
        }

        // if (!primeIdx.empty())
        // {
        //     for (int i = 0; i < pool.size(); ++i)
        //     {
        //         for (auto it = primeIdx.begin(); it != primeIdx.end(); ++it)
        //         {
        //             if (nums[pool[i]] % it->first == 0)
        //             {
        //                 pool[poolEnd] = pool[i];
        //                 poolEnd++;
        //                 break;
        //             }
        //         }
        //     }
        // }
        
        dist[0] = 0;
        toVisit.push(0);

        while(dist[nums.size()-1] == DIST_INIT_VLAUE && !toVisit.empty())
        {
            int curIdx = toVisit.front();
            int curDist = dist[curIdx];
            toVisit.pop();

            auto iter = primeIdx.find(nums[curIdx]);

            // check teleportable
            if (iter != primeIdx.end())
            {
                int toRemain = 0;
                
                for (const auto& pIdx : iter->second)
                {
                    if (dist[pIdx] > curDist+1)
                    {
                        dist[pIdx] = curDist+1;
                        toVisit.push(pIdx);
                    }
                }

                for (int i = nums[curIdx]*2; i <= maxValue; i += nums[curIdx])
                {
                    if (valToIdx[i] != -1 && dist[valToIdx[i]] == DIST_INIT_VLAUE)
                    {
                        dist[valToIdx[i]] = curDist+1;
                        toVisit.push(valToIdx[i]);
                    }
                }

                // for (int i = 0; i < poolEnd; ++i)
                // {
                //     if (nums[pool[i]] % nums[curIdx] == 0 && dist[pool[i]] > curDist+1)
                //     {
                //         dist[pool[i]] = curDist+1;
                //         if (pool[i] != nums.size()-1)
                //         toVisit.push(pool[i]);
                //         else
                //             break;
                //     }
                //     else if (dist[pool[i]] == DIST_INIT_VLAUE)
                //     {
                //         pool[toRemain] = pool[i];
                //         toRemain++;
                //     }
                // }

                primeIdx.erase(iter);
                poolEnd = toRemain;
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

    bool isPrime(const int num)
    {
        for (int i = 2; i*i <= num; ++i)
        {
            if (num % i == 0)
                return false;
        }

        return true;
    }
};

int main()
{
    Solution s;
    vector<int> v = {1,2,4,6};
    s.minJumps(v);

    return 0;
}