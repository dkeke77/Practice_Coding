#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    우선 나올 수 있는 최댓값은 대략 1800으로, 굉장히 작은 값을 가짐
    그렇다면 각 셀에 대해 어떤 특정 값에 도달하는데 몇개의 루트가 있는지 저장하는 것이 가능할 것
    또한 합계는 적어도 줄어드는 경우가 없을 것이니, 각 셀에 저장되는 것은 최댓값과 그 루트의 개수만으로도 충분할 것
    인접 3셀에 대해 취합을 진행하는 방식으로 진행하면 될듯
     ㄴ 그렇다면 셀은 3가지 종류가 있음. 모서리, 대각선, 그외
     ㄴ 모서리 -> 그외 -> 대각선 순서로 진행해야함
     ㄴ 그런데 모서리만 인접 1셀을 확인하고, 나머지는 인접 3셀 확인을 하므로 모서리만 따로 계산하는 것이 좋아보임
    실행 결과, 7ms(over 80.84%), 12MB(over 58.19%)
    0ms가 뜨는 사람도 있었지만, 그 정도 차이는 서버 상황에 따른 편차 정도로 생각해도 무방할듯
*/

struct Cell
{
    int maxVal = 0;
    int count = 0;
};

const int MOD_FACTOR = 1'000'000'007;

class Solution {
public:
    void updateCell(const vector<string>& board, vector<vector<Cell>>& memo, int i, int j)
    {
        if (board[i][j] == 'X')
        {
            memo[i][j].maxVal = 0;
            memo[i][j].count = 0;
        }
        else
        {
            memo[i][j] = memo[i+1][j];
            const Cell& cell1 = memo[i][j+1];
            const Cell& cell2 = memo[i+1][j+1];

            if (memo[i][j].maxVal == cell1.maxVal && cell1.count != 0)
                memo[i][j].count = (memo[i][j].count + cell1.count) % MOD_FACTOR;
            else if (memo[i][j].maxVal < cell1.maxVal)
                memo[i][j] = cell1;

            if (memo[i][j].maxVal == cell2.maxVal && cell2.count != 0)
                memo[i][j].count = (memo[i][j].count + cell2.count) % MOD_FACTOR;
            else if (memo[i][j].maxVal < cell2.maxVal)
                memo[i][j] = cell2;

            if (board[i][j] != 'E' && memo[i][j].count != 0)
                memo[i][j].maxVal += (board[i][j] - '0');
        }
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int n = board.size();
        vector<vector<Cell>> memo(n, vector<Cell>(n));

        memo[n-1][n-1].count = 1;
        for (int i=n-2; i>=0; i--)
        {
            if (board[n-1][i] != 'X')
            {
                memo[n-1][i].maxVal = memo[n-1][i+1].maxVal + (board[n-1][i] - '0');
                memo[n-1][i].count = 1;
            }
            else
                break;
        }
        for (int i=n-2; i>=0; i--)
        {
            if (board[i][n-1] != 'X')
            {
                memo[i][n-1].maxVal = memo[i+1][n-1].maxVal + (board[i][n-1] - '0');
                memo[i][n-1].count = 1;
            }
            else
                break;
        }

        for (int i=n-2; i>=0; i--)
        {
            
            for (int j=n-2; j>i; j--)
            {
                updateCell(board, memo, i, j);
                updateCell(board, memo, j, i);
            }
            updateCell(board, memo, i, i);
        }

        return { memo[0][0].maxVal,memo[0][0].count };
    }
};

int main()
{
    Solution s;

    return 0;
}