#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B62378
class GfMenuObjFieldSkill : public ::gf::GfMenuObject {
public:
    class BaseListener;
    class BladeListener;
    class InputListener;
    class MainListener;
    class ResultListener;
    class SkillInfoListener;
    class TotalListener;
    virtual ~GfMenuObjFieldSkill();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // what openResult shows (GfMenuFieldSkill::StateDispResult fills it from its StartParam; the names are not the
    // original's)
    struct OpenResultParam {
        bool m_unk0;  // StartParam::m_unk130 1
        unsigned long m_unk8;  // StartParam::m_unk100 (m_unk130 0)
        unsigned int m_unk10;  // StartParam::m_unk108 (m_unk130 0)
        unsigned int m_unk14;  // StartParam::m_unk11C
    };
    // what openTotalInfo shows (GfMenuFieldSkill::StateDispTotal fills it; the names are not the original's)
    struct OpenTotalParam {
        OpenTotalParam() : m_unk0(0), m_unk8(0), m_noSkills(false) {}
        unsigned long m_unk0;  // StartParam::m_unk100, when it and m_unk108 are set
        unsigned int m_unk8;   // StartParam::m_unk108
        mm::mtl::FixedVector<GfMenuFieldSkill::SkillLevel, 2> m_levels;  // StartParam::m_levels
        bool m_noSkills;  // StartParam::m_skills is empty
    };
    // what openSkillInfo shows (GfMenuFieldSkill::StateDispInfo fills it from a StartParam skill; the names are not
    // the original's)
    struct OpenSkillInfoParam {
        OpenSkillInfoParam() : m_unk4(0.0f), m_unk8(1.0f) {}
        unsigned short m_skill;
        unsigned char m_level;
        float m_unk4;
        float m_unk8;
        unsigned short m_blade;
    };
    // GfMenuFieldSkill's calls (its states'); the return types are not known yet (the callers ignore them)
    static void close(GfMenuCallContext* context);
    static void attachSkip(GfMenuCallContext* context);
    static void openResult(GfMenuCallContext* context, const OpenResultParam& param);
    static void openTotalInfo(GfMenuCallContext* context, const OpenTotalParam& param);
    static void setSkipInput(GfMenuCallContext* context, bool enable);
    static void closeResult(GfMenuCallContext* context);
    static void closeTotalInfo(GfMenuCallContext* context);
    static void undoTotalSkillLevel(unsigned char slot);
    static void openSkillInfo(GfMenuCallContext* context, unsigned char slot, const OpenSkillInfoParam& param);
    static void addTotalSkillLevel(unsigned char slot, unsigned char level);
    static void setCurrentTotalSkill(unsigned char slot);
};
}  // namespace gf

#endif
