#include "binary_trees.h"
#include "111-bst_insert.c"

/**
 * rebalance - re balances the tree to keep its AVL property
 * @tree: pointer to the root of the subtree
 * Return: pointer to the new root
 */
avl_t *rebalance(avl_t *tree)
{
	int balance;

	if (!tree)
		return (NULL);

	balance = binary_tree_balance((const binary_tree_t *)tree);
	/* left has more height */
	if (balance > 1)
	{
		if (binary_tree_balance((const avl_t *)tree->left) <= -1)
			tree->left = binary_tree_rotate_left(tree->left);
		tree = binary_tree_rotate_right(tree);
	}
	else if (balance < -1) /* right */
	{
		if (binary_tree_balance((const avl_t *)tree->right) >= 1)
			tree->right = binary_tree_rotate_right(tree->right);
		tree = binary_tree_rotate_left(tree);
	}
	return (tree);
}

/**
 * avl_insert - insert a value in an AVL tree
 * @tree: pointer to tree
 * @value: value to insert into tree
 * Return: pointer to created tree
 **/
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new, *tmp;

	/* Perform the normal BST insertion */
	new = bst_insert(tree, value);
	tmp = new;
	/* chack the balance at every node until the root */
	while (new->parent)
	{
		new = rebalance(new);
		new = new->parent;
	}
	/* At the root */
	*tree = rebalance(new);

	return (tmp);
}
