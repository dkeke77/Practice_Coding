#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    저번엔 n이 충분히 작으면서 t 또한 10이하였기 때문에 브루트 포스가 가능했음
    하지만 이번 문제에선 n과 t 둘다 훨씬 커졌기 때문에 브루트 포스는 불가능함
    따라서 보다 규칙을 활용하여 문제를 풀어나가야함

    우선, t를 소인수분해했을 시, 10 이상의 소수가 있으면 안됨
    1~9 숫자들만 곱하기 때문에 10 이상의 소수는 절대 표현할 수 없음
    
    그리고 t를 소인수분해하여 2,3,5,7의 freq를 구하고, 이를 만족하는 숫자들의 조합을 찾는 방향으로 가야할듯함
    이 문제를 푸는 데에 있어 중요한 관점은 새로운 자릿수를 추가해야하는가 여부로 생각됨
    만약 새로운 자릿수가 필요없다면, 기존 자릿수들을 어떤 수로 바꿔야하는가를 따져야함
    반대로 새로운 자릿수를 추가하게 된다면, 필요한 자릿수가 최소 몇개인지 파악하는 것이 중요하게 됨
     ㄴ 이때, 9999같이 더 큰 수를 찾아야 하는 규칙으로 인해 새로운 자릿수가 필요한 경우도 따져야함
    그렇게 새로운 자릿수가 최소한만으로 추가됐다면, 그리디하게 1의 자릿수부터 제일 큰 수부터 채워넣으면 됨

    힌트에 따르면, suffix를 그리디하게 구성해보라고 되어있음
    prefix를 고정한 채로 나머지 suffix를 구성해나가는건 어떨까?
    우선 바꾸려는 suffix를 그리디하게 구성해보는 것
    그런데 이렇게 할 시, 기존 suffix보다 작을 수 있음
    이 경우엔 제일 앞의 자리를 바꿔주면 될듯
     ㄴ 이전 시도들에서 실패했기 때문에, 현재 시행의 제일 앞자리만 신경쓰면 되지 않을까 생각함
    만약, 새로운 앞자리가 1이라면 기존보다 1만큼만 크면 됨
    1이 아니라면, 2,3,4 순으로 곱하면서 기존보다 커지는 경우를 체크

    위 방법은 예외가 너무 많았음
    우선, 제일 앞자리에 2,3,4를 곱하게 되면, 뒷자리에서 어떤 수에 저것을 나눠는 편이 작아짐
     ㄴ 1'248 -> 2'148과 같이 앞의 곱이 뒤에 나눗셈으로써 전파됨
    그리고 tempStr의 제일 앞이 1인지, 제일의 앞이 2배로 하지않아도 되는 케이스 확인인지 등, 많은 예외 확인을 필요로 했음

    그래서 보다 간단하게 i번째 자리에 기존 num[i]에서부터 9까지 전부 대입하면서, 뒤의 문자열을 알아서 구성하도록 해봤음
    그 결과, num 중간에 0이 등장하는 케이스를 처리하질 못했음
     ㄴ 정답 문자열엔 0이 등장하지 않으므로, 정답 문자열에서 0을 제외해야하는 문제였음
    이는 제일 앞에 있는 0의 바로 앞에서부터 기존 과정을 시행하여 해결 가능했음
     ㄴ 어차피 처리 과정으로 생성된 문자열엔 0이 존재하지 않으므로 자연스럽게 0이 배제됨
     ㄴ 동시에 제일 큰 수가 뒤에 배치되도록 압축되니, 숫자들의 재배치도 같이 수행됐음
    하지만 num[i]가 9인 경우를 무조건 스킵하게 하여 오답이 발생했었음
    이 문제는 90처럼 바로 뒤에 0이 오는 케이스에서 발생했음
     ㄴ 다른 케이스에선 왜 괜찮았냐면, 해당 자리에 도달하기전에 이미 검사를 끝낸 상태였을테니 9를 검사할 필요가 없었음
     ㄴ 하지만 0은 검사를 하지 않은 상황에서 9에 도달하게 되니, 해당 9가 유망하지 않을진 모르는 상태였음
    따라서 90과 같은 특이 케이스만 예외로 처리하게 하여 모든 문제를 해소했음

    실행 결과, 35ms(over 82.76%), 33MB(over 55.17%)
    꽤 준수한 성능이 나왔음
    의외로 매번 문자열을 새로 구성함에도 생각만큼 느리지 않았음
    문자열 중 5,7,8,9가 등장하면 이것들은 확정으로 간주하고, 이들을 제외하고 처리하는 것도 괜찮은 방법일듯

    공식 풀이법은 전반적으로 이 풀이와 비슷하나, 별도의 클래스를 만들지 않는 점과 num 자체를 변경하여 매번 문자열을 만들지 않는 점이 차이점임
    하지만 문자열을 생성하지 않을뿐, 매번 문자열을 새로 구성해야하는 것은 동일함
    또한 의외로 느리지 않았던 이유 또한 여기서 밝혀지는데,
    t를 위해 채워야하는 자릿수는 최대 O(logt)정도임
     ㄴ 제일 작은 소인수 2만으로 구성되더라도, 10^14는 대략 2^46정도임
    즉, 문자열 구성 과정은 46 상수시간만큼만 걸리며, 이를 1~9에 대해 순회하니 9*46정도임
    메인 루프는 정답 문자열의 길이가 num을 넘는지에 따라 달라지긴 하지만,
    9*logt^2 혹은 거기에 n을 더한 정도일것
     ㄴ 9999...999 케이스처럼 엄청 길지만, 문자열의 길이가 num을 넘는 케이스
    그리고 여기에 초기 순회까지 포함해야하므로, O(n+9*logt^2)가 시간복잡도임
