#include <iostream>>
#include <vector>

using namespace std;

/*
@성공1
    상자를 90도 돌렸을 때, 행이 열이 됨
    그리고 상자 안의 물체는 같은 행끼리만 영향을 줌
    따라서 각 행에서 대해서 90도 돌린 이후를 시뮬레이션하면 하면 됨
    또한 행은 obstacle을 기준으로 segment를 나눠서 생각할 수 있음
    각 segment는 독립적으로 시뮬레이션해야함
     ㄴ 앞의 segment가 stone으로 가득 찼는데 현재 segment가 공간이 비어 있어도, 옆의 segment의 stone은 넘어오지 않음
    
    이에 영감을 얻어 각 행을 순회하며 stone과 empty 개수를 셈
    obstacle을 만나면 segment 종료이므로, segment 시작점으로부터 empty 개수만큼 뒤부터 stone을 채워넣음
     ㄴ segment flush라고 생각할 수도 있음
    그리고 segment 시작점을 obstacle 한칸 뒤로 이동시킴
    이를 계속 순회하며 계속 반복함
    그리고 순회 종료 후, stone 개수가 0 초과라면 segment flush
     ㄴ 구조적으로 루프 종료로 인한 segment 종료를 루프 내부에서 알 수 없음
     ㄴ 그렇다고 if문에 조건문 하나 더 넣는건 비용적으로 좋아보이지 않음...

    결과는 5ms(over 90.91%), 56.9MB(over 38.33%)
    시간복잡도는 O(m*n*2)로 예상됨
    메모리는 56.8MB에 집중적으로 분포되어 있기 때문에 크게 문제되진 않는다고 생각됨
    
    cntEmpty와 idxObstacle는 쓰지 않고 구현 가능함
    Obstacle를 만나면 그 앞부터 stone를 cntStone만큼 채운다고 생각하면 됨
*/

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int n = boxGrid.size();
        int m = boxGrid[0].size();

        vector<vector<char>> result(m,vector<char>(n,'.'));

        for (int i = 0; i < n; ++i)
        {
            int cntStone = 0;
            int cntEmpty = 0;
            int idxObstacle = 0;
            for (int j = 0; j < m; ++j)
            {
                if (boxGrid[i][j] == '#')
                    cntStone++;
                else if (boxGrid[i][j] == '.')
                    cntEmpty++;
                else
                {
                    for (int k = 0; k < cntStone; ++k)
                        result[idxObstacle+cntEmpty+k][n-i-1] = '#';

                    result[j][n-i-1] =  '*';
                    idxObstacle = j + 1;
                    cntStone = 0;
                    cntEmpty = 0;
                }
            }
            if (cntStone > 0)
            {
                for (int k = 0; k < cntStone; ++k)
                    result[idxObstacle+cntEmpty+k][n-i-1] = '#';
            }
        }
        
        return result;
    }
};

int main()
{
    return 0;
}