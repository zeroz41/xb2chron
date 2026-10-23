#ifndef CLASSES_GF_GFMENUFIELDSKILL_H
#define CLASSES_GF_GFMENUFIELDSKILL_H

#include "mm/mtl/FixedVector.h"

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuFieldSkill; }

namespace gf {
// table 0x7100B5E588
class GfMenuFieldSkill : public ::mm::mtl::PtrSingleton< ::gf::GfMenuFieldSkill> {
public:
    class StateDispInfo;
    class StateDispResult;
    class StateDispTotal;
    class StateIdle;
    class StateQuit;
    class StateSkip;
    class StateStart;
    class StateTotalNext;
    class StateWait;
    virtual ~GfMenuFieldSkill();  // slot 0
    // what start shows: the skills that worked (the names are not the original's: StateSalvageSkillCheck fills
    // m_skills, each a blade, kind 9 and the skill's level)
    struct StartParam {
        struct Skill {
            Skill(unsigned short blade, unsigned char level)
                : m_blade(blade), m_unk2(0), m_kind(9), m_unk5(0), m_level(level), m_unk7(0) {}
            unsigned short m_blade;
            unsigned short m_unk2;
            unsigned char m_kind;
            unsigned char m_unk5;
            unsigned char m_level;
            unsigned char m_unk7;
        };
        StartParam() : m_type(0), m_unk100(0), m_unk108(0), m_unk110(0), m_unk118(0), m_unk130(0) {}

        unsigned int m_type;
        mm::mtl::FixedVector<Skill, 30> m_skills;
        unsigned long m_unk100;
        unsigned int m_unk108;
        unsigned long m_unk110;
        unsigned long m_unk118;
        mm::mtl::FixedVector<unsigned int, 2> m_unk120;
        unsigned int m_unk130;
    };

    static bool start(const StartParam& param);
    static bool isRunning();  // whether the field skill menu is up
};
}  // namespace gf

#endif
