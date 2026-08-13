#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
@접근
    투 포인터로 구간 내 freq가 k이하이도록 관리하면 됨
    숫자는 최대 10^9까지 등장한다고 하니, freq는 해시테이블이 적절함
     ㄴ 왜냐면 숫자가 크고, sparse하기 때문
    실행 결과, 56ms(over 86.74%), 156MB(over 5.11%)
    
    이것이 성립하는 이유는 다음과 같이 생각할 수 있음
    어떤 구간에 숫자 a가 k+1번 등장하는 경우가 발생한다면,
    그 구간에서 제일 왼쪽이나 오른쪽에 존재하는 숫자 a까지 제외해야함
     ㄴ 중간의 a를 배제하는 것은 불가능, subarray가 깨져버림
    그런데 투 포인터 진행 과정에서 오른쪽을 제외한 경우를 이미 확인하였음
    따라서 왼쪽을 제외하는 것이 순서에 맞음
    또한 구간 [i,j]가 유효하지 않다면, [i,n]도 마찬가지로 유효하지 않기 때문에 유효한 배열을 계속 유지시켜줘야함
*/

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        const int n = nums.size();

        unordered_map<int,int> freq;
        freq.reserve(n);
        int maxLen = 0;

        for (int ptrR = 0, ptrL = 0; ptrR<n; ptrR++)
        {
            freq[nums[ptrR]]++;
            while (freq[nums[ptrR]] > k)
            {
                freq[nums[ptrL]]--;
                ptrL++;
            }

            maxLen = max(maxLen, ptrR-ptrL+1);
        }

        return maxLen;
    }
};

int main()
{
    Solution s;

    return 0;
}