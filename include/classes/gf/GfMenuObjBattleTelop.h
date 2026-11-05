#ifndef CLASSES_GF_GFMENUOBJBATTLETELOP_H
#define CLASSES_GF_GFMENUOBJBATTLETELOP_H

#include "classes/gf/GfMenuObject.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B5FD10
class GfMenuObjBattleTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    class UniteComboListener;
    virtual ~GfMenuObjBattleTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // one combo line of a unite combo telop (packed in one word; the names are not the original's)
    struct UniteCombo {
        unsigned char m_type;  // 0, 1, 2: the line
        unsigned char m_sub;
        unsigned short m_value;
    };
    // what openUniteCombo is given (the symbol names the type; btl::UIManager::DispUniteComboUI fills it; the field
    // names are not the original's)
    struct OpenUniteParam {
        int m_param0;
        int m_param1;
        mm::mtl::FixedVector<UniteCombo, 3> m_combos;
    };
    static unsigned int openUniteCombo(const OpenUniteParam& param);

    // the rest of the layout (the constructor's: a GfMenuSequence at 0x28, three GfMenuReferenceNumber pointers at
    // 0x2C0) is not written yet. The name is not the original's
    unsigned int m_telop;  // 0x24: the open telop's layout (MainListener's 0x21 searches it by s_telopLayouts)
};
}  // namespace gf

#endif
