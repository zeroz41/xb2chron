#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_ENEMYLISTCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_ENEMYLISTCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuEnemyList.h"

namespace gf {
// table 0x7100B5B818
class GfMenuCharDataAdapter::EnemyListConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // an enemy list's entry; index -1: the list's selected one
    EnemyListConverter(const GfMenuEnemyList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuEnemyList* m_list;
    int m_index;
};
}  // namespace gf

#endif
