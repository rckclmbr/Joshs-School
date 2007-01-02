//Header File Binary Search Tree
#ifndef H_binaryTree
#define H_binaryTree

#include <iostream>

using namespace std;

     //Definition of the node
template<class elemType>
struct nodeType
{
   elemType	           name;
   elemType            desc;
   nodeType<elemType>  *llink;
   nodeType<elemType>  *rlink;
};

    //Definition of the class
template <class elemType>
class binaryTreeType
{
public:
    const binaryTreeType<elemType>& operator=
                 (const binaryTreeType<elemType>&); 
      //Overload the assignment operator.
    bool isEmpty();
      //Function to determine if the binary tree is empty.
      //Postcondition: Returns true if the binary tree is empty;
      //               otherwise, returns false.
    void inorderTraversal();
      //Function to do an inorder traversal of the binary tree.
      //Postcondition: The nodes of the binary tree are output
      //               in the inorder sequence.
    void preorderTraversal();
      //Function to do a preorder traversal of the binary tree.
      //Postcondition: The nodes of the binary tree are output
      //               in the preorder sequence.
    void postorderTraversal();
      //Function to do a postorder traversal of the binary tree.
      //Postcondition: The nodes of the binary tree are output
      //               in the postorder sequence.

    int treeHeight();
      //Function to deteremine the height of the binary tree.
      //Postcondition: The height of the binary tree is returned.
    int treeNodeCount();
      //Function to determine the number of nodes in the 
      //binary tree.
      //Postcondition: The number of nodes in the binary tree
      //               is returned.
    int treeLeavesCount();
      //Function to determine the number of leaves in the 
      //binary tree.
      //Postcondition: The number of leaves in the binary tree
      //               is returned.
    void destroyTree();
      //Deallocates the memory space occupied by the binary tree.
      //Postcondition: root = NULL;

    binaryTreeType(const binaryTreeType<elemType>& otherTree); 
      //copy constructor

    binaryTreeType();   
      //default constructor

    ~binaryTreeType();   
      //destructor

protected:
    nodeType<elemType> *root;

private:
    void copyTree(nodeType<elemType>* &copiedTreeRoot,
                  nodeType<elemType>* otherTreeRoot);
      //Function to make a copy of the binary tree to 
      //which otherTreeRoot points. 
      //Postcondition: The pointer copiedTreeRoot points to
      //               the root of the copied binary tree.

    void destroy(nodeType<elemType>* &p);
      //Function to destroy the binary tree to which p points. 
      //Postcondition: The nodes of the binary tree to which
      //               p points are deallocated.
      //               p = NULL.

    void inorder(nodeType<elemType> *p);
      //Function to do an inorder traversal of the binary
      //tree to which p points.  
      //Postcondition: The nodes of the binary tree to which p
      //               points are output in the inorder sequence.
    void preorder(nodeType<elemType> *p);
      //Function to do a preorder traversal of the binary
      //tree to which p points.  
      //Postcondition: The nodes of the binary tree to which p
      //               points are output in the preorder sequence.
    void postorder(nodeType<elemType> *p);
      //Function to do a postorder traversal of the binary
      //tree to which p points.  
      //Postcondition: The nodes of the binary tree to which p
      //               points are output in the postorder sequence.

    int height(nodeType<elemType> *p);
      //Function to determine the height of the binary tree
      //to which p points. 
      //Postcondition: The height of the binary tree to which p
      //               points is returned.

    int max(int x, int y);
      //Function to determine the larger of x and y.
      //Postcondition: The larger of x and y is returned.

    int nodeCount(nodeType<elemType> *p);
      //Function to determine the number of nodes in the binary 
      //tree to which p points. 
      //Postcondition: The number of nodes in the binary tree
      //               to which p points is returned.

    int leavesCount(nodeType<elemType> *p);
      //Function to determine the number of leaves in the binary 
      //tree to which p points.
      //Postcondition: The number of nodes in the binary tree
      //               to which p points is returned.
};

	//Definition of member functions

template<class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
	root = NULL;
}

