// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution // TODO:142循环链表
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        // 引入虚拟头节点避免head为null的情况
        ListNode *dummyhead = new ListNode(0);
        dummyhead->next = head;
        ListNode *fast = dummyhead, *slow = dummyhead;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) // 如果快指针与慢指针相遇，则说明有环
            {
                ListNode *index1 = dummyhead, *index2 = fast;
                while (index1 != index2)
                {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index1;
            }
        }
        return nullptr;
    }
};