#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    Y셀과 비-Y셀의 0,1,2 분포를 체크
    비-Y셀에서 제일 많이 등장하는 수를 남기고, Y셀에서 그 수를 제외한 수 중 제일 많이 등장하는 것을 남기기
    그러나 위 방식은 최빈 등장하는 수가 2개 이상인 경우, 별도의 처리를 필요로 함
    이 처리를 또 하기 하려면 필요 이상으로 코드가 복잡해질 우려가 있음
    따라서 브루트-포스로 최고 조합을 찾는 것이 더 좋다고 생각됨
     ㄴ 어차피 3*3 탐색이라서 큰 문제는 안됨
    시간복잡도 예상 O(n^2) : n^2 + 9
    실행 결과, 0ms(over 100%), 42MB(over 50.41%)
*/

class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        const int n = grid.size();
        int result = n*n;
        auto isLeftOfY = [&grid,n](int u, int v){ return u == v && u < n/2; };
        auto isRightOfY = [&grid,n](int u, int v){ return u == (n-v-1) && u < n/2; };
        auto isBottomOfY = [&grid,n](int u, int v){ return v == n/2 && u >= n/2; };

        vector<int> counterY(3,0);
        vector<int> counterNonY(3,0);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (isLeftOfY(i,j) || isRightOfY(i,j) || isBottomOfY(i,j))
                    counterY[grid[i][j]]++;
                else
                    counterNonY[grid[i][j]]++;
            }
        }
        
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (j==i)
                    continue;
                else
                    result = min(result, n*n - counterY[i] - counterNonY[j]);
            }
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}