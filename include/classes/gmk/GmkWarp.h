#ifndef CLASSES_GMK_GMKWARP_H
#define CLASSES_GMK_GMKWARP_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/BootedGmkCond.h"
#include "classes/gmk/DistHvCond.h"
class CBdatWrapper;
#include "mm/Vec3NA.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkWarpGobCustom; }

namespace gmk {
// table 0x7100B6CCA8
class GmkWarp : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondCommonMatched() const;
        // 2.0.0's symbols name them: the common conditions and the ene_disp_r/h (pop) / ene_release_r/h (depop) distances
        bool isPopCondMatched(const mm::Vec3& pos) const;
        bool isDepopCondMatched(const mm::Vec3& pos) const;
        unsigned short m_condition = 0;    // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned short m_nameRadius = 10;  // the row's "nameRadius"
        BootedGmkCond m_bootedGmk;         // the row's OP_gimmickType/ID
        // squared distances from the current map's row of BDAT 0x5D: ene_disp_r/h, and with ene_release_r/h added
        DistHvCond m_eneDisp = {0.0f, 0.0f};
        DistHvCond m_eneRelease = {0.0f, 0.0f};
    };
    GmkWarp() {
        m_firstHandle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        m_secondHandle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        for (unsigned int i = 0; i < 2; i++) {
            m_iconEffects[i] = 0;
        }
    }  // inline: Vector<T>::resize/extend construct in place
    virtual ~GmkWarp();  // slot 0
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}  // slot 9
    virtual void debugUpdateMmf();  // slot 10
    // destroys the objects at both points (m_firstHandle, m_secondHandle) and sets them back to -1
    void clearGobInsts();
    // makes the icon effect of the point at index (0 or 1) in m_iconEffects
    void createIcon(unsigned int index);
    void reqDeadIcon();
    void reqRecreateIcon();
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    // one end of the warp in AGmkBase::m_data (GfFieldWarp::onFsSucceeded reads two of them; the names are not the
    // original's)
    struct Point {
        mm::Vec3NA m_pos;
        float m_param;  // passed on in MsgPcFieldNotifyWarp (meaning not known)
    };
    const Point* getPoints() const { return reinterpret_cast<const Point*>(m_createInfo.m_data); }
    static const gmk::GmkType TYPE = gmk::GmkType(38);
    void* pad_48 = nullptr;  // fields: size from TGmkList::getInst's stride
    // the object at the first point (inferred): GfFieldWarp::onFsSucceeded sends the player to the second point when
    // the access came from it, to the first from any other (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_firstHandle;  // -1, set in the constructor body (Vector<T>::resize stores 0x50..0x67 after 0x6D)
    // the object at the second point (inferred: clearGobInsts destroys it like m_firstHandle; the name is not the
    // original's)
    gf::GF_OBJ_HANDLE* m_secondHandle;  // -1, set in the constructor body
    // the icon effect (fw::EffectManager handle) of each point: createIcon(index) makes m_iconEffects[index],
    // dispose removes both (the name is not the original's)
    unsigned int m_iconEffects[2];
    // the square of row 0's field 1 of BDAT 0x7B (create; GmkCollection::BdatInfo keeps the same value as its pop
    // distance; the name is not the original's)
    float m_popDistSq = 0.0f;
    bool m_iconDead = false;  // set by reqDeadIcon, cleared by reqRecreateIcon (the name is not the original's)
    unsigned char pad_6d = 1;  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
