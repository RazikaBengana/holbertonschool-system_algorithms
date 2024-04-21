#include "rb_trees.h"

/**
 * rb_tree_insert - program that inserts a new node with a given value
 * into a Red-Black tree
 *
 * @tree: a pointer to the root of the tree or subtree where the new value
 *        is to be inserted
 * @value: the integer value to be inserted into the tree
 *
 * Return: a pointer to the new node if insertion is successful,
 *         otherwise NULL
 */

rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *current = NULL;
	rb_tree_t *parent = NULL;
	rb_tree_t *new_node = NULL;

	if (!tree)
		return (NULL);

	current = *tree;

	while (current != NULL)
	{
		parent = current;

		if (current->n == value)
			return (NULL);
		if (value < current->n)
			current = current->left;
		else if (value > current->n)
			current = current->right;
	}

	new_node = rb_tree_node(parent, value, RED);

	if (!new_node)
		return (NULL);

	if (parent == NULL)
		*tree = new_node;
	else if (new_node->n < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	rb_insert_fixup(tree, new_node);

	return (new_node);
}



/**
 * rb_insert_fixup - program that performs necessary tree rotations
 * and color changes in the tree after insertion to maintain
 * the Red-Black properties
 *
 * @tree: a pointer to the root of the tree
 * @new_node: a pointer to the newly inserted node that may have
 *            caused violations of the Red-Black properties
 *
 * Return: nothing (void)
 */

void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *new_node)
{
	while (new_node->parent && new_node->parent->color == RED)
	{
		if (new_node->parent->parent && new_node->parent ==
		    new_node->parent->parent->left)
			new_node = rb_insert_fixup_right(tree, new_node);
		else
			new_node = rb_insert_fixup_left(tree, new_node);
	}
	(*tree)->color = BLACK;
}



/**
 * rb_insert_fixup_left - program that fixes the Red-Black tree properties
 * after an insertion on the left subtree
 *
 * @tree: a pointer to the root of the tree
 * @new_node: a pointer to the newly inserted node or subtree root
 *            after rotations
 *
 * Return: a pointer to the new subtree root after adjustment
 */

rb_tree_t *rb_insert_fixup_left(rb_tree_t **tree, rb_tree_t *new_node)
{
	rb_tree_t *uncle = NULL;

	uncle = new_node->parent->parent->left;

	if (uncle && uncle->color == RED)
	{
		new_node->parent->color = BLACK;
		uncle->color = BLACK;
		new_node->parent->parent->color = RED;
		new_node = new_node->parent->parent;
	}
	else
	{
		if (new_node == new_node->parent->left)
		{
			new_node = new_node->parent;
			rb_rotate_right(tree, new_node);
		}
		new_node->parent->color = BLACK;
		new_node->parent->parent->color = RED;
		rb_rotate_left(tree, new_node->parent->parent);
	}
	return (new_node);
}



/**
 * rb_insert_fixup_right - program that fixes the Red-Black tree
 * properties after an insertion on the right subtree
 *
 * @tree: a pointer to the root of the tree
 * @new_node: a pointer to the newly inserted node or subtree root
 *            after rotations
 *
 * Return: a pointer to the new subtree root after adjustment
 */

rb_tree_t *rb_insert_fixup_right(rb_tree_t **tree, rb_tree_t *new_node)
{
	rb_tree_t *uncle = NULL;

	uncle = new_node->parent->parent->right;

	if (uncle && uncle->color == RED)
	{
		new_node->parent->color = BLACK;
		uncle->color = BLACK;
		new_node->parent->parent->color = RED;
		new_node = new_node->parent->parent;
	}
	else
	{
		if (new_node == new_node->parent->right)
		{
			new_node = new_node->parent;
			rb_rotate_left(tree, new_node);
		}
		new_node->parent->color = BLACK;
		new_node->parent->parent->color = RED;
		rb_rotate_right(tree, new_node->parent->parent);
	}
	return (new_node);
}



/**
 * rb_rotate_left - program that performs a left rotation on the Red-Black tree
 *
 * @tree: a pointer to the root of the tree
 * @x: a pointer to the node around which the left rotation is to be performed
 *
 * Return: nothing (void)
 */

void rb_rotate_left(rb_tree_t **tree, rb_tree_t *x)
{
	rb_tree_t *y = NULL;

	y = x->right;
	x->right = y->left;

	if (y->left)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == NULL)
		*tree = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}



/**
 * rb_rotate_right - program that performs a right rotation on the Red-Black tree
 *
 * @tree: a pointer to the root of the tree
 * @y: a pointer to the node around which the right rotation is to be performed
 *
 * Return: nothing (void)
 */

void rb_rotate_right(rb_tree_t **tree, rb_tree_t *y)
{
	rb_tree_t *x = NULL;

	x = y->left;
	y->left = x->right;

	if (x->right)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == NULL)
		*tree = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}
