#include <iostream>>
#include <vector>

using namespace std;

/*
@성공2
    기존 방식에서 투 포인터를 적용한 방식
    마찬가지로 각 행을 순회하는데, 순회 도중 empty를 만나면 ptr와 swap 후, ptr을 한칸 전진함
    stone이면 현재 칸을 stone으로 채우고, obstacle이면 현재 칸을 obstacle로 하고 ptr를 obstacle 앞 칸으로 전진함
    이 때, ptr의 앞은 목표대로 정렬된 상태임이 보장됨
    이는 이전처럼 segment 단위로 생각하면 타당함을 알 수 있음
    각 segment는 a개의 stone과 b개의 empty로 구성됨
    그런데 empty를 만나면 현재 ptr와 swap하고 ptr를 한칸 전진함
    이 동작은 가능한 제일 앞으로 empty를 밀어내는 것과 동일함
    segment 동안 b번 위 동작이 발생하기 때문에, 결과적으로 제일 앞에서부터 empty를 b개가 밀어나짐
    그리고 밀려나지 못한 a개의 stone는 뒤에 정렬되기 떄문에 원하는 결과를 얻을 수 있음
    또한 obstacle로 인해 segment가 종료되면 ptr를 obstacle 앞 칸으로 전진하여, 완성된 이전 segment를 수정하지 않음
    이 방식은 이전 방식처럼 추가 for문과 루프 종료 이후 추가 처리를 하지 않아도 되는 점이 좋음
    
    결과는 7ms(over 87.22%), 56.9MB(over 69.53%)
    시간복잡도는 O(n*m)로 예상되어, 이전보다 유의미하게 빨라야 하지만 차이는 미미함
    이는 swap이 메모리 2개에 대해 읽기/쓰기를 수행하기 때문에 예상보다 많은 시간을 소모하는 것으로 보임
    이로 인해 O(n*m*2)로 시간복잡도가 실질적으로 늘어나는 것으로 생각됨
*/

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int n = boxGrid.size();
        int m = boxGrid[0].size();
        int ptr;

        vector<vector<char>> result(m,vector<char>(n,'.'));

        for (int i = 0; i < n; ++i)
        {
            ptr = 0;
            for (int j = 0; j < m; ++j)
            {
                if (boxGrid[i][j] == '#')
                    result[j][n-i-1] = '#';
                else if (boxGrid[i][j] == '.')
                {
                    swap(result[j][n-i-1], result[ptr][n-i-1]);
                    ptr++;
                }
                else
                {
                    result[j][n-i-1] =  '*';
                    ptr = j + 1;
                }
            }
        }
        
        return result;
    }
};

int main()
{
    return 0;
}