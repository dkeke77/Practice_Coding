#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

/*
@접근
    prefix를 이용하면 되지 않을까 생각됨
     ㄴ sum과 non-zero를 각각 저장하는 방식
    그런데 문자열의 길이는 최대 10^5이므로 int64으로도 오버플로우 가능성이 높음
    따라서 prefix non-zero는 정수형이 아닌 문자열로 저장할 필요가 있음
     ㄴ 혹은 full non-zero 문자열을 만들어두고, 벡터엔 자릿수만 적어두는 것도 방법
    하지만 non-zero와 sum을 곱하고 mod해야하기 때문에 문자열로도 문제가 있음
    따라서 non-zero에 mod된 결과를 저장하는 방향이 제일 적절하다 생각됨
     ㄴ 이 경우, non-zero끼리 빼면서 음수가 발생할 수 있음
     ㄴ 음수가 발생하면 MOD_FACTOR를 더해야함
    실행 결과, 465ms(over 5.70%), 314MB(over 5.18%)
    
    아무래도 digitMod가 불필요하게 가능한 전부를 생성하기 때문에, 예상보다 느린 것으로 보임
    따라서 동적으로 필요한 부분만 생성하도록 만듦
    실행 결과, 26ms(over 91.19%), 138MB(over 94.82%)
    메모리를 보면 거의 2배나 차이가 나는데, 아무래도 시행마다 digitMod 벡터가 생성된 것으로 보임
     ㄴ 하지만 생성자를 통해 한번만 생성하도록 했음에도 이런 결과가 나온 것을 보면, 예상 밖의 Solution 객체가 여러번 생성된 것으로 보임
     ㄴ 해당 벡터를 static으로 한다면 더 빨라질 수도 있음
    실행 결과, 15ms(over 99.48%), 136MB(over 94.71%)
    여러번 실행하여도 생성자 방식보다 static 객체로 만드는 편이 평균적으로 더 빨랐음
    더불어 약 2MB 정도 메모리를 덜 쓰는 것을 보아, 확실히 객체가 여러번 생성되는 것으로 예상됨
*/

class Solution {
public:
    static constexpr int MOD_FACTOR = 1'000'000'007;
    inline static int digitMod[100'001];

    inline static int init = []() {
        digitMod[0] = 1;
        for (int i = 1; i < 100'001; i++)
            digitMod[i] = digitMod[i - 1] * 10LL % MOD_FACTOR;
        return 0;
    }();

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const int n = s.length();
        vector<int> answer;
        answer.reserve(queries.size());

        vector<int> prefSum;
        vector<pair<int,int>> prefNonZero;
        prefSum.reserve(n);
        prefNonZero.reserve(n);

        int sum = 0;
        long long nonZero = 0;
        int digit = 1;

        for (int i=0; i<n; i++)
        {
            int num = s[i] - '0';
            if (num != 0)
            {
                sum += num;
                nonZero = (nonZero*10 + num) % MOD_FACTOR;
                digit++;
            }

            prefSum.push_back(sum);
            prefNonZero.push_back({nonZero,digit});
        }

        for (const auto& query : queries)
        {
            sum = prefSum[query[1]];
            nonZero = prefNonZero[query[1]].first;

            if (query[0] > 0)
            {
                sum -= prefSum[query[0]-1];
                if (sum < 0)
                    sum += MOD_FACTOR;

                int digitDiff = prefNonZero[query[1]].second - prefNonZero[query[0]-1].second;
                long long toSubNZ = (1LL * prefNonZero[query[0]-1].first * digitMod[digitDiff]) % MOD_FACTOR;
                nonZero -= toSubNZ;
                if (nonZero < 0)
                    nonZero += MOD_FACTOR;
            }

            int queryAns = (1LL * sum * nonZero) % MOD_FACTOR;
            answer.push_back(queryAns);
        }

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}