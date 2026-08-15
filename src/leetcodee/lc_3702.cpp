#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    어떤 구간의 XOR이 0이라는 것은 그 구간을 어떻게 나누어도 동일한 수가 나옴
     ㄴ 즉, XOR([a,b]) == 0 -> XOR([a,i]) == XOR([i+1,b])
    그런데 2개말고 3개로 분할되는 경우도 생각해야 하나, 이는 2개 나누기 2번을 통해 유도될 수 있음
    아무튼 어떤 구간의 XOR이 0이라면, 그 구간을 적당히 나눠서 0이 되지 않는 구간들로 나누는 것이 핵심
    만약 어느 구간으로 나누어도 0이라면, 그 구간은 모두 0으로 구성된 것
     ㄴ [a,i] == 0이면서 [a,i+1] == 0이면, i+1번째 원소는 0
     ㄴ 이 규칙이 구간 전체에 전파되어 모든 원소가 0이라는 결론을 내릴 수 있음
    그런데 문제가 하나 발생함
    부분배열이 아니라 부분순열을 찾는 문제였음
    하지만 그래도 풀이에 큰 차이는 없음
     ㄴ 기본 정리에서 구간을 구간 전체에서 원소 하나를 빼는 것으로 바꿔도 동일한 결론을 얻을 수 있음
    실행 결과, 0ms(over 100%), 171MB(over 88.49%)
*/

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        const int n = nums.size();
        int allXor = 0;
        for (int i=0; i<n; i++)
            allXor ^= nums[i];

        if (allXor != 0)
            return n;
        
        for (int i=0; i<n; i++)
        {
            if (allXor ^ nums[i] != 0)
                return n-1;
        }

        return 0;
    }
};

int main()
{
    Solution s;

    return 0;
}