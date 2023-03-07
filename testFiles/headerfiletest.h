/* @file BST.h
 * @author Narissa Tsuboi */
#ifndef BST_H
#define BST_H
#include <string>

using namespace std;

template<class ItemType>
class BST {

public:
    //-------------------------------------------------------------------------
    // Binary Search Tree
    // Constructor, CopyConstructor, Assignment Op, Destructor
    // ------------------------------------------------------------------------

	BST<ItemType>();

	BST(const BST<ItemType>&);

    BST<ItemType>& operator=(const BST<ItemType>& otherBST);

    ~BST<ItemType>();

    //-------------------------------------------------------------------------
    // Public Methods
    // Accessors and Mutators
    //-------------------------------------------------------------------------

    // Adds a new node containing the given data item to this BST
    // @pre item is data
    // @post
    bool insert(ItemType);

    // Tests whether the given data item occurs in this BST
    // @pre key is the data item to search
    // @return true if BST contains the given data item, false if not
    bool contains(const ItemType&);

    // Removes the key value from the tree by calling removeHelper
    // @pre key is the data item to remove
    // @return true if removal was successful,
    bool remove(const ItemType&);

    // Checks if the BST has 1 or more nodes
    // @return true if BST has 1 or more nodes, false if BST has 0 nodes
    bool empty() const;

    // Returns the size of the BST
    // @return number of nodes held in the BST
    int size() const;

    // Returns the number of leaf nodes in the BST
    // @return number of leaf nodes
    int getLeafCount() const;

    // Returns the height of the BST, where the root has height = 0
    // @return height of BST
    int getHeight() const;

    // Returns the level at which a given key resides, where the root has
    // level = 41
    // @pre key is the data in the node of which to find the level
    // @return level of BST
    int getLevel(const ItemType&) const;

    // Returns a string of all the ancestors of node with a given key,
    // returns a blank if no ancestors
    // @pre key is the data in the node of which to find its ancestors
    // @return string containing ancestors
    string getAncestors(const ItemType&) const;

    //-------------------------------------------------------------------------
    // Public Transversals
    // Preorder, Inorder, Postorder
    //-------------------------------------------------------------------------

    // Preorder traverses BST and returns a string containing the data of the
    // nodes encountered during each visit, if empty, returns a blank string
    // @return a string containing the data from each visit
    string getpreorderTransversal() const;

    // Inorder traverses BST and returns a string containing the data of the
    // nodes encountered during each visit, if empty, returns a blank string
    // @return a string containing the data from each visit
    string getinorderTransversal() const;

    // Postorder traverses BST and returns a string containing the data of the
    // nodes encountered during each visit, if empty, returns a blank string
    // @return a string containing the data from each visit
    string getpostOrderTransversal() const;

private:
    //-------------------------------------------------------------------------
    // Node Struct
    //-------------------------------------------------------------------------

    // Struct of nodes for link-base binary tree
    struct Node {
        Node();
        Node(ItemType& , Node*, Node*);
		ItemType data; // data portion of node
		Node * left;   // pointer to left child
		Node * right;  // pointer to right child
	};
	Node * root; // first node in BST

	/* Copy Constructor Helper*/
    BST<ItemType>* copyTree(Node*&);

    //-------------------------------------------------------------------------
    // Helpers for Public Accessors and Setters
    //-------------------------------------------------------------------------

    // Recursively inserts a new node to the BST
    // @pre Node pointer (root) and new node pointer
    // @post BST size increases +1
    // @return true if inserted successfully
    bool insertHelper(Node *&, Node *& );

    // Recursively checks if a node is contained in the BST
    // @pre Node pointer (root) and key, the data of the node pointer
    // @return true if node is contained in the BSt
    bool containsHelper(const Node *, const ItemType&) const;

    // Recursively postorder traverses the BST until the node with the key is
    // found, them deletes the node from the BST using makeDeletion
    // @pre key is the data in the node to remove
    // @return true if removal was successful
    bool removeHelper(Node *&, const ItemType&);


    // Recursively counts the number of nodes in the BST via its left and
    // right branches from the root
    // @pre Node pointer (root)
    // @return number of nodes found in current iteration
    int sizeHelper(const Node *) const;

    // Recursively counts the number of leaf nodes in the BST via its left
    // and right branches from the root
    // @pre Node pointer (root)
    // @return number of leaf nodes found in current iteration
    int getLeafCountHelper(const Node *) const;

    // Recursively tallies the height of the BST via its left and right
    // branches from the root
    // @pre Node pointer (root)
    // @return height of the current iteration
    int getHeightHelper(const Node *) const;

    // Recursively tallies the level of the BSt via its left and right
    // branches from the root
    // @pre Node pointer(root)
    // @return level of the current iteration
    int getLevelHelper(const Node *, const ItemType&, int&) const;

    // Recursively concatenates a string containing the ancestors found up to
    // the point of the current iteration
    // @pre Node pointer(root), key to find ancestors for, string to store
    // list of ancestors
    // @return string containing list of ancestors
    bool getAncestorsHelper(const Node *, const ItemType&, stringstream&) const;

    // Deletes a node from the BST
    void makeDeletion(Node *&);

    // Clears the BST of all nodes
    void destroyTree(Node *&);

    //-------------------------------------------------------------------------
    // Helpers for Public Transversals
    //-------------------------------------------------------------------------
    //*** All helpers convert int to string within function ***//

    // Recursively preorder traverses BST and returns a string containing the
    // data of the nodes encountered during each visit, if empty, returns a
    // blank string
    // @return a string containing the ancestors from each visit
    void preorderTraversalHelper(Node *, stringstream&) const;
//    void preorderTraversalHelper(Node *, string&);

    // Recursively inorder traverses BST and returns a string containing the
    // data of the nodes encountered during each visit, if empty, returns a
    // blank string
    // @return a string containing the ancestors from each visit
    void inorderTraversalHelper(Node *, stringstream&) const;

    // Recursively postorder traverses BST and returns a string containing the
    // data of the nodes encountered during each visit, if empty, returns a
    // blank string
    // @return a string containing the ancestors from each visit
    void postorderTraversalHelper(Node *, stringstream&)const;
};
#include "BST.cpp"
#endif
