#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <list>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void PreOrder(TreeNode *root)
{
    if (root == NULL) 
        return;

    stack<TreeNode *> s;
    while (root != NULL || !s.empty()) {
        while (root != NULL) {
            cout << root->val << endl;
            s.push(root);
            root = root->left;
        }

        root = s.top();
        s.pop();
        root = root->right;
    }
}

void InOrder(TreeNode *root)
{
    if (root == NULL)
        return;

    stack<TreeNode *> s;
    while(root != NULL || !s.empty()) {
        while (root != NULL) {
            s.push(root);
            root = root->left;
        }

        root = s.top();
        s.pop();
        cout << root->val << endl;
        root = root->right;
    }
}

struct FlagTreeNode
{
    TreeNode *node;
    bool flag;
    FlagTreeNode(TreeNode *x) : node(x), flag(false) {}
};

void PostOrder(TreeNode *root)
{
    if (root == NULL)
        return;

    stack<FlagTreeNode *> s;
    while (root != NULL || !s.empty()) {
        while (root != NULL) {
            s.push(new FlagTreeNode(root));
            root = root->left;
        }

        FlagTreeNode *flagRoot = s.top();
        if (flagRoot->flag) {
            s.pop();
            cout << flagRoot->node->val << endl;
        } else {
            flagRoot->flag = true;
            root = flagRoot->node->right;
        }
    }
}

void LevelOrder(TreeNode *root)
{
    if (root == NULL)
        return;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        root = q.front();
        q.pop();
        cout << root->val << endl;

        if (root->left != NULL)
            q.push(root->left);
        if (root->right != NULL)
            q.push(root->right);
    }
}

TreeNode *FromPreorderAndInorder
(
    int *startPreorder, int *endPreorder,
    int *startInorder, int *endInorder
)
{
    TreeNode *root = new TreeNode(*startPreorder);
    if (startPreorder == endPreorder) {
        if (startInorder == endInorder
            && *startPreorder == *startInorder)
            return root;
        else
            return NULL;
    }

    int *rootInorder = startInorder;
    while (rootInorder < endInorder && *rootInorder != root->val)
        ++rootInorder;

    if (rootInorder == endInorder && *rootInorder != root->val)
        return NULL;

    int leftLength = rootInorder - startInorder;
    int *leftPreorderEnd = startPreorder + leftLength;
    
    if (leftLength > 0) {
        root->left = FromPreorderAndInorder(startPreorder + 1, leftPreorderEnd,
            startInorder, rootInorder - 1);
    }
    if (leftLength < endPreorder - startPreorder) {
        root->right = FromPreorderAndInorder(leftPreorderEnd + 1, endPreorder,
            rootInorder + 1, endInorder);
    }

    return root;
}

TreeNode *FromPostorderAndInorder
(
    int *startPostorder, int *endPostorder,
    int *startInorder, int *endInorder
)
{
    TreeNode *root = new TreeNode(*endPostorder);
    if (startPostorder == endPostorder) {
        if (startInorder == endInorder
            && *startInorder == *startPostorder)
            return root;
        else
            return NULL;
    }

    int *rootInorder = startInorder;
    while (rootInorder < endInorder && *rootInorder != root->val)
        ++rootInorder;

    if (rootInorder == endInorder && *rootInorder != root->val)
        return NULL;

    int leftLength = rootInorder - startInorder;
    int *leftPostorderEnd = startPostorder + leftLength - 1;
    if (leftLength > 0) {
        root->left = FromPostorderAndInorder(startPostorder, leftPostorderEnd,
            startInorder, rootInorder - 1);
    }
    if (leftLength < endPostorder - startPostorder) {
        root->right = FromPostorderAndInorder(leftPostorderEnd + 1, endPostorder - 1,
            rootInorder + 1, endInorder);
    }

    return root;
}

TreeNode *Construct(int *porder, int *inorder, int length) {
    if (porder == NULL || inorder == NULL || length <= 0)
        return NULL;

    return FromPostorderAndInorder(porder, porder + length - 1,
        inorder, inorder + length - 1);
}

bool DoesTree1HasTree2(TreeNode *root1, TreeNode *root2)
{
    if (root2 == NULL)
        return true;

    if (root1 == NULL)
        return false;

    if (root1->val != root2->val)
        return false;

    return DoesTree1HasTree2(root1->left, root2->left) &&
        DoesTree1HasTree2(root1->right, root2->right);
}

bool HasSubtree(TreeNode *root1, TreeNode *root2)
{
    bool result = false;

    if (root1 != NULL && root2 != NULL) {
        if (root1->val == root2->val)
            result = DoesTree1HasTree2(root1, root2);
        if (!result)
            result = HasSubtree(root1->left, root2);
        if (!result)
            result = HasSubtree(root1->right, root2);
    }

    return result;
}

void Mirror(TreeNode *root)
{
    if (root == NULL)
        return;

    swap(root->left, root->right);

    if (root->left != NULL)
        Mirror(root->left);
    
    if (root->right != NULL) 
        Mirror(root->right);
}

