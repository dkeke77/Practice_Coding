#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
@접근
    우선 n의 크기가 이전 문제보다 작아졌기 때문에, 저번에 시도하려다 실패했던 접근이 가능할 수도 있음
    두 수에 대해서만 XOR을 수행하고, 이 중간결과를 해시셋에 저장함
    그리고 이 중간결과와 nums를 다시 XOR를 수행하여 최종 결과를 계산
    실행 결과, 2269ms(over 20.79%), 98MB(over 28.09%)
    의외로 성공하긴 했는데, 예상 시간복잡도가 O(n^3)이었음을 고려한다면 데이터셋 분포 덕분에 통과했다고 보여짐

    힌트와 다른 풀이를 본 결과, 이 방법이 의외로 정석 풀이였음
    왜냐하면 수의 분포 또한 1500이하였기 때문에 나올 수 있는 숫자의 크기 또한 제한적이었음
    계산해보면 2048이 나올 수 있는 최대 숫자임
    따라서 2048 길이의 배열을 만들어두고, 첫번째 XOR를 통해 어떤 수가 발생했는지 기록함
    그리고 다시 두번째 XOR를 통해 어떤 수가 최종적으로 나왔는지 기록하고, 이들의 개수를 반환하는 것이 정석 풀이였음
    이 과정을 보면 왜 첫 풀이가 통과가 됐는지 유추할 수 있는데, n*n + first*n 꼴로 계산이 진행됨을 알 수 있음
    즉, 예상과 달리 n^3이 아니라 n^2+2048*n과 같은 꼴이 나온 것이고, 이는 5*10^6 정도로 충분히 감당 가능함
    실행 결과, 595ms(over 66.29%), 35MB(over 80.90%)
    내가 처음 했던 풀이와 이 풀이의 차이점은 해시셋을 쓰는지, 아니면 bool 벡터와 같은 고정된 배열을 쓰는지 차이였음

    더 빠른 풀이로는 Walsh-Hadamard Transform이라는 방법을 사용한 것도 있는데,
    이 문제의 삼중 XOR은 합성곱의 일종으로 볼 수 있고, 따라서 FFT를 적용할 수 있다고 함
    그리고 bitwise에 적합한 Fast Walsh-Hadamard Transform를 사용하여 풀 수 있다고 함
    놀라운 방법이지만, 이에 대한 정확한 이론이나 원리를 당장 파악하는 것은 불필요하다고 판단됨
*/

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int n = nums.size();
        vector<bool> first(2048, false);
        vector<bool> second(2048, false);
        first[0] = true;

        for (int i=0; i<n; i++)
        {
            for (int j=i+1; j<n; j++)
                first[nums[i]^nums[j]] = true;
        }

        for (int i=0; i<2048; i++)
        {
            if (!first[i]) continue;
            for (int j=0; j<n; j++)
                second[nums[j]^i] = true;
        }

        int answer = 0;
        for (int i=0; i<2048; i++)
            answer += second[i];

        return answer;
    }
};
int main()
{
    Solution s;

    return 0;
}