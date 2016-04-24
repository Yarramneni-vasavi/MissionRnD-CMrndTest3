/*
Given a Sorted Doubly Linked List and a Binary Search Tree , Check if they are identical or not .
The DLL will have nodes of type node_dll
Note :
A DLL can be represented as a BST in many forms ,And if a dll and any one of the forms is given as input you
need to return 1 otherwise 0. 

->Dont Create an Extra Array ,or else your solution would receive 20% Cut in the Marks you got .

Examples :

Example 0:
DLL:1->5->8
BST(All 3 return 1):
    5         8      1
   / \       /        \
  1   8     5          5
           /            \
          1              8
Returns 1
    8
   / \
  5   1
Returns 0
Example 1:
DLL : 1->5
BST : 
5
 \
 10
Returns 0

Example 2:
DLL:1->3->5-9->11
BST:
    5
   / \
  1   11
   \  /      
    3 9

Returns 1

Example 3:
DLL: 1->5->7->10->12->15->20
BST:
        10
        /\
       5  15
      /\  / \
     1  7 12 20
Returns 1

Note 2 :
Unequal Length BST and DLL should return 0;
Return -1 for NULL inputs

Difficulty : Medium +
*/
#include <stdlib.h>
#include <stdio.h>

struct node_dll{
	int data;
	struct node_dll *next;
	struct node_dll *prev;
};
struct node{
	int data;
	struct node *left;
	struct node *right;
};
int DLL_Length(struct node_dll *head)
{
	int len = 0;
	while (head != NULL)
	{
		head = head->next;
		len++;
	}
	return len;
}
void BST_Length(struct node *root, int *b_len)
{
	if (root != NULL)
	{
		(*b_len)++;
		BST_Length(root->left, b_len);
		BST_Length(root->right, b_len);
	}
}

int isBST(struct node* root, int min, int max)
{
	if (root == NULL)
		return 1;

	if (root->data < min || root->data > max)
		return 0;

	int t1 = isBST(root->left, min, (root->data) - 1);
	int t2 = isBST(root->right, (root->data) + 1, max);
	return t1 && t2;
}
int FindMax(struct node_dll *head)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	return head->data;
}
int Ele_search(int ele, struct node_dll *head)
{
	while (head != NULL)
	{
		if (head->data == ele)
		{
			return 1;
		}
		head = head->next;
	}
	return 0;
}
void CheckNodeValues(struct node *root, struct node_dll *head, int *flag)
{
	if (root != NULL)
	{
		if (Ele_search(root->data, head) == 0)
		{
			*flag = 0;
		}
		CheckNodeValues(root->left, head, flag);
		CheckNodeValues(root->right, head, flag);
	}
}
int CheckBst(struct node *root, struct node_dll *head)
{
	int max = FindMax(head);
	if (isBST(root, head->data, max) == 1)
	{
		return 1;
	}
	return 0;
}
int is_identical(struct node_dll *head, struct node *root)
{
	if (head == NULL || root == NULL)
		return -1;

	int b_len = 0;
	BST_Length(root, &b_len);

	if (DLL_Length(head) == b_len)
	{
		if (CheckBst(root, head) == 1)
		{
			int flag = 1;
			CheckNodeValues(root, head, &flag);
			if (flag == 1)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}