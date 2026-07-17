#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    제일 큰 문제는 어떤 gcd가 몇번째로 큰지 파악할 수 있는 방법이 없다는 것
    단순히 n*n 행렬을 만들어, 가능한 모든 gcd들을 크기순으로 정렬하는 것도 방법이겠지만,
    n이 10^5이기 때문에 무조건 TLE이 발생할 것임
    또한 어떤 gcd가 몇번째로 큰지 알아야 하기 때문에 전체 gcd 배열이 필요하지만,
    전체 gcd 배열은 n^(n-1)/2이기 때문에 직접 전체를 구하는 것 또한 불가능함
    따라서 전체를 구하는 것이 아니라, 각 gcd가 몇번 등장했는지 기록하고 이를 이진 탐색하는 것이 맞음
    
    그렇다면 각 수를 전부 직접 비교하지 않고, gcd의 분포를 파악하는 것이 관건임
    먼저 약수에 대한 분포를 구하는 것도 방법이지만, 수의 최대 크기가 5*10^4이므로,
    모든 수에 대해 약수를 처리하는 것은 2.5*10^9까지 늘어날 수 있음
     ㄴ 최대한 줄이면 각 수마다 최대 sqrt(5*10^4)가 필요한데, 이는 약 224정도
     ㄴ 즉, 소수 감별법을 응용한다면 224*10^5 정도로 그 수의 모든 약수를 파악할 수 있음
    하지만 약수를 구한다고 하여도 이를 어떻게 활용할 방법이 마땅히 없음

    코멘트를 보니 약수를 이용하여 접근하는 것이 맞긴 함
    코멘트에 따르면 어떤 쌍의 약수 분포를 구한다면,
    freq[i] - freq[2*i] - freq[3*i]...를 통해 i가 gcd인 쌍의 개수를 구할 수 있다고 함
    즉, 해당 약수의 배수인 케이스를 제외하면, 순수하게 해당 약수 케이스만 남게 됨
     ㄴ 마치 집합에서 어느 집합의 개수를 세는 것과 같음
    힌트의 포함배제(inclusion-exclusion)가 이를 두고 언급했던 것임

    실제 구현은 다음과 같이 진행됨
    우선 각 수를 순회하며 그 약수의 분포를 구함
     ㄴ 위에서 정리했듯, 소수 감별법을 응용하면 이를 충분히 가능한 정도로 처리할 수 있음
     ㄴ 단, i*i은 별도로 처리할 것
    그러나 이 약수의 분포가 곧 숫자쌍의 약수 분포는 아님
    따라서 해당 약수 개수가 가능한 조합이 몇개인지 알기 위해, f*(f-1)/2하여 저장하면 됨
    그리고 제일 약수부터 순차적으로 gcd인 케이스를 분리함
     ㄴ 이 때, 합집합의 개수를 정확히 세기 위해, divFreq가 아닌 gcdFreq를 참조해야함
     ㄴ freq[i] - freq[2*i] - ... - freq[4*i] - ...에서 freq[2*i]는 freq[4*i]를 포함하기에 중복 배제가 발생함
     ㄴ 이를 방지하려면 각 계수가 소수여야하지만, gcd를 참조하는 것으로 이를 간단히 해결할 수 있음
    마지막으로 이렇게 구한 gcdFreq로 prefixSum를 구축하고, 이를 lower_bound하면 쿼리를 빠르게 수행할 수 있음
    실행 결과, 111ms(over 32.00%), 132MB(over 37.33%)

    배열을 역할마다 새로운 것을 만들어 사용하지만, 실제로는 재사용하여도 문제가 없음
    또한 약수 조합 생성 과정과 gcd 케이스 분리 과정은 같은 루프에서 처리할 수 있음
    그리고 gcd 케이스 분리 이전에 해당 약수의 케이스가 0이라면 스킵해도 됨
    개선 결과, 101ms(over 32.00%), 121MB(over 90.67%)
    아무래도 합집합 구하는 과정에서 병목이 발생하는 것으로 생각됨
     ㄴ 이전에 구했던 것을 다시 구하기 때문...
    
    다른 풀이를 보니, 처음 약수를 구하는 것을 더 빠르게 할 수 있었음
    각 수들에 대한 freq를 구하고, 작은 수부터 k배인 케이스를 누적하면 됐음
    실행 결과, 23ms(over 100%), 121MB(over 89.33%)
*/

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        const int n = nums.size();
        const int maxNum = *max_element(nums.begin(), nums.end());
        vector<long long>freq(maxNum+1,0);

        for (const auto& num : nums)
            freq[num]++;

        for (int i=1; i<=maxNum; i++)
        {
            for (int j=2; i*j<=maxNum; j++)
                freq[i] += freq[i*j];
        }

        for (int i=maxNum; i>0; i--)
        {
            freq[i] = (freq[i]-1)*freq[i]/2;
            if (freq[i] == 0)
                continue;

            for (int j=2; i*j<=maxNum; j++)
                freq[i] -= freq[i*j];
        }

        for (int i=1; i<=maxNum; i++)
            freq[i] += freq[i-1];
        
        vector<int> answer;
        answer.reserve(queries.size());
        for (const auto& query : queries)
        {
            answer.push_back(
                lower_bound(freq.begin(), freq.end(), query+1) - freq.begin()
            );
        }

        return answer;
    }
};

int main()
{
    Solution s;

    vector<long long>prefixSum = { 0,3,3,3,3,7,7,7,7,12,12,12,15 };

    return 0;
}