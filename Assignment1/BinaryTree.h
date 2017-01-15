#include "TreeNode.h"

class NoTreeExcpetion {};

class BinaryTree
{
private:
	TreeNode* root;
	int totalDepth;
public:
	BinaryTree();
	~BinaryTree();
	void printPostOrder() const;
	void insert(int key);
	void verboseDeleteTree();
	void deleteTree();
	int getTotalDepth() const;
	//Helper fucntions
private:
	void insert(int key, TreeNode *tree, int depth);
	void postorder(TreeNode* tree, int indent) const;
	void verboseDeleteTree(TreeNode* tree);
	void deleteTree(TreeNode* tree);
	bool getRandomBool() const;
};