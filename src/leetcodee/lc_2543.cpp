#include <iostream>>
#include <vector>

using namespace std;

/*
@접근
    힌트를 본 결과 아래와 같이 생각할 수 있음
    (1,1)에서 출발하는 것이 아닌, 반대로 (x,y)에서 출발해야됨
    그러면 (x+y,x), (x/2,y), (x,x+y), (x,y/2) 연산으로 변형됨
    이 때, 어떤 x, y에 대해 x=a*G, y=b*G라고 하자 (G는 두 수의 GCD)
     ㄴ x,y는 2로 최대한 나누어, 홀수인 상태라고 하자
    위의 a와 b는 2의 배수가 아닌 서로소임
    그러면 (a+b)는 2의 배수임으로 q=(a+b)/2^k로 연산이 가능해짐
    이렇게 나온 q는 a와 b 중 하나보다 작을것임 (a와 b이 아닌 경우)
    위 과정을 계속 반복하면 a와 b 둘다 1에 도달하게 됨
    그러면 x=G, y=G만 남게 되는데, 이 때 G가 1이 아니라면 어떻게 해도 (1,1)로 도달할 수 없음
    왜냐하면 더하기 연산으론 c*G꼴만 나올 수 있는데, 이를 통해선 2의 제곱에 도달할 수 없음
     ㄴ 이 식은 c*G=2^k=2^i*2^j로 풀 수 있으며, 이에 따라 c와 G는 2의 제곱이어야 함
     ㄴ 그런데 G는 1이 아닌 홀수이니, 위 식은 불가능하다는 결론이 나옴
    
    결과는 0ms(over 100%), 7.74MB(over 54.05%)
*/

class Solution {
public:
    bool isReachable(int targetX, int targetY) {
        while (targetX % 2 == 0)
            targetX /= 2;
        while (targetY % 2 == 0)
            targetY /= 2;
        
        // always x >= y
        if (targetX < targetY)
            swap(targetX,targetY);
        
        while(targetY != 0)
        {
            int temp = targetX % targetY;
            targetX = targetY;
            targetY = temp;
        }

        if (targetX == 1)
            return true;
        else
            return false;
    }
};

int main()
{
    Solution s;
    vector<pair<int,int>> testCase;

    testCase.push_back({6,9});
    testCase.push_back({4,7});
    testCase.push_back({9,2});

    for (auto t : testCase)
    {
        cout << "(" << t.first << ", " << t.second << ") : ";
        if (s.isReachable(t.first,t.second))
            cout << "Reachable" << endl;
        else
            cout << "Imreachable" << endl;
    }
    
    return 0;
}