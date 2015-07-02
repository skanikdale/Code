#include "stdafx.h"
#include "BTree.h"


void BTree::addNodeinTree(BTreeNode* parentNode, BTreeNode** ppNode, int value)
{
  BTreeNode* pNode = *ppNode;

  if(NULL == pNode)
  {
    *ppNode = initNode(parentNode, value);
  }
  else if (pNode->value < value)
  {
    addNodeinTree(pNode, &pNode->rightNode, value);
  }
  else if(pNode->value > value)
  {
    addNodeinTree(pNode, &pNode->leftNode, value);
  }
}

BTreeNode* BTree::initNode(BTreeNode* parentNode, int value)
{
  BTreeNode* pNode = (BTreeNode*) malloc(sizeof(BTreeNode));
  pNode->leftNode = NULL;
  pNode->rightNode = NULL;
  pNode->value = value;
  pNode->parentNode = parentNode;

  return pNode;
}

void BTree::addNode(int value)
{
  if(NULL == m_pRootNode)
  {
    m_pRootNode = initNode(NULL, value);
  }
  else if(m_pRootNode->value > value)
  {
    // Traverse left tree & add node at appropriate position
    addNodeinTree(m_pRootNode, &m_pRootNode->leftNode, value);
  }
  else if(m_pRootNode->value < value)
  {
    // Traverse right tree & add node at apt location
    addNodeinTree(m_pRootNode, &m_pRootNode->rightNode, value);
  }
  else if(m_pRootNode->value == value)
  {
    // ..... How to handle such case????
    // No need to add new node. it means node already exists
  }
}

void BTree::populateBTree()
{
  // add node to tree
  addNode(28);

  addNode(14);
  addNode(12);
  addNode(17);

  addNode(41);
  addNode(30);
  addNode(45);
  addNode(42);
  addNode(48);
  addNode(72);
}

void BTree::visitEachNode(BTreeNode* pNode)
{
  if(NULL != pNode)
  {
    // printf("%d", pNode->value);  ... Order: Root - Left - right
    visitEachNode(pNode->leftNode);
    printf("%d", pNode->value);    //... Order: Left - Root - right
    visitEachNode(pNode->rightNode);
  }
}

void BTree::traverseBTree()
{  
  visitEachNode(m_pRootNode);
}

BTreeNode* BTree::findinTree(BTreeNode* pNode, int value)
{
  if(NULL == pNode)
    return false;

  if(pNode->value == value)
    return pNode;

  else if(pNode->value > value)
    return findinTree(pNode->leftNode, value);
  else if(pNode->value < value)
    return findinTree(pNode->rightNode, value);
}

BTreeNode* BTree::findElem(int value)
{
  if(m_pRootNode->value == value)
    return m_pRootNode;
  else
    return findinTree(m_pRootNode, value);
}

void  BTree::removeEleminTree(BTreeNode* pNode, int value)
{

  if(NULL == pNode)
    return;

  if(pNode->value == value)
  {
    // remove this node. re-arrange other nodes.
    // check for lowest elem in right tree,
    // replace that elem with root
  }
  else if(pNode->value > value)
  {
    removeEleminTree(pNode->leftNode, value);
  }
  else if(pNode->value < value)
  {
    removeEleminTree(pNode->rightNode, value);
  }
}

BTreeNode* BTree::findLowestElem(BTreeNode* pNode)
{
  if(pNode->leftNode != NULL)
    findLowestElem(pNode->leftNode);
  else
    return pNode;
}

void BTree::removeElem(int value)
{
  BTreeNode* pNode = findElem(value);

  if(pNode == NULL)
    return;

  // 3 cases

  // 1. Selected node has no child
  if(pNode->leftNode == NULL && pNode->rightNode == NULL)
  {
    // get parent
    // check whether selected node is parent's left / right child
    // set left / right child == NULL

    if(pNode->parentNode->leftNode->value == value)
    {
      pNode->parentNode->leftNode->value = 0;
      free(pNode->parentNode->leftNode);
    }
    else
    {
      pNode->parentNode->rightNode->value = 0;
      free(pNode->parentNode->rightNode);
    }
  }

  // 2. Selcted node has child

  // Replace node to be deleted with child
  else
  {
    // 3. Selected node has 2 children
    if(pNode->leftNode != NULL && pNode->rightNode != NULL)
    {
      // Find lowest elem from right tree
      BTreeNode* pLowNode = findLowestElem(pNode->rightNode);

      // pNode = lowest elem;
      pNode->value = pLowNode->value;

      //free lowest elem
      free(pLowNode);
    }
    else // Selected node has one child
    {
      if(pNode->leftNode != NULL)
      {
        pNode->parentNode->leftNode = pNode->leftNode;
        //free(pNode->leftNode);
      }
      else
      {
        pNode->parentNode->rightNode = pNode->rightNode;

        pNode->parentNode->rightNode->parentNode = pNode->parentNode;
        //free(pNode->rightNode);
      }
    }
  }
  
  // release memory for pNode
}

void binaryTreeTest()
{

  /*///////////////////////////////////////////////
  
                28
         14             41
      12     17      30     45
                          42   48
                                  72

  ///////////////////////////////////////////////*/

  BTree* pTree = new BTree();

  // 1. Populate a binary tree
  pTree->populateBTree();
  
  // 2. Traverse a binary tree & print numbers
  pTree->traverseBTree();

  // 3. Second method of traversing
  // 4. Find element in a binary tree
  bool isThere = pTree->findElem(48);
  isThere = pTree->findElem(30);
  isThere = pTree->findElem(4843);

  // 5. Add element in a tree

  // 6. Remove element from  tree

  /* 
    3 cases

    1. Elem don't have child. 
       Find elem & remove it.

    2. Elem has only one child
       Find elem
       Replace elem with child

    3. Elem has 2 children
       Find elem
       Find lowest elem from right tree
       Replace lowest elem with elem to be deleteed.

   */

  pTree->removeElem(41);

  pTree->removeElem(48);
}