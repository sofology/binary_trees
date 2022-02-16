#include "binary_trees.h"

/**
 * bst_search - searches for a value in a Binary Search Tree
 * @tree: a pointer to the root node of the BST
 * @value: the value to be searched
 * Return: a pointer to the node containing the found value, otherwise NULL
 */
bst_t *bst_search(const bst_t *tree, int value)
{
	if (!tree)
		return (NULL);
	if (value == tree->n)
		return ((bst_t *)tree);
	if (value < tree->n)
		return (bst_search(tree->left, value));
	return (bst_search(tree->right, value));
}

/**
 * left - removes a node with only a left child
 * @root: pointer to root of the tree
 * @del_node: node to delete
 * Return: returns the root of node
 */
bst_t *left(bst_t *root, bst_t *del_node)
{
	if (!root || !del_node)
		return (NULL);
	if (root == del_node)
	{
		root = del_node->left;
		del_node->left->parent = NULL;
		free(del_node);
		return (root);
	}

	if (del_node->parent->left == del_node)
		del_node->parent->left = del_node->left;
	else
		del_node->parent->right = del_node->left;
	del_node->left->parent = del_node->parent;

	free(del_node);
	return (root);
}

/**
 * right - removes a node with only a right child
 * @root: pointer to root of the tree
 * @del_node: node to remove
 * Return: returns the root node
 */
bst_t *right(bst_t *root, bst_t *del_node)
{
	if (!root || !del_node)
		return (NULL);
	if (root == del_node)
	{
		root = del_node->right;
		del_node->right->parent = NULL;
		free(del_node);
		return (root);
	}

	if (del_node->parent->left == del_node)
		del_node->parent->left = del_node->right;
	if (del_node->parent->right == del_node)
		del_node->parent->right = del_node->right;
	del_node->right->parent = del_node->parent;

	free(del_node);
	return (root);
}

/**
 * two_children - removes a node which has 2 children
 * @root: a pointer to root of the tree
 * @del_node: node to delete
 * Return: returns the root node
 */
bst_t *two_children(bst_t *root, bst_t *del_node)
{
	bst_t *right_node;

	if (!root || !del_node)
		return (NULL);

	right_node = del_node->right;
	/* get the smallest node of the right subtree */
	while (right_node->left)
		right_node = right_node->left;
	del_node->n = right_node->n;

	if (!right_node->left && !right_node->right)
		right_node->parent->left = NULL;
	if (right_node->right)
	{
		right_node->parent->left = right_node->right;
		right_node->right->parent = right_node->parent;
	}
	free(right_node);
	return (root);
}


/**
 * bst_remove - removes a node from a Binary Search Tree
 * @root: a pointer to root node of the tree
 * @value: the value to be remove
 * Return: a pointer to the new root node
 */
bst_t *bst_remove(bst_t *root, int value)
{
	bst_t *del_node;

	if (!root)
		return (NULL);
	del_node = bst_search(root, value);
	if (!del_node)
		return (NULL);

	/* the del_node is a leaf */
	if (!del_node->left && !del_node->right)
	{
		if (root == del_node)
		{
			free(del_node);
			return (NULL);
		}
		if (del_node->parent->left == del_node)
			del_node->parent->left = NULL;
		if (del_node->parent && (del_node->parent->right == del_node))
			del_node->parent->right = NULL;
		free(del_node);
		return (root);
	}
	/* the del_node has two children */
	if (del_node->left && del_node->right)
		return (two_children(root, del_node));

	/* the del_node has only one child */
	if (del_node->left)
		return (left(root, del_node));
	return (right(root, del_node));
}
