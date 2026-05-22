#include <vector>
#include <iostream>

using namespace std;

/*
@풀이
    전에 풀었던 문제는 최솟값을 찾는 문제라서 더 간단한 형태로 가능했지만,
    이번 문제는 특정 값을 찾는 문제라서 살짝 더 복잡함
    그러나 이전에 풀었던 문제의 핵심인 2개의 정렬된 배열이 적층된 형태로 존재한다는 관점은 유효함
    이를 통해 2가지 단계로 이 문제를 풀어낼 수 있음
    1) target이 포함된 단일 정렬된 구간 찾아내기
    2) 해당 구간에서 target 찾아내기
    단계 1에서 먼저 mid를 기준으로 좌우측에 대해 어느쪽이 단일 정렬되었는지 평가함
     ㄴ 한쪽이 중복 정렬되었다면, 반대편은 무조건 단일 정렬임
    단일 정렬 구간에 대해, 해당 구간에 target이 있을지 평가함
    만약 구간 내에 target이 있다면 ptr를 해당 구간에 맞게 이동시킴
    만약 아니라면 남은 구간으로 이동시킴
    단계 1를 반복하다 보면 언젠가 ptr들이 단일 정렬 구간을 가르킬 것임
    그러면 단계 2로 넘어가, 일반적인 이진 탐색을 통해 해당 값이 있는지 탐색함
    예상 시간 복잡도는 O(logn) : logn*3~4 정도로 생각됨
     ㄴ if문 분기가 추가로 필요하기 때문
    실행 결과, 0ms(over 100%), 15MB(over 33.81%)가 나옴
    약 62%가 15.1~2MB에 분포하기에 메모리 사용량은 문제 없다고 생각됨
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        const int n = nums.size();
        int ptrL = 0;
        int ptrR = n-1;

        while (ptrL < ptrR)
        {
            int mid = (ptrL + ptrR) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[ptrL] < nums[ptrR])
            {
                if (target < nums[mid])
                    ptrR = mid;
                else
                    ptrL = mid + 1;
            }
            else
            {
                if (nums[mid] < nums[ptrR])
                {
                    if (nums[mid] < target && target <= nums[ptrR])
                        ptrL = mid + 1;
                    else
                        ptrR = mid;
                }
                else
                {
                    if (nums[ptrL] <= target && target < nums[mid])
                        ptrR = mid;
                    else
                        ptrL = mid + 1;
                }
            }

        }

        if (nums[ptrL] == target)
            return ptrL;
        else
            return -1;
    }
};

int main()
{
    Solution s;

    return 0;
}