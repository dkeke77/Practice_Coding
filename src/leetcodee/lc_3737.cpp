#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    n=1000이기에 일단 브루트포스로 시도해보았으나, TLE 발생
    prefix에 대해 카운팅을 수행하고, 이를 이용하여 구간 내의 target의 개수를 빠르게 알 수 있음
     ㄴ 바로 떠올렸다면 좋았겠지만, tag에 prefix sum이 있는걸 보고서 깨달음
    실행 결과, 35ms(over 78.65%), 41MB(over 35.95%)
    
*/

class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        const int n = nums.size();
        int count = 0;
        vector<int> prefixCount(n);

        for (int i=0; i<n; i++)
        {
            if (nums[i] == target)
                count++;
            prefixCount[i] = count;
        }
        count = 0;

        for (int i=0; i<n; i++)
        {
            if (prefixCount[i]*2 > i+1)
                count++;

            for (int j=i-1; j>=0; j--)
            {
                if (2 * (prefixCount[i]-prefixCount[j]) > i-j)
                    count++;
            }
        }

        return count;
    }
};

int main()
{
    Solution s;

    return 0;
}