#ifndef CLASSES_EVENT_SKIPMANAGER_H
#define CLASSES_EVENT_SKIPMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::SkipManager no evidence names yet
class TUnk_B3E1F0 {
public:
    virtual ~TUnk_B3E1F0() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::SkipManager no evidence names yet
class TUnk_B3E218 {
public:
    virtual ~TUnk_B3E218() {}
};
// table 0x7100B3E1F0; base at 0x0 unknown (TUnk_B3E1F0), base at 0x8 unknown (TUnk_B3E218)
class SkipManager : public TUnk_B3E1F0, public TUnk_B3E218 {
public:
    SkipManager();  // out of line (0x7100133CD4); the script plugins' getPtr statics call it
    virtual ~SkipManager();  // slot 0
    // whether the scene is being skipped fast (evt_chara's mount then queues nothing)
    bool isSkipFast() const;
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    bool isSkip() const;

private:
    // bit 0: skipping (isSkip); the name is not the original's
    unsigned int m_flags;  // 0x10
    // fields the constructor initializes; what they hold is not known yet
    unsigned int pad_14;
    float pad_18;  // -1.0f at first
    unsigned char pad_1c[0x4];
};
}  // namespace event

#endif
