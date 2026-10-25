#ifndef CLASSES_GF_GFMENUFIELDSKILL_H
#define CLASSES_GF_GFMENUFIELDSKILL_H

#include "ai/Fsm.h"
#include "mm/mtl/FixedVector.h"

#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfMenuFieldSkill; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5E588; the field skill result menu: a state machine (ai::Fsm) that shows the skills that worked one
// by one (or their total), then the result, through GfMenuObjFieldSkill's call contexts (the member names are not
// the original's)
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
    // a skill and its level (StateDispTotal hands start's list of them to GfMenuObjFieldSkill::openTotalInfo, which
    // copies the three bytes; the names are not the original's)
    struct SkillLevel {
        SkillLevel(unsigned short skill, unsigned char level) : m_skill(skill), m_level(level) {}
        unsigned short m_skill;
        unsigned char m_level;
    };
    // a blade skill shown (1.0.0: gf::GfGameUtil::findBladeSkillList(mm::mtl::FixedVector<GfMenuFieldSkill::BladeSkillInfo, 30>&, unsigned int)
    // fills StartParam::m_skills)
    struct BladeSkillInfo {
        BladeSkillInfo(unsigned short blade, unsigned char level)
            : m_blade(blade), m_unk2(0), m_skill(9), m_level(level), m_unk7(0) {}
        unsigned short m_blade;
        unsigned short m_unk2;
        // bit fields of one word: StateDispInfo::enter and StateSkip::update load the word once for both
        unsigned int m_skill : 16;  // compared with m_levels' skills
        unsigned int m_level : 8;
        unsigned int m_unk7 : 8;
    };
    // what start shows: the skills that worked (the names are not the original's: StateSalvageSkillCheck fills
    // m_skills, each a blade, skill 9 and the skill's level)
    struct StartParam {
        StartParam() : m_type(0), m_unk100(0), m_unk108(0), m_unk130(0) {
            clearExtra();
        }
        // zeroes m_unk110..m_unk11C; the constructor calls it after its init list (GfMenuFieldSkill::build's
        // inlined constructor stores these three as one block after the others; the name is not the original's)
        void clearExtra() {
            m_unk110 = 0;
            m_unk118 = 0;
            m_unk11C = 0;
        }

        unsigned int m_type;  // 0: one skill at a time (StateDispInfo), 1: the total (StateDispTotal)
        mm::mtl::FixedVector<BladeSkillInfo, 30> m_skills;
        // with m_unk108, handed to openTotalInfo and (m_unk130 0) openResult: a message file and the id of a text in
        // it (the menu object builds a ui::UIStr from them)
        unsigned char* m_unk100;
        unsigned int m_unk108;
        unsigned long m_unk110;
        unsigned int m_unk118;
        unsigned int m_unk11C;  // handed to openResult
        mm::mtl::FixedVector<SkillLevel, 2> m_levels;
        unsigned int m_unk130;  // openResult's kind: 0 hands it m_unk100/m_unk108, 1 a flag

        // the index of skill's entry in m_levels, -1 when it has none (the name is not the original's)
        int findLevel(unsigned short skill) const {
            int index = 0;
            for (const SkillLevel* level = m_levels.begin(); level != m_levels.end(); ++index, ++level) {
                if (level->m_skill == skill) {
                    return index;
                }
            }
            return -1;
        }
    };
    // a skill window StateDispInfo opened: its index in m_levels (-1: none), its level, its context
    struct Info {
        signed char m_index;
        unsigned char m_level;
        unsigned char pad_2[6];
        GfMenuCallContext* m_context;
    };

    GfMenuFieldSkill() : m_fsm(getAllocator(ALLOCATOR(0))), m_context(nullptr), m_resultContext(nullptr),
                         m_totalContext(nullptr), m_waitFrames(0), m_nextState(0), m_skipped(false) {
        m_context = GfMenuCallContext::create();
    }
    virtual ~GfMenuFieldSkill();  // slot 0

    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void postUpdate(const fw::UpdateInfo& info);
    static bool start(const StartParam& param);
    static bool isRunning();  // whether the field skill menu is up

    ai::Fsm m_fsm;
    StartParam m_param;
    unsigned int m_levelIndex;  // the m_levels entry shown (StateStart clears it, StateDispInfo counts it up)
    unsigned char pad_1BC[4];
    mm::mtl::FixedVector<Info, 3> m_infos;
    GfMenuCallContext* m_context;        // the menu's own (skip input)
    GfMenuCallContext* m_resultContext;  // StateDispResult's and StateQuit's
    GfMenuCallContext* m_totalContext;   // StateDispTotal's
    unsigned int m_waitFrames;           // StateWait counts it down
    unsigned int m_nextState;            // the state StateWait changes to
    bool m_skipped;                      // postUpdate sets it when the menu's context reports result 2
};
}  // namespace gf

#endif
