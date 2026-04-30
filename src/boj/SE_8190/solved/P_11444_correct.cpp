#include <iostream>
#include <vector>

#define MODULAR 1000000007

using namespace std;

/*
    엄청 큰 피보나치 수열을 구하고 특정한 수로 나눈 나머지를 구하는 문제
    처음엔 피사노 주기같은 지엽적인 개념을 이용하는 것인줄 알았지만 아니었음
    피보나치수열의 어떤 특징을 이용하는 사람도 있었지만 일반적으로 행렬의 거듭제곱을 이용해서 풀음

    나도 행렬의 거듭제곱이니 대각화를 통해 풀고 했으나, 피보나치 수열 행렬의 고유치에 무리수가 들어가서 다른 방법을 사용함
    만약에 구해야하는 피보나치 수열이 N번째라면 행렬을 N번 곱해야됨
    그런데 이 N을 2진법으로 생각하고 이용한다면 컴퓨터에 최적화된 방법으로 수행할 수 있다고 생각함
    비트연산을 통해 N을 시프트하며 1의 자리가 1일때만 result에 곱하는 방식으로 깔끔하게 구현함
    그리고 시프트하며 행렬은 제곱되게 구성함
*/

struct Matrix22
{
    unsigned long long a = 0;
    unsigned long long b = 0;
    unsigned long long c = 0;
    unsigned long long d = 0;

    Matrix22 operator*(const Matrix22& other) const
    {
        return Matrix22 {
            (a*other.a + b*other.c)%MODULAR,
            (a*other.b + b*other.d)%MODULAR,
            (c*other.a + d*other.c)%MODULAR,
            (c*other.b + d*other.d)%MODULAR
        };
    }
};

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    unsigned long long N;
    int bit=0;

    cin >> N;

    Matrix22 result {1,0,0,1};
    Matrix22 fibo {1,1,1,0};

    while(N>0)
    {
        if(N&1)
            result = result*fibo;

        N >>= 1;
        fibo = fibo*fibo;
    }

    cout << result.c;

    return 0;
}