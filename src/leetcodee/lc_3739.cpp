#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    어제 문제와 동일하되, n이 10^5로 더 커졌음
    따라서 nlogn 해법이 필요할 것으로 보임
    우선 어제 문제의 다른 풀이에서 사용되었으며, 코멘트들에서 자주 언급되는 남은 target 개수로 prefix를 구성하자
    이 경우, prefix[r] - prefix[l] > 0 이어야 유효한 부분배열임
     ㄴ 해당 구간에 남은 target 개수가 1 이상이어야 하기 때문
    그리고 prefix는 1씩 증가 혹은 감소함
    뾰족한 모양을 가지게 될 것이며, 동일한 값 C을 갖는 어떤 두 지점으로 만들어지는 구간 [a,b]는 모두 C보다 크거나 작음
     ㄴ 골짜기거나 봉우리거나...
    이와 위의 수식을 조합하면, 왼쪽 구간 중에서 자신과 동일한 값을 갖는 지점을 안다면 그 사이 구간을 한번에 카운트할 수 있음
    하지만 이 직관은 연속된 동일값 지점 둘 사이에서만 성립함
     ㄴ 구간 [a,b]에 동일값을 가지는 다른 지점이 있어선 안됨
    
    힌트에 따르면, 좌표 압축 후, 펜윅 트리를 이용하여 특정 값 이하의 개수를 빠르게 세면 된다고 함
    정리하자면 좌표 압축을 통해, prefix의 값이 몇번째로 작은 값인지 확인할 수 있음
    그리고 펜윅 트리를 이용하여 해당 값보다 작은 prefix의 개수를 빠르게 알 수 있음
    이 둘을 조합하여 현재 prefix-1번째까지 개수를 구해서 답에 가산하고, prefix에 1를 더하는 방식임
    그리고 펜윅트리로는 부분 배열에 대해서만 따지게 되므로, 반드시 현재 최대 배열에 대해서만 따로 확인해야함
     ㄴ i번째 원소를 확인하고 있다면, 펜윅 트리로는 [k,i] (k>0) 부분배열의 경우만 확인하게 됨
     ㄴ 따라서 [0,i], prefix[i]가 0 초과인지 따로 확인해야함
    실행 결과, 67ms(over 57.62%), 97.34MB(over 75.50%)
    처음 구현해보는 요소들이 많았던 바람에 그렇게 효율적으로 구현하지 못했던 것으로 보임
    특히 좌표 압축에서 성능이 떨어진다고 생각됨
     ㄴ erase가 vector에서 그렇게 효율적이지 않은 함수이기 때문
    
    더 성능좋은 풀이를 보면, prefix의 변동은 +-1이라는 사실을 이용함
    그리고 이 덕분에 prefix의 범위는 -10^5~10^5이기에 좌표압축없이 바로 펜윅을 만들 수 있음
    여기에 더해 한번의 순회만으로 정답을 도출할 수도 있는데, 자신보다 작은 prefix의 개수를 순회와 동시에 추적하는 방식임
     ㄴ 좌표압축을 [-n,n] 공간으로 대체하고, 카운팅을 펜윅트리를 생략하여 단순화하였다고 분석됨
*/

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        const int n = nums.size();
        long long count = 0;
        vector<int> prefix(n);

        for (int i=0; i<n; i++)
        {
            if (nums[i] == target)
                count++;
            else
                count--;
            prefix[i] = count;
        }
        if (count+n <= 0)
            return 0;

        count = 0;
        
        vector<int> comp(prefix);
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());

        for (int i=0; i<n; i++)
            prefix[i] = lower_bound(comp.begin(), comp.end(), prefix[i]) - comp.begin() + 1;

        const int compSize = comp.size();
        vector<int> fwt(compSize+1,0);

        for (int i=0; i<n; i++)
        {
            int toFind = prefix[i];
            while(toFind < compSize+1)
            {
                fwt[toFind]++;
                toFind += toFind & -toFind;
            }

            toFind = prefix[i]-1;
            while(toFind > 0)
            {
                count += fwt[toFind];
                toFind -= toFind & -toFind;
            }

            if (comp[prefix[i]-1] > 0)
                count++;
        }

        return count;
    }
};

int main()
{
    Solution s;

    return 0;
}