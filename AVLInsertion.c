#include <stdio.h>
#include <stdlib.h>

#define GLOBALSPACE 3

typedef struct node
{
    struct node *left;
    int data;
    struct node *right;
} node;

node *RightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    return x;
}

node *LeftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    return y;
}

node *RLRotate(node *z)
{
    z->right = RightRotate(z->right);
    return LeftRotate(z);
}

node *LRRotate(node *z)
{
    z->left = LeftRotate(z->left);
    return RightRotate(z);
}

int getHeight(node *Alpha)
{
    if (Alpha == NULL)
    {
        return -1;
    }
    else
    {
        int R_height = getHeight(Alpha->right);
        int L_height = getHeight(Alpha->left);

        if (R_height < L_height)
        {
            return L_height + 1;
        }
        else
        {
            return R_height + 1;
        }
    }
}

node *newNode(int givenData)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = givenData;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

int balenceFac(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int L_height = getHeight(root->left);
        int R_height = getHeight(root->right);
        return L_height - R_height;
    }
}

node *insertTree(node *root, int givenData)
{
    if (root == NULL)
    {
        return newNode(givenData);
    }

    if (givenData < root->data)
    {
        root->left = insertTree(root->left, givenData);
    }
    else if (givenData > root->data)
    {
        root->right = insertTree(root->right, givenData);
    }
    else
    {
        printf("Duplicate data found: %d already exists in the tree.\n", givenData);
        return root;
    }

    int balance = balenceFac(root);

    if (balance > 1)
    {
        if (givenData < root->left->data)
        {
            return RightRotate(root);
        }
        else
        {
            return LRRotate(root);
        }
    }

    if (balance < -1)
    {
        if (givenData > root->right->data)
        {
            return LeftRotate(root);
        }
        else
        {
            return RLRotate(root);
        }
    }

    return root;
}

void Print2D(node *root, int space)
{
    if (root == NULL)
    {
        return;
    }
    space = space + GLOBALSPACE;
    Print2D(root->right, space);
    printf("\n");
    for (int i = GLOBALSPACE; i < space; i++)
    {
        printf(" ");
    }
    printf("%d\n", root->data);
    Print2D(root->left, space);
}

int main()
{
    int n;
    printf("Please enter the number of elements you want to enter: ");
    scanf("%d", &n);
    int input;
    node *root = NULL;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &input);
        root = insertTree(root, input);
    }

    printf("Look at the graph --> way\n");
    Print2D(root, 5);

    return 0;
}
