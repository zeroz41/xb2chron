#ifndef BTL_ACTIONCOMMAND_H
#define BTL_ACTIONCOMMAND_H

namespace btl {
// a battle character's action command; 0x14 bytes (1.0.0's BattleCharacter::ResetActionCommand copies it as
// 8 + 8 + 4 bytes). 1.0.0 also had SetActionID(int), which sets bit id of m_actionIDs.
class ActionCommand {
public:
    ActionCommand();
    void Reset();
    // whether action id's bit is set
    bool IsProcAction(int id) const;

    unsigned long pad_0;
    unsigned long pad_8;
    unsigned int pad_10 : 5;
    // the name is not the original's: one bit per action id (1.0.0's SetActionID sets them)
    unsigned int m_actionIDs : 26;
    unsigned int pad_10_31 : 1;
};
}  // namespace btl

#endif
