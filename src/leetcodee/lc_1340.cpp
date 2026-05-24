#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@풀이
    현재 위치와 점프 뛰려는 곳 사이에 현재 위치보다 더 작은 값으로만 있어야 함
    그런데 뛴 곳에서 또 다른 곳으로 뛰는 것이 계속 연쇄적으로 반복됨
    이 특성을 활용하면 된다고 판단됨
    그리고 작은 값일수록 연쇄적으로 뛸 수 있는 곳이 적고, 큰 값일수록 더 많아짐
    따라서 작은 값부터 처리하고, 큰 값에서는 이 값을 이용하는 것이 효율적이라고 생각함
    이를 위해 오름차순 정렬된 인덱스 배열을 마련하자
    그리고 작은 순부터 주변으로 점프 가능한 곳을 탐색하고,
    점프 가능한 곳이 이전에 처리했던 곳이라면 해당 위치의 점프 가능수를 합산, 아니라면 +1
    여기서 성능을 더 챙기려면 정렬 인덱스 배열을 점프 가능 위치 탐색에 이용하는 것도 고려할만함
     ㄴ 그러나 d가 충분히 작다면 직접 탐색하는 것이 빠를 수도 있음
     ㄴ 왜냐하면 어차피 인덱스 배열을 앞에서부터 쭉 탐색해야되기 때문
    직접 탐색 방식의 시간복잡도는 아마 O(nlogn+n*d) : nlogn + n*2*d
    인덱스 배열 탐색 방식은 아마 O(nlogn+n^2) : nlogn + n*(n+1)/2
    
    처음에 문제를 잘못 해석했는데, 뛰려는 곳 너머에 더 작은 값이 있어야 하는 것으로 해석하였음
    하지만 현재 위치와 뛰려는 곳 사이에 현재 위치보다 더 작은 값만 있어야 하는 것이었음
    때문에 직접 탐색만이 유효한 방법이 됨
    실행 결과, 3ms(over 99.54%), 19MB(over 31.96%)
    메모리는 약 50%가 18.9~19.1MB에 분포해있기에 크게 뒤쳐지는 수치는 아니라고 생각됨
    그리고 이 방식은 공간복잡도가 O(2n)이기 때문에 어쩔 수 없다는 측면도 있음
    성능은 상당히 준수하게 나왔는데, 방문 가능 여부 탐색이 상당히 효율적이기 때문이라고 생각됨
     ㄴ 모든 탐색은 깊이 1 이상으로 수행되지 않음
     ㄴ 즉, 탐색했던 경로를 다시 탐색하는 방식이 아니라, 탐색했던 경로 뒤에 이어붙이는 느낌임
    그리고 직접 탐색은 지역성이 높아 캐시 히트율이 높았디고 생각할 수도 있음

    다른 풀이로는 dfs를 사용하는 것도 있지만, 이 방식은 이전에 탐색했던 경로를 다시 탐색할 수 있음
    따라서 그렇게 효율적이진 않다고 생각됨
*/

class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        const int n = arr.size();
        int maxVisit = 1;
        vector<int> sortedIdx(n,0);
        vector<int> visitCounter(n,1);

        for (int i=1; i<n; ++i)
            sortedIdx[i] = i;

        sort(sortedIdx.begin(), sortedIdx.end(), [&arr](int a, int b){ return arr[a] < arr[b]; });

        for (auto idx : sortedIdx)
        {
            int counter = 1;
            for (int i=idx-1; i>=max(0,idx-d); --i)
            {
                if (arr[i] < arr[idx])
                    counter = max(counter, visitCounter[i] + 1);
                else
                    break;
            }
            for (int i=idx+1; i<=min(n-1,idx+d); ++i)
            {
                if (arr[i] < arr[idx])
                    counter = max(counter, visitCounter[i] + 1);
                else
                    break;
            }

            visitCounter[idx] = counter;
            maxVisit = max(maxVisit,counter);
        }

        return maxVisit;
    }
};

int main()
{
    Solution s;

    vector<int> v = { 6,4,14,6,8,13,9,7,10,6,12 };
    int d = 2;

    s.maxJumps(v,d);

    return 0;
}