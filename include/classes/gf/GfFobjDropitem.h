#ifndef CLASSES_GF_GFFOBJDROPITEM_H
#define CLASSES_GF_GFFOBJDROPITEM_H

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B52910
class GfFobjDropitem {
public:
    virtual ~GfFobjDropitem() {}  // slot 0
    void initialize();
    void destroy();
    void update(const fw::UpdateInfo& info);
    void setEventDisp(bool disp);

    unsigned char pad_0x8[0x8];
    // the item's object: GfFobjManager finds an item by it (listenerGfObj, leaveGameField) and destroys it
    // (GfObjUtil::destroy) (the name is not the original's)
    GF_OBJ_HANDLE* m_handle;
};
}  // namespace gf

#endif
