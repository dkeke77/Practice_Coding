#include <iostream>
#include <vector>

using namespace std;

/*
    트리의 지름 구하는 문제. 플로이드로 풀 수 있지 않을까 했는데 어림도 없었음

    애초에 시간복잡도도 n^3이라서 안됐음
    그리고 메모리도 n이 커서 제약이 심함
    어찌저찌 1차원 배열로 변환하게 짜긴 했는데 의미가 없다
    그냥 정석적인 방법을 찾아서 하자
*/

int N = 0;

int convertIdx(int i, int j)
{
    if (i>j)
        swap(i,j);
    
    return ((2*N-1)*i-i*i)/2 + j-i-1;
}

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int v1, v2, weight, maxVal = 0;
    cin >> N;
    vector<int> tb((N*N-N)/2,0);

    for(int i=0; i<N; i++)
    {
        cin >> v1;
        while(1)
        {
            cin >> v2;
            if (v2 == -1)
                break;
            cin >> weight;

            tb[convertIdx(v1-1,v2-1)] = weight;
            if (maxVal < weight)
                maxVal = weight;
        }
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N-1; j++)
        {
            if(i==j) continue;

            for(int k=j+1; k<N; k++)
            {
                if(i==k) continue;

                if(tb[convertIdx(j,i)]!=0 && tb[convertIdx(i,k)]!=0 && tb[convertIdx(j,k)] == 0)
                {
                    if (tb[convertIdx(j,k)] < tb[convertIdx(j,i)] + tb[convertIdx(i,k)])
                    {
                        tb[convertIdx(j,k)] = tb[convertIdx(j,i)] + tb[convertIdx(i,k)];
                    }

                    if (tb[convertIdx(j,k)] > maxVal)
                        maxVal = tb[convertIdx(j,k)];
                }
            }
        }
    }

    cout << maxVal;

    return 0;
}