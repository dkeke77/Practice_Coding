#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    제일 높은 값의 상한은 그 배열의 길이임
     ㄴ 인접 원소간 최대 +-1 차이만 날 수 있으므로
    그리고 증가는 불가능하고, 감소만 가능하므로 현재 배열의 원소들중 최댓값을 넘는 원소는 나올 수 없음
    이 둘을 따져보면, 배열의 길이와 배열의 최댓값 중 더 작은 것을 반환하면 됨
    그런데 이 직관은 틀렸음
    다른 원소들이 배열 길이보다 작음에도 최댓값에 도달하지 못하는 경우가 발생할 수 있음
     ㄴ 1,2,2,2,2,10
    즉, 현재 배열을 정렬하고 배열 구성을 시뮬레이션하는 것이 우선 가능한 방법으로 보임
    실행 결과, 8ms(over 63.84%), 55MB(over 69.21%)

    하지만 이야기를 들어보니 O(n)으로 달성할 수 있는 방법이 있다고 함
    카운팅 정렬을 이용하면 됨
    수의 범위가 최대 10^9까지이므로 불가능하다고 판단할 수 있지만, 배열의 길이보다 큰 수는 의미가 없음
    즉, 배열의 최대 길이인 10^5까지만 카운팅하고, 그 이상은 10^5으로 카운팅하면 됨
    실행 결과, 0ms(over 100%), 56MB(over 4.52%)
*/

class Solution {
public:
    int freq[100'001] = { 0 };
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        const int n = arr.size();
        int i = 0;
        int answer = 1;

        for (const auto& num : arr)
            freq[min(num,n)]++;

        for (int i=2; i<=n; i++)
        {
            if (freq[i] >= i-answer)
                answer = i;
            else
                answer += freq[i];
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