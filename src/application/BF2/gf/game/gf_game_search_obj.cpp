#include "classes/fw/ReferenceFrame.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "gf/GfSearchParam.h"
#include "classes/gf/GfGameSearchObj.h"
#include "classes/gf/GfAllocator.h"
#include "fw/UpdateInfo.h"
#include "gf/GfSetupParam.h"

namespace gf {

GfGameSearchObj::~GfGameSearchObj() {}

void GfGameSearchObj::build(const GfSetupParam& param) {
#line 69
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameSearchObj(param);
}

void GfGameSearchObj::destroy() {
    GfGameSearchObj* self = get();
    self->finalize();
    delete self;
}

void GfGameSearchObj::destroyList(InfoList* list) {
    if (list != nullptr) {
        for (InfoList::iterator it = list->begin(); it != list->end(); ++it) {
            m_searchInfos.deallocate(*it);
        }
        list->clear();
    }
}

GfGameSearchObj::InfoList* GfGameSearchObj::getObj(GF_SEARCH_OBJ* obj) {
    return get()->m_infos[reinterpret_cast<unsigned long>(obj) & 0x3F].m_list;
}

GF_SEARCH_OBJ* GfGameSearchObj::createObj(const GfSearchParam& param) {
    GfGameSearchObj* self = get();
    GF_SEARCH_OBJ* handle = reinterpret_cast<GF_SEARCH_OBJ*>(-1);
    if (self != nullptr) {
        unsigned int index;
        GFSEARCH_INFO* info = new (self->m_infos.allocate(index)) GFSEARCH_INFO();
        unsigned int serial = self->m_serial++;
        if (serial >= 0x3FFFFFF) {
            serial = self->m_serial++;
        }
        handle = reinterpret_cast<GF_SEARCH_OBJ*>(static_cast<unsigned long>((index & 0x3F) | (serial << 6)));
        info->m_handle = handle;
        info->m_param = param;
#line 160
        info->m_list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) InfoList();
        self->m_objs.push_back(handle);
    }
    return handle;
}
void GfGameSearchObj::destroyObj(GF_SEARCH_OBJ* obj) {
    GfGameSearchObj* self = get();
    if (self != nullptr) {
        GFSEARCH_INFO& info = self->m_infos[reinterpret_cast<unsigned long>(obj) & 0x3F];
        self->destroyList(info.m_list);
        if (info.m_list != nullptr) {
            delete info.m_list;
            info.m_list = nullptr;
        }
        info.~GFSEARCH_INFO();
        self->m_infos.free(reinterpret_cast<unsigned long>(obj) & 0x3F);
        ObjList::iterator it = self->m_objs.find(obj);
        if (it != self->m_objs.end()) {
            self->m_objs.erase(it);
        }
    }
}
}  // namespace gf

// instantiated for gf::GfGameSearchObj::destroyObj
template mm::mtl::FixedList<gf::GF_SEARCH_OBJ*, 64>::iterator mm::mtl::FixedList<gf::GF_SEARCH_OBJ*, 64>::erase(mm::mtl::FixedList<gf::GF_SEARCH_OBJ*, 64>::iterator);

namespace gf {

void GfGameSearchObj::setEnable(GF_SEARCH_OBJ* obj, bool enable) {
    if (obj != reinterpret_cast<GF_SEARCH_OBJ*>(-1) && get() != nullptr) {
        GFSEARCH_INFO& info = get()->m_infos[reinterpret_cast<unsigned long>(obj) & 0x3F];
        info.m_flags.set(0, !enable);
    }
}

void GfGameSearchObj::update(const fw::UpdateInfo& info) {
    GfGameSearchObj* self = get();
    for (int i = 0; i < GfSearchCache::TYPE_NUM; ++i) {
        self->m_cache.m_count[i] = -1;
    }
    for (ObjList::iterator it = self->m_objs.begin(); it != self->m_objs.end(); ++it) {
        self->updateObj(*it);
    }
}

}  // namespace gf
