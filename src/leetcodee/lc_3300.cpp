#include <vector>
#include <iostream>

using namespace std;

/*
@풀이
    쭉 순회하며 계산하고 min 비교하면 됨
    예상 시간복잡도 O(n)
    실행 결과, 0ms(over 100%), 28MB(over 49.30%)
    메모리는 27.6~8MB에 약 72%가 분포해있음
    따라서 크게 변별력 있는 지표는 아님
*/

class Solution {
public:
    int minElement(vector<int>& nums) {
        int minValue = 50;

        for (auto num :nums)
        {
            int temp = 0;
            while(num > 0)
            {
                temp += num%10;
                num /= 10;
            }
            minValue = min(minValue, temp);
            if (minValue == 1)
                break;
        }

        return minValue;
    }
};

int main()
{
    Solution s;

    return 0;
}