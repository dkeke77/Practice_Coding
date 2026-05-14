#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
@접근
    nums 오름차순 정렬 후, 순열에 맞는지 검사하며 순회
    마지막만 따로 처리
    예상 시간복잡도 O(nlogn) : nlogn+n
    실행 결과, 0ms(100%), 26MB(over 97.93%)

    처리여부 확인용 배열을 만들고 순회하며 이를 체크하도록 한다면 정렬을 생략할 수 있으므로 n도 가능
     ㄴ 그런데 이러면 확인용 배열보다 큰 수가 들어오는 경우에 대해 예외처리가 필요함
     ㄴ 때문에 보기엔 2n이지만 비슷하지만 더 느릴 수도 있음
    때문에 더 나은 것은 hash set인데, 예외처리를 딱히 할 필요가 없음
    또한 hash에 그 기반을 두고 있기 때문에, 값 추가에 이론적으로 O(1)이 발생함
     ㄴ 그냥 set이었다면 tree 기반이므로 값 추가마다 O(logn)이 발생해, 최종적으로 nlogn이었을것
     ㄴ 어떤 풀이에선 bitset을 이용했지만, 아마 메모리 최적화 때문으로 보임
    하지만 그 대신 if문을 추가로 더 사용해야되며, 버킷 생성 때문에 정말 더 빠르진 모호한 점이 있음
     ㄴ n-1은 2번 등장해도 되는 점 때문
*/

class Solution {
public:
    bool isGood(vector<int>& nums) {
        vector<int> freq(nums.size(),0);

        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] >= nums.size())
                return false;
            
            if(nums[i] == nums.size()-1)
            {
                if(freq[nums.size()-1] > 1)
                    return false;
                freq[nums.size()-1]++;
            }
            else
            {
                if(freq[nums[i]] > 0)
                    return false;
                freq[nums[i]]++;
            }
        }

        return true;
    }
};

int main()
{
    Solution s;

    return 0;
}