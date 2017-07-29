/* 
 * File:   RBtree.cpp
 * Author: mark
 *
 * Adapted from: http://www.coders-hub.com/2015/07/red-black-tree-rb-tree-using-c.html#.WXzUvieQxpg
 */
#include "RBtree.h"

void RBtree::insert(int z) {
    int i = 0;
    node *p, *q;
    node *t = new node;
    t->key = z;
    t->left = NULL;
    t->right = NULL;
    t->color = 'r';
    p = root;
    q = NULL;
    if (root == NULL) {
        root = t;
        t->parent = NULL;
    } else {
        while (p != NULL) {
            q = p;
            if (p->key < t->key)
                p = p->right;
            else
                p = p->left;
        }
        t->parent = q;
        if (q->key < t->key)
            q->right = t;
        else
            q->left = t;
    }
    insertfix(t);
    std::cout << z << " inserted\n";
}

void RBtree::insertfix(node *t) {
    node *u;
    if (root == t) {
        t->color = 'b';
        return;
    }
    while (t->parent != NULL && t->parent->color == 'r') {
        node *g = t->parent->parent;
        if (g->left == t->parent) {
            if (g->right != NULL) {
                u = g->right;
                if (u->color == 'r') {
                    t->parent->color = 'b';
                    u->color = 'b';
                    g->color = 'r';
                    t = g;
                }
            } else {
                if (t->parent->right == t) {
                    t = t->parent;
                    leftrotate(t);
                }
                t->parent->color = 'b';
                g->color = 'r';
                rightrotate(g);
            }
        } else {
            if (g->left != NULL) {
                u = g->left;
                if (u->color == 'r') {
                    t->parent->color = 'b';
                    u->color = 'b';
                    g->color = 'r';
                    t = g;
                }
            } else {
                if (t->parent->left == t) {
                    t = t->parent;
                    rightrotate(t);
                }
                t->parent->color = 'b';
                g->color = 'r';
                leftrotate(g);
            }
        }
        root->color = 'b';
    }
}

void RBtree::del(int x) {
    if (root == NULL) {
        std::cout << "\nEmpty Tree.";
        return;
    }
    node *p;
    p = root;
    node *y = NULL;
    node *q = NULL;
    int found = 0;
    while (p != NULL && found == 0) {
        if (p->key == x)
            found = 1;
        if (found == 0) {
            if (p->key < x)
                p = p->right;
            else
                p = p->left;
        }
    }
    if (found == 0) {
        std::cout << "\nElement Not Found.";
        return;
    } else {
        std::cout << "\nDeleted Element: " << p->key;
        std::cout << "\nColour: ";
        if (p->color == 'b')
            std::cout << "Black\n";
        else
            std::cout << "Red\n";

        if (p->parent != NULL)
            std::cout << "\nParent: " << p->parent->key;
        else
            std::cout << "\nThere is no parent of the node.  ";
        if (p->right != NULL)
            std::cout << "\nRight Child: " << p->right->key;
        else
            std::cout << "\nThere is no right child of the node.  ";
        if (p->left != NULL)
            std::cout << "\nLeft Child: " << p->left->key;
        else
            std::cout << "\nThere is no left child of the node.  ";
        std::cout << "\nNode Deleted.";
        if (p->left == NULL || p->right == NULL)
            y = p;
        else
            y = successor(p);
        if (y->left != NULL)
            q = y->left;
        else {
            if (y->right != NULL)
                q = y->right;
            else
                q = NULL;
        }
        if (q != NULL)
            q->parent = y->parent;
        if (y->parent == NULL)
            root = q;
        else {
            if (y == y->parent->left)
                y->parent->left = q;
            else
                y->parent->right = q;
        }
        if (y != p) {
            p->color = y->color;
            p->key = y->key;
        }
        if (y->color == 'b')
            delfix(q);
    }
}

void RBtree::delfix(node *p) {
    node *s;
    while (p != root && p->color == 'b') {
        if (p->parent->left == p) {
            s = p->parent->right;
            if (s->color == 'r') {
                s->color = 'b';
                p->parent->color = 'r';
                leftrotate(p->parent);
                s = p->parent->right;
            }
            if (s->right->color == 'b' && s->left->color == 'b') {
                s->color = 'r';
                p = p->parent;
            } else {
                if (s->right->color == 'b') {
                    s->left->color == 'b';
                    s->color = 'r';
                    rightrotate(s);
                    s = p->parent->right;
                }
                s->color = p->parent->color;
                p->parent->color = 'b';
                s->right->color = 'b';
                leftrotate(p->parent);
                p = root;
            }
        } else {
            s = p->parent->left;
            if (s->color == 'r') {
                s->color = 'b';
                p->parent->color = 'r';
                rightrotate(p->parent);
                s = p->parent->left;
            }
            if (s->left->color == 'b' && s->right->color == 'b') {
                s->color = 'r';
                p = p->parent;
            } else {
                if (s->left->color == 'b') {
                    s->right->color = 'b';
                    s->color = 'r';
                    leftrotate(s);
                    s = p->parent->left;
                }
                s->color = p->parent->color;
                p->parent->color = 'b';
                s->left->color = 'b';
                rightrotate(p->parent);
                p = root;
            }
        }
        p->color = 'b';
        root->color = 'b';
    }
}

