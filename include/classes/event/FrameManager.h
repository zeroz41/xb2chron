#ifndef CLASSES_EVENT_FRAMEMANAGER_H
#define CLASSES_EVENT_FRAMEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::FrameManager no evidence names yet
class TUnk_B3E1A8 {
public:
    virtual ~TUnk_B3E1A8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::FrameManager no evidence names yet
class TUnk_B3E1D0 {
public:
    virtual ~TUnk_B3E1D0();
};
// table 0x7100B3E1A8; base at 0x0 unknown (TUnk_B3E1A8), base at 0x8 unknown (TUnk_B3E1D0)
class FrameManager : public TUnk_B3E1A8, public TUnk_B3E1D0 {
public:
    virtual ~FrameManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // out of line (mm::mtl::Singleton<event::FrameManager>::getPtr's static calls it)
    FrameManager();
    // the evt plugin's wait passes its frame count (1.0.0's evt wait calls it by this name)
    void setSkipAbleFrame(float frame);
    float getFrame() const;
    float getMaxFrame() const;

private:
    unsigned char pad_10[0x148];
    // what getFrame returns; the name is not the original's
    float m_frame;  // 0x158
    unsigned char pad_15c[0x14];
    // what getMaxFrame returns; the name is not the original's
    float m_maxFrame;  // 0x170
};
}  // namespace event

#endif
