#ifndef CLASSES_EVENT_CHARAMANAGER_H
#define CLASSES_EVENT_CHARAMANAGER_H

namespace event { enum MSG_TYPE : int; enum CHARA_TYPE : int; }

namespace event {

// a base of event::CharaManager no evidence names yet
class TUnk_B3CD30 {
public:
    virtual ~TUnk_B3CD30() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};

// a base of event::CharaManager no evidence names yet
class TUnk_B3CD58 {
public:
    virtual ~TUnk_B3CD58() {}
};

// table 0x7100B3CD30; base at 0x0 unknown (TUnk_B3CD30), base at 0x8 unknown (TUnk_B3CD58)
class CharaManager : public TUnk_B3CD30, public TUnk_B3CD58 {
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
