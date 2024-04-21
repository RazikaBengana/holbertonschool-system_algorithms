#include "rb_trees.h"

/**
 * rb_tree_is_valid - program that checks if a Red-Black tree is valid
 *
 * this function checks if a RBT is valid, based on several properties:
 * - the tree must be a binary search tree
 * - all nodes must be either red or black
 * - the root must be black
 * - all paths from any given node to its descendant leaves contain
 *   the same number of black nodes
 *
 * @tree: a pointer to the root node of the tree
 *
 * Return: 1 if the tree is valid, 0 otherwise
 */

int rb_tree_is_valid(const rb_tree_t *tree)
{
	int height;

	if (!tree)
		return (0);

	if (tree->color != BLACK)
		return (0);

	if (!is_binary_search_tree(tree, 0, 0))
		return (0);

	if (!has_valid_colors(tree))
		return (0);

	height = calculate_height(tree);

	if (!check_black_height(tree, height, 0))
		return (0);

	return (1);
}



/**
 * is_binary_search_tree - helper function to ensure that the tree
 * satisfies the binary search tree property
 *
 * @tree: a pointer to the node to check
 * @min: the minimum value for the node's key, or 0 if there is no minimum
 * @max: the maximum value for the node's key, or 0 if there is no maximum
 *
 * Return: 1 if the subtree rooted at 'tree' is a binary search tree
 *         within the specified bounds, 0 otherwise
 */

int is_binary_search_tree(const rb_tree_t *tree, int min, int max)
{
	if (!tree)
		return (1);

	if ((min && tree->n < min) || (max && tree->n > max))
		return (0);

	return (is_binary_search_tree(tree->left, 0, tree->n) &&
		is_binary_search_tree(tree->right, tree->n, 0));
}



/**
 * has_valid_colors - program that checks that all nodes are either red or black
 * and that no two red nodes are consecutive
 *
 * @tree: a pointer to the node to check
 *
 * Return: 1 if the subtree rooted at 'tree' has valid red and black
 *         color configuration, 0 otherwise
 */

int has_valid_colors(const rb_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->color != RED && tree->color != BLACK)
		return (0);

	if (tree->color == RED)
	{
		if (tree->left && tree->left->color == RED)
			return (0);
		if (tree->right && tree->right->color == RED)
			return (0);
	}

	return (has_valid_colors(tree->left) && has_valid_colors(tree->right));
}



/**
 * calculate_height - program that calculates the black height of the tree
 *
 * the height is the number of black nodes on any path from
 * the root to a leaf, not including the leaf node itself
 *
 * @tree: a pointer to the root of the subtree
 *
 * Return: the black height of the tree
 */

int calculate_height(const rb_tree_t *tree)
{
	int height;

	if (!tree)
		return (0);

	height = MAXIMUM(calculate_height(tree->left), calculate_height(tree->right));

	if (tree->color == BLACK)
		height++;

	return (height);
}



/**
 * check_black_height - program that verifies that all paths
 * from the root to a leaf contain the same number of black nodes
 *
 * @tree: a pointer to the node to start checking from
 * @black_height: the expected black height from the 'calculate_height' function
 * @height: the running total of black nodes encountered
 *
 * Return: 1 if all paths contain the same number of black nodes, 0 otherwise
 */

int check_black_height(const rb_tree_t *tree, int black_height, int height)
{
	if (!tree)
	{
		if (height == black_height)
			return (1);
		return (0);
	}

	if (tree->color == BLACK)
		height++;

	return (check_black_height(tree->left, black_height, height) &&
		check_black_height(tree->right, black_height, height));
}
