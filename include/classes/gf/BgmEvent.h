#ifndef CLASSES_GF_BGMEVENT_H
#define CLASSES_GF_BGMEVENT_H

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::BgmEvent no evidence names yet
class TUnk_B51288 {
public:
    virtual ~TUnk_B51288();
    virtual void getTrackName() const = 0;
    virtual void isPlaying() const = 0;
    virtual void update(fw::UpdateInfo const&) = 0;
    unsigned char pad_8[0x628];  // fields: size from where the next base starts
};
// a base of gf::BgmEvent no evidence names yet
class TUnk_B512C0 {
public:
    virtual ~TUnk_B512C0();
};
// table 0x7100B51288; base at 0x0 unknown (TUnk_B51288), base at 0x630 unknown (TUnk_B512C0)
class BgmEvent : public TUnk_B51288, public TUnk_B512C0 {
public:
    virtual ~BgmEvent();  // slot 0
    virtual void getTrackName() const;  // slot 2
    virtual void isPlaying() const;  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
