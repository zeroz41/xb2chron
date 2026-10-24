#ifndef CLASSES_EVENT_CAPTUREMANAGER_H
#define CLASSES_EVENT_CAPTUREMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::CaptureManager no evidence names yet
class TUnk_B3D988 {
public:
    virtual ~TUnk_B3D988();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::CaptureManager no evidence names yet
class TUnk_B3D9B0 {
public:
    virtual ~TUnk_B3D9B0();
};
// table 0x7100B3D988; base at 0x0 unknown (TUnk_B3D988), base at 0x8 unknown (TUnk_B3D9B0)
class CaptureManager : public TUnk_B3D988, public TUnk_B3D9B0 {
public:
    virtual ~CaptureManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void ready();
    void start();
    void stop();
    void update();
    void render();

    // OnEventProc: bit 0 gates ready(), bits 0..1 == 1 gate start(), bit 1 gates stop(); the name is not the original's
    unsigned int m_flags;  // @0x10
};
}  // namespace event

#endif
