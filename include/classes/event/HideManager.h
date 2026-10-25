#ifndef CLASSES_EVENT_HIDEMANAGER_H
#define CLASSES_EVENT_HIDEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::HideManager no evidence names yet
class TUnk_B3D178 {
public:
    virtual ~TUnk_B3D178();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::HideManager no evidence names yet
class TUnk_B3D1A0 {
public:
    virtual ~TUnk_B3D1A0();
};
// table 0x7100B3D178; base at 0x0 unknown (TUnk_B3D178), base at 0x8 unknown (TUnk_B3D1A0)
class HideManager : public TUnk_B3D178, public TUnk_B3D1A0 {
public:
    virtual ~HideManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    enum GRP_TYPE {};
    void defineGroup(GRP_TYPE group);
    GRP_TYPE getGroup() const;
    // out of line (mm::mtl::Singleton<event::HideManager>::getPtr's static calls it)
    HideManager();
    void hideGroup(bool hide);

private:
    unsigned int pad_10;
    // the group defineGroup sets and getGroup returns; the name is not the original's
    GRP_TYPE m_group;  // 0x14
    // fields the constructor initializes; what they hold is not known yet
    unsigned char pad_18[0x1000];
    unsigned long pad_1018;
    unsigned char pad_1020[0x1000];
    unsigned long pad_2020;
    unsigned char pad_2028[0x200];
    unsigned long pad_2228;
};
}  // namespace event

#endif
