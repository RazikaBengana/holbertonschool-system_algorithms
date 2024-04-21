#include "rb_trees.h"

/**
 * rb_tree_node - program that creates a new node in a red-black tree
 *
 * @parent: the parent node of the new node being created;
 *          if this is the root node, the parent should be NULL
 * @value: the integer value that the new node will hold
 * @color: the color of the new node, which should be either
 *         RED or BLACK as defined by the enum `rb_color_t`
 *
 * Return: a pointer to the newly created node, or NULL if memory allocation fails
 */

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *node = malloc(sizeof(rb_tree_t));

	if (node == NULL)
		return (NULL);

	node->n = value;
	node->color = color;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;

	return (node);
}