*/

class PrimeTracker
{
public:
    PrimeTracker(long long num)
    {
        for (const auto& p : primes)
        {
            while(num % p == 0 && num > 0)
            {
                freq[p]++;
                num /= p;
            }
        }
        if (num > 9)
            existPrimeOver9 = true;
    }

    void add(int i)
    {
        for (const auto& p : primes)
        {
            while(i % p == 0 && i > 0)
            {
                freq[p]++;
                i /= p;
            }
        }
    }

    void remove(int i)
    {
        for (const auto& p : primes)
        {
            while(i % p == 0 && i > 0)
            {
                freq[p]--;
                i /= p;
            }
        }
    }

    int popMaxNum()
    {
        if (freq[3] >= 2)
        {
            freq[3] -= 2;
            return 9;
        }
        else if (freq[2] >= 3)
        {
            freq[2] -= 3;
            return 8;
        }
        else if (freq[7] >= 1)
        {
            freq[7] -= 1;
            return 7;
        }
        else if (freq[3] >= 1 && freq[2] >= 1)
        {
            freq[3] -= 1;
            freq[2] -= 1;
            return 6;
        }
        else if (freq[5] >= 1)
        {
            freq[5] -= 1;
            return 5;
        }
        else if (freq[2] >= 2)
        {
            freq[2] -= 2;
            return 4;
        }
        else if (freq[3] >= 1)
        {
            freq[3] -= 1;
            return 3;
        }
        else if (freq[2] >= 1)
        {
            freq[2] -= 1;
            return 2;
        }
        else
            return 1;
    }

    bool isEmpty()
    {
        bool result = true;

        for (const auto& p : primes)
        {
            result &= freq[p] <= 0;
        }

        return result;
    }

    bool existPrimeOver9 = false;

private:
    int freq[10] = {};
    static inline const int primes[4] = { 2,3,5,7 };
};

class Solution {
public:
    string smallestNumber(string num, long long t) {
        int zeroAppeared = num.length();
        PrimeTracker pt(t);

        if (pt.existPrimeOver9)
            return "-1";
        
        for (int i=0; i<num.length(); i++)
        {
            if (num[i] == '0')
            {
                zeroAppeared = i;
                break;
            }
            else
                pt.remove(num[i]-'0');
        }
        
        if (zeroAppeared == num.length() && pt.isEmpty())
            return num;

        for (int i=zeroAppeared-1; i>=0; i--)
        {
            pt.add(num[i]-'0');
            if (num[i] == '9')
            {
                if (!(i+1 < num.length() && num[i+1] == '0'))
                    continue;
            }

            for (int j=num[i]-'0'; j<=9; j++)
            {
                string tempStr = "";
                auto ptTemp = pt;
                ptTemp.remove(j);

                for (int k=0; k<num.length()-i-1; k++)
                    tempStr.push_back('0'+ptTemp.popMaxNum());
                tempStr.push_back('0'+j);

                if (!ptTemp.isEmpty())
                    continue;
                else
                {
                    reverse(tempStr.begin(),tempStr.end());
                    auto result = num.substr(0,i) + tempStr;
                    if (result >= num)
                        return result;
                }
            }
        }

        string tempStr = "";
        while (!pt.isEmpty())
            tempStr.push_back('0'+pt.popMaxNum());
        
        while (tempStr.length() <= num.length())
            tempStr.push_back('1');
        
        reverse(tempStr.begin(),tempStr.end());

        return tempStr;
    }
};
int main()
{
    Solution s;

    cout << s.smallestNumber("4093", 180) << endl;

    return 0;
}