#include <iostream>
#include <vector>

using namespace std;

/*
    유명한 배낭 문제
*/
struct item
{
    int weight;
    int value;
};

struct node
{
    int curWeight;
    int curValue;
    vector<bool> itemAvailable;
    
    node makeChild(vector<item> &items, const int &idx)
    {
        node child;
        child.curWeight = curWeight + items[idx].weight;
        child.curValue = curValue + items[idx].value;
        child.itemAvailable = itemAvailable;
        child.itemAvailable[idx] = false;
        return child;
    }

    void initNode(const int &LEN)
    {
        curWeight = 0;
        curValue = 0;
        itemAvailable = vector<bool>(LEN,true);
    }
};

int main()
{
    int ITEM_COUNT, MAX_WEIGHT;
    cin >> ITEM_COUNT >> MAX_WEIGHT;

    vector<item> itemVec(ITEM_COUNT);
    for (int i=0; i < ITEM_COUNT; i++)
    {
        cin >> itemVec[i].weight >> itemVec[i].value;
    }

    int maxValue = -1;
    vector<node> visitStack;
    node leaf;
    leaf.initNode(ITEM_COUNT);
    visitStack.push_back(leaf);

    while (!visitStack.empty())
    {
        node curNode = visitStack.back();
        visitStack.pop_back();

        if (curNode.curWeight <= MAX_WEIGHT)
        {
            // make child that available
            if (curNode.curWeight != MAX_WEIGHT)
            {
                for (int i=0; i < ITEM_COUNT; i++)
                {
                    if (curNode.itemAvailable[i])
                    {
                        node ch = curNode.makeChild(itemVec, i);
                        for(int j=0; j < i; j++)
                            ch.itemAvailable[j] = false;
                        visitStack.push_back(ch);
                    }
                }
            }

            if (maxValue < curNode.curValue)
                maxValue = curNode.curValue;
        }
    }
    
    cout << maxValue;
}