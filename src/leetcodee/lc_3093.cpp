#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
@풀이
    브루트포스로 접근한다면?
    최악의 경우, 매번 5*10^5번 비교를 해야하므로 25*10^10까지도 갈 수 있음
     ㄴ aaa....aa, b인 배열에서 b 접미사를 5*10^5 찾는 경우
    일단 생각할 수 있는 것은 캐싱
     ㄴ 찾은 최적의 suffix를 저장해두는 것
     ㄴ 하지만 해시를 이용해서 모든 케이스를 저장해두는 것은 지나침
        ㄴ "c", "bc", "abc"... 이런 방식
     ㄴ 다른 방법으로는 trie를 구성하는 것
     ㄴ 하지만 이 또한 어떻게 구성할지가 관건임
     ㄴ 문자열의 길이가 최대 10^4이기 때문에 무작정 trie를 만들었다간 26^(10^4)개의 리프를 만들게 될 수도 있음
        ㄴ 하지만 문자열은 최대 5*10^5이므로 많이 만들어져도 저것이 끝
     ㄴ 이런 관점으로 보면 해시도 마냥 나쁘진 않은듯?
    캐시를 구성하는 것은 5*10^5, 최적값을 찾는건 5*10^5
    따라서 최대 10^6만큼 걸리므로 캐시를 이용하는 것은 옳은 생각임

@실패
    해시를 이용하여 빠르게 구현해본 결과, MLE이 발생함
    때문에 trie도 잘못하면 MLE이 발생할 우려가 있음
    trie로 해본 결과, 해시에서 MLE이 발생했던 케이스는 통과했으나, 다른 케이스에서 MLE이 발생함
    leetcode가 테스트케이스를 연속으로 실행한다는 점에서 착안해서 쿼리 종료 후에 trie를 정리하도록 함
    모든 자식 노드에 대해, nullptr가 아니라면 소멸자를 호출하도록 함
     ㄴ 소멸자를 호출하면 메모리 해제는 안된다고 함. 따라서 delete를 호출하도록 해야함
    실행 결과, 847ms(over 43.83%), 623MB(over 41.67%)
    아무래도 메모리를 정리하는 과정에 적지 않은 시간이 소모되는 것으로 보임
    
    스마트포인터로 바꿔서도 테스트해봄
    실행 결과, 1383ms(over 14.20%), 671MB(over 8.96%)
    raw pointer보다 더 수행하는 연산이 많기 때문에 더 오래 실행되고, 더 많은 메모리를 소모하는 것을 확인할 수 있음

@개선
    다른 풀이를 본 결과, 기본적인 접근은 이것과 다르지 않음
    지금 방식보다 더 빠르게 하기 위해선 힙 메모리가 아닌 벡터를 이용하여 가상의 메모리를 구축하는 것임
    이 방식에 따라 수정한 결과, 1677ms(over 8.34%), 145MB(over 99.38%)
    오히려 크게 느려진 이유는 reserve를 매번 최대 크기로 수행하기 때문임
    따라서 실제 총 길이를 계산하고, 이만큼만 reserve시킴
    그 결과, 243ms(over 93.52%), 333MB(over 76.85%)
    속도는 엄청나게 상승됐지만, 메모리를 2배 이상 사용하는 것은 의외임
    단순히 wordsContainer를 순회하며 총 길이를 합산할뿐임에도 메모리를 2배 이상 사용하게 됨
     ㄴ 순회 과정에서 wordsContainer를 참조하는 것으로 인해 발생하는 순간적인 메모리 소모까지도 측정된 것으로 보임
    
    이를 방지하기 위해 벡터가 아닌 배열로 구성하도록 함
    큰 배열을 만들고, 사용 후엔 사용한만큼에 대해서만 초기화를 수행하도록 함
    실행 결과, 78ms(over 95.68%), 145MB(over 99.38%)
    메모리 소모 또한 이전과 동일한 수준으로 줄어들었을 뿐만 아니라, 속도 또한 비약적으로 개선됨
    벡터를 매번 생성/할당하는 비용이 생략되었기 때문으로 추정됨

    하지만 이런 개선들은 leetcode가 케이스를 연속적으로 실행하는 환경 때문에 더 크게 보이는 것임
    또한 이 문제의 테스트 케이스는 817개로, 이러한 현상을 더 극대화하였다고 생각함
    따라서 만약 실전 코테에선 이러한 개선들은 반드시 필수는 아님
     ㄴ 최초의 방법만으로도 충분하다는 것
    허나 실제 제품 등에선 어느 정도 유의미할 수도 있음
     ㄴ 특히 메모리 관리 및 절약 관점
*/

struct Node
{
    Node(int i = -1) : value(i) {}
    int child[26] =
    {
        -1,-1,-1,-1, -1,-1,-1,-1,
        -1,-1,-1,-1, -1,-1,-1,-1,
        -1,-1,-1,-1, -1,-1,-1,-1,
        -1,-1
    };
    int value;
};
Node trie[500'000];

class Solution {
public:
    inline int toIdx(const char c)
    { return c-'a'; }

    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        vector<int> result(wordsQuery.size());
        int pushPtr = 0;

        int minLenIdx = -1;
        int minLength = 1e5;

        trie[++pushPtr] = Node(minLenIdx);

        // Caching
        for (int i=0; i<wordsContainer.size(); ++i)
        {
            const auto& word = wordsContainer[i];
            auto triePtr = 0;
            
            for (int j=word.length()-1; j>=0; --j)
            {
                auto idx = toIdx(word[j]);
                auto& childPtr = trie[triePtr].child[idx];

                if (childPtr == -1)
                {
                    childPtr = pushPtr;
                    trie[++pushPtr] = Node(i);
                }
                else if (wordsContainer[trie[childPtr].value].length() > word.length())
                    trie[childPtr].value = i;
                    
                triePtr = childPtr;
            }
            if (minLength > word.length())
            {
                minLength = word.length();
                minLenIdx = i;
            }
        }
        trie[0].value = minLenIdx;

        for (int i=0; i<wordsQuery.size(); ++i)
        {
            const auto& query = wordsQuery[i];
            auto triePtr = 0;
            int cached = trie[0].value;

            for (int j=query.length()-1; j>=0; --j)
            {
                auto idx = toIdx(query[j]);
                auto childPtr = trie[triePtr].child[idx];

                if (childPtr != -1)
                    cached = trie[childPtr].value;
                else
                    break;
                
                triePtr = childPtr;
            }
            result[i] = cached;
        }

        // init trie for next
        for (pushPtr; pushPtr>=0; --pushPtr)
        {
            trie[pushPtr] = Node(-1);
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}