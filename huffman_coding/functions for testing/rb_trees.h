#ifndef _RB_TREES_H_
#define _RB_TREES_H_



/**
 * enum rb_color_e - Enumeration of possible color
 * of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 * @DOUBLE_BLACK: 2 -> Double-black node (used for deletion)
 */

typedef enum rb_color_e
{
    RED = 0,
    BLACK,
    DOUBLE_BLACK
} rb_color_t;



/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: the integer stored in the node
 * @parent: a pointer to the parent node
 * @left: a pointer to the left child node
 * @right: a pointer to the right child node
 * @color: the color of the node (RED or BLACK)
 */

typedef struct rb_tree_s
{
    int n;
    rb_color_t color;
    struct rb_tree_s *parent;
    struct rb_tree_s *left;
    struct rb_tree_s *right;
} rb_tree_t;



#endif /* _RB_TREES_H_ */