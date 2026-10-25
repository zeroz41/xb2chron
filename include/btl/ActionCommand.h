#ifndef BTL_ACTIONCOMMAND_H
#define BTL_ACTIONCOMMAND_H

namespace mm { class Vec3; }

namespace btl {
// a battle character's action command; 0x14 bytes (1.0.0's BattleCharacter::ResetActionCommand copies it as
// 8 + 8 + 4 bytes; BattleCharacter::GetFreeCommand steps its array of them by 0x14, so 4-byte aligned). The act_cmd classes below fill it: each sets its command type and the actions that take it.
class ActionCommand {
public:
    // which act_cmd class filled the command: each act_cmd Initialize stores its own value (the enumerator names
    // are not the original's, they follow the classes; 5 and 6 are set by two functions the symbols leave unnamed)
    enum COMMAND_TYPE : int {
        COMMAND_MOVE_DIR_RATE = 1,
        COMMAND_MOVE_LOCK = 2,
        COMMAND_SUFFER_DAMAGE = 3,
        COMMAND_ATTACK_REPELLED = 4,
    };

    ActionCommand();
    void Reset();
    // whether action id's bit is set
    bool IsProcAction(int id) const;
    // marks the action (a BattleCharacter::ACTION_ID) as one that takes the command; 1.0.0 has it out of line, 3.0.1
    // inlines it into every act_cmd Initialize
    void SetActionID(int id) { m_actionIDs |= 1 << id; }

    // the command's parameters, laid out by its type (the field names are not the original's)
    union {
        struct {
            unsigned int pad_0[2];
            unsigned int pad_8[2];
        };
        // act_cmd::MOVE_DIR_RATE: the XZ direction, the rate scaled by the direction's length, field run
        struct {
            float m_dirX;
            float m_dirZ;
            float m_rate;
            int m_fieldRun;
        } m_moveDirRate;
        // act_cmd::MOVE_LOCK: the input pair and the flags (1 field run, 2 turn to the target, 4 satellite)
        struct {
            float m_inputX;
            float m_inputY;
            unsigned int m_flags;
        } m_moveLock;
    };
    // the name is not the original's: the COMMAND_TYPE the act_cmd class stores
    unsigned int m_type : 5;
    // the name is not the original's: one bit per action id (SetActionID sets them)
    unsigned int m_actionIDs : 26;
    unsigned int pad_10_31 : 1;
};

namespace act_cmd {
class MOVE_DIR_RATE : public ActionCommand {
public:
    void Initialize(mm::Vec3& dir, float rate, bool fieldRun);
    void GetDirection(mm::Vec3& dir) const;
    float GetRate() const;
    bool IsFieldRun() const;
};

class MOVE_LOCK : public ActionCommand {
public:
    void Initialize(float inputX, float inputY, bool fieldRun, bool turnTarget, bool satellite);
    void GetInput(float& inputX, float& inputY) const;
    bool IsFieldRun() const;
    bool IsTurnTarget() const;
    bool IsSatellite() const;
};

class SUFFER_DAMAGE : public ActionCommand {
public:
    void Initialize();
};

class ATTACK_REPELLED : public ActionCommand {
public:
    void Initialize();
};
}  // namespace act_cmd
}  // namespace btl

#endif
