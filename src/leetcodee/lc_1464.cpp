#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    제일 큰 두 수를 곱하면 되는 문제
    정렬해서 선택하는 방법도 있고, 순회하면서 제일 큰 두 수를 직접 찾는 방법도 있음
    이론적으로 O(nlogn)과 O(n)의 차이가 있지만, 상수적으로 그렇게 큰 차이가 있지는 않음
    실행 결과, 0ms(over 100%), 14MB(over 25.65%)
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());

        return (nums[0]-1)*(nums[1]-1);
    }
};

int main()
{
    Solution s;

    return 0;
}