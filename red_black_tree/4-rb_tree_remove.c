#include "rb_trees.h"

/**
 * rb_rotate_left - program that performs a left rotation
 * on the given node in the binary tree
 *
 * @tree: a double pointer to the root of the red-black tree
 * @node: a pointer to the node to rotate around
 *
 * Return: nothing (void)
 */

void rb_rotate_left(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *right = node->right;

	node->right = right->left;

	if (right->left != NULL)
		right->left->parent = node;
	right->parent = node->parent;

	if (node->parent == NULL)
		*tree = right;
	else if (node == node->parent->left)
		node->parent->left = right;
	else
		node->parent->right = right;

	right->left = node;
	node->parent = right;
}



/**
 * rb_rotate_right - program that performs a right rotation
 * on the given node in the binary tree
 *
 * @tree: a double pointer to the root of the red-black tree
 * @node: a pointer to the node to rotate around
 *
 * Return: nothing (void)
 */

void rb_rotate_right(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *left = node->left;

	node->left = left->right;

	if (left->right != NULL)
		left->right->parent = node;

	left->parent = node->parent;

	if (node->parent == NULL)
		*tree = left;
	else if (node == node->parent->right)
		node->parent->right = left;
	else
		node->parent->left = left;

	left->right = node;
	node->parent = left;
}



/**
 * left_sibling - program that fixes the tree after deletion
 * of a black node by managing a left sibling
 *
 * @root: a pointer to the root of the red-black tree
 * @child: a double pointer to the node being fixed
 * @parent: a double pointer to the parent of the node being fixed
 * @sibling: a pointer to the sibling node used for adjustments
 *
 * Return: nothing (void)
 */

void left_sibling(rb_tree_t **root, rb_tree_t **child,
		rb_tree_t **parent, rb_tree_t *sibling)
{
	if (sibling->color == RED)
	{
		sibling->color = BLACK;
		(*parent)->color = RED;
		rb_rotate_left(root, *parent);
		sibling = (*parent)->right;
	}
	if ((sibling->left == NULL || sibling->left->color == BLACK) &&
		(sibling->right == NULL || sibling->right->color == BLACK))
	{
		sibling->color = RED;
		*child = *parent;
		*parent = (*child)->parent;
	}
	else
	{
		if (sibling->right == NULL || sibling->right->color == BLACK)
		{
			sibling->left->color = BLACK;
			sibling->color = RED;
			rb_rotate_right(root, sibling);
			sibling = (*parent)->right;
		}
		sibling->color = (*parent)->color;
		(*parent)->color = BLACK;
		if (sibling->right != NULL)
			sibling->right->color = BLACK;
		rb_rotate_left(root, *parent);
		*child = *root;
		return;
	}
}



/**
 * right_sibling - program that fixes the tree after deletion
 * of a black node by managing a right sibling
 *
 * @root: a pointer to the root of the red-black tree
 * @child: a double pointer to the node being fixed
 * @parent: a double pointer to the parent of the node being fixed
 * @sibling: a pointer to the sibling node used for adjustments
 *
 * Return: nothing (void)
 */

void right_sibling(rb_tree_t **root, rb_tree_t **child,
		rb_tree_t **parent, rb_tree_t *sibling)
{
	if (sibling->color == RED)
	{
		sibling->color = BLACK;
		(*parent)->color = RED;
		rb_rotate_right(root, *parent);
		sibling = (*parent)->left;
	}
	if ((sibling->right == NULL || sibling->right->color == BLACK) &&
		(sibling->left == NULL || sibling->left->color == BLACK))
	{
		sibling->color = RED;
		*child = *parent;
		*parent = (*child)->parent;
	}
	else
	{
		if (sibling->left == NULL || sibling->left->color == BLACK)
		{
			sibling->right->color = BLACK;
			sibling->color = RED;
			rb_rotate_left(root, sibling);
			sibling = (*parent)->left;
		}
		sibling->color = (*parent)->color;
		(*parent)->color = BLACK;
		if (sibling->left != NULL)
			sibling->left->color = BLACK;
		rb_rotate_right(root, *parent);
		*child = *root;
		return;
	}
}



/**
 * rb_tree_delete_fixup - program that adjusts the tree after deletion
 * to maintain red-black properties
 *
 * @root: a double pointer to the root of the tree
 * @child: a pointer to the node that was deleted or moved
 * @parent: a pointer to the parent of the child, used for adjustments
 *
 * Return: nothing (void)
 */

void rb_tree_delete_fixup(rb_tree_t **root, rb_tree_t *child,
			  rb_tree_t *parent)
{
	rb_tree_t *sibling;

	while (child != *root && (child == NULL || child->color == BLACK))
	{
		if (child == parent->left)
		{
			sibling = parent->right;
			left_sibling(root, &child, &parent, sibling);
		}
		else
		{
			sibling = parent->left;
			right_sibling(root, &child, &parent, sibling);
		}
	}
	if (child != NULL)
		child->color = BLACK;
}



/**
 * rb_tree_successor - program that finds the successor of a given node
 * in an in-order traversal of the tree
 *
 * @node: the node to find the successor for
 *
 * Return: a pointer to the successor node
 */

rb_tree_t *rb_tree_successor(rb_tree_t *node)
{
	rb_tree_t *successor = node;

	if (successor->right != NULL)
	{
		successor = successor->right;
		while (successor->left != NULL)
			successor = successor->left;
	}
	else
	{
		while (successor->parent != NULL && successor == successor->parent->right)
			successor = successor->parent;
		successor = successor->parent;
	}
	return (successor);
}



/**
 * rb_tree_remove - program that removes a node from the red-black tree
 *
 * @root: a pointer to the root of the red-black tree
 * @n: the value of the node to be removed
 *
 * Return: a pointer to the new root of the tree
 */

rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *target, *successor, *child, *parent;

	target = root;

	while (target != NULL && target->n != n)
	{
		if (n < target->n)
			target = target->left;
		else if (n > target->n)
			target = target->right;
	}
	if (target == NULL)
		return (root);

	if (target->left != NULL && target->right != NULL)
	{
		successor = rb_tree_successor(target);
		target->n = successor->n;
		target = successor;
	}
	child = target->left != NULL ? target->left : target->right;
	parent = target->parent;

	if (child != NULL)
		child->parent = parent;
	if (parent == NULL)
		root = child;
	else if (target == parent->left)
		parent->left = child;
	else
		parent->right = child;
	if (target->color == BLACK)
		rb_tree_delete_fixup(&root, child, parent);

	free(target);

	return (root);
}
