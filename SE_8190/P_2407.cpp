#include <iostream>
#include <deque>

using namespace std;

struct BigInt
{
    deque<char> num;
    
};

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N, M;
    unsigned long long result = 1;

    cin >> N >> M;
    if (N-M<M)
    {
        for(int i=M+1; i<=N; i++)
        {
            result *= i;
        }

        for(int i=2; i<=N-M; i++)
            result /= i;
    }
    else
    {
        for(int i=N-M+1; i<=N; i++)
            result *= i;

        for(int i=2; i<=M; i++)
            result /= i;
    }

    cout << result;

    return 0;
}