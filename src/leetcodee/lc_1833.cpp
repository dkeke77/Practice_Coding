#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    0-1 배낭 문제와 유사하지만, 모든 물건의 가치가 동등하다는 면에서 큰 차이가 있음
    때문에 무조건 비용이 싼 물건을 집는 것이 이득임
    왜냐하면 이 문제는 순환적이기 때문임
    문제를 약간 바꿔서 여러 회차에 거쳐 물건을 1개씩 고른다고 생각해보자
     ㄴ 하나 고른 다음에 다른 하나 고르고...
    그러면 예산이 클수록 고를 수 있는 물건의 폭이 커짐
    이는 초기 예산에만 국한되지 않고, 매 회차마다 반복되는 특징임
    따라서 다음 회차를 위하여 예산은 최대한 적게 쓰는 것이 미래의 이득에 직결됨
    이러한 이유로 매회차마다 남은 물건 중 제일 싼 것을 선택하여야 미래에 더 많은 선택을 줄 수 있음
    실행 결과, 36ms(over 42.67%), 80MB(over 37.51%)

    카운팅 정렬을 이용하면 더 빠르게 계산할 수 있음
    실행 결과, 4ms(over 92.11%), 81MB(over 29.48%)
    기존의 정렬 방법은 O(nlogn)이지만, 이 방법은 O(n+k)임
     ㄴ 여기서 k는 수의 등장 범위
     ㄴ 그런데 문제에서 최대 10^5이라고 했으니 n과 동일함
    따라서 상수항을 따져보아도 2n수준일것
*/

class Solution {
public:
    int freq[100'001] = {};
    int maxIceCream(vector<int>& costs, int coins) {
        int minCost = costs.front();
        int maxCost = costs.front();
        int leftCoins = coins;
        int answer = 0;

        for (const auto& c : costs)
        {
            freq[c]++;
            minCost = min(minCost,c);
            maxCost = max(maxCost,c);
        }

        for (int i=minCost; i<=maxCost; i++)
        {
            if (freq[i] == 0)
                continue;

            if (leftCoins >= i)
            {
                int count = min(leftCoins/i, freq[i]);
                leftCoins -= i * count;
                answer += count;
            }

            freq[i] = 0;
        }

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}