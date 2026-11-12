#ifndef CLASSES_GF_GFMENUOBJBATTLETELOP_H
#define CLASSES_GF_GFMENUOBJBATTLETELOP_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5FD10
class GfMenuObjBattleTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    class UniteComboListener;
    GfMenuObjBattleTelop(unsigned int handle);
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
        // the two ints zeroed (openUniteCombo's copy stores them as one zero before the copy)
        OpenUniteParam() : m_param0(0), m_param1(0) {}
        int m_param0;
        int m_param1;
        mm::mtl::FixedVector<UniteCombo, 3> m_combos;
    };
    // sends the attached object 0x4E a copy of the combos (event 0x100 to LAY_fusion_combo)
    static void openUniteCombo(const OpenUniteParam& param);
    // what open is given (the symbol names the type; the field name is not the original's)
    struct OpenParam {
        unsigned short m_index;  // the telop: sent as the open event's (0x21) index; 1 is skipped in a battle arena
    };
    static void open(const OpenParam& param);

    // the names are not the original's
    unsigned int m_telop;  // 0x24: the open telop's layout (MainListener's 0x21 searches it by s_telopLayouts)
    GfMenuSequence<GfMenuObjBattleTelop, 8> m_seq;  // 0x28
    bool pad_2B8;
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numbers[3];  // 0x2C0: the constructor creates them
    mm::mtl::FixedVector<UniteCombo, 3> m_combos;  // 0x2D8: UniteComboListener reads the combos here
};
}  // namespace gf

#endif
