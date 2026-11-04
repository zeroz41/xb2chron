#ifndef CLASSES_GF_PC_PADBATTLE_H
#define CLASSES_GF_PC_PADBATTLE_H

#include "fw/PadRelay.h"  // the tree: "fw/PadRelay.h"
#include "classes/gf/pc/PadField.h"  // InputID

namespace anm { class ResASM; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B66B38
class PadBattle {
public:
    PadBattle();
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 0
    void setup(int padNo, gf::GfComPropertyPc& property);
    void cleanup(gf::GfComPropertyPc& property);
    // the stick's axes (bound to "move_front" and "move_side"): write the property's input direction
    void moveFront(float value);
    void moveSide(float value);

    // the bound actions: setup binds them to "btl_start", "btl_end", "art_01".."art_03", "blade_change_00".."02",
    // "kakusei", "request_permit_01"/"02", "sp_attack", "chain_attack", "battle_rescue", "change_camera_mode",
    // "tactics", and the second relay's "select_right"/"select_left" (1.0.0's symbols name them, bound to the
    // same strings by 1.0.0's setup)
    void battleStart() const;
    void battleEnd() const;
    void art01() const;
    void art02() const;
    void art03() const;
    void bladeChange00() const;
    void bladeChange01() const;
    void bladeChange02() const;
    void kakusei() const;
    void requestPermit01() const;
    void requestPermit02() const;
    void spAttack() const;
    void chainAttack() const;
    void battlRescue() const;
    void changeCameraMode() const;
    void orderRally() const;
    void changeTargetR() const;
    void changeTargetL() const;
    // 2.0.0's symbols name them. Setup binds them as actions of this class (bindAction<PadBattle, void (PadBattle::*)()
    // const>). What they do: as the actions above, set input bit 23 ("auto_switch"), 24 ("mind_eye"), 25
    // ("ira_formation_change" and "ira_formation_change2"), 26 ("ira_blade_change"), 27-30 ("ira_tactics_00".."03"), 31
    // ("ira_talent_arts"), 32 ("spskill")
    void switchAuto() const;
    void mindEye() const;
    void iraFormationChange() const;
    void iraBladeChange() const;
    void iraTactics00() const;
    void iraTactics01() const;
    void iraTactics02() const;
    void iraTactics03() const;
    void iraTalentArts() const;
    void ocg() const;

    // whether an action may set its input: a property is being updated, and while BattleGlobal's flag bit 3 is
    // set, only for the controlled character or during a chain attack (inline: no symbol; the name is not the
    // original's). The actions first skip everything while ChallengeBattleManager's IsExit holds.
    bool isInputEnable() const;
    // sets bit id of the property's action set (1.0.0's symbols name it; out of line there with an assert, 3.0.1
    // inlines every use)
    void setInput(InputID id) const;

    fw::PadRelay m_relay0;  // fields: two relays (PadAgent's destructor destroys both)
    fw::PadRelay m_relay1;
    // update's: the property the handlers write while the relays run, null otherwise (the name is not the original's)
    gf::GfComPropertyPc* m_property;
};

// the battle's animation callback name ("battle"; GfComBehaviorPc::setup reads it)
extern const char* ASM_CB_NAME_BATTLE;
bool registerAsmCallbackBattle(gf::GF_OBJ_HANDLE* obj, anm::ResASM* res);
}}  // namespace gf::pc

#endif
