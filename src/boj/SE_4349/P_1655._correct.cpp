#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
    2개 힙을 구성하고 두 힙간 개수의 균형을 유지하는 문제
    중간값 아래 힙(최대 힙), 중간값 위 힙(최소 힙)으로 구성

    직접 힙을 구현해봤음
    그런데 push만 있으면 될줄 알았는데 pop도 있어야됨....
    왜냐면 균형을 맞추기 위해 힙의 루트가 다른 힙으로 옮겨야할 때도 있기 때문....
*/

template <typename Compare>
struct Test
{
    vector<int> elements;
    int count = 0;
    Compare cmp;

    Test(Compare c = Compare()) : cmp(c){}

    void push(int newElem)
    {
        elements.push_back(newElem);
        count++;
        
        int newElemIdx = count-1;
        while(newElemIdx > 0)
        {
            if (cmp(elements[newElemIdx], elements[(newElemIdx-1)/2]))
            {
                swap(elements[newElemIdx], elements[(newElemIdx-1)/2]);
                newElemIdx = (newElemIdx-1)/2;
            }
            else
                break;
        }
    }

    int pop()
    {
        int root = elements.front();
        swap(elements.front(),elements.back());
        elements.pop_back();
        count--;

        int curIndex = 0;
        int swapIdx = 0;

        while(curIndex < count)
        {
            swapIdx = curIndex;
            int leftChildIdx = curIndex*2 + 1;
            int rightChildIdx = curIndex*2 + 2;

            if (leftChildIdx >= count)
                break;
            
            bool leftCmpFlg = cmp(elements[leftChildIdx], elements[curIndex]);

            if (rightChildIdx < count)
            {
                bool rightCmpFlg = cmp(elements[rightChildIdx], elements[curIndex]);

                if(leftCmpFlg && rightCmpFlg)
                {
                    if(cmp(elements[leftChildIdx], elements[rightChildIdx]))
                        swapIdx = leftChildIdx;
                    else
                        swapIdx = rightChildIdx;
                }
                else if(leftCmpFlg)
                    swapIdx = leftChildIdx;
                else if(rightCmpFlg)
                    swapIdx = rightChildIdx;
            }
            else
            {
                if(leftCmpFlg)
                    swapIdx = leftChildIdx;
            }

            if (swapIdx == curIndex)
                break;
                
            swap(elements[swapIdx],elements[curIndex]);
            curIndex = swapIdx;
        }
        
        return root;
    }
};

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);
    
    int iter, input;
    Test<greater<int>> lowerMid;
    Test<less<int>> upperMid;

    cin >> iter;

    for (int i=0; i<iter; i++)
    {
        cin >> input;

        if (lowerMid.count == 0)
            lowerMid.push(input);
        else
        {
            if (lowerMid.elements.front() < input)
                upperMid.push(input);
            else
                lowerMid.push(input);
        }

        if (lowerMid.count - upperMid.count > 1)
        {
            upperMid.push(lowerMid.elements.front());
            lowerMid.pop();
        }
        else if(lowerMid.count - upperMid.count < -1)
        {    
            lowerMid.push(upperMid.elements.front());
            upperMid.pop();
        }

        if (lowerMid.count < upperMid.count)
            cout << upperMid.elements.front() << '\n';
        else
            cout << lowerMid.elements.front() << '\n';
    }
}