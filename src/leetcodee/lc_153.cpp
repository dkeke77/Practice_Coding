#include <vector>
#include <iostream>

using namespace std;

/*
@접근
    문제 제약에서 반드시 O(logn)안에 돌아야된다고 한 것을 보면, 트리나 이진 탐색을 이용해야함을 유추할 수 있음

    회전된 배열에서는 최대와 최소는 배열 상에서 서로 접하고 있음
    이를 찾기위해 이진 탐색처럼 왼쪽 값과 오른쪽 값의 비교를 계속 반복
    따라서 왼쪽 값보다 오른쪽 값이 작은 구간을 계속 탐색하면 언젠가 해당 지점에 도달하게 됨
    회전이 되지 않은 상태라면, 반복자체가 발생하지 않으므로 바로 최소를 찾을 수 있음
    실행 결과, 0ms(over 100%), 14MB(over 78.89%)

    다른 접근법으로 배열을 확장해나가는 방법을 생각해봄
    회전으로 인해 배열엔 2개의 오름차순 배열이 있게 됨
     ㄴ 최대가 포함된 오름차순 배열과 최소가 포함된 오름차순 배열
     ㄴ 최대 배열은 좌측, 최소 배열은 우측에 위치
    제일 우측의 값은 언제나 최소 배열의 최댓값임
    따라서 해당 값을 고정점으로 삼고, 남은 배열을 절반씩을 확인 및 확장해나가는 접근
    하지만 최소배열의 길이만 저장해선 다음 탐색 범위를 알 수 없기에, 남은 길이를 같이 업데이트할 필요가 있음
    실행 결과, 0ms(over 100%), 14MB(over 48.18%)

    두 방법 모두 관점은 다르지만, 그 구현은 거의 비슷함
    그런데 길이확장법은 그렇게 범용적이지 않으며, 동시에 더 최적이지도 않음
    단순히 흥미로운 접근 정도로 생각하는 것이 좋다고 생각됨
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        return segmentExtendMethod(nums);
    }

private:
    int binSearchMethod(vector<int>& nums)
    {
        int ptrL = 0;
        int ptrR = nums.size() - 1;
        int mid = 0;

        while (nums[ptrL] > nums[ptrR])
        {
            mid = (ptrL+ptrR) / 2;

            if (nums[ptrL] > nums[mid])
                ptrR = mid;
            else
                ptrL = mid + 1;

        }
        return nums[ptrL];
    }

    int segmentExtendMethod(vector<int>& nums)
    {
        const int rightEnd = nums.size()-1;
        int length = 0;
        int leftLength = nums.size()-1;

        while (leftLength > 0)
        {
            int stepSize = leftLength/2 + leftLength%2;
            if (nums[rightEnd-length-stepSize] < nums[rightEnd])
                length += stepSize;
            
            leftLength /= 2;
        }

        return nums[rightEnd-length];
    }
};

int main()
{
    Solution s;

    vector<int> v = {4,5,6,7,8,9,0,1,2};

    cout << s.findMin(v) << endl;

    return 0;
}