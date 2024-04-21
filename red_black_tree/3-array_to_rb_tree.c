#include "rb_trees.h"

/**
 * array_to_rb_tree - program that converts an array of integers into a red-black tree
 *
 * @array: a pointer to the first element of the array of integers to be converted
 * @size: the number of elements in the array
 *
 * Return: a pointer to the root of the newly created red-black tree,
 *         or NULL if the array is NULL or empty
 */

rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	rb_tree_t *root = NULL;
	size_t i;

	if (array == NULL || size == 0)
		return (NULL);

	for (i = 0; i < size; i++)
		rb_tree_insert(&root, array[i]);

	return (root);
}
