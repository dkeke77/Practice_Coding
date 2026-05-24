#include <vector>
#include <iostream>

using namespace std;

/*
@풀이
    다시 또 나온 회전된 배열 문제
    O(logn)안에 수행해야된다는 제약이 없으므로, O(n) 순회하면 됨
     ㄴ 당연히 모든 원소가 정렬되었는지 확인하기 위해선 O(n)이 필요함
    회전된 배열의 특성인 정렬된 배열이 2개 존재한다는 특성을 이용하면 됨
     ㄴ 특히 좌측의 배열은 우측 배열의 모든 값들보다 높음
    실행 결과, 0ms(over 100%), 11MB(over 18.08%)
     ㄴ 메모리 사용량은 11.1~4MB에 약 90%가 분포해있으므로, 신경 쓸 지표는 아님
*/

class Solution {
public:
    bool check(vector<int>& nums) {
        bool flag = false;
        
        for (int i=1; i<nums.size(); ++i)
        {
            if (nums[i-1] > nums[i])
            {
                if (!flag)
                    flag = true;
                else
                    return false;
            }
            
            if (flag && nums[0] < nums[i])
                    return false;
        }

        return true;
    }
};

int main()
{
    Solution s;

    return 0;
}