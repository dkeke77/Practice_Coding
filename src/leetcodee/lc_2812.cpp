#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
@접근
    일단 safeness 맵을 구성하는 것 먼저 해야함
     ㄴ 매번 safeness를 계산하는 것은 너무 오래 걸림
    그리고 우선순위 큐에 safeness 내림차순으로 셀을 넣고, 하나씩 꺼내면서 경로가 올바른지 확인하면 되지 않을까
    하지만 이 방법은 n^3일 수 있음
    따라서 접근을 바꿔서 매개변수 탐색법을 이용해서 유효한 safeness를 찾는 편이 더 적절할 것 같음
    셀들을 safeness에 따라 정렬한 배열을 이진탐색하여,
    현재 가능한 셀을 배열을 구성하고 이 배열에 있는 셀들로만 bfs하여 목적지에 도달할 수 있는지 확인하면 됨
    그런데 굳이 배열 같은걸 쓸 필요도 없이 단순히 safeness 맵을 던져주고 특정 safeness 미만은 방문하지 않게만 하면 됨
    예상 시간복잡도는 O(n^2*logn)
    실행 결과, 367ms(over 71.10%), 166MB(over 52.96%)

    다른 풀이로는 safeness 맵 구축 후, bfs를 하는데 방문큐를 우선순위 큐로 하는 방법이 있음
    하지만 이 방법도 기본적으로 시간복잡도는 O(n^2*logn)이지만, 위 방법보다 빠를 것으로 생각됨
    매번 완전히 새로 bfs를 수행하는 것이 아니기 때문
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

    bool canVisit(const vector<vector<int>>& safeness, int minSafeness)
    {
        const int n = safeness.size();
        queue<Cell> toVisit;
        vector<vector<bool>> isVisited(n, vector<bool>(n, false));

        toVisit.push(Cell(0,0));
        isVisited[0][0] = true;

        while (!toVisit.empty())
        {
            auto visit = toVisit.front();
            toVisit.pop();

            for (const auto& mv : MOVE_SET)
            {
                auto next = visit + mv;
                if (next.y < 0 || next.y >= n) continue;
                if (next.x < 0 || next.x >= n) continue;
                if (safeness[next.y][next.x] < minSafeness) continue;

                if (!isVisited[next.y][next.x])
                {
                    isVisited[next.y][next.x] = true;
                    toVisit.push(next);
                }
            }

            if (isVisited[n-1][n-1])
                return true;
        }

        return false;
    }

    int maximumSafenessFactor(vector<vector<int>>& grid) {
        const int n = grid.size();
        vector<vector<int>> safeness(n, vector<int>(n, INF));
        queue<Cell> toVisit;

        // find thieves
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if (grid[i][j] == 1)
                {
                    safeness[i][j] = 0;
                    toVisit.push(Cell(i,j));
                }
            }
        }

        // build safeness matrix
        while (!toVisit.empty())
        {
            auto visit = toVisit.front();
            toVisit.pop();

            for (const auto& mv : MOVE_SET)
            {
                auto next = visit + mv;
                if (next.y < 0 || next.y >= n) continue;
                if (next.x < 0 || next.x >= n) continue;

                if (safeness[next.y][next.x] > safeness[visit.y][visit.x]+1)
                {
                    safeness[next.y][next.x] = safeness[visit.y][visit.x]+1;
                    toVisit.push(next);
                }
            }
        }
        
        int end = min(safeness[0][0], safeness[n-1][n-1]);
        int start = 0;
        
        while(start < end)
        {
            int mid = (end+start+1)/2;
            if (canVisit(safeness, mid))
                start = mid;
            else
                end = mid-1;
        }

        return end;
    }
};

int main()
{
    Solution s;

    return 0;
}