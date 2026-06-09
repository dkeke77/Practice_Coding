#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    동일한 부분배열을 2번 이상 사용할 수 있으면,
    전역 최대/최소가 나오는 부분배열을 k번 사용할 수 있다는 것으로 생각할 수 있지 않나?
    이 직관대로 정답이었음
    실행 결과, 0ms(over 100%), 104MB(over 69.26%)

    만약 겹치는 것은 허용하되, 동일한 부분배열은 2번 이상 사용할 수 없다면...
    구간을 줄여나가며 값을 계산하는 것이 좋다고 생각됨
    구간을 줄일땐, 원소들을 크기 순에 따라 정렬한 인덱스 배열을 참고하면 되지 않을까 싶음
     ㄴ 이전 최대값이 안 나오는 다음 최대 부분배열값을 계속 추적하도록 하면 될듯
        ㄴ 부분배열의 begin과 end를 잘 처리하면 되지 않을까?
     ㄴ 모든 구간에 대해 계산해두긴 2^n이라서 너무 부담이 큼
     ㄴ 이건 세그먼트 트리로 만들기도 적합해보이진 않음(상태공간이 너무 크고, 원하는 값을 찾기도 어려워보임)
     ㄴ 그런데 다음 최대/최소 쌍을 고를때 투 포인터로 해버리면 놓쳐버리는 쌍이 발생할 수 있음
*/

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        long long result = 0;
        int minVal = nums[0];
        int maxVal = 0;

        for (auto num : nums)
        {
            minVal = min(minVal,num);
            maxVal = max(maxVal,num);
        }

        result = maxVal - minVal;

        return result * k;
    }
};

int main()
{
    Solution s;

    return 0;
}