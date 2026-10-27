#ifndef CLASSES_GF_GFGAMESEARCHOBJ_H
#define CLASSES_GF_GFGAMESEARCHOBJ_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "gf/GfSearchInfo.h"
#include "gf/GfSearchParam.h"
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/FixedList.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_SEARCH_OBJ; }
namespace gf { class GfGameSearchObj; }
namespace gf { class GfSetupParam; }
namespace fw { class Transform; }

namespace gf {
// a search: not an object but its slot's index (6 bits) and a serial number above it (createObj), -1 for none
class GF_SEARCH_OBJ;

// table 0x7100B55F30 (0x90980 bytes, build); the field names are not the original's
class GfGameSearchObj : public ::mm::mtl::PtrSingleton< ::gf::GfGameSearchObj> {
public:
    typedef ::mm::mtl::FixedList<GfSearchInfo*, 256> InfoList;
    typedef ::mm::mtl::FixedList<GF_SEARCH_OBJ*, 64> ObjList;

    // a search's slot (0x90 bytes)
    class GFSEARCH_INFO {
    public:
        GFSEARCH_INFO() : m_param(0), m_handle(reinterpret_cast<GF_SEARCH_OBJ*>(-1)), m_list(nullptr), m_flags() {}
        GfSearchParam m_param;  // getInfo's: createObj's copy
        GF_SEARCH_OBJ* m_handle;
        InfoList* m_list;  // getObj's: what the last update found
        ::mm::mtl::Bitflag<32> m_flags;  // flag 0: disabled (setEnable) (the size is inferred)
    };

    // the positions of every object of a list type, gathered once per update (updateObj)
    class GfSearchCache {
    public:
        struct POS {
            const fw::Transform* m_transform;
            const mm::Vec3* m_pos;
            float m_radius;
            unsigned char pad_14[0x4];
            GF_OBJ_HANDLE* m_handle;
            float m_forwardAng;  // getForwardAng(*m_pos)
            float m_distance;
        };
        enum { TYPE_NUM = 13, POS_NUM = 1024 };
        POS m_pos[TYPE_NUM][POS_NUM];
        int m_count[TYPE_NUM];  // -1: not gathered this update
    };

    struct SearchResult;

    GfGameSearchObj(const GfSetupParam& param) {
        for (int i = 0; i < GfSearchCache::TYPE_NUM; ++i) {
            m_cache.m_count[i] = -1;
        }
        m_serial = 0;
        initialize(param);
    }
    virtual ~GfGameSearchObj();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    void destroyList(InfoList* list);
    // what a search found, by its handle
    static InfoList* getObj(GF_SEARCH_OBJ* obj);
    static GF_SEARCH_OBJ* createObj(const GfSearchParam& param);
    static void destroyObj(GF_SEARCH_OBJ* obj);
    // the search's parameters as createObj copied them, null for no search
    static GfSearchParam* getInfo(GF_SEARCH_OBJ* obj);
    static void setEnable(GF_SEARCH_OBJ* obj, bool enable);
    static bool isEnable(GF_SEARCH_OBJ* obj);
    static void update(const fw::UpdateInfo& info);
    void updateObj(GF_SEARCH_OBJ* obj);
    bool calcVisible(SearchResult& result, const GFSEARCH_INFO* info, const GfSearchCache::POS& target,
                     const GfSearchCache::POS& base);
    static float getForwardAng(const mm::Vec3& pos, const mm::Vec3& basePos, const mm::Quat& baseRot);
    static float getForwardAng(const mm::Vec3& pos);

    // (1.0.0's; 3.0.1 inlines it)
    void initialize(const GfSetupParam& param) { m_initialized = true; }

    ::ml::fixed_size_alloc_inside<GFSEARCH_INFO, 64> m_infos;
    ObjList m_objs;  // every search's handle, in creation order
    ::ml::fixed_size_alloc_inside<GfSearchInfo, 1024> m_searchInfos;  // the InfoLists' elements
    GfSearchCache m_cache;
    unsigned int m_serial;  // the next handle's serial number
    bool m_initialized;
};
}  // namespace gf

#endif
