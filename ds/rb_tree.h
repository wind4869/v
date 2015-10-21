#ifndef RB_TREE_H
#define RB_TREE_H

typedef bool rb_tree_color_type;
const rb_tree_color_type rb_tree_red = false;
const rb_tree_color_type rb_tree_black = true;

template <typename Value>
struct rb_tree_node {
    rb_tree_node* parent;
    rb_tree_node* left;
    rb_tree_node* right;

    rb_tree_color_type color;

    Value value_field;
};

template <typename Value>
class rb_tree {
public:    
    typedef rb_tree_color_type color_type;
    typedef rb_tree_node<Value> tree_node;
    typedef tree_node* link_type;
    typedef Value value_type;
    typedef Value& reference;
protected:
    link_type create_node(const value_type& v)
    {
        link_type tmp = new tree_node();
        tmp->value_field = v;
        return tmp;
    }

    void destroy_node(link_type p) { delete p; }

    static link_type& left(link_type x) { return x->left; }
    static link_type& right(link_type x) { return x->right; }
    static link_type& parent(link_type x) { return x->parent; }
    static reference value(link_type x) { return x->value_field; }
    static color_type& color(link_type x) { return x->color; }
    
    void rotate_left(link_type x);
    void rotate_right(link_type x);

    void rebalance_for_insert(link_type z);
    void rebalance_for_erase(link_type x, link_type x_parent);

    void print_aux(link_type x)
    {
        if (x != 0) {
            print_aux(left(x));
            cout << value(x) << endl;
            print_aux(right(x));
        }
    }

private:
    link_type root;
public:
    rb_tree() : root(0) {  }

    void insert(const value_type& v);
    void erase(link_type z);

    void print() { print_aux(root); }
    void test() { erase(root->left); }
};

template <typename Value> inline void
rb_tree<Value>::insert(const value_type& v)
{
    link_type y = 0;
    link_type x = root;

    link_type z = create_node(v);

    while (x != 0) {
        y = x;
        x = (v < value(x)) ? left(x) : right(x);
    }

    if (y == 0)
        root = z;
    else if (v < value(y))
        left(y) = z;
    else 
        right(y) = z;

    parent(z) = y;
    left(z) = 0;
    right(z) = 0;
    color(z) = rb_tree_red;

    rebalance_for_insert(z);
}

template <typename Value> inline void
rb_tree<Value>::erase(link_type z)
{
    link_type y = 0;
    link_type x = 0;
    link_type x_parent = 0;

    if (left(z) == 0 || right(z) == 0)
        y = z;
    else {
        y = right(z);
        while (left(y) != 0)
            y = left(y);
    }

    x = (left(y) != 0) ? left(y) : right(y);
    if (x != 0) parent(x) = parent(y);
    x_parent = parent(y);

    if (parent(y) == 0)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z)
        value(z) = value(y);

    if (x && color(y) == rb_tree_black)
        rebalance_for_erase(x, x_parent);
}

template <typename Value> inline void
rb_tree<Value>::rotate_left(link_type x)
{
    link_type y = x->right;
    x->right = y->left;
    if (y->left != 0)
        y->left->parent = x;
    y->parent = x->parent;
    if (x == root)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    x->parent = y;
    y->left = x;
}

template <typename Value> inline void
rb_tree<Value>::rotate_right(link_type x)
{
    link_type y = x->left;
    x->left = y->right;
    if (y->right != 0)
        y->right->parent = x;
    y->parent = x->parent;
    if (x == root)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    x->parent = y;
    y->right = x;
}

template <typename Value> inline void
rb_tree<Value>::rebalance_for_insert(link_type z)
{
    while (z != root && z->parent->color == rb_tree_red) {
        if (z->parent == z->parent->parent->left) {
            link_type y = z->parent->parent->right;
            if (y && y->color == rb_tree_red) {
                z->parent->color = rb_tree_black;
                y->color = rb_tree_black;
                z->parent->parent->color = rb_tree_red;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(z);
                }

                z->parent->color = rb_tree_black;
                z->parent->parent->color = rb_tree_red;
                rotate_right(z->parent->parent);
            }
        }
        else {
            link_type y = z->parent->parent->left;
            if (y && y->color == rb_tree_red) {
                z->parent->color = rb_tree_black;
                y->color = rb_tree_black;
                z->parent->parent->color = rb_tree_red;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(z);
                }

                z->parent->color = rb_tree_black;
                z->parent->parent->color = rb_tree_red;
                rotate_left(z->parent->parent);
            }
        }
    }

    root->color = rb_tree_black;
}

template <typename Value> inline void
rb_tree<Value>::rebalance_for_erase(link_type x, link_type x_parent)
{
    while (x != root && (x == 0 || x->color == rb_tree_black)) {
        if (x == x_parent->left) {
            link_type w = x_parent->right;
            if (w->color == rb_tree_red) {
                w->color = rb_tree_black;
                x_parent->color = rb_tree_red;
                rotate_left(x_parent);
                w = x_parent->right;
            }
            if ((w->left == 0 || w->left->color == rb_tree_black) &&
                    (w->right == 0 || w->right->color == rb_tree_black)) {
                w->color = rb_tree_red;
                x = x_parent;
                x_parent = x_parent->parent;
            }
            else {
                if (w->right == 0 || w->right->color == rb_tree_black) {
                    if (w->left != 0) w->left->color = rb_tree_black;
                    w->color = rb_tree_red;
                    rotate_right(w);
                    w = x_parent->right;
                }
                w->color = x_parent->color;
                x_parent->color = rb_tree_black;
                if (w->right != 0) w->right->color = rb_tree_black;
                rotate_left(x_parent);
                break;
            }
        }
        else {
            link_type w = x_parent->left;
            if (w->color == rb_tree_red) {
                w->color = rb_tree_black;
                x_parent->color = rb_tree_red;
                rotate_right(x_parent);
                w = x_parent->left;
            }
            if ((w->right == 0 || w->right->color == rb_tree_black) &&
                    (w->left == 0 || w->left->color == rb_tree_black)) {
                w->color = rb_tree_red;
                x = x_parent;
                x_parent = x_parent->parent;
            }
            else {
                if (w->left == 0 || w->left->color == rb_tree_black) {
                    if (w->right != 0) w->right->color = rb_tree_black;
                    w->color = rb_tree_red;
                    rotate_left(w);
                    w = x_parent->left;
                }
                w->color = x_parent->color;
                x_parent->color = rb_tree_black;
                if (w->left != 0) w->left->color = rb_tree_black;
                rotate_right(x_parent);
                break;
            }
        }
    }

    if (x != 0) x->color = rb_tree_black;
}

#endif
