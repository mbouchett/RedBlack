/* 
 * File:   RBtree.h
 * Author: mark
 *
 * Created on July 29, 2017, 2:37 PM
 */

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

struct node
{
       int key;
       node *parent;
       char color;
       node *left;
       node *right;
};
class RBtree{
    node *root;
    node *q;
public:
      RBtree()
      {
              q=NULL;
              root=NULL;
      }
      void insert(int);
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void del(int);
      node* successor(node *);
      void delfix(node *);
      void disp();
      void display( node *);
      void search();    
};


#endif /* RBTREE_H */

