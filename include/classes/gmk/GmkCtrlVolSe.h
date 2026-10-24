#ifndef CLASSES_GMK_GMKCTRLVOLSE_H
#define CLASSES_GMK_GMKCTRLVOLSE_H

namespace gmk {
// table 0x7100B52528; 0x80 bytes (GfFieldMapGimmick holds five, 0x80 apart)
class GmkCtrlVolSe {
public:
    class CreateInfo;
    GmkCtrlVolSe();
    // inline: GfFieldMapGimmick's destructor stores this table and calls dispose() in place
    virtual ~GmkCtrlVolSe() {  // slot 0
        dispose();
    }
    void dispose();
    void createInst();
    void update(float dt);
    bool isPlayEnd() const;
    void create(const CreateInfo& info);
    unsigned char pad_8[0x78];
};
}  // namespace gmk

#endif
