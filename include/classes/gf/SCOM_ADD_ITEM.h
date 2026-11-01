#ifndef CLASSES_GF_SCOM_ADD_ITEM_H
#define CLASSES_GF_SCOM_ADD_ITEM_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B210
class SCOM_ADD_ITEM : public ::gf::SCOM {
public:
    explicit SCOM_ADD_ITEM(SCOM_TYPE type) : SCOM(type) {}
    // the destructor is implicit: its D0 sits in the unit's inline tail and exec is the key function
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(unsigned int, int);
    static unsigned long createForBattle(unsigned int, int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_item;
    // how many to add; a negative count adds what the box still holds room for and sells the rest (exec)
    int m_count;
    // createForBattle sets it: exec opens GfPlayFactory::createMenuPrecious for a precious item
    bool m_showPrecious;
};
}  // namespace gf

#endif
