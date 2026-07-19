#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    최대/최소 구해서 gcd 구하기
    실행 결과, 0ms(over 100%), 16MB(over 31.74%)
*/

class Solution {
public:
    int getGCD(int a, int b)
    {
        while(a % b != 0)
        {
            int temp = a % b;
            a = b;
            b = temp;
        }

        return b;
    }

    int findGCD(vector<int>& nums) {
        int minNum = *min_element(nums.begin(), nums.end());
        int maxNum = *max_element(nums.begin(), nums.end());

        return getGCD(minNum, maxNum);
    }
};

int main()
{
    Solution s;

    return 0;
}