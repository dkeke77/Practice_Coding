#include <iostream>>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
@성공4
    SPF를 이용하는 풀이를 사용해봄
    이 풀이도 미리 계산을 하지만, 그 결과는 소수의 여부가 아님
    각 숫자가 가지는 소인수 중 최소를 배열에 저장함
    그리고 nums의 원소에 대해, 연속적으로 SPF를 확인함
     ㄴ SPF 확인하고, 그 최소 소인수로 최대한 나누고.. 를 반복
    그러면 자연스럽게 소인수 분해를 하게 됨
    즉, 각 값들에 대한 소인수 분해를 통해, 소수들이 어디로 텔레포트할 수 있을지 전부 파악할 수 있게 됨
    또한 이 과정은 불필요한 순회없이 수행되기 때문에 꽤 효율적임
     ㄴ 10^6 이하 숫자가 가질 수 있는 소인수는 최대 7개임
     ㄴ 따라서 무조건 7*n번 미만 반복하게 됨
    그리고 BFS에서는 소수를 만나면, 텔레포트 가능한 노드들을 가져와서 큐에 추가하면 끝임

    실행 결과는 179ms(over 83.77%), 210MB(over 94.36%)가 나옴
    2개 배열을 사용하는 방법보다 느린 것은, 아무래도 모든 노드에 대한 확인을 한번 더 진행하는 것이 큰 것으로 보임
     ㄴ 2개 배열은 1번만 전체 nums를 순회함
    또한 2개 배열 방법은 순수하게 vector만 사용하기 때문에, unordered_map를 사용하는 이번 풀이는 불리하다고 생각됨
     ㄴ 그러나 unordered_map 대신, 소수를 통해 접근하는 2차원 vector를 사용해서는 안됨
     ㄴ 소수는 굉장히 sparse하기 때문에 지역성이 굉장히 낮음
     ㄴ 즉, 낭비되는 공간도 많고, 캐시 히트율도 낮다는 의미임
     ㄴ 만약 2차원 vector를 사용한다면 공간을 줄일 수 있는 방향으로 생각해야함
    추가로 unordered_map를 미리 reserve하는 것이 좋다고 하지만, 이번 코드에서 그 영향은 미미했음
*/

class Solution {
public:
    static constexpr int MAX_VAL = 1e6;
    static constexpr int MAX_LEN = 1e5;
    static const vector<int>& spf()
    {
        static const vector<int> arr = []()
            {
                vector<int> p(MAX_VAL+1);
                for (int i = 0; i < MAX_VAL+1; ++i)
                    p[i] = i;
                
                for (int i = 2; i <= 1000; ++i)
                {
                    if (p[i] == i)
                    {
                        for (int j = i * i; j < MAX_VAL; j += i)
                        {
                            p[j] = i;
                        }
                    }
                }

                return p;
            }();

        return arr;
    }

    bool isPrime(int val)
    {
        if (val != 1 && spf()[val] == val)
            return true;
        else
            return false;
    }

    int minJumps(vector<int>& nums) {
        int maxValue = *max_element(nums.begin(), nums.end());

        vector<int> dist(nums.size(), MAX_VAL);
        vector<bool> isValidPrime(maxValue+1, false);
        unordered_map<int,vector<int>> teleportIdx;
        queue<int> toVisit;

        teleportIdx.reserve(nums.size()*2);

        for (int i = 0; i < nums.size(); ++i)
        {
            if (isPrime(nums[i]))
            {
                teleportIdx[nums[i]].push_back(i);
                isValidPrime[nums[i]] = true;
            }
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            int val = nums[i];
            if (isValidPrime[val]) continue;

            while(val != 1)
            {
                
                int p = spf()[val];

                if (isValidPrime[p])
                    teleportIdx[p].push_back(i);

                while (val % p == 0)
                    val /= p;
            }
        }

        dist[0] = 0;
        toVisit.push(0);

        while(dist[nums.size()-1] == MAX_VAL && !toVisit.empty())
        {
            int curIdx = toVisit.front();
            int curDist = dist[curIdx];
            int curVal = nums[curIdx];
            toVisit.pop();

            if (isValidPrime[curVal])
            {
                for (auto& idx : teleportIdx[curVal])
                {
                    if (dist[idx] > curDist+1)
                    {
                        dist[idx] = curDist+1;
                        toVisit.push(idx);
                    }
                }
                isValidPrime[curVal] = false;
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