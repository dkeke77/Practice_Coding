#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
@접근
    dp를 구성하며 bfs를 시행하면 된다고 봄
    다음 셀을 방문하려 할 때, 해당 셀의 인접 셀의 dp 값 중 최댓값을 선택함
     ㄴ dp엔 해당 셀에 방문했을때 최대 체력을 저장
    즉, 현재 선택한 셀에 도달 가능한 최대 체력이 저장됨
    이 과정을 bfs를 통해 반복되어 모든 셀에 대해 도달 가능한 최대 체력이 dp에 기록됨
    예상 시간복잡도는 O(m*n) 정도
     ㄴ 다음 셀 방문큐 추가 과정에서 다음 셀의 인접 셀을 탐색하기에, 16정도 발생할 것으로 예상됨
     ㄴ 또한 방문했던 셀을 다시 방문할 수 있으므로 상수항은 더 커질 수 있음
    실행 결과, 11ms(over 83.21%), 31MB(over 65.49%)
    그런데 다음 셀의 인접 셀을 전부 확인할 필요는 없음
     ㄴ 어차피 다른 셀이 해당 셀을 방문하려할때 확인하게 되니...

    혹은 다익스트라의 변형처럼 접근할 수도 있을 것임
    최대힙을 이용해서 남은 체력이 제일 높은 셀을 우선적으로 선택하며 방문하는 방법도 가능할것
*/

struct Cell
{
    Cell(int a, int b) : y(a), x(b) {}
    int y, x;

    Cell operator+(const Cell& other) const
    { return Cell(y+other.y, x+other.x); }
};

class Solution {
public:
    const Cell MOVE_SET[4] = { Cell(-1,0),Cell(0,1),Cell(1,0),Cell(0,-1) };
    const int INF = 1'000'000;

    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        const int m = grid.size();
        const int n = grid[0].size();
        queue<Cell> toVisit;
        vector<vector<int>> dp(m, vector<int>(n, 0));

        toVisit.push(Cell(0,0));
        dp[0][0] = health - grid[0][0];

        while (!toVisit.empty())
        {
            auto visit = toVisit.front();
            toVisit.pop();

            for (const auto& mv1 : MOVE_SET)
            {
                auto next = visit + mv1;
                if (next.y < 0 || next.y >= m) continue;
                if (next.x < 0 || next.x >= n) continue;

                if (dp[visit.y][visit.x] - grid[next.y][next.x] > dp[next.y][next.x])
                {
                    dp[next.y][next.x] = dp[visit.y][visit.x] - grid[next.y][next.x];
                    toVisit.push(next);
                }
            }
        }

        if (dp[m-1][n-1] > 0)
            return true;
        else
            return false;
    }
};


int main()
{
    Solution s;

    return 0;
}