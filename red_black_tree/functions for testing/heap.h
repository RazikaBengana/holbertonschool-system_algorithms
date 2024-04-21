#ifndef HEAP_H
#define HEAP_H


/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: the data stored in a node
 * @left: a pointer to the left child
 * @right: a pointer to the right child
 * @parent: a pointer to the parent node
 */

typedef struct binary_tree_node_s
{
    void *data;
    struct binary_tree_node_s *left;
    struct binary_tree_node_s *right;
    struct binary_tree_node_s *parent;
} binary_tree_node_t;


#endif /* HEAP_H */