#ifndef CLASSES_EVENT_QUESTMANAGER_H
#define CLASSES_EVENT_QUESTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {

// a base of event::QuestManager no evidence names yet
class TUnk_B3D698 {
public:
    virtual ~TUnk_B3D698() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};

// a base of event::QuestManager no evidence names yet
class TUnk_B3D6C0 {
public:
    virtual ~TUnk_B3D6C0() {}
};

// table 0x7100B3D698; base at 0x0 unknown (TUnk_B3D698), base at 0x8 unknown (TUnk_B3D6C0)
class QuestManager : public TUnk_B3D698, public TUnk_B3D6C0 {
public:
    QuestManager() : m_flags(0) {}
    virtual ~QuestManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's clear() (0x71000F54E4)
    void clear();

private:
    // bit 0: active (1.0.0's isActive; setComp sets it); the name is not the original's
    unsigned int m_flags;  // 0x10
};

}  // namespace event

#endif
