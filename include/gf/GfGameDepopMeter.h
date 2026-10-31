#ifndef GF_GFGAMEDEPOPMETER_H
#define GF_GFGAMEDEPOPMETER_H

#include "mm/Vec3.h"
#include "mm/mtl/IntrusiveList.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// no table: one object's depop meter, a node of GfGameDepopMeterManager's list (create unlinks it from the
// manager's list first); the field names are not the original's. Its size is not proven (0x41 bytes are used)
class GfGameDepopMeter : public ::mm::mtl::IntrusiveListNodeBase {
public:
    struct CreateInfo;
    explicit GfGameDepopMeter(const CreateInfo* info);
    ~GfGameDepopMeter() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(float deltaTime);

    GF_OBJ_HANDLE* m_handle;  // -1 without one
    bool pad_18;
    unsigned char pad_19[0x7];
    bool pad_20;
    unsigned char pad_21[0xF];
    mm::Vec3 pad_30;  // zero at first
    bool pad_40;
    unsigned char pad_41[0xF];
};
}  // namespace gf

#endif
