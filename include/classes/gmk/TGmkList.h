#ifndef CLASSES_GMK_TGMKLIST_H
#define CLASSES_GMK_TGMKLIST_H

#include "classes/fw/CommonResource.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAccManager.h"
#include "classes/gmk/GmkGobEventListener.h"
#include "classes/gmk/IGmkList.h"
#include "mm/mtl/Vector.h"
#include "classes/ml/Scn.h"
#include "plugin/Bdat.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk {
// the gimmicks of one kind (T0), read from a resource whose gimmick section carries the magic T2, with their rows
// (T1) in a BDAT table; 55 instances in the module
template <typename T0, typename T1, unsigned int T2, unsigned int T3, typename T4>
class TGmkList : public ::gmk::IGmkList {
public:
    typedef void (TGmkList::*SeqFunc)(float);
    // the count of gimmicks seqUpdate updates a frame comes from the creator (GmkSet::createGmkLists)
    // every list shares the gimmick object listener (GmkGobEventListener::addRef); the destructor releases it
    explicit TGmkList(unsigned int updateGmkNumPerFrame)
        : m_resource(nullptr), m_assetData(nullptr), pad_180(nullptr), pad_188(nullptr), pad_190(nullptr), pad_198(nullptr), m_gmkSection(nullptr),
          pad_1a8(nullptr), pad_1b0(nullptr), m_bdatFp(nullptr),
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
    void seqWaitResourceLoaded(float dt);
    // (seqUpdate has no body here yet: its last candidate is two instructions off, kept outside the tree)
    void seqUpdate(float dt);

    unsigned char pad_8[0x8];
    CreateInfo m_createInfo;  // 0x10
    fw::CommonResource* m_resource;  // 0x170: the gimmick resource create requests
    void* m_assetData;  // 0x178: its data, createGmk's (the name is not the original's)
    // 0x180..0x1a0 and 0x1a8: four and two words disposeGmk clears (not read yet)
    void* pad_180;
    void* pad_188;
    void* pad_190;
    void* pad_198;
    const unsigned int* m_gmkSection;  // 0x1a0: the section whose first word is T2 (the name is not the original's)
    void* pad_1a8;
    void* pad_1b0;
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
    return *m_gmkSection == T2;
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
    pad_180 = nullptr;
    pad_188 = nullptr;
    pad_190 = nullptr;
    pad_198 = nullptr;
    m_gmkSection = nullptr;
    pad_1a8 = nullptr;
    pad_1b0 = nullptr;
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

}  // namespace gmk

#endif
