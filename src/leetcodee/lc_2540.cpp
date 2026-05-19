#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
@접근
    각 배열에 대한 포인터를 별도로 마련하고, 이를 규칙에 따라 순회하면 됨
     ㄴ 어느 한 쪽이 더 작다면 그쪽을 한칸 전진
    예상 시간복잡도 O(m+n)
    실행 결과, 0ms(over 100%), 54MB(over 81.53%)가 나옴

    다른 풀이로는 이진탐색을 이용하는 방법이 있음
    어느 한 배열을 기준으로, 다른 배열에 대해 low_bound를 수행하면 됨
    이 경우, low_bound를 통해 나온 값이 기준값과 동일하다면 해당값 반환,
    그렇지 않다면 다음 배열값으로 기준을 이동하고 다시 수행하면 됨
    이 경우, 시간복잡도는 O(m*log(n))
     ㄴ 시간복잡도를 줄이기 위해선 m < n 이어야 함
     ㄴ 따라서 알고리즘 수행 전에 크기를 확인하고 swap할 필요가 있음
*/

class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int ptr1 = 0;
        int ptr2 = 0;

        while(ptr1 < nums1.size() && ptr2 < nums2.size())
        {
            if (nums1[ptr1] == nums2[ptr2])
                return nums1[ptr1];
            
            if (nums1[ptr1] > nums2[ptr2])
                ptr2++;
            else if (nums1[ptr1] < nums2[ptr2])
                ptr1++;
        }

        return -1;
    }
};

int main()
{
    Solution s;

    return 0;
}