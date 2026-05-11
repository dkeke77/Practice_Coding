#include <iostream>>
#include <vector>

using namespace std;

/*
@접근
    그냥 빡구현인 느낌
     ㄴ 최대 50*50 행렬이라 엄청 크진 않음
    핵심은 각 껍질마다 한바퀴 도는 데 걸리는 k가 다름
    각 껍질마다 k를 적절히 줄이는 것이 핵심으로 보임
    밖 껍질이 m*n 크기라면 바로 안 껍집은 (m-2)*(n-2)임
    한 바퀴에 2*(m+n)-4
    그리고 껍질을 순환하는 코드가 필요함
    직접 교환하는 것은 복잡해질 것으로 보임
    따라서 껍집을 순회하며 1차원 배열에 이를 저장하고 다시 순회하는 방법을 쓰면 어떨까?
     ㄴ 순회할때 k만큼 오프셋을 줘서 순회하는 것

    실행 결과, 14ms(over 69.08%), 17MB(over 94.64%) 나옴
    메모리는 아마 오프셋용 배열이 없다면 더 낮을 것으로 보임

    기존 코드는 함수 본문 내부에서 for문을 2번 돌려서 굉장히 더러운 형태였는데,
    *int 함수로 변경하여 재사용성과 편의성을 올려봄
*/

class Solution {
public:
    int* getRingElem(vector<vector<int>>& grid, int s, int idx)
    {
        int m = grid.size() - 2*s;
        int n = grid[0].size() - 2*s;

        if (idx > (2*m+n-3))
        {
            idx -= (2*m+n-3);
            return &grid[s][s+n-1-idx];
        }
        else if (idx > (m+n-2))
        {
            idx -= (m+n-2);
            return &grid[s+m-1-idx][s+n-1];
        }
        else if (idx > (m-1))
        {
            idx -= (m-1);
            return &grid[s+m-1][s+idx];
        }
        else
            return &grid[s+idx][s];
    }

    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        int layer = (min(m,n)+1)/2;
        vector<int> temp(2*(m+n)-4);

        for (int s=0; s < layer; ++s)
        {
            int round = 2*(m+n)-4;
            int offset = round-(k % round);

            for (int i = 0; i < round; ++i)
                temp[i] = *getRingElem(grid,s,i);

            for (int i = 0; i < round; ++i)
                *getRingElem(grid,s,i) = temp[(offset+i) % round];
            
            m -= 2;
            n -= 2;
        }

        return grid;
    }
};

int main()
{
    Solution s;

    return 0;
}