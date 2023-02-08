#include<stdio.h>
#include<stdlib.h>

struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
};

typedef struct tree TREE;

TREE* insert_into_bst(TREE *root,int data){
    TREE *newnode;
    newnode = (TREE*)malloc(sizeof(TREE));
    if(newnode==NULL){
        printf("Memory allocation failed.");
        return root;
    }
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    if(root==NULL){
        root = newnode;
        printf("Root created and %d successfully inserted\n",data);
        return root;
    }
    TREE *curr,*parent;
    curr = root;
    parent = NULL;
    while(curr!=NULL){
        parent = curr;
        if(newnode->data<curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if(newnode->data<parent->data)
        parent->left = newnode;
    else
        parent->right = newnode;
    printf("Node created and %d successfully inserted\n",data);
    return root;
}

void inorder(TREE *root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d\n",root->data);
        inorder(root->right);
    }
}

void preorder(TREE *root){
    if(root!=NULL){
        printf("%d\n",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TREE *root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d\n",root->data);
    }
}

TREE* delete_from_bst(TREE *root,int data){
    if(root==NULL){
        printf("BST is empty\n");
        return root;
    }
    TREE *curr,*parent,*p,*succ;
    curr = root;
    parent = NULL;
    while(curr!=NULL && curr->data!=data){
        parent = curr;
        if(curr->data>data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if(curr==NULL){
        printf("DATA not found\n");
        return root;
    }
    if(curr->left==NULL)
        p = curr->right;
    else if(curr->right==NULL)
        p = curr->left;
    else{
        succ = curr->right;
        while(succ->left!=NULL)
            succ = succ->left;
        succ->left = curr->left;
        p = curr->right;
    }
    if(parent == NULL){
        free(curr);
        printf("%d successfully deleted from BST",data);
        return p;
    }
    if(curr==parent->left)
        parent->left = p;
    else
        parent->right = p;
    free(curr);
    printf("%d successfully deleted from BST",data);
    return root;
}


int main()
{
    TREE *root = NULL;
    int choice=0,data;
    while(1){
        printf("\n\n---------BST OPS---------\n\n");
        printf("1.Insert a node\n2.Inorder Traversal\n3.Preorder Traversal\n4.Postorder Traversal\n5.Delete a node\n6.EXIT\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:printf("Enter the data to be inserted\n");
                   scanf("%d",&data);
                   root=insert_into_bst(root,data);
                   break;
            case 2:printf("The inorder traversal is...\n");
                   inorder(root);
                   break;
            case 3:printf("The preorder traversal is...\n");
                   preorder(root);
                   break;
            case 4:printf("The postorder traversal is...\n");
                   postorder(root);
                   break;
            case 5:printf("Enter the data to be deleted\n");
                   scanf("%d",&data);
                   root=delete_from_bst(root,data);
                   break;
            case 6:printf("\nThank you and have a nice day!!\n");
                   exit(1);
            default:printf("\nInvalid choice!!\n");
        }
    }
    return 0;
}
