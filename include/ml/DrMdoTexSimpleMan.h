#ifndef ML_DRMDOTEXSIMPLEMAN_H
#define ML_DRMDOTEXSIMPLEMAN_H

#include "ml/DrMdoResList.h"
#include "ml/DrResMdoTexSimple.h"

namespace ml {
class DrMan;

// The simple texture manager (no table: its constructor stores none): four lists of DrResMdoTexSimple. Field
// names are not the original's; the destructor empties them in the order 0x8, 0x18, 0x38, 0x28.
class DrMdoTexSimpleMan {
public:
    DrMdoTexSimpleMan(DrMan* drMan);
    ~DrMdoTexSimpleMan();

    DrMan* m_pDrMan;                           // 0x0
    DrMdoResList<DrResMdoTexSimple> m_list0;   // 0x8
    DrMdoResList<DrResMdoTexSimple> m_list1;   // 0x18
    DrMdoResList<DrResMdoTexSimple> m_list3;   // 0x28
    DrMdoResList<DrResMdoTexSimple> m_list2;   // 0x38
};
}  // namespace ml

#endif
