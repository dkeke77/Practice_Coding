#include <iostream>
#include <vector>

using namespace std;

/*
    1~N 숫자에서 길이 M 수열을 만드는 문제
    뒤에 나오는 수는 무조건 앞 숫자보다 커야함이 제약 조건
    
    포인터 배열을 만들어서 해결함
    제일 뒤에 있는 포인터가 자신의 한계점에 도달하면 그 앞에 있는 포인터를 이동시키려고 시도
    그 포인터도 자신의 한계점에 도달하면 똑같이 앞에 있는 포인터를 이동시키려고 시도
    그렇게 한계점에 도달하지 않은 포인터가 나올때까지 반복함
    만약 제일 앞의 포인터가 자신의 한계점에 도달했다면 프로그램 종료
    
    불필요한 반복을 줄이기 위해 M이 1,N일때는 별도 처리함
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N,M;
    bool breakLoop = false;
    cin >> N >> M;

    vector<int> pointer(M);

    if(M==1)
    {
        for(int j=1; j<=N; j++)
            cout << j << '\n';
    }
    else if(M==N)
    {
        for(int j=1; j<=N; j++)
            cout << j << " ";
    }
    else
    {
        //init
        for(int j=0; j<M; j++)
            pointer[j] = j+1;

        while(!breakLoop)
        {
            for(int j=0; j<M; j++)
                cout << pointer[j] << " ";
            cout << '\n';
            
            //shift pointer!
            if (pointer[M-1]==N)
            {
                for(int j=M-1; j>=0; j--)
                {
                    if(pointer[j] == N-(M-j-1))
                    {
                        if(j==0)
                            breakLoop = true;
                        else    
                            continue;
                    }
                    else
                    {
                        int startPoint = pointer[j]+1;
                        for(int k=j; k<M; k++)
                            pointer[k] = startPoint + (k-j);
                        break;
                    }
                }
            }
            else
                pointer[M-1] += 1;
        }
    }
}
