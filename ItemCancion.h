/* 
 * File:   ItemCancion.h
 * Author: alf
 *
 * Created on 20 de noviembre de 2014, 13:42
 */

#ifndef ITEMCANCION_H
#define	ITEMCANCION_H

using namespace std;

class ItemCancion {
public:
    ItemCancion             (string word): palabra(word), qArtist(false), qTittle(false) {};
    ItemCancion             (const ItemCancion& orig);
    virtual ~ItemCancion    () {};
    bool operator<          (const ItemCancion& orig) const;
    bool operator>          (const ItemCancion& orig) const;
private:
    string  palabra;
    bool    qArtist;
    bool    qTittle;
};

ItemCancion::ItemCancion(const ItemCancion& orig) {
    palabra = orig.palabra;
    qArtist = orig.qArtist;
    qTittle = orig.qTittle;
}

bool ItemCancion::operator< (const ItemCancion& orig) const {
    return palabra < orig.palabra;
    
}

bool ItemCancion::operator> (const ItemCancion& orig) const {
   return palabra > orig.palabra;
}

#endif	/* ITEMCANCION_H */

