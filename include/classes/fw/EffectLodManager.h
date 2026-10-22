#ifndef CLASSES_FW_EFFECTLODMANAGER_H
#define CLASSES_FW_EFFECTLODMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Mat44.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class EffectLodManager; }
namespace fw { class EffectPack; }
namespace fw { class ModelObject; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41390; the effects a model's seam parts place, shown and faded by the camera's distance
class EffectLodManager : public ::mm::mtl::PtrSingleton< ::fw::EffectLodManager> {
public:
    // one effect a seam part places (init makes one per part matrix; the names are not the original's)
    struct Entry : public mm::mtl::IntrusiveListNodeBase {
        Entry() : m_handle(0), m_matrix(mm::Mat44::identity), m_seamIndex(-1), m_partsIndex(-1), m_range(0.0f),
                  m_scale(1.0f), m_nearFade(false), m_farFade(false), m_created(false), m_alpha(0.0f) {
            m_nearClip[0] = 0.0f;
            m_nearClip[1] = 0.0f;
            m_farClip[0] = 0.0f;
            m_farClip[1] = 0.0f;
        }

        unsigned int m_handle;          // EffectManager::create's, 0 for none
        mm::mtl::FixStr<32> m_objName;  // the part's object name
        mm::mtl::FixStr<32> m_effName;  // the effect's name (what update creates)
        mm::Mat44 m_matrix;             // where the effect is, its rows normalized
        int m_seamIndex;
        int m_partsIndex;
        float m_range;        // shown within this distance of the camera
        float m_nearClip[2];  // faded in between the two
        float m_farClip[2];   // faded out between the two
        float m_scale;        // the matrix's first row's length
        bool m_nearFade;      // a near clip above 1e-4
        bool m_farFade;       // a far clip above 1e-4
        bool m_created;
        float m_alpha;  // the last update's
    };

    EffectLodManager();
    virtual ~EffectLodManager();  // slot 0
    // the model's seam parts' effects, made anew; set up for a map's model and its effect pack (gf::MapEff::create),
    // undone by term
    void init(ModelObject* model, EffectPack* pack);
    void term();
    void update(const UpdateInfo& info);

    EffectPack* m_pack;    // init's (the name is not the original's)
    ModelObject* m_model;  // init's (the name is not the original's)
    mm::mtl::IntrusiveList<Entry> m_entries;  // init's (the name is not the original's)
    float m_speed;  // the last update's UpdateInfo::m_speed (the name is not the original's)
};
}  // namespace fw

#endif
