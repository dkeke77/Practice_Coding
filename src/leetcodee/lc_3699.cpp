#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    DP를 이용하는 것이 적절해보임
    우선 문제에서 답이 클 수 있으니 10^9+7로 mod하는 것을 통해,
    각 케이스를 검사하는 것은 불가하다고 유추할 수 있음
    또한 길이 n 배열은 길이 n-1를 이용하여 만들 수 있음
    즉, 이 문제는 점화식을 내포하고 있기에 DP를 사용하는 것이 적절함
    또한 대략 2000^2 정도가 최대이므로 충분히 안전함

    i번째 배열을 구성함에 있어 다음과 같이 구성하면 됨
    우선 2가지 형태가 존재한다는 사실을 명심하고 진행해야함
     ㄴ 짝수번째 원소가 인접 원소보다 큰 경우와 작은 경우
    때문에 dp 테이블엔 2가지 정보를 저장해야함
     ㄴ 간단하게 직전 원소가 작은 경우와 큰 경우로 나눠 생각하면 됨
     ㄴ 이를 각각 lower/upper라고 부르겠음
    i-1가 자신보다 커야하는 경우
     ㄴ 고른 숫자 k보다 큰 숫자에 대해 lower 케이스를 합산하여 저장
    i-1가 자신보다 작아야하는 경우
     ㄴ 보다 작은 숫자에 대해 upper 케이스를 합산하여 저장
    이때, 각각의 케이스는 자기자신을 제외하고 합산

    TLE이 발생했었는데, 매 k에서 lower sum과 upper sum을 전부 다시 계산하기 때문이었음
    때문에 매 i마다 w^2이 발생하여 n*W^2, 2000^3가 발생했기 때문임
    이는 prefix sum을 이용하여 2w만 순회하도록 구성하면 해결할 수 있는 문제임

    실행 결과, 427ms(over 70.37%), 16MB(over 65.74%)
    더 빠르게 구현하려면 정답표를 미리 완성해두고, 입력에 따라서 이를 적절히 가공해서 반환하면 될듯
     ㄴ l,r이 매번 다르기에 정답표를 그대로 사용하는 것은 불가할 것
    아니면 각 형태는 그와 정확히 대칭되는 형태가 하나씩 존재하므로,
    이를 이용하여 한 형태만 계산하고 이를 2배하여 반환할 수도 있음
     ㄴ 이 경우, 연산 수뿐만 아니라 메모리도 절반으로 줄어들것
*/

struct Case
{
    int lower = 0;
    int upper = 0;
};

inline int MOD(int a)
{ return a % 1'000'000'007; }

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const int width = r-l+1;
        vector<Case> prevDP(width);
        vector<Case> curDP(width);

        for (int i=0; i<width; i++)
        {
            curDP[i].lower = width - i - 1;
            curDP[i].upper = i;
        }

        for (int i=3; i<=n; i++)
        {
            swap(prevDP, curDP);
            int sum = 0;
            for (int j=1; j<width; j++)
            {
                sum = MOD(sum + prevDP[j-1].lower);
                curDP[j].upper = sum;
            }

            sum = 0;
            for (int j=width-2; j>=0; j--)
            {
                sum = MOD(sum + prevDP[j+1].upper);
                curDP[j].lower = sum;
            }
        }

        int answer = 0;
        for (int i=0; i<width; i++)
            answer = MOD(answer + MOD(curDP[i].upper + curDP[i].lower));

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}