template<class elemType>
bool binaryTreeType<elemType>::isEmpty()
{
	return (root == NULL);
}

template<class elemType>
void binaryTreeType<elemType>::inorderTraversal()
{
	inorder(root);
}

template<class elemType>
void binaryTreeType<elemType>::preorderTraversal()
{
	preorder(root);
}

template<class elemType>
void binaryTreeType<elemType>::postorderTraversal()
{
	postorder(root);
}

template<class elemType>
int binaryTreeType<elemType>::treeHeight()
{
	return height(root);
}

template<class elemType>
int binaryTreeType<elemType>::treeNodeCount()
{
	return nodeCount(root);
}

template<class elemType>
int binaryTreeType<elemType>::treeLeavesCount()
{
	return leavesCount(root);
}

template <class elemType>
void  binaryTreeType<elemType>::copyTree
                      (nodeType<elemType>* &copiedTreeRoot,
		               nodeType<elemType>* otherTreeRoot)
{
	if(otherTreeRoot == NULL)
		copiedTreeRoot = NULL;
	else
	{
		copiedTreeRoot = new nodeType<elemType>;
		copiedTreeRoot->name = otherTreeRoot->name;
		copiedTreeRoot->desc = otherTreeRoot->desc;
		copyTree(copiedTreeRoot->llink, otherTreeRoot->llink);
		copyTree(copiedTreeRoot->rlink, otherTreeRoot->rlink);
	}
} //end copyTree

template<class elemType>
void binaryTreeType<elemType>::inorder(nodeType<elemType> *p)
{
	if(p != NULL)
	{
		inorder(p->llink);
		cout<<p->name<<" ";
		inorder(p->rlink);
	}
}

template<class elemType>
void binaryTreeType<elemType>::preorder(nodeType<elemType> *p)
{
	if(p != NULL)
	{
		cout<<p->name<<" ";
		preorder(p->llink);
		preorder(p->rlink);
	}
}

template<class elemType>
void binaryTreeType<elemType>::postorder(nodeType<elemType> *p)
{
	if(p != NULL)
	{
		postorder(p->llink);
		postorder(p->rlink);
		cout<<p->name<<" ";
	}		
}

   //Overload the assignment operator
template<class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::
           operator=(const binaryTreeType<elemType>& otherTree)
{ 
     
	if(this != &otherTree) //avoid self-copy
	{
		if(root != NULL)  //if the binary tree is not empty, 
			              //destroy the binary tree
			destroy(root);

		if(otherTree.root == NULL) //otherTree is empty
			root = NULL;
		else
			copyTree(root, otherTree.root);
	}//end else

   return *this; 
}

template <class elemType>
void  binaryTreeType<elemType>::destroy(nodeType<elemType>* &p)
{
	if(p != NULL)
	{
		destroy(p->llink);
		destroy(p->rlink);
		delete p;
		p = NULL;
	}
}

template <class elemType>
void  binaryTreeType<elemType>::destroyTree()
{
	destroy(root);
}

	//copy constructor
template <class elemType>
binaryTreeType<elemType>::binaryTreeType
              (const binaryTreeType<elemType>& otherTree)
{
	if(otherTree.root == NULL) //otherTree is empty
		root = NULL;
	else
		copyTree(root, otherTree.root);
}

template <class elemType>
binaryTreeType<elemType>::~binaryTreeType()
{
	destroy(root);
}

template<class elemType>
int binaryTreeType<elemType>::height(nodeType<elemType> *p)
{
	if(p == NULL)
		return 0;
	else
		return 1 + max(height(p->llink), height(p->rlink));
}

template<class elemType>
int binaryTreeType<elemType>::max(int x, int y)
{
	if(x >= y)
		return x;
	else
		return y;
}

template<class elemType>
int binaryTreeType<elemType>::nodeCount(nodeType<elemType> *p)
{
	cout<<"Write the definition of the function nodeCount"
		<<endl;

	return 0;
}

template<class elemType>
int binaryTreeType<elemType>::leavesCount(nodeType<elemType> *p)
{
	cout<<"Write the definition of the function leavesCount"
		<<endl;

	return 0;
}

#endif

