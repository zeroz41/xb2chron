#ifndef CLASSES_GMK_TGMKLIST_H
#define CLASSES_GMK_TGMKLIST_H

#include <algorithm>
#include "classes/fw/CommonResource.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAccManager.h"
#include "classes/gmk/GmkGobEventListener.h"
#include "classes/gmk/IGmkList.h"
#include "mm/mtl/Vector.h"
#include "classes/ml/Scn.h"
#include "plugin/Bdat.h"
#include "classes/gmk/Lvlb.h"
#include "classes/fw/FrameworkMemory.h"
#include <string.h>
#include "classes/ml/ScnObjCam.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk {
// A kind's BdatInfo either reads a BDAT row (it has create(table, row, gmk), taking the table or a CBdatWrapper made
// from it) or holds nothing (an empty class: Trigger, BattleLock, the form kinds, ...). For the empty kinds createGmk
// still indexes m_bdatInfos, but initGmkBdatInfo is `return false` inlined away: 21 lists have no initGmkBdatInfo of
// their own. This picks the case from the type (the original's mechanism is not known; the code is the same).
template <typename T1>
class GmkBdatRowTest {
    template <typename U>
    static char test(U* info, decltype(info->create(static_cast<unsigned char*>(nullptr), 0,
                                                    *static_cast<const gmk::AGmkBase*>(nullptr)))* = nullptr);
    template <typename U>
    static long test(...);

public:
    static const bool HAS_ROW = sizeof(test<T1>(nullptr)) == 1;
};
template <typename T1, bool HAS = GmkBdatRowTest<T1>::HAS_ROW>
struct GmkBdatRow {
    static const bool HAS_ROW = true;
    static void create(T1& info, unsigned char* fp, int row, const gmk::AGmkBase& gmk) { info.create(fp, row, gmk); }
};
template <typename T1>
struct GmkBdatRow<T1, false> {
    static const bool HAS_ROW = false;
    static void create(T1&, unsigned char*, int, const gmk::AGmkBase&) {}
};
// the gimmicks of one kind (T0), read from a resource whose gimmick section carries the magic T2, with their rows
// (T1) in a BDAT table; 55 instances in the module
template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
class TGmkList : public ::gmk::IGmkList {
public:
    typedef void (TGmkList::*SeqFunc)(float);
    // the count of gimmicks seqUpdate updates a frame comes from the creator (GmkSet::createGmkLists)
    // every list shares the gimmick object listener (GmkGobEventListener::addRef); the destructor releases it
    explicit TGmkList(unsigned int updateGmkNumPerFrame)
        : m_resource(nullptr), m_assetData(nullptr), m_xformSection(nullptr), m_xforms(nullptr), m_infoSection(nullptr), m_infos(nullptr),
          m_gmkSection(nullptr), m_gmkData(nullptr), m_strings(nullptr), m_bdatFp(nullptr),
          m_seq(nullptr), m_updateGmkNumPerFrame(updateGmkNumPerFrame), m_updateGmkIndex(0) {
        GmkGobEventListener::addRef();
    }
    virtual ~TGmkList();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual const CreateInfo& getCreateInfo() const;  // slot 4
    virtual unsigned int getInstNum() const;  // slot 5
    virtual gmk::AGmkBase* getInst(unsigned int index) const;  // slot 6
    virtual unsigned char* getBindedBdatFp() const;  // slot 7
    virtual void setUpdateGmkNumPerFrame(unsigned int num);  // slot 8
    virtual void create(gmk::IGmkList::CreateInfo const& info);  // slot 9
    virtual void dispose();  // slot 10
    virtual void update(float dt);  // slot 11
    virtual bool updateImmediate();  // slot 12
    virtual void debugUpdateMmf();  // slot 13
    virtual void debugDraw() const;  // slot 14
    virtual void createGmk(void* data);  // slot 16
    virtual void disposeGmk();  // slot 17
    virtual void onResetUpdateGmkIndex();  // slot 18
    // the sequences update runs: wait for the resource, then update a share of the gimmicks each frame
    // finds the BDAT row named as the gimmick's INFO entry and fills bdatInfo from it (the name is the original's)
    bool initGmkBdatInfo(T1& bdatInfo, int& bdatId, const gmk::AGmkBase& gmk);
    void seqWaitResourceLoaded(float dt);
    void seqUpdate(float dt);

