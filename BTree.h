
struct BTreeNode{

  BTreeNode* leftNode;
  int        value;
  BTreeNode* rightNode;
  BTreeNode* parentNode;
};


class BTree
{

public:
  void addNode(int value);
  void populateBTree();
  void traverseBTree();
  BTreeNode* findElem(int value);
  void removeElem(int value);

private:

  BTreeNode* initNode(BTreeNode* parentNode, int value);
  void addNodeinTree(BTreeNode* parentNode, BTreeNode** pNode, int value);

  void visitEachNode(BTreeNode* pNode);
  BTreeNode* findinTree(BTreeNode* pNode, int value);
  void  removeEleminTree(BTreeNode* pNode, int value);

  BTreeNode* findLowestElem(BTreeNode* pNode);

  BTreeNode* m_pRootNode;
};