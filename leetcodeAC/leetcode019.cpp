// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummyhead = new ListNode(0);
        dummyhead->next = head;
        // 常规写法
        // ListNode *cur = dummyhead;
        // int count = 0;
        // while (cur->next != nullptr)
        // {
        //     ++count;
        //     cur = cur->next;
        // }
        // int rm = count - n;
        // cur = dummyhead;
        // while (rm--)
        // {
        //     cur = cur->next;
        // }
        // ListNode *tmp = cur->next;
        // cur->next = cur->next->next;
        // delete tmp;
        // tmp = nullptr;

        // 只扫描一次
        ListNode *fast = dummyhead;
        ListNode *slow = dummyhead;
        n++;
        while (n--)
        {
            fast = fast->next;
        }
        while(fast != nullptr)
        {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode *tmp = slow->next;
        slow->next = slow->next->next;
        delete tmp;
        tmp = nullptr;
        return dummyhead->next;
    }
};

int main()
{
    Solution s;
    ListNode *p1 = new ListNode(1);
    ListNode *p2 = new ListNode(2);
    ListNode *p3 = new ListNode(3);
    p1->next = p2;
    p2->next = p3;
    s.removeNthFromEnd(p1, 1);

    return 0;
}