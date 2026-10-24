#ifndef CLASSES_EVENT_DEBUGMANAGER_H
#define CLASSES_EVENT_DEBUGMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::DebugManager no evidence names yet
class TUnk_B3BFD0 {
public:
    virtual ~TUnk_B3BFD0();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::DebugManager no evidence names yet
class TUnk_B3BFF8 {
public:
    virtual ~TUnk_B3BFF8();
};
// table 0x7100B3BFD0; base at 0x0 unknown (TUnk_B3BFD0), base at 0x8 unknown (TUnk_B3BFF8)
class DebugManager : public TUnk_B3BFD0, public TUnk_B3BFF8 {
public:
    virtual ~DebugManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    bool isMovieDebug() const;

private:
    unsigned char pad_10[0x2];
    // bit 0: movie debugging (isMovieDebug); the name is not the original's
    unsigned char m_movieFlags;  // 0x12
};
}  // namespace event

#endif
