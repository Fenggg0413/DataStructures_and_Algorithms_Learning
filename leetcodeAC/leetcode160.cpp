// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *curA = headA, *curB = headB;
        int count1 = 0, count2 = 0;
        while (curA)
        {
            ++count1;
            curA = curA->next;
        }
        curA = headA;
        while (curB)
        {
            ++count2;
            curB = curB->next;
        }
        curB = headB;
        if (count1 > count2) // A链较长, 移动指向A链的指针使其与B链对齐
        {
            int tmp = count1 - count2;
            while (tmp--)
            {
                curA = curA->next;
            }    
        }
        else
        {
            int tmp = count2 - count1;
            while (tmp--)
            {
                curB = curB->next;
            }
        }
        while (curA && curB)
        {
            if(curA == curB)
                return curA;
            curA = curA->next;
            curB = curB->next;
        }
        return nullptr;
    }
};