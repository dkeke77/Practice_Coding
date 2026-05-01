#include <vector>
#include <iostream>
#include <queue>

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
    BFS로 구현해봤지만, 메모리 초과가 발생
    처음에 생각했을땐 최대 200*2개 만큼의 노드가 발생할 것이라고 생각했음
    노드가 계속 늘어나지만 그에 맞게 줄어들기 때문에 최대 노드가 그렇게 많지 않으리라 생각했지만,
    동일한 좌표에 노드가 중첩으로 존재할 수 있다는 점과 현재 깊이의 노드의 2배씩 늘어난다는 점.
    이로 인해 매 깊이마다 약 2배씩 노드가 늘어남
    따라서 200*200 그리드에서 최대 노드는 2^200, 약 1M^10이라는 막대한 노드가 발생함
    이를 통해 BFS는 노드를 빠른 시점에 자주 줄일 수 있는 문제에 적절하다는 점을 알 수 있음
    혹은 정답 도달 즉시 알고리즘이 종료되는 문제 또한 해당됨
    예를 들면 미로 찾기나 최단 경로 찾기 같은 것
*/

struct Coord
{
    Coord(int u, int v) : x(u), y(v) {}
    int x, y;
};

struct node : public Coord
{
    node(int u, int v, int c, int s) : 
    Coord(u,v), cost(c), score(s) {}
    int cost;
    int score;
};

class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k)
    {
        queue<node> toVisit;
        int maxScore = -1;

        int m = grid.size();
        int n = grid[0].size();

        toVisit.push(node(0,0,0,0));

        while(!toVisit.empty())
        {
            auto curNode = toVisit.front();
            toVisit.pop();

            if (curNode.x == (n-1) && curNode.y == (m-1))
            {
                if (maxScore < curNode.score)
                    maxScore = curNode.score;
            }
            else
            {
                for (const auto& MOVE : MOVE_SET)
                {
                    int nextX = curNode.x + MOVE.x;
                    int nextY = curNode.y + MOVE.y;

                    if (nextX == n || nextY == m)
                        continue;

                    int nextCost = curNode.cost + min(grid[nextY][nextX], 1);
                    int nextScore = curNode.score + grid[nextY][nextX];

                    if (nextCost <= k)
                    {
                        toVisit.push(node(nextX, nextY, nextCost, nextScore));
                    }
                }
            }
        }

        return maxScore;
    }
private:
    const Coord MOVE_SET[2] = { 
        Coord(1,0), 
        Coord(0,1) 
    };
};

int main()
{
    Solution s;
    vector<vector<int>> grid1 = {{0,1},{2,0}};
    int k1 = 1;

    vector<vector<int>> grid2 = {{0,1},{1,2}};
    int k2 = 1;

    cout << s.maxPathScore(grid1, k1) << endl;
    cout << s.maxPathScore(grid2, k2) << endl;

    return 0;
}