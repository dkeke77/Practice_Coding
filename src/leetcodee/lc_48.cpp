#include <vector>
#include <iostream>

using namespace std;

/*
@풀이
    이 문제는 공간복잡도 O(1)의 조건을 두고 푸는 문제임
     ㄴ 단순히 새로운 행렬을 만들어서 풀어도 통과는 되지만 문제 의도를 벗어나게 된다
    따라서 기존 행렬에서 그대로 데이터를 이동만 하게 해야한다
    이에 대한 풀이는 2가지가 있다
    1) transpose + reverse
        주어진 행렬을 transpose하고, 각 행을 reverse하면 90도 시간방향 회전이다
        이는 회전행렬을 생각해보면 된다
    2) 4점 교환
        회전 시, 4개의 점끼리 데이터 이동이 발생함
        이를 연속적으로 수행하는 방법임
        for문을 n^2/4만큼 돌아 효율적으로 보이지만, 1회 루프당 4번 교환이 발생하므로 위 방법과 큰 차이는 없다
*/

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int size = matrix.size();

        // transpose
        for (int i = 0; i < size-1; ++i)
        {
            for (int j = i+1; j < size; ++j)
                swap(matrix[i][j],matrix[j][i]);
        }
        // reverse
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size/2; ++j)
                swap(matrix[i][j],matrix[i][size-1-j]);
        }
    }
};

int main()
{
    Solution s;

    return 0;
}