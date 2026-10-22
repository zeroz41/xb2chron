#ifndef CLASSES_GF_GFRELSMNENEMY_H
#define CLASSES_GF_GFRELSMNENEMY_H

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gf {
// table 0x7100B59128
class GfRelSmnEnemy {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    virtual ~GfRelSmnEnemy();  // slot 1
    unsigned int getEnemyNum() const;  // how many enemies it summoned
    gf::GF_OBJ_HANDLE* getEnemy(unsigned int index) const;  // one of them
};
}  // namespace gf

#endif
