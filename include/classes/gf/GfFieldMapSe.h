#ifndef CLASSES_GF_GFFIELDMAPSE_H
#define CLASSES_GF_GFFIELDMAPSE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/FixedVector.h"
#include "gf/SoundHandle.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfFieldMapSe; class GF_OBJ_HANDLE; }
namespace ml { class ScnObjAccSeamEtcPos; }

namespace gf {
// table 0x7100B521E8: the map model's seam sound points (FLD_actorSE rows matched by LOD name), each playing up to
// 16 sounds at its nearest matrices
class GfFieldMapSe : public ::mm::mtl::PtrSingleton< ::gf::GfFieldMapSe> {
public:
    // a matrix of an object and its squared distance (the field names are not the original's)
    struct SECOND {
        SECOND() : m_matrix(-1), m_dist(0.0f) {}
        SECOND(int matrix, float dist) : m_matrix(matrix), m_dist(dist) {}
        int m_matrix;
        float m_dist;
    };
    // one playing sound (the field names are not the original's)
    struct SEOBJ {
        SoundHandle m_handle;
        int m_obj;  // the seam object's index
        int m_matrix;  // its matrix the sound plays at
        float m_volume;  // getVolume's
        SECOND m_second;  // the matrix and its squared distance, refreshed each update
        unsigned int m_seId;  // the FLD_actorSE row
    };
    // one seam object with a sound (the field names are not the original's)
    struct SEDATA {
        SEDATA(int obj, int matrixMax, unsigned int seId)
            : m_obj(obj), m_matrixMax(matrixMax), m_seId(seId), m_nextMatrix(0) {}
        int m_obj;  // the seam object's index
        int m_matrixMax;  // its matrix count
        unsigned int m_seId;  // the FLD_actorSE row
        int m_nextMatrix;  // the matrix updateSeObjDataForFindActivate checks next
        ::mm::mtl::FixedVector<SEOBJ*, 16> m_objs;  // its playing sounds
        ::mm::mtl::FixedQueue<SECOND, 16> m_founds;  // matrices found in range, to play
    };
    // sorts SEOBJs nearest first
    struct DistCompare {
        bool operator()(const SEOBJ* a, const SEOBJ* b) const { return a->m_second.m_dist < b->m_second.m_dist; }
    };

    GfFieldMapSe();  // GfFieldSound::initialize creates it
    virtual ~GfFieldMapSe();  // slot 0
    // GfFieldSound's forwards (its update, postUpdate, clear and gev* functions call them)
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    void destroy();
    void gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag);
    void gevPause(unsigned int flags0, unsigned int flags1);

    void createMapSe();
    void destroyMapSe();
    void updateSeObj(fw::UpdateInfo info);
    void updateSeObjDataForFindActivate(fw::UpdateInfo info, SEDATA& data, ml::ScnObjAccSeamEtcPos& acc);
    void updateSeObjDataForActivate(fw::UpdateInfo info, SEDATA& data, ml::ScnObjAccSeamEtcPos& acc);
    SEOBJ* createSeObj(const SECOND& second, const SEDATA& data, ml::ScnObjAccSeamEtcPos& acc);
    float getVolume(const SEOBJ* obj);

    // stops obj's sound and gives it back (inline: destroyMapSe and updateSeObjDataForActivate repeat it; the name
    // is not the original's)
    void destroySeObj(SEOBJ* obj);

    int m_objMax;  // the seam's object count (createMapSe's)
    ::mm::mtl::FixedVector<SEDATA*, 32> m_datas;
    ::ml::fixed_size_alloc_inside<SEOBJ, 128> m_seObjs;
};
}  // namespace gf

#endif