void RBtree::leftrotate(node *p) {
    if (p->right == NULL)
        return;
    else {
        node *y = p->right;
        if (y->left != NULL) {
            p->right = y->left;
            y->left->parent = p;
        } else
            p->right = NULL;
        if (p->parent != NULL)
            y->parent = p->parent;
        if (p->parent == NULL)
            root = y;
        else {
            if (p == p->parent->left)
                p->parent->left = y;
            else
                p->parent->right = y;
        }
        y->left = p;
        p->parent = y;
    }
    std::cout << "  Forced Left Rotate <--\n";
}

void RBtree::rightrotate(node *p) {
    if (p->left == NULL)
        return;
    else {
        node *y = p->left;
        if (y->right != NULL) {
            p->left = y->right;
            y->right->parent = p;
        } else
            p->left = NULL;
        if (p->parent != NULL)
            y->parent = p->parent;
        if (p->parent == NULL)
            root = y;
        else {
            if (p == p->parent->left)
                p->parent->left = y;
            else
                p->parent->right = y;
        }
        y->right = p;
        p->parent = y;
    }
    std::cout << "  Forced Right Rotate -->\n";
}

node* RBtree::successor(node *p) {
    node *y = NULL;
    if (p->left != NULL) {
        y = p->left;
        while (y->right != NULL)
            y = y->right;
    } else {
        y = p->right;
        while (y->left != NULL)
            y = y->left;
    }
    return y;
}

void RBtree::disp() {
    display(root);
}

void RBtree::display(node *p) {
    if (root == NULL) {
        std::cout << "\nEmpty Tree.";
        return;
    }
    if (p != NULL) {
        std::cout << "\n\t NODE: ";
        std::cout << "\n Key: " << p->key;
        std::cout << "\n Colour: ";
        if (p->color == 'b')
            std::cout << "Black";
        else
            std::cout << "Red";
        if (p->parent != NULL)
            std::cout << "\n Parent: " << p->parent->key;
        else
            std::cout << "\n There is no parent of the node.  ";
        if (p->right != NULL)
            std::cout << "\n Right Child: " << p->right->key;
        else
            std::cout << "\n There is no right child of the node.  ";
        if (p->left != NULL)
            std::cout << "\n Left Child: " << p->left->key;
        else
            std::cout << "\n There is no left child of the node.  ";
        std::cout << std::endl;
        if (p->left) {
            std::cout << "\n\nLeft:\n";
            display(p->left);
        }
        /*else
         cout<<"\nNo Left Child.\n";*/
        if (p->right) {
            std::cout << "\n\nRight:\n";
            display(p->right);
        }
        /*else
         cout<<"\nNo Right Child.\n"*/
    }
}

void RBtree::search() {
    if (root == NULL) {
        std::cout << "\nEmpty Tree\n";
        return;
    }
    int x;
    std::cout << "\n Enter key of the node to be searched: ";
    std::cin>>x;
    node *p = root;
    int found = 0;
    while (p != NULL && found == 0) {
        if (p->key == x)
            found = 1;
        if (found == 0) {
            if (p->key < x)
                p = p->right;
            else
                p = p->left;
        }
    }
    if (found == 0)
        std::cout << "\nElement Not Found.";
    else {
        std::cout << "\n\t FOUND NODE: ";
        std::cout << "\n Key: " << p->key;
        std::cout << "\n Color: ";
        if (p->color == 'b')
            std::cout << "Black";
        else
            std::cout << "Red";
        if (p->parent != NULL)
            std::cout << "\n Parent: " << p->parent->key;
        else
            std::cout << "\n There is no parent of the node.  ";
        if (p->right != NULL)
            std::cout << "\n Right Child: " << p->right->key;
        else
            std::cout << "\n There is no right child of the node.  ";
        if (p->left != NULL)
            std::cout << "\n Left Child: " << p->left->key;
        else
            std::cout << "\n There is no left child of the node.  ";
        std::cout << std::endl;

    }
}