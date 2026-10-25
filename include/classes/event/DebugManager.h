#ifndef CLASSES_EVENT_DEBUGMANAGER_H
#define CLASSES_EVENT_DEBUGMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::DebugManager no evidence names yet
class TUnk_B3BFD0 {
public:
    virtual ~TUnk_B3BFD0() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::DebugManager no evidence names yet
class TUnk_B3BFF8 {
public:
    virtual ~TUnk_B3BFF8() {}
};
// table 0x7100B3BFD0; base at 0x0 unknown (TUnk_B3BFD0), base at 0x8 unknown (TUnk_B3BFF8)
class DebugManager : public TUnk_B3BFD0, public TUnk_B3BFF8 {
public:
    virtual ~DebugManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    bool isMovieDebug() const;
    void render();
    // 1.0.0's DebugManager::update (0x7100096898); 3.0.1 inlines it into OnEventProc
    void update() {
        if (m_flags & 2) {
            if (m_messageTime-- <= 0) {
                m_flags &= ~2;
            }
        }
        if (m_flags & 4) {
            if (m_warningTime-- <= 0) {
                m_flags &= ~4;
            }
        }
    }

private:
    // 1.0.0's setX(bool)/isX() pairs set and test its bits (setMovieDebug: bit 16); the name is not the original's
    unsigned int m_flags;  // 0x10
    unsigned char pad_14[0x104];
    // frames left of the message (bit 1) and the warning (bit 2); the name is not the original's
    int m_messageTime;  // 0x118
    unsigned char pad_11c[0x104];
    int m_warningTime;  // 0x220
};
}  // namespace event

#endif
