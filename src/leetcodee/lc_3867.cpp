#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    특별할 것도 없이, 문제에서 요구하는대로 시뮬레이션하면 됨
    실행 결과, 64ms(over 90.78%), 156MB(over 87.10%)
*/

class Solution {
public:
    int calcGCD(int a, int b)
    {
        while(a % b != 0)
        {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return b;
    }

    long long gcdSum(vector<int>& nums) {
        const int n = nums.size();
        long long answer = 0;

        vector<int> prefixGCD;
        prefixGCD.reserve(n);

        int maxVal = nums.front();

        for (const auto& num : nums)
        {
            maxVal = max(maxVal, num);
            prefixGCD.push_back(calcGCD(maxVal, num));
        }
        sort(prefixGCD.begin(), prefixGCD.end());

        for (int i=0; i<n/2; i++)
            answer += calcGCD(prefixGCD[i],prefixGCD[n-1-i]);

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}