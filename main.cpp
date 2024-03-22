#include <iostream>
#include <vector>

using namespace std;

// Define binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* traversal(vector<int>& inorder, int inorderBegin, int inorderEnd, vector<int>& preorder, int preorderBegin, int preorderEnd) {
        if (preorderBegin == preorderEnd) return nullptr;

        int rootValue = preorder[preorderBegin];
        TreeNode* root = new TreeNode(rootValue);

        if (preorderEnd - preorderBegin == 1) return root;

        int delimiterIndex;
        for (delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++) {
            if (inorder[delimiterIndex] == rootValue) break;
        }

        int leftInorderBegin = inorderBegin;
        int leftInorderEnd = delimiterIndex;
        int rightInorderBegin = delimiterIndex + 1;
        int rightInorderEnd = inorderEnd;

        int leftPreorderBegin = preorderBegin + 1;
        int leftPreorderEnd = preorderBegin + 1 + delimiterIndex - inorderBegin;
        int rightPreorderBegin = preorderBegin + 1 + (delimiterIndex - inorderBegin);
        int rightPreorderEnd = preorderEnd;

        root->left = traversal(inorder, leftInorderBegin, leftInorderEnd, preorder, leftPreorderBegin, leftPreorderEnd);
        root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, preorder, rightPreorderBegin, rightPreorderEnd);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (inorder.size() == 0 || preorder.size() == 0) return nullptr;

        return traversal(inorder, 0, inorder.size(), preorder, 0, preorder.size());
    }

    void postorderTraversal(TreeNode* root) {
        if (root == nullptr) return;
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->val << " ";
    }
};

int main() {
    vector<int> preorder = { 1, 2, 4, 5, 6, 3, 7 };
    vector<int> inorder = { 4, 2, 5, 1, 3, 6, 7 };

    Solution solution;
    TreeNode* root = solution.buildTree(preorder, inorder);

    cout << "Postorder traversal: ";
    solution.postorderTraversal(root);
    cout << endl;

    return 0;
}
