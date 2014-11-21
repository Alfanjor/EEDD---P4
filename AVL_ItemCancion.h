/* 
 * File:   AVL_ItemCancion.h
 * Author: alf
 *
 * Created on 20 de noviembre de 2014, 13:59
 */

#ifndef AVL_ITEMCANCION_H
#define	AVL_ITEMCANCION_H

#include "ItemCancion.h"
#include "Song.h"
#include <vector>

using namespace std;

template<class U>
class Node {
public:
    Node<U> *left, *right;
    U data;
    char bal; // -1, 0, 1

    Node(U &ele) : left(0), right(0), bal(0), data(ele) {};
};

class AVL_ItemCancion {
public:
    AVL_ItemCancion (): root(0) {} ;
    
    bool insert             (ItemCancion &data) { return insert(root, data); }
    bool erase              (ItemCancion &data);
    ItemCancion* search     (ItemCancion &data);
    
private:
    Node<ItemCancion> *root;
    
    int insert      (Node<ItemCancion>* &c, ItemCancion &data);
    void rotRight   (Node<ItemCancion>* &p);
    void rotLeft    (Node<ItemCancion>* &p);
    
    ItemCancion* searchKey          (ItemCancion &data, Node<ItemCancion> *p);
    Node<ItemCancion>* eraseData    (ItemCancion &data, Node<ItemCancion>* &p);
    Node<ItemCancion>* eraseMin     (Node<ItemCancion>* &p);
};

bool AVL_ItemCancion::erase(ItemCancion &data) {
    Node<ItemCancion> *result = eraseData(data, root);
    if (result)
        return true;
    return false;
}

Node<ItemCancion>* AVL_ItemCancion::eraseData(ItemCancion& data, Node<ItemCancion>* &p) {
    if (p) 
        eraseData(data, p->left);
    else {
        if (data > p->data)
            eraseData (data, p->right);
        else {
            Node<ItemCancion> *temp = p;
            if (!p->left)
                p = p->right;
            else
                if (!p->right)
                    p = p->left;
                else if (p->left && p->right) {
                    temp = eraseMin(p->right);
                    p->data = temp->data;
                }
            delete temp;
        }
    }
}

Node<ItemCancion>* AVL_ItemCancion::eraseMin (Node<ItemCancion>* &p) {
    Node<ItemCancion> *result;
    if (p) {
        if (p->left)
            return eraseMin(p->left);
        else {
            result = p;
            p = p->right;
            return result;
        }
    }
}

ItemCancion* AVL_ItemCancion::searchKey(ItemCancion &data, Node<ItemCancion> *p) {
    if (!p)
        return 0;
    else if (data < p->data)
        return searchKey (data, p->left);
    else if (data > p->data)
        return searchKey (data, p->right);
    else
        return &p->data;
}

ItemCancion* AVL_ItemCancion::search(ItemCancion &data) {
    ItemCancion *p = searchKey(data, root);
    return p;
}

int AVL_ItemCancion::insert(Node<ItemCancion>* &c, ItemCancion &data) {
    Node<ItemCancion> *p = c;
    int deltaH = 0;
    
    if (!p) {
        p = new Node<ItemCancion> (data);
        c = p;
        deltaH = 1;
    } else if (data > p->data) {
        if (insert(p->right, data)) {
            p->bal--;
            if (p->bal == -1)
                deltaH = 1;
            else if (p->bal == -2) {
                if (p->right->bal == 1)
                    rotRight(p->right);
                rotLeft(c);
            }
        }
    } else if (data < p->data) {
        if (insert(p->left, data)) {
            p->bal++;
            if (p->bal == 1)
                deltaH = 1;
            else if (p->bal == 2) {
                if (p->left->bal == -1)
                    rotLeft(p->left);
                rotRight(c);
            }
        }
    }
    return deltaH;
}

void AVL_ItemCancion::rotRight(Node<ItemCancion>*& p) {
    Node<ItemCancion> *q = p, *l;
    p = l = q->left;
    q->left = l->right;
    l->right = q;
    q->bal--;
    if (l->bal > 0)
        q->bal -= l->bal;
    l->bal--;
    if (q->bal < 0)
        l->bal -= -q->bal;
}

void AVL_ItemCancion::rotLeft(Node<ItemCancion>* &p) {
    Node<ItemCancion> *q = p, *r;
    p = r = q->right;
    q->right = r->left;
    r->left = q;
    q->bal++;
    if (r->bal < 0)
        q->bal += -r->bal;
    r->bal++;
    if (q->bal > 0)
        r->bal += q->bal;
}

#endif	/* AVL_ITEMCANCION_H */

