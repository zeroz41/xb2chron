#ifndef GF_GFSETUPPFTALK_H
#define GF_GFSETUPPFTALK_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a talk's setup, as GfPlayFactory::createTalk hands it to GfSequentialPlay::addTalk (only its first field is known;
// the name is not the original's)
class GfSetupPfTalk {
public:
    int m_eventId;  // the event createTalk opens and closes its callback event sequence with
    unsigned char pad_4[0x4];
    GF_OBJ_HANDLE* m_handle;  // the object talked to (StateTalk::enter: its npc; the name is not the original's)
    unsigned int pad_10;
    unsigned int m_npcTurn;  // the npc gimmick's NpcTurn (StateTalk::enter; the name is not the original's)
};
}  // namespace gf

#endif
