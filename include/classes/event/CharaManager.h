#ifndef CLASSES_EVENT_CHARAMANAGER_H
#define CLASSES_EVENT_CHARAMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; enum CHARA_TYPE : int; }

namespace event {
// table 0x7100B3CD30; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CharaManager>
class CharaManager : public IManager, public mm::mtl::Singleton<CharaManager> {
public:
    CharaManager();
    // out of line: Singleton<CharaManager>::getPtr in the evt_setup plugin registers it with __cxa_atexit (an inline
    // empty one would be dropped)
    virtual ~CharaManager();  // slot 0
    // called by the evt_setup script plugin (application/BF2/ScriptPlayText); a result its callers ignore is declared void
    void loadResource(const char* name);
    void loadMdlstream(float frame, const char* name, unsigned int id);
    void loadMdlstream(float frame, event::CHARA_TYPE type, unsigned int id, unsigned int);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's clear() (0x71000D7094): zeroes m_offscrID, m_reuseFlag, then m_modeFlags
    void clear();
    // 1.0.0 0x71000BC388; 3.0.1 inlines it
    bool isStreamMode() const { return m_modeFlags & 1; }
    // 1.0.0 0x71000C5718; 3.0.1 inlines it
    bool isAutoTalkMode() const { return m_modeFlags & 4; }
    // inlined in 3.0.1 (CharaObj::setTar tests bit 4, which 1.0.0's accessors do not name); the name is not the original's
    unsigned int getModeFlags() const { return m_modeFlags; }

private:
    // 1.0.0's accessors name the bits: 0 stream mode (isStreamMode), 1 offscreen mode (isOffscrMode), 2 auto talk
    // mode, 3 seamless action, 5 use hood; the field's name is not the original's
    unsigned int m_modeFlags;  // 0x10
    // 1.0.0's accessors name the bits: 0 chara disp, 1 facial disp, 2 bone disp; the field's name is not the original's
    unsigned int m_dispFlags;  // 0x14
    int m_offscrID;            // 0x18 (1.0.0's getOffscrID)
    int m_reuseFlag;           // 0x1c (1.0.0's getReuseFlag/setReuseFlag)
};

}  // namespace event

#endif
