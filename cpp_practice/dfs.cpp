
#include<iostream>
#include<queue>
using namespace std;

class TreeNode {
    private:
        int         value;
        TreeNode   *left;
        TreeNode   *right;

    public:

        TreeNode(int val) : value(val), left(NULL), right(NULL) { 

        }

        int getValue() { return value; }
        TreeNode *getLeft() { return left; }
        TreeNode * getRight() { return right; }

        void setValue(int val) { this->value = val; }
        void setLeft(TreeNode *l) { this->left = l; }
        void setRight(TreeNode *r) { this->right = r; }
};

class BST {
    private:
        TreeNode *rootNode;

        TreeNode *insertNodeHelper(int val, TreeNode *node) 
        {
            TreeNode *t;

            if (node == NULL) 
                return new TreeNode(val);

            if (val < node->getValue()) 
            {
                // insert on the left
                t = insertNodeHelper(val, node->getLeft());

                if (t) 
                    node->setLeft(t);
            }
            else
            {
                // insert on the right
                t = insertNodeHelper(val, node->getRight());

                if (t) 
                    node->setRight(t);
            }
            return NULL;
        }

        void performDFSHelper(TreeNode *node)
        {
            // base
            if (node == NULL)
                return;
            
            if (node->getLeft())
                performDFSHelper(node->getLeft());

            cout << node->getValue() << " ";

            if (node->getRight()) 
                performDFSHelper(node->getRight());
        }

        void performBFSHelper(queue<TreeNode *> bfs_queue)
        {
            TreeNode *node;

            if (bfs_queue.empty())
                return;
            
            node = bfs_queue.front();
            cout << node->getValue() << " ";
            
            bfs_queue.pop();

            if (node->getLeft()) 
                bfs_queue.push(node->getLeft());
            if (node->getRight()) 
                bfs_queue.push(node->getRight());
            

            performBFSHelper(bfs_queue);
        }

    public:

        BST() {
            this->rootNode = NULL;
        }

        void insertNode(int val)
        {

            TreeNode *t = insertNodeHelper(val, this->rootNode);
            if (this->rootNode == NULL) {
                this->rootNode = t;
            }
        }

        TreeNode *findNode(TreeNode *root, int val)
        {
            if (root == NULL)
                return NULL;

            if (root->getValue() == val)
                return root;
            else if (root->getValue() < val)
                return findNode(root->getRight(), val);
            else
                return findNode(root->getLeft(), val);
        }

        TreeNode *findInOrderSuccessor(TreeNode *root)
        {

        }

        // void deleteNode(int val)
        // {
        //     TreeNode *parent;
        //     TreeNode *node = findNode(this->rootNode, val, parent);

        //     if (node == NULL)
        //         return;

        //     bool isLeftNode = (parent->getLeft() == node) ? true : false;

        //     bool hasLeftNode = node->getLeft() != NULL;
        //     bool hasRightNode = node->getRight() != NULL;

        //     // delete leaf
        //     if (hasLeftNode && hasRightNode)
        //     {
        //         // What is in-order traversal: Left Root Right. Gives Sorted List
        //         TreeNode *inOrderSuccessor = findInOrderSuccessor(this->rootNode, val);
        //         (isLeftNode) ? parent->setLeft(inOrderSuccessor) : parent->setRight(inOrderSuccessor);
        //     }
        //     else if (hasLeftNode || hasRightNode)
        //     {
        //         TreeNode *temp = (hasLeftNode) ? node->getLeft() : node.getRight();
        //         (isLeftNode) ? parent->setLeft(temp) : parent->setRight(temp);
        //     }
        //     else
        //     {
        //         (isLeftNode) ? parent->setLeft(NULL) : parent->setRight(NULL);
        //     }
        //     delete node;
        // }

        void performDFS() 
        {
            performDFSHelper(this->rootNode);
        }

        void performBFS() 
        {
            queue<TreeNode *> bfs_queue;
            bfs_queue.push(this->rootNode);
            performBFSHelper(bfs_queue);
        }
};

int main()
{
    BST myTree;

    myTree.insertNode(10);
    myTree.insertNode(5);
    myTree.insertNode(15);
    myTree.insertNode(12);
    myTree.insertNode(13);
    myTree.insertNode(8);
    myTree.insertNode(1);
    myTree.insertNode(2);

    myTree.performDFS();
    cout << "\n";
    myTree.performBFS();

    return 0;
}