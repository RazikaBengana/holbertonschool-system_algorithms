#ifndef NARY_TREES_H
#define NARY_TREES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


/**
 * struct nary_tree_s - N-ary tree node structure
 *
 * @content: the content of the node
 * @parent: a pointer to the parent node
 * @nb_children: the number of children
 * @children: a pointer to the head node of the children linked list
 * @next: a pointer to the next child in the parent's children linked list
 */

typedef struct nary_tree_s
{
	char *content;
	struct nary_tree_s *parent;
	size_t nb_children;
	struct nary_tree_s *children;
	struct nary_tree_s *next;
} nary_tree_t;



/* task 0 */
nary_tree_t *create_node(char const *str);
void insert_at_beginning(nary_tree_t *parent, nary_tree_t *node);
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str);


/* task 1 */
void nary_tree_delete(nary_tree_t *tree);


/* task 2 */
void nary_tree_traverse_helper(nary_tree_t const *node,
			       void (*action)(nary_tree_t const *node, size_t depth),
			       size_t depth, size_t *max_depth);
size_t nary_tree_traverse(nary_tree_t const *root,
			  void (*action)(nary_tree_t const *node, size_t depth));


/* task 3 */
size_t calculate_max_depths(nary_tree_t const *child, size_t depth,
			    size_t *diameter);
void update_diameter(size_t max_depth_1, size_t max_depth_2, size_t depth,
		     size_t *diameter);
size_t find_tree_diameter(nary_tree_t const *root, size_t depth,
			  size_t *diameter);
size_t nary_tree_diameter(nary_tree_t const *root);


/* task 4 */
int check_node_match(char const *node_content, char const *expected_content);
int search_path_in_tree(nary_tree_t const *node, char const * const *path,
			size_t index);
int path_exists(nary_tree_t const *root, char const * const *path);



#endif /* NARY_TREES_H */
