#ifndef CLASSES_GF_TUNK_B5B878_H
#define CLASSES_GF_TUNK_B5B878_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5B878 (no RTTI, no 1.0.0 symbol): a GfMenuCharDataAdapter converter new in 3.0.1, built only by
// GfMenuCharDataAdapter::createFromNamedList: the enemy (type 5) an ID list's entry names, through GfBdatChrEnArrange's
// getBTL_NamedListIraEnemyID or getBTL_NamedListEnemyID (GfGameManager::isGameTypeIra chooses).
class TUnk_B5B878 : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // index -1: the list's selected one
    TUnk_B5B878(const GfMenuIDList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuIDList* m_list;
    int m_index;
};
}  // namespace gf

#endif
