#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct Node
{
    int data;
    int color;
    struct Node *parent, *left, *right;
};

typedef struct Node Node;

// Function prototypes
Node *createNode(int data);
Node *insert(Node *root, int data);
Node *insertFixup(Node *root, Node *newNode);
void leftRotate(Node **root, Node *x);
void rightRotate(Node **root, Node *y);
Node *search(Node *root, int data);
void inOrderTraversal(Node *root);

int main()
{
    Node *root = NULL;

    // Insert elements into the Red-Black Tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);

    // Search for an element in the tree
    int searchData = 20;
    Node *searchResult = search(root, searchData);
    if (searchResult != NULL)
    {
        printf("%d found in the Red-Black Tree.\n", searchData);
    }
    else
    {
        printf("%d not found in the Red-Black Tree.\n", searchData);
    }

    // Display the Red-Black Tree using in-order traversal
    printf("Red-Black Tree (in-order traversal):\n");
    inOrderTraversal(root);

    return 0;
}

// Create a new node with the given data
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->data = data;
        newNode->color = RED; // New nodes are always red initially
        newNode->parent = newNode->left = newNode->right = NULL;
    }
    return newNode;
}

// Insert a new node with the given data into the Red-Black Tree
Node *insert(Node *root, int data)
{
    Node *newNode = createNode(data);

    if (root == NULL)
    {
        // If the tree is empty, the new node becomes the root
        newNode->color = BLACK; // Root is always black
        return newNode;
    }

    // Perform a standard BST insert
    Node *parent = NULL;
    Node *current = root;
    while (current != NULL)
    {
        parent = current;
        if (data < current->data)
        {
            current = current->left;
        }
        else if (data > current->data)
        {
            current = current->right;
        }
        else
        {
            // Duplicate keys are not allowed in the Red-Black Tree
            free(newNode);
            return root;
        }
    }

    // Set the parent of the new node
    newNode->parent = parent;

    // Link the new node to its parent
    if (data < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    // Fix the Red-Black Tree properties
    return insertFixup(root, newNode);
}

// Fix the Red-Black Tree properties after insertion
Node *insertFixup(Node *root, Node *newNode)
{
    Node *parent, *grandparent;

    while (newNode != root && newNode->color == RED && newNode->parent->color == RED)
    {
        parent = newNode->parent;
        grandparent = parent->parent;

        // Case 1: Parent is the left child of the grandparent
        if (parent == grandparent->left)
        {
            Node *uncle = grandparent->right;

            // Case 1a: Uncle is red
            if (uncle != NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            }
            else
            {
                // Case 1b: Uncle is black or NULL, and newNode is the right child
                if (newNode == parent->right)
                {
                    leftRotate(&root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                // Case 1c: Uncle is black or NULL, and newNode is the left child
                rightRotate(&root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                newNode = parent;
            }
        }
        else // Case 2: Parent is the right child of the grandparent
        {
            Node *uncle = grandparent->left;

            // Case 2a: Uncle is red
            if (uncle != NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            }
            else
            {
                // Case 2b: Uncle is black or NULL, and newNode is the left child
                if (newNode == parent->left)
                {
                    rightRotate(&root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                // Case 2c: Uncle is black or NULL, and newNode is the right child
                leftRotate(&root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                newNode = parent;
            }
        }
    }

    // Ensure the root is black
    root->color = BLACK;

    return root;
}

// Left rotation of the Red-Black Tree
void leftRotate(Node **root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL)
    {
        *root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Right rotation of the Red-Black Tree
void rightRotate(Node **root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NULL)
    {
        *root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

// Search for a node with the given data in the Red-Black Tree
Node *search(Node *root, int data)
{
    while (root != NULL && root->data != data)
    {
        if (data < root->data)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return root;
}

// In-order traversal of the Red-Black Tree
void inOrderTraversal(Node *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}
