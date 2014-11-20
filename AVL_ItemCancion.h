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
    AVL_ItemCancion             (vector<Song> &v);
    vector<Song*> searchTittle  (string &tit);
    vector<Song*> searchAuthor  (string &aut);
    
    bool insert     (ItemCancion &data) { return insert(root, data); }
    bool search     (ItemCancion &data, ItemCancion &result);
    
private:
    Node *root;
    
    int insert      (Node<ItemCancion>* &c, ItemCancion &data);
    void rotRight   (Node<ItemCancion>* &p);
    void rotLeft    (Node<ItemCancion>* &p);
    
    Node<ItemCancion>* searchKey    (ItemCancion &data, Node<ItemCancion> *p);
};

vector<Song*> AVL_ItemCancion::searchAuthor(string& aut) {
    
}

vector<Song*> AVL_ItemCancion::searchTittle(string& tit) {
    
}

AVL_ItemCancion(vector<Song> &v) {
    for (int i = 0; i < v.size(); ++i) {
        insert(v[i]);
    }
}

Node<ItemCancion>* AVL_ItemCancion::searchKey(ItemCancion& data, Node<ItemCancion>* p) {
    if (!p)
        return 0;
    else if (data < p->data)
        return searchKey (data, p->left);
    else if (data > p->data)
        return searchKey (data, p->right);
    else
        return p;
}

bool AVL_ItemCancion::search(ItemCancion& data, ItemCancion& result) {
    Node<ItemCancion> *p = searchKey(ItemCancion &data, ItemCancion &result);
    if (p) {
        result = p->data;
        return true;
    }
    return false;
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

