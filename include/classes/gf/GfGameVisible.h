#ifndef CLASSES_GF_GFGAMEVISIBLE_H
#define CLASSES_GF_GFGAMEVISIBLE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Map.h"
#include "mm/mtl/FixedQueue.h"

namespace gf { class GfGameVisible; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }

namespace gf {
// table 0x7100B56AF0 (0x4030 bytes, GfGameVisible::build): whether the game's objects can be seen from the camera,
// kept per object in a map of Infos taken from a pool (the field names are not the original's)
class GfGameVisible : public ::mm::mtl::PtrSingleton< ::gf::GfGameVisible> {
public:
    // one object's state (8 bytes: build constructs 1024 of them)
    struct Info {
        Info() : m_visible(false), m_checked(false), m_hasModel(false), m_wait(0) {}

        bool m_visible;  // isVisible's answer, checkVisible's last result
        bool m_checked;  // searchObj met the object this update (updateImpl drops the ones it did not)
        bool m_hasModel;  // the object has a GfComModel (checkVisible tests its model, not a line)
        int m_wait;  // updates until the next check
    };
    typedef ::mm::mtl::Map<GF_OBJ_HANDLE*, Info*> InfoMap;

    virtual ~GfGameVisible();  // slot 0
    static void build(const GfSetupParam& param);
    void setup();
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    void updateImpl(const fw::UpdateInfo& info);
    static bool isVisible(GF_OBJ_HANDLE* handle);
    void searchObj(unsigned int type, const mm::Vec3& pos);
    bool checkVisible(GF_OBJ_HANDLE* handle, const mm::Vec3& pos, bool hasModel);

    InfoMap m_map;
    ::mm::mtl::FixedQueue<Info*, 1024> m_pool;  // the free Infos
    Info m_infos[1024];
};
}  // namespace gf

#endif
