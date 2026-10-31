#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfMenuReferenceFs.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfMenuCallContext; class GfMenuFieldSkillList; class GAME_VOICE_HANDLE; }

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
    GfMenuObjFieldSkill(unsigned int handle);
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
    // BladeListener's: what it sets on the handle's blade images (not written yet)
    static void applyImageParam(unsigned int handle);

    unsigned char pad_24[0x4];
    // the constructor makes each (9999 at most): per request skill row, the level initialize hands to
    // TXT_request_skill_lv_num@01-02 and the gauge it hands to IMG_requestskill_gauge@01-02; TotalListener fills
    // them (the names are not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_skillLevels[2];
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_skillGauges[2];
    GfMenuFieldSkillList* m_skillList;  // 0x48 initialize creates it for LAY_request (the name is not the original's)
    // the constructor makes it; SkillInfoListener copies m_skill into it, initialize hands it to
    // TXT_blade_info_skill_name/_lv_num (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceFs> m_skillRef;
    // SkillInfoListener's open (0x21) takes it from the event (the name is not the original's)
    MenuFieldSkill m_skill;
    // BaseListener's open (0x21): 0x5C set picks its skill variants, 0x5D set (with it) the one-blade ones
    unsigned char pad_5C;
    unsigned char pad_5D;
    unsigned int m_mainHandle;  // 0x60 MainListener's close (0x22) keeps the LAY_main handle (the name is not the original's)
    GAME_VOICE_HANDLE* m_voice;  // update stops or drops it; seqWaitVoice waits for it to go
    // 0x70: update runs its jobs; MainListener's event 0x10D clears it and adds seqWaitVoice (the name is not the
    // original's)
    GfMenuSequence<GfMenuObjFieldSkill, 4> m_seq;
};
}  // namespace gf

#endif
