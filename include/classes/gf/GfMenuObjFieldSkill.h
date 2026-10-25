#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfMenuCallContext; class GAME_VOICE_HANDLE; }

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
    // its sequence step while a voice plays: done (the call context ends) once update has let the voice go
    bool seqWaitVoice();

    // what openResult shows (GfMenuFieldSkill::StateDispResult fills it from its StartParam; the names are not the
    // original's)
    struct OpenResultParam {
        // StartParam::m_unk130 1; a byte, not a bool: openResult passes it on as loaded (no 0/1 normalising)
        unsigned char m_unk0;
        unsigned char* m_unk8;  // StartParam::m_unk100 (m_unk130 0): a message file, m_unk10 the text's id
        unsigned int m_unk10;  // StartParam::m_unk108 (m_unk130 0)
        unsigned int m_unk14;  // StartParam::m_unk11C
    };
    // what openTotalInfo shows (GfMenuFieldSkill::StateDispTotal fills it; the names are not the original's)
    struct OpenTotalParam {
        OpenTotalParam() : m_unk0(0), m_unk8(0), m_noSkills(false) {}
        unsigned char* m_unk0;  // StartParam::m_unk100, when it and m_unk108 are set: a message file, m_unk8 the id
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

    unsigned char pad_24[0x44];  // the constructor's fields (see NOTES): not laid out yet
    GAME_VOICE_HANDLE* m_voice;  // update stops or drops it; seqWaitVoice waits for it to go
    // steps update runs from the front, dropping each once it returns true (seqWaitVoice is one; the name is not
    // the original's)
    mm::mtl::FixedVector<mm::mtl::Delegate<bool()>, 4> m_seq;
};
}  // namespace gf

#endif