bool IsPostorderOfBST(int postorder[], int length)
{
    if (postorder == NULL || length <= 0)
        return false;

    int root = postorder[length - 1];
    int i = 0;
    for (; i < length - 1; ++i) {
        if (postorder[i] > root)
            break;
    }

    int j = i;
    for (; j < length - 1; ++j) {
        if (postorder[j] < root)
            return false;
    }

    bool left = true;
    if (i > 0) 
        left = IsPostorderOfBST(postorder, i);

    bool right = true;
    if (i < length - 1)
        right = IsPostorderOfBST(postorder + i, length - i - 1);

    return (left && right);
}

void FindPath
(
    TreeNode *root,
    int expectedSum,
    vector<int> path,
    int currentSum
)
{
    currentSum += root->val;
    path.push_back(root->val);

    bool isLeaf = root->left == NULL && root->right == NULL;
    if (currentSum == expectedSum && isLeaf) {
        for (auto &i : path)
            cout << i << " ";
        cout << endl;
    }

    if (root->left != NULL)
        FindPath(root->left, expectedSum, path, currentSum);
    if (root->right != NULL)
        FindPath(root->right, expectedSum, path, currentSum);

    path.pop_back();
}

void FindPath(TreeNode *root, int expectedSum)
{
    if (root == NULL)
        return;

    vector<int> path;
    int currentSum = 0;
    FindPath(root, expectedSum, path, currentSum);
}

void ConvertNode(TreeNode *root, TreeNode **pLastNodeInList)
{
    if (root == NULL)
        return;

    ConvertNode(root->left, pLastNodeInList);
    root->left = *pLastNodeInList;
    if (*pLastNodeInList != NULL)
        (*pLastNodeInList)->right = root;

    *pLastNodeInList = root;
    ConvertNode(root->right, pLastNodeInList);
}

TreeNode *ConvertToList(TreeNode *root)
{
    if (root == NULL)
        return NULL;

    TreeNode *lastNodeInList = NULL;
    ConvertNode(root, &lastNodeInList);

    TreeNode *head = lastNodeInList;
    while (head != NULL && head->left != NULL)
        head = head->left;

    return head;
}

int Depth(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int left = Depth(root->left);
    int right = Depth(root->right);

    return max(left, right) + 1;
}

// bool IsBalanced(TreeNode *root)
// {
//     if (root == NULL)
//         return true;

//     int left = Depth(root->left);
//     int right = Depth(root->right);
//     if (abs(left - right) > 1)
//         return false;

//     return IsBalanced(root->left) &&
//         IsBalanced(root->right);
// }

bool IsBalanced(TreeNode *root, int *depth)
{
    if (root == NULL) {
        *depth = 0;
        return true;
    }

    int left, right;
    if (IsBalanced(root->left, &left)
        && IsBalanced(root->right, &right)) {
        if (abs(left - right) <= 1) {
            *depth = max(left, right) + 1;
            return true;
        }
    }

    return false;
}

bool IsBalanced(TreeNode *root)
{
    int depth = 0;
    return IsBalanced(root, &depth);
}

bool GetNodePath(TreeNode *root, TreeNode *n, list<TreeNode *> &path)
{
    path.push_back(root);

    if (root == n)
        return true;

    bool found = false;
    if (root->left != NULL)
        found = GetNodePath(root->left, n, path);
    if (!found && root->right != NULL)
        found = GetNodePath(root->right, n, path);

    if (!found)
        path.pop_back();

    return found;
}

TreeNode *GetLastCommonNode(const list<TreeNode *> &path1, const list<TreeNode *> &path2)
{
    auto it1 = path1.begin();
    auto it2 = path2.begin();

    TreeNode *last = NULL;

    while (it1 != path1.end() && it2 != path2.end()) {
        if (*it1 == *it2)
            last = *it1;

        ++it1;
        ++it2;
    }

    return last;
}

TreeNode* LowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == NULL || p == NULL || q == NULL)
        return NULL;

    list<TreeNode *> path1;
    GetNodePath(root, p, path1);

    list<TreeNode *> path2;
    GetNodePath(root, q, path2);

    return GetLastCommonNode(path1, path2);
}

int main()
{
    int preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inorder[] = {4, 7, 2, 1, 5, 3, 6, 8};
    int postorder[] = {7, 4, 2, 5, 8, 6, 3, 1};

    TreeNode *root1 = Construct(postorder, inorder, 8);
    // TreeNode *root2 = Construct(postorder, inorder, 8);

    // LevelOrder(root);
    // cout << HasSubtree(root1, root2) << endl;
    // Mirror(root1);
    // PreOrder(root1);
    // int sequence[] = {5, 7, 6, 9, 11, 10, 8};
    // int sequence[] = {7, 4, 6, 5};
    // cout << IsPostorderOfBST(sequence, 4) << endl;
    // FindPath(root1, 18);
    // TreeNode *head = ConvertToList(root1);
    // while (head != NULL) {
        // cout << head->val << endl;
        // head = head->right;
    // }
    // cout << IsBalanced(root1) << endl;
}