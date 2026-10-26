#ifndef CLASSES_GF_GFMENUOBJDAMAGEBUFF_H
#define CLASSES_GF_GFMENUOBJDAMAGEBUFF_H

#include "classes/gf/GfMenuObject.h"
#include "mm/Vec3.h"

namespace gf {
// table 0x7100B61760
class GfMenuObjDamageBuff : public ::gf::GfMenuObject {
public:
    class DamageInfo;
    class ListListener;
    // what openUniteCombo is given (btl::UIManager::DispUniteComboUI fills it; the field names are not the
    // original's): the two values go out as the opened object's event parameters, the position to its
    // GfMenuFieldPosAdapter
    struct OpenUniteParam {
        int m_eventParam0;
        int m_eventParam1;
        unsigned char pad_8[0x8];
        mm::Vec3 m_pos;
    };
    static unsigned int openUniteCombo(const OpenUniteParam& param);
    static void closeAll();  // GfMenuManager::gevSalvageStateChange(6) calls it (1.0.0 symbol)
    virtual ~GfMenuObjDamageBuff();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