    unsigned char pad_8[0x8];
    CreateInfo m_createInfo;  // 0x10
    fw::CommonResource* m_resource;  // 0x170: the gimmick resource create requests
    void* m_assetData;  // 0x178: its data, createGmk's (the name is not the original's)
    // 0x180..0x1b0: the resource's sections createGmk finds, and their data (the names are not the original's)
    const LvlbSection* m_xformSection;
    Xform* m_xforms;
    const LvlbSection* m_infoSection;
    LvlbInfo* m_infos;
    const LvlbSection* m_gmkSection;  // 0x1a0: the section whose magic is T2
    const unsigned char* m_gmkData;
    const char* m_strings;
    unsigned char* m_bdatFp;  // 0x1b8: the BDAT table of m_createInfo.m_bdatName
    SeqFunc m_seq;  // 0x1c0: what update runs, none when disposed
    mm::mtl::Vector<T1> m_bdatInfos;  // 0x1d0
    mm::mtl::Vector<T0> m_gmks;  // 0x1f8
    unsigned int m_updateGmkNumPerFrame;  // 0x220: how many gimmicks seqUpdate updates a frame
    unsigned int m_updateGmkIndex;  // 0x224: the next one it updates
    // (no field at 0x228: GmkMobList and GmkCollectionList keep theirs there, in the tail padding of this 16-aligned class)
};

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
gmk::GmkType TGmkList<T0, T1, T2, T3, T4>::getGmkType() const {
    return T0::TYPE;
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
bool TGmkList<T0, T1, T2, T3, T4>::isValid() const {
    if (m_assetData == nullptr) {
        return false;
    }
    if (m_createInfo.m_bdatName.m_nLen != 0 && m_bdatFp == nullptr) {
        return false;
    }
    if (m_gmkSection == nullptr) {
        return false;
    }
    return m_gmkSection->m_magic == T2;
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
const IGmkList::CreateInfo& TGmkList<T0, T1, T2, T3, T4>::getCreateInfo() const {
    return m_createInfo;
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
unsigned int TGmkList<T0, T1, T2, T3, T4>::getInstNum() const {
    return m_gmks.size();
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
gmk::AGmkBase* TGmkList<T0, T1, T2, T3, T4>::getInst(unsigned int index) const {
    return const_cast<T0*>(&m_gmks[index]);
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
unsigned char* TGmkList<T0, T1, T2, T3, T4>::getBindedBdatFp() const {
    return m_bdatFp;
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
TGmkList<T0, T1, T2, T3, T4>::~TGmkList() {
    dispose();
    GmkGobEventListener::release();
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::create(const IGmkList::CreateInfo& info) {
    dispose();
    // field by field (the copy of the position has no self-assignment test)
    m_createInfo.m_allocHandle = info.m_allocHandle;
    m_createInfo.m_param = info.m_param;
    m_createInfo.m_path = info.m_path;
    m_createInfo.m_bdatName = info.m_bdatName;
    m_createInfo.m_pos.x = info.m_pos.x;
    m_createInfo.m_pos.y = info.m_pos.y;
    m_createInfo.m_pos.z = info.m_pos.z;
    m_createInfo.m_rotY = info.m_rotY;
    m_resource = fw::CommonResource::request(info.m_allocHandle, m_createInfo.m_path.m_str, 9, false);
    m_seq = &TGmkList::seqWaitResourceLoaded;
    if (m_createInfo.m_bdatName.m_nLen != 0) {
        m_bdatFp = Bdat::getFP(m_createInfo.m_bdatName.m_str);
        if (m_bdatFp == nullptr) {
            dispose();
        }
    }
}

// the gimmicks near the camera (within 100 on the ground plane) update their debug menus
template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::debugUpdateMmf() {
    if (isValid() && mm::mtl::PtrSingleton<ml::Scn>::get() != nullptr &&
        mm::mtl::PtrSingleton<ml::Scn>::get()->getCam(-1) != nullptr) {
        const mm::Vec3& camPos = mm::mtl::PtrSingleton<ml::Scn>::get()->getCam(-1)->m_info.m_render->m_transform.m_posGbl;
        for (T0* it = m_gmks.begin(); it != m_gmks.end(); ++it) {
            if (it->m_pos != nullptr) {
                float dx = camPos.x - it->m_pos->x;
                float dz = camPos.z - it->m_pos->z;
                if (!(dx * dx + dz * dz > 10000.0f)) {
                    it->debugUpdateMmf();
                }
            }
        }
    }
}

// the gimmicks near the camera (within 100 on the ground plane) draw their debug shapes
template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::debugDraw() const {
    if (isValid() && mm::mtl::PtrSingleton<ml::Scn>::get() != nullptr &&
        mm::mtl::PtrSingleton<ml::Scn>::get()->getCam(-1) != nullptr) {
        const mm::Vec3& camPos = mm::mtl::PtrSingleton<ml::Scn>::get()->getCam(-1)->m_info.m_render->m_transform.m_posGbl;
        for (const T0* it = m_gmks.begin(); it != m_gmks.end(); ++it) {
            if (it->m_pos != nullptr) {
                float dx = camPos.x - it->m_pos->x;
                float dz = camPos.z - it->m_pos->z;
                if (!(dx * dx + dz * dz > 10000.0f)) {
                    it->debugDraw();
                }
            }
        }
    }
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::disposeGmk() {
    m_gmks.destroy();
    m_bdatInfos.destroy();
    m_assetData = nullptr;
    m_xformSection = nullptr;
    m_xforms = nullptr;
    m_infoSection = nullptr;
    m_infos = nullptr;
    m_gmkSection = nullptr;
    m_gmkData = nullptr;
    m_strings = nullptr;
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::setUpdateGmkNumPerFrame(unsigned int num) {
    m_updateGmkNumPerFrame = num;
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::dispose() {
    GmkAccManager::invalidateAccs(*this);
    m_seq = nullptr;
    disposeGmk();
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
    m_createInfo = CreateInfo();
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::update(float dt) {
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
bool TGmkList<T0, T1, T2, T3, T4>::updateImmediate() {
    bool valid = isValid();
    unsigned int num = m_updateGmkNumPerFrame;
    unsigned int index = m_updateGmkIndex;
    if (m_seq) {
        m_updateGmkNumPerFrame = getInstNum();
        m_updateGmkIndex = 0;
        (this->*m_seq)(0.0f);
    }
    m_updateGmkNumPerFrame = num;
    m_updateGmkIndex = index;
    return valid;
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::onResetUpdateGmkIndex() {}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::createGmk(void* data) {
    if (data == nullptr) {
        return;
    }
    disposeGmk();
    LvlbHeader* header = static_cast<LvlbHeader*>(data);
    LvlbInfo* infos = nullptr;
    if (header->m_magic != 0x424C564C || header->m_version != 3) {
    fail:
        dispose();
        return;
    }
    for (const LvlbSection* section = reinterpret_cast<const LvlbSection*>(header + 1);
         section < reinterpret_cast<const LvlbSection*>(static_cast<unsigned char*>(data) + header->m_size);
         section = reinterpret_cast<const LvlbSection*>(reinterpret_cast<const unsigned char*>(section) + section->m_size)) {
        switch (section->m_magic) {
        case 0x4D524658: {  // XFRM
            m_xformSection = section;
            if (section->m_version != 2) {
                goto fail;
            }
            Xform* xforms = reinterpret_cast<Xform*>(const_cast<LvlbSection*>(section + 1));
            m_xforms = xforms;
            if (m_createInfo.m_rotY != 0.0f || !m_createInfo.m_pos.isZero()) {
                mm::Mat44 local;
                mm::Mat44 world;
                mm::Mat44 mat;
                if (m_createInfo.m_rotY != 0.0f || !m_createInfo.m_pos.isZero()) {
                    mat.setRotY(m_createInfo.m_rotY);
                    mat.addTrans(mm::Vec3(m_createInfo.m_pos.x, m_createInfo.m_pos.y, m_createInfo.m_pos.z));
                } else {
                    mat = mm::Mat44::identity;
                }
                unsigned int count = m_xformSection->m_count;
                for (unsigned int i = 0; i < count; ++i) {
                    Xform& xform = xforms[i];
                    xform.toMatrix(local, true);
                    world.mul(local, mat);
                    mm::Vec3 pos = world.getTrans();
                    xform.m_pos.setV(pos);
                    world.getRotXYZ(xform.m_rot);
                    xform.m_rot.x = -xform.m_rot.x;
                    xform.m_rot.y = -xform.m_rot.y;
                    xform.m_rot.z = -xform.m_rot.z;
                }
            }
            break;
        }
        case 0x47525453:  // STRG
            m_strings = reinterpret_cast<const char*>(section + 1);
            break;
        case 0x4F464E49:  // INFO
            m_infoSection = section;
            if (section->m_version != 4) {
                goto fail;
            }
            infos = reinterpret_cast<LvlbInfo*>(const_cast<LvlbSection*>(section + 1));
            m_infos = infos;
            break;
        case T2:
            m_gmkSection = section;
            if (section->m_version != T3) {
                goto fail;
            }
            m_gmkData = reinterpret_cast<const unsigned char*>(section + 1);
            break;
        }
    }
    if (m_gmkSection == nullptr) {
        dispose();
        return;
    }
    const LvlbSection* gmkSection = m_gmkSection;
    if (m_strings != nullptr && (header->m_flags & 1) == 0) {
        header->m_flags |= 1;
        if (infos != nullptr) {
            unsigned int count = m_infoSection->m_count;
            for (unsigned int i = 0; i < count; ++i) {
                infos[i].m_name += reinterpret_cast<unsigned long>(m_strings);
            }
        }
        gmkSection = m_gmkSection;
    }
    m_assetData = data;
    unsigned int num = gmkSection->m_count;
    if (m_createInfo.m_bdatName.m_nLen != 0) {
        m_bdatInfos.setAllocator(fw::FrameworkMemory::getAllocator(5));
        m_bdatInfos.reserve(num);
        m_bdatInfos.resize(num);
    }
    m_gmks.setAllocator(fw::FrameworkMemory::getAllocator(5));
    m_gmks.reserve(num);
    m_gmks.resize(num);
    for (unsigned int i = 0; i < num; ++i) {
        // the gimmick is used as its AGmkBase: create is called on the base (the 10 kinds that do not override
        // AGmkBase::create, e.g. GmkNpc/GmkMapObj, call it with the same pointer as those that do)
        AGmkBase& gmk = m_gmks[i];
        const T1* bdatInfo = nullptr;
        bool noInfo = (m_gmkSection->m_flags & 1) != 0;
        if (noInfo) {
            gmk.m_list = this;
            gmk.m_pos = nullptr;
            gmk.m_info = nullptr;
        } else {
            const LvlbInfo* info = &m_infos[i + m_gmkSection->m_infoIndex];
            const mm::Vec3* pos = info != nullptr ? &m_xforms[info->m_xformIndex].m_pos : nullptr;
            gmk.m_list = this;
            gmk.m_pos = pos;
            gmk.m_info = info;
        }
        // one store of -1 after the if/else (not one per branch): where initGmkBdatInfo is inlined away (the empty
        // kinds) bdatId then has a single store, and that sets the order of the placement matrix's spill slots above
        int bdatId = -1;
        if (!noInfo && m_createInfo.m_bdatName.m_nLen != 0 && initGmkBdatInfo(m_bdatInfos[i], bdatId, gmk)) {
            bdatInfo = &m_bdatInfos[i];
        }
        AGmkBase::CreateInfo info;
        info.m_version = m_gmkSection->m_version;
        info.m_data = m_gmkData + m_gmkSection->m_stride * i;
        info.m_bdatInfo = bdatInfo;
        info.m_bdatId = bdatId;
        gmk.create(info);
    }
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::seqWaitResourceLoaded(float dt) {
    if (m_resource->valid()) {
        void* data = m_resource->getAssetData();
        if (data == nullptr) {
            dispose();
            return;
        }
        createGmk(data);
        m_seq = &TGmkList::seqUpdate;
    }
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
void TGmkList<T0, T1, T2, T3, T4>::seqUpdate(float dt) {
    if (!isValid()) {
        return;
    }
    if (m_updateGmkNumPerFrame == 0) {
        return;
    }
    unsigned int count = m_gmks.size();
    if (count == 0) {
        return;
    }
    if (count <= m_updateGmkIndex) {
        m_updateGmkIndex = 0;
        onResetUpdateGmkIndex();
    }
    unsigned int num = std::min(count, m_updateGmkNumPerFrame);
    // each gimmick is updated once every that many frames: with that many frames' time
    float frameDt = static_cast<float>((count + num - 1) / num) * dt;
    for (unsigned int i = 0; i < num; i++, m_updateGmkIndex++) {
        if (count <= m_updateGmkIndex) {
            m_updateGmkIndex = 0;
            onResetUpdateGmkIndex();
            return;
        }
        m_gmks[m_updateGmkIndex].update(frameDt);
    }
}

template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
bool TGmkList<T0, T1, T2, T3, T4>::initGmkBdatInfo(T1& bdatInfo, int& bdatId, const gmk::AGmkBase& gmk) {
    if (!GmkBdatRow<T1>::HAS_ROW) {
        return false;
    }
    if (m_createInfo.m_bdatName.m_nLen == 0) {
        return false;
    }
    const char* name = gmk.m_info->m_name;
    if (name == nullptr || *name == '\0') {
        return false;
    }
    unsigned char* fp = getBindedBdatFp();
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    int found = -1;
    for (int id = top; id < top + count; ++id) {
        const char* rowName = (const char*)Bdat::getValCheck(fp, "name", id, 7);
        if (rowName == nullptr || ::strcmp(rowName, name) != 0) {
            continue;
        }
        found = id;
        break;
    }
    if (found >= 0) {
        bdatId = found;
        // T1::create takes a CBdatWrapper (made from the table) or the table itself (GmkTbox, GmkGrave)
        GmkBdatRow<T1>::create(bdatInfo, getBindedBdatFp(), found, gmk);
        return true;
    }
    return false;
}

}  // namespace gmk

#endif
