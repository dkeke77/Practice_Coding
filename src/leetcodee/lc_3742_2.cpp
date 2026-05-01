#include <vector>
#include <iostream>

using namespace std;

/*
    @문제
    m*n 그리드가 있으며, 각 셀은 0,1,2 중 한 값을 가짐
    (0,0)에서 (m-1, n-1)까지 도달해야하는데, 오른쪽과 아래쪽으로만 이동 가능
    각 셀은 값에 따라 비용과 점수를 가짐
     - 0 : 비용 0, 점수 0
     - 1 : 비용 1, 점수 1
     - 2 : 비용 1, 점수 2
    주어진 k 이하의 비용으로 가능한 최대 점수 반환하기
    만약 가능한 경로가 없다면 -1 반환

    @제한사항
    1 <= m,n <= 200
    0 <= k <= 10^3
    grid[0][0] == 0
    0 <= grid[i][j] <= 2

    @실패
    잘못된 문제 접근
    Cell 이라는 하나의 객체로 점수와 비용을 동시에 저장하도록 하였음
    DP처럼 위쪽/왼쪽 Cell을 비교하여 가능하며 점수가 더 높아지는 Cell을 저장함
    그러나 점수와 비용을 동시에 평가해야 하는 상황이 존재함
    이 상황에서 어떤 Cell이 나중에 더 이득일지 파악할 수 없음
    따라서 하나의 객체로 저장하는 것은 결국 1차원 데이터로 2차원 데이터를 저장하는 것과 동일함

    @성공
    0-1 배낭 문제와 같이, 각 Cell은 정답표를 가진다고 생각함
    정답표는 길이가 c인 1차원 배열이며, 각 인덱스는 제공되는 비용을 의미함
    즉, 해당 Cell에 도달하기까지 주어진 비용 이내 가능한 최대 점수가 저장되는 것
    또한 모든 그리드가 동시에 정답표를 가진다면 m*n*c 만큼의 크기를 가질것임
    따라서 한 행만 정답표를 가지도록 하고, 다음 행에서 이를 재활용한다면 n*c만으로 충분함
    그리고 달성 가능한 최대 비용은 사실상 m+n-3임
    따라서 c의 크기도 그만큼 줄인다면 필요없는 메모리를 줄일 수 있고, 그만큼 순회비용이 줄어들어 성능도 향상됨
     ㄴ c 크기를 최대 401로 했을 시 2056ms이 나왔지만, m+n로 가변하게 만드니 1020ms로 큰 성능 향상이 확인됨
    
    이 문제를 풀며 차원이 다른 요소들을 잘 저장하는 것이 중요함을 느낌

    @최적화
    3번째 for문에서 발생하지 않을 비용까지 전부 확인하는 것이 관찰됨
    따라서 발생 가능한 비용(limit))까지만 확인하도록 수정함
    이 때, 이전 셀보다 비용을 한칸 더 확인해야 되는 것이 문제였음
    지금 인덱스의 정보를 만들기 위해선, 이전 셀에서 동일한 인덱스를 참조해야됨
    그러나 이전 셀보다 한칸 더 확인하기 때문에, 필연적으로 없는 정보를 참조하는 상황이 발생함

    이를 for문 종료 후, [limit]에 있는 정보를 [limit+1]로 복사하여 해결함
    이것이 가능한 이유는 limit 이후로는 점수들이 전부 동일하게 됨
    왜냐하면 이미 limit가 발생 가능한 최대 비용인 시점에서, limit+n의 최적값까지 확정된 것
    따라서 limit보다 더 큰 비용을 지불하더라도 최적값에 영향을 주지 않음

    예상대로 1020ms -> 582ms로, 약 절반가량 실행시간이 감소함
*/

class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k)
    {
        int m = grid.size();
        int n = grid[0].size();

        const int MAX_COST = m+n;

        vector<vector<int>> record(n+1, vector<int>(MAX_COST, -1));
        vector<int> oldCell(MAX_COST, 0);
        record[1] = vector<int>(MAX_COST, 0);

        for (int i = 0; i < m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                int cost = min(grid[i][j-1], 1);
                int score = grid[i][j-1];
                int limit = i+j;

                oldCell = record[j];

                for (int u = 0; u < cost; ++u)
                    record[j][u] = -1;
                for (int u = cost; u < min(limit,MAX_COST); ++u)
                {
                    int maxScore = max(record[j-1][u-cost], oldCell[u-cost]);
                    if (maxScore < 0)
                        record[j][u] = -1;
                    else
                        record[j][u] = maxScore + score;
                }
                record[j][limit] = record[j][limit-1];
            }
        }

        return record[n][min(MAX_COST-1,k)];
    }
};

int main()
{
    Solution s;
    vector<vector<int>> grid1 = {{0, 1, 0, 1, 0, 0, 2, 0}};
    int k1 = 88;

    vector<vector<int>> grid2 = {{0,1},{1,2}};
    int k2 = 1;

    cout << s.maxPathScore(grid1, k1) << endl;
    //cout << s.maxPathScore(grid2, k2) << endl;

    return 0;
}