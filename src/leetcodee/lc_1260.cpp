#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    무식하게 shift를 k번 반복하더라도, 50^2*100(250,000) 수준이라서 통과 가능함
    하지만 좀 더 우아하게 푼다면 k를 m과 n으로 나눠서 그 결과를 바로 만드는 것이 가능함
    k%n번 만큼 열이 shift된 상태이고, k/n번만큼 행이 전체 shift된 상태임
    하지만 행은 부분 shift된 상태까지 생각해야함
    부분 shift는 왼쪽열부터 k%n개 열이 수행된 상태일것
    따라서 행 전체 shift -> 열 shift -> 행 부분 shift 순으로 수행하면 될 것
    실행 결과, 0ms(over 100%), 18MB(over 39.39%)

    1회 순회와 swap만으로 shift를 구현하고 싶었으나, 이에 대한 일반적인 함수를 작성하는 것은 어려움
     ㄴ 왜냐하면 swap 시, 기존 위치에 다른 수가 들어오기 때문
    따라서 swap이 아니라 복사를 통해서 구현하거나, shift-1은 비교적 간단하니 k번 shift-1하는 것이 권장됨

    하지만 굳이 1회 순회와 swap만으로 shift를 구현하는 것이 불가능한 것은 아님
    shift하려는 배열 A와 shift 회수 k번이 있다고 칠 시,
    A 제일의 뒤에서부터 k번째의 공간을 임시 저장공간으로써 사용하는 아이디어가 있음
    ptr이 가리키는 곳에서부터 k번 swap을 하여 이동을 한다면, A의 [ptr,ptr+k] 구간은 정답인 상태가 됨
    그리고 뒤의 k공간은 기존 ptr구간이 순서대로 들어가있음
    따라서 ptr+k 뒤에서부터 위 동작을 다시 수행하면 [ptr,ptr+2*k] 구간까지 정답인 상태가 됨
    하지만 남은 공간이 k공간보다 작은 경우엔 k공간을 온전히 사용할 수 없음
    그 경우엔 남은 공간만큼만 k공간에서 데이터를 인출하고, k공간을 축소시켜야 함
    그러면 k공간이 남은 공간보다 작아지기 때문에 기본 동작을 재개할 수 있어짐
    이 동작들을 k공간이 0이 될때까지 수행하면 됨
    swap 횟수는 A의 크기-1로 고정임
    실행 결과, 0ms(over), 18MB(over 91.78%)
    작성해보고 나니, 예전에 작성했었던 임시 큐와 유사한 느낌이 들음

    다른 풀이로는 1차원 배열로 풀어서 푸는 방법도 있음
    이 문제의 shift는 사실 1차원으로 풀어서 보면, 1차원 배열을 shift하고 다시 2차원으로 묶은 것과 동일함
    따라서 1차원 배열로 풀고 이를 shift하는 것이 가능함
    그리고 1차원 배열의 shift는 전체 반전, [0,k) [k,n) 각각 반전하는 것으로 구현 가능함
     ㄴ 시간복잡도는 아마 내 방법이 미약하게 유세하겠으나, 이 방법이 훨씬 단순함
     ㄴ 이 방법은 swap이 전체 배열의 길이 2배만큼 발생함
*/

template <typename T>
void shiftN(vector<T>& vec, int n)
{
    const int size = vec.size();
    int ptrL = 0;
    int ptrR = size-n;
    int len = min(ptrR - ptrL, n);

    while(len > 0)
    {
        for (int i=0; i<len; i++)
            swap(vec[ptrL+i], vec[ptrR+i]);
        
        ptrL += len;
        if (ptrL == ptrR)
            ptrR += len;

        len = min(ptrR - ptrL, size - ptrR);
    }
}

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        const int m = grid.size();
        const int n = grid[0].size();

        int shiftCol = k%n;
        int shiftRow = (k/n)%m;

        shiftN(grid, shiftRow);
        
        for (int i=0; i<m; i++)
            shiftN(grid[i], shiftCol);

        for (int i=0; i<shiftCol; i++)
        {
            for (int j=m-1; j>0; j--)
                swap(grid[j][i], grid[(j+1)%m][i]);
        }

        return grid;
    }
};

int main()
{
    Solution s;

    return 0;
}