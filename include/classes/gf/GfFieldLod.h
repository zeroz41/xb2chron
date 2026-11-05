#ifndef CLASSES_GF_GFFIELDLOD_H
#define CLASSES_GF_GFFIELDLOD_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfFieldLodColiAnim.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"

namespace gf { class GfFieldLod; }
namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; }
namespace fw { class UpdateInfo; }
namespace ml { class ScnObjModel; }
namespace mm { class Mat44; }

namespace gf {
// table 0x7100B51EB0; the field's LOD parts by their BDAT rows (BDAT 0x72: LODID, flag Visible/AnimReverse)
class GfFieldLod : public ::mm::mtl::PtrSingleton< ::gf::GfFieldLod> {
public:
    // a row's state (a class with no table; 0x34 bytes)
    class BdatInfo {
    public:
        // one condition of the row (1.0.0's isCondMatched tests the three; the field names are not the original's)
        struct CondInfo {
            // (createBdatInfos's pushed row: all zero but m_matched)
            CondInfo() : m_gameCond(0), m_cached(false) {}
            bool isCondMatched() const;

            gmk::ScenarioFlagCond m_scenarioFlag;  // 0x0
            gmk::QuestFlagCond m_questFlag;        // 0x4
            unsigned short m_gameCond;             // 0x8: GfGameCond::isGameCond's id (0: none)
            bool m_cached;                         // 0xa: dirtyCache clears it
            bool m_matched;                        // 0xb
        };
        // 1.0.0's symbols have it out of line (3.0.1 inlines it into createBdatInfos, which pushes BdatInfo(0)):
        // every field zero but the conditions' m_matched, then create when an id is given
        BdatInfo(unsigned short bdatId) : m_lodId(0), m_fadeInTime(0.0f), m_fadeOutTime(0.0f), m_bdatId(0) {
            if (bdatId != 0) {
                create(bdatId);
            }
        }
        ~BdatInfo() { dispose(); }
        void create(unsigned short bdatId);
        void dispose();
        void update();
        void dirtyCache();

        unsigned short m_lodId;  // 0x00: (inferred: GmkElevator reads it as the LOD id; the name is not the original's)
        unsigned char pad_2[2];
        float m_fadeInTime;     // 0x04: setFade's time when shown (the name is not the original's)
        float m_fadeOutTime;    // 0x08: setFade's time when hidden (the name is not the original's)
        unsigned short m_bdatId;  // 0x0c
        CondInfo m_conds[3];    // 0x0e
    };

    GfFieldLod(const GfSetupParam& param);
    virtual ~GfFieldLod();  // slot 0
    bool isPlayAnimEnd(int anim) const;
    float getAnimEndTime(int bdatId) const;
    // GfFieldManager's forwards (its initialize, finalize, clear, update and gev* functions call them)
    static void build(const GfSetupParam& param);
    static void destroy();
    static void validateByInitData();
    static void validateBySaveData();
    static void update(const fw::UpdateInfo& info);
    static bool isAnimReverseOfInit(int bdatId);
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    void gevPlayEvent(GEV gev, unsigned int eventId);
    int findBdatIdByLodId(unsigned short lodId) const;
    // true when a part of the LOD model animates (GfFieldMapGimmick::seqLod_init then waits for the animation's end)
    bool setAnimReverse(int bdatId, bool flag0, bool flag1);
    void setFade(int bdatId, bool flag0, bool flag1);
    void setPlaySpeed(int bdatId, float speed);
    void setLodSwitchId(int bdatId, unsigned int switchId);
    // 2.0.0's symbols name it. It reads the object's LOD ids and model as setLodSwitchId does. What it does: the
    // switch id (ScnObjAccPartsPos::getSwitchID) of the last switch part of the row's LOD id, -1 when none.
    unsigned int getLodSwitchId(int bdatId) const;
    bool isFadeOut(int bdatId) const;  // GfGameEvent::isMapLodDisp's: not shown
    bool isAnimReverse(int bdatId) const;  // GfGameEvent::isMapLodAnimReverse's
    void createColiAnim(ml::ScnObjModel* model, bool flag);
    void validateVeSe();
    void createBdatInfos();
    bool findTransform(mm::Mat44& mat, int bdatId) const;
    const BdatInfo* findBdatInfo(int bdatId) const;
    void initialize(const GfSetupParam& param);
    void finalize();
    void updateBdatInfos();
    void disposeColiAnim();
    void disposeBdatInfos();
    BdatInfo* _findBdatInfo(int bdatId);

    unsigned short m_lodIds[0x400];        // 0x008: LODID, by BDAT id - m_idTop
    int m_idTop;                           // 0x808: the BDAT's first id
    bool m_initialized;                    // 0x80c: the constructor has read the ids (the name is not the original's)
    mm::mtl::Vector<BdatInfo> m_bdatInfos;  // 0x810
    unsigned int m_updateIndex;            // 0x838: the next row update updates (the name is not the original's)
    GfFieldLodColiAnim m_coliAnim;         // 0x840
    bool m_updating;                       // 0x888: while update updates rows (the name is not the original's)
    bool m_eventPlaying;                   // 0x889: GEV 10 sets it, 11 clears it (the name is not the original's)
};
}  // namespace gf

#endif
