#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void Add(ListNode *&head, int val)
{
	ListNode *newNode = new ListNode(val);
	if (head == NULL) head = newNode;
	else {
		ListNode *node = head;
		while (node->next != NULL)
			node = node->next;
		node->next = newNode;
	}
}

void Remove(ListNode *&head, int val)
{
	if (head == NULL)
		return;

	ListNode *toBeDeleted = NULL;
	if (head->val == val) {
		toBeDeleted = head;
		head = head->next;
	} else {
		ListNode *node = head;
		while (node->next != NULL && node->next->val != val)
			node = node->next;

		if (node->next != NULL && node->next->val == val) {
			toBeDeleted = node->next;
			node->next = node->next->next;
		}
	}

	if (toBeDeleted != NULL) {
		delete toBeDeleted;
		toBeDeleted = NULL;
	}
}

void Remove(ListNode *&head, ListNode *toBeDeleted)
{
	if (head == NULL || toBeDeleted == NULL)
		return;

	if (toBeDeleted->next != NULL) {
		ListNode *next = toBeDeleted->next;
		toBeDeleted->val = next->val;
		toBeDeleted->next = next->next;

		delete next;
		next = NULL;
	} else if (toBeDeleted == head) {
		delete toBeDeleted;
		toBeDeleted = NULL;
		head = NULL;
	} else {
		ListNode *node = head;
		while (node->next != toBeDeleted)
			node = node->next;

		node->next = NULL;
		delete toBeDeleted;
		toBeDeleted = NULL;
	}
}

ListNode *Reverse(ListNode *head)
{
	if (head == NULL)
		return NULL;

	ListNode *prev = NULL;
	ListNode *node = head;
	ListNode *reversedHead = NULL;

	while (node != NULL) {
		ListNode *next = node->next;

		if (next == NULL)
			reversedHead = node;

		node->next = prev;
		prev = node;
		node = next;
	}
	return reversedHead;
}

void PrintReversively(ListNode *head) {
	if (head != NULL) {
		if (head->next != NULL)
			PrintReversively(head->next);
		cout << head->val << endl;
	}
}

ListNode *FindKthFromEnd(ListNode *head, unsigned int k)
{
	if (head == NULL || k == 0)
		return NULL;

	ListNode *fast = head;
	ListNode *slow = head;

	for (unsigned int i = 0; i < k - 1; ++i) {
		if (fast->next != NULL)
			fast = fast->next;
		else
			return NULL;
	}

	while (fast->next != NULL) {
		fast = fast->next;
		slow = slow->next;
	}

	return slow;
}

ListNode *FindMid(ListNode *head)
{
	if (head == NULL)
		return NULL;

	ListNode *fast = head;
	ListNode *slow = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

	return slow;
}

bool HasCircle(ListNode *head)
{
	ListNode *slow = head;
	ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        	return true;
	}
    
	return false;
}

ListNode *Merge(ListNode *head1, ListNode *head2)
{
	if (head1 == NULL)
		return head2;
	if (head2 == NULL)
		return head1;

	ListNode *mergedHead = NULL;
	if (head1->val <= head2->val) {
		mergedHead = head1;
		mergedHead->next = Merge(head1->next, head2);
	} else {
		mergedHead = head2;
		mergedHead->next = Merge(head1, head2->next);
	}

	return mergedHead;
}

int Length(ListNode *head)
{
	int length = 0;
	for (; head != NULL; ++length)
		head = head->next;
	return length;
}

ListNode *FirstCommonNode(ListNode *head1, ListNode *head2)
{
	int diff = Length(head1) - Length(head2);

	ListNode *longHead = head1;
	ListNode *shortHead = head2;

	if (diff < 0) 
		swap(longHead, shortHead);

	for (int i = 0; i < diff; ++i)
		longHead = longHead->next;

	while (longHead != NULL && longHead != shortHead) {
		longHead = longHead->next;
		shortHead = shortHead->next;
	}

	return longHead;
}

bool IsPalindrome(ListNode *&left, ListNode *right)
{
	if (right == NULL)
		return true;

	if (!IsPalindrome(left, right->next))
		return false;

	if (left->val == right->val) {
		left = left->next;
		return true;
	}

	return false;
}

bool IsPalindrome(ListNode *head)
{
	if (head == NULL)
		return true;
	return IsPalindrome(head, head);
}

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

void cloneNodes(RandomListNode *head) {
	RandomListNode *node = head;
	while (node != NULL) {
		RandomListNode *cloned = new RandomListNode(node->label);
		cloned->next = node->next;
		node->next = cloned;
		node = cloned->next;
	}
}

void connectRandomNodes(RandomListNode *head) {
	RandomListNode *node = head;
	while (node != NULL) {
		RandomListNode *cloned = node->next;
		if (node->random != NULL)
			cloned->random = node->random->next;
		node = cloned->next;
	}
}

RandomListNode *reconnectNodes(RandomListNode *head) {
	RandomListNode *clonedHead = head->next;
	RandomListNode *clonedNode = clonedHead;
	RandomListNode *node = head;

	node->next = clonedNode->next;
	node = node->next;

	while (node != NULL) {
		clonedNode->next = node->next;
		clonedNode = clonedNode->next;
		node->next = clonedNode->next;
		node = node->next;
	}

	return clonedHead;
}

RandomListNode *copyRandomList(RandomListNode *head) {
	if (head == NULL)
		return NULL;

	cloneNodes(head);
	connectRandomNodes(head);
	return reconnectNodes(head);
}

int main()
{
	ListNode *head1 = NULL;
    // ListNode  *head2 = NULL;
    // for (int i = 0; i < 10; i++) {
        // if (i & 0x1) Add(head1, i);
        // else Add(head2, i);
    // }
    // PrintReversively(Merge(head1, head2));

    Add(head1, 0);
    Add(head1, 1);
    Add(head1, 1);
    Add(head1, 0);
   	cout << IsPalindrome(head1) << endl; 
}