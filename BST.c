#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *right_child;
    struct node *left_child;
};
int binary_search_tree_check(struct node *root)
{
    static struct node *prev = NULL;
    if (root != NULL)
    {
        if (!binary_search_tree_check(root->left_child))
        {
            return 0;
        }
        if (prev != NULL && root->data <= prev->data)
        {
            return 0;
        }
        prev = root;
        return binary_search_tree_check(root->right_child);
    }
    else
    {
        return 1;
    }
}
struct node *search(struct node *root, int key)
{
    while (root != NULL)
    {
        if (key == root->data)
        {
            return root;
        }
        if (key > root->data)
        {
            root = root->right_child;
        }
        else
        {
            root = root->left_child;
        }
    }
    return NULL;
}
struct node *new_node(int x)
{
    struct node *temp;
    temp = malloc(sizeof(struct node));
    temp->data = x;
    temp->left_child = NULL;
    temp->right_child = NULL;

    return temp;
}
void insert(struct node **root, int data)
{
    struct node *prev = NULL;
    struct node *current = *root;

    while (current != NULL)
    {
        prev = current;
        if (data == current->data)
        {
            printf("Cannot insert, element already found in the BST.\n");
            return;
        }
        else if (data > current->data)
        {
            current = current->right_child;
        }
        else
        {
            current = current->left_child;
        }
    }

    struct node *new = new_node(data);
    if (prev == NULL)
    {
        *root = new;
    }
    else if (data > prev->data)
    {
        prev->right_child = new;
    }
    else
    {
        prev->left_child = new;
    }
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left_child);
        printf(" %d ", root->data);
        inorder(root->right_child);
    }
}
void postorder(struct node *root)

{
    if (root != NULL)

    {
        postorder(root->left_child);
        postorder(root->right_child);
        printf("%d  ", root->data);
    }
}
void preorder(struct node *root)
{

    if (root != NULL)
    {
        printf("%d  ", root->data);
        preorder(root->left_child);
        preorder(root->right_child);
    }
}

struct node *inOrderPredesessor(struct node *root)
{
    if (root == NULL || root->left_child == NULL)
    {
        return NULL;
    }

    root = root->left_child;
    while (root->right_child != NULL)
    {
        root = root->right_child;
    }

    return root;
}


struct node *delete_node(struct node *root, int key)
{
    struct node *iPre;
    if (root == NULL)
    {
        return NULL;
    }
    if (root->left_child == NULL && root->right_child == NULL)
    {
        if (root->data == key)
        {
            free(root);
            return NULL;
        }
        else
        {
            return root;
        }
    }
    if (key < root->data)
    {
        root->left_child = delete_node(root->left_child, key);
    }
    else if (key > root->data)
    {
        root->right_child = delete_node(root->right_child, key);
    }
    else
    {
        if (root->left_child != NULL)
        {
            iPre = inOrderPredesessor(root);
            root->data = iPre->data;
            root->left_child = delete_node(root->left_child, iPre->data);
        }
        else
        {
            struct node *temp = root->right_child;
            free(root);
            return temp;
        }
    }
    return root;
}


int main()
{
    struct node *root = NULL;
    // 20 5 1 15 9 7 12 30 25 40 45 42

    int ni;
    printf("how many entities you want to enter\n");
    scanf("%d", &ni);
    int a;
    printf("enter the data to be insteted \n");

    for (int i = 0; i < ni; i++)
    {
        scanf("%d", &a);
        insert(&root, a);
    }

    /*insertion of data completed till here
    all the data is strctured into a binary search tree*/

    printf("postOrder of BST is : ");
    postorder(root);
    printf("\n");
    printf("InOrder of BST is : ");
    inorder(root);
    printf("\n");
    printf("PreOrder of BST is : ");
    preorder(root);
    printf("\n");

    /*printing the data in formats */

    int isBST = binary_search_tree_check(root);
    if (isBST)
    {
        printf("The tree is a valid binary search tree.\n");
    }
    else
    {
        printf("The tree is not a valid binary search tree.\n");
    }

    /*checking the tree wheather the given inputs form a BST */

    printf("which element do you want to search :  ");
    int n;
    scanf("%d", &n);

    struct node *searchResult = search(root, n);
    if (searchResult != NULL)
    {
        printf("Element %d is found.\n", n);
    }
    else
    {
        printf("Element %d is not found.\n", n);
    }

    /*searching the data*/
    int gama;
    printf("please enter the element you want to delete : ");
    scanf("%d", &gama);
    delete_node(root, gama);
    printf("element %d is been deleted from BST \n", gama);
    printf("new Inorder");
    inorder(root);
    /*deleting the data and priinting the new inorder*/

    return 0;
}
