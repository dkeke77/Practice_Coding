#include <iostream>>
#include <vector>

using namespace std;

/*
@접근
    뒤로 점프할 일은 절대 없음
    그렇다면 DFS로 풀어도 되지 않을까?
    마침 배열의 길이도 1000 이하로 굉장히 짧음
    그런데 생각해보니 DFS 최악의 경우엔 O(n^3)
     ㄴ sigma_i=n:(i^2/2)번 순회
     ㄴ 이렇게 되면 10^9로 너무 느려짐
    그래도 입력 수가 적으니, n^2까진 괜찮을 것으로 생각됨
    한칸씩 전진하면서 앞에서 연결 가능한 것들 중, 제일 점프수가 많은 것과 연결하면 될듯
     ㄴ 인덱스 0에서부터 노드가 확장되는 느낌임
    그리고 점프가 불가능한 노드는 더 이상 유망하지 않기 때문에, 순회 대상에서 제외하는 것이 좋음
    따라서 점프가 가능한 노드들만 pool에 넣고, 이들에 대해서만 순회하며 연결 가능한 노드를 탐색
    시간복잡도는 O(n^2)임
     ㄴ 대략 최대 (n-1)^2/2인데, pool에 의해 이것보다 작게 나올 가능성이 있음
    실행 결과, 11ms(over 93.64%), 69MB(over 13.41%)
    메모리는 대부분 68.2~68.6MB에 분포되는데, 이 정도 차이는 신경 쓸 필요 없어 보임
    pool을 제외하고 실행보니 18ms가 나온 것을 보아, pool이 최적화에 유효했던 것으로 보임
    또한 실행시간 분포가 5ms에서 높은데, 지금보다 더 좋은 방법이나 더 최적화할 여지가 있을 것으로 생각됨

    정석적인 풀이는 여기서 크게 다르지 않는 것으로 보임
*/

class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        vector<int> table(nums.size(),-1);
        vector<int> pool;
        pool.push_back(0);
        table[0] = 0;
        
        for (int i = 1; i < nums.size(); ++i)
        {
            int maxJmp = -1;
            for (int j = pool.size()-1; j >= 0; --j)
            {
                if (abs(nums[pool[j]] - nums[i]) <= target && table[pool[j]] > maxJmp)
                    maxJmp = table[pool[j]];
            }
            if (maxJmp != -1)
            {
                table[i] = maxJmp+1;
                pool.push_back(i);
            }
        }

        return table.back();
    }
};

int main()
{
    Solution s;
    vector<int> v = {1,3,4,0,2};
    int k = 2;

    cout << s.maximumJumps(v, k) << endl;

    return 0;
}