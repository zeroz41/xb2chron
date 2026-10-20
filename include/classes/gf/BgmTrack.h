#ifndef CLASSES_GF_BGMTRACK_H
#define CLASSES_GF_BGMTRACK_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B51390
class BgmTrack {
public:
    virtual ~BgmTrack();  // slot 0
    virtual void getTrackName() const = 0;  // slot 2
    virtual void isPlaying() const;  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 4
    unsigned char pad_8[0x628];  // fields: size from its derived classes
};
}  // namespace gf

#endif
