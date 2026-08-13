#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    먼저 prefix seq를 찾아서 sum을 찾음
    그리고 전체 배열을 순회하며 숫자들의 분포를 확인하고, 분포 배열을 sum부터 확인하며 비어있는 숫자를 식별함
    만약 비어있는 숫자가 없었다면, sum 자신을 반환
    실행 결과, 0ms(over 100%), 23MB(over 77.12%)
*/

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        const int n = nums.size();

        int seqNum = nums.front();
        int seqSum = seqNum;
        for (int i = 1; i < n; i++)
        {
            if (seqNum+1 != nums[i])
                break;
            
            seqNum = nums[i];
            seqSum += seqNum;
        }

        vector<int> isTouched(52, false);
        for (int i = 0; i < n; i++)
            isTouched[nums[i]] = true;

        for (int i = seqSum; i < 52; i++)
        {
            if (!isTouched[i])
                return i;
        }

        return seqSum;
    }
};

int main()
{
    Solution s;

    return 0;
}