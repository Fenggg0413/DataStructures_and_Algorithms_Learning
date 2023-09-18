/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 双指针法
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *pre, *cur = head;
        head = nullptr;
        while(cur)
        {
            pre = cur;
            cur = cur->next;
            pre->next = head;
            head = pre;
        }
        return head;
    }
};