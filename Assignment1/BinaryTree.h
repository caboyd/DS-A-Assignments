#include "TreeNode.h"

class BinaryTree
{
private:
	TreeNode* root;
	int totalDepth;
public:
	BinaryTree():root(0), totalDepth(0) {};
	~BinaryTree();
	bool isMember(int key) const;
	void printPostOrder() const;
	void insert(int key);
	void verboseDeleteTree();
	void deleteTree();
	int getTotalDepth() const;
	//Helper fucntions
private:
	bool isMember(int key, TreeNode *tree) const;
	void insert(int key, TreeNode *tree, int depth);
	void postorder(TreeNode* tree, int indent) const;
	void verboseDeleteTree(TreeNode* tree);
	void deleteTree(TreeNode* tree);
	bool getRandomBool() const;
};