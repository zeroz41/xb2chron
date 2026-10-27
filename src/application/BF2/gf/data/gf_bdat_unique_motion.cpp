#include "mm/mtl/Map.h"
#include "classes/gf/GfBdatUniqueMotion.h"
#include "algorithm"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGamePlayerUniqueScheduler.h"
#include "mm/mtl/Map.h"
#include "mm/mtl/Vector.h"
#include "plugin/Bdat.h"

namespace gf {

class GfBdatUniqueMotion::Impl {
public:
    Impl() : m_presets(getAllocator(ALLOCATOR(0))), m_charaInfos(getAllocator(ALLOCATOR(0))) {}
    void build();
    void queryPreset(mm::mtl::FixedQueue<const PresetInfo*, 32>* presets, const PresetKey& key);

    mm::mtl::Vector<PresetInfo> m_presets;
    mm::mtl::Map<unsigned short, CharaInfo> m_charaInfos;  // by chara id
};

void GfBdatUniqueMotion::Impl::build() {
    {
        unsigned char* fp = GfDataBdat::getFP(0x1DB);
        unsigned int top = Bdat::getIdTop(fp);
        unsigned int count = Bdat::getIdCount(fp);
        unsigned int end = top + count;
        m_presets.reserve(count);
        for (unsigned int id = top; id < end; ++id) {
            PresetInfo info;
            info.m_weight =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Frequency", id, 2)));
            union {
                unsigned int bits;
                float value;
            } wait;
            info.m_entries[0].m_charaId =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Chara0", id, 2)));
            info.m_entries[0].m_motion =
                static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Motion0", id, 1)));
            wait.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Delay0", id, 8)));
            info.m_entries[0].m_wait = wait.value;
            info.m_entries[1].m_charaId =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Chara1", id, 2)));
            info.m_entries[1].m_motion =
                static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Motion1", id, 1)));
            wait.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Delay1", id, 8)));
            info.m_entries[1].m_wait = wait.value;
            info.m_entries[2].m_charaId =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Chara2", id, 2)));
            info.m_entries[2].m_motion =
                static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Motion2", id, 1)));
            wait.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Delay2", id, 8)));
            info.m_entries[2].m_wait = wait.value;
            info.m_entries[3].m_charaId =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Chara3", id, 2)));
            info.m_entries[3].m_motion =
                static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Motion3", id, 1)));
            wait.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Delay3", id, 8)));
            info.m_entries[3].m_wait = wait.value;
            info.m_entries[4].m_charaId =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Chara4", id, 2)));
            info.m_entries[4].m_motion =
                static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Motion4", id, 1)));
            wait.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Delay4", id, 8)));
            info.m_entries[4].m_wait = wait.value;
            info.m_entries[5].m_charaId =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Chara5", id, 2)));
            info.m_entries[5].m_motion =
                static_cast<unsigned char>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Motion5", id, 1)));
            wait.bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Delay5", id, 8)));
            info.m_entries[5].m_wait = wait.value;
            info.m_key = PresetKey(info.m_entries[0].m_charaId, info.m_entries[1].m_charaId,
                                   info.m_entries[2].m_charaId, info.m_entries[3].m_charaId,
                                   info.m_entries[4].m_charaId, info.m_entries[5].m_charaId);
            std::sort(info.m_key.m_ids, info.m_key.m_ids + 6);
            m_presets.push_back(info);
        }
    }
    {
        unsigned char* fp = GfDataBdat::getFP(0x1DC);
        unsigned int top = Bdat::getIdTop(fp);
        unsigned int count = Bdat::getIdCount(fp);
        for (unsigned int id = top; id < top + count; ++id) {
            unsigned short charaId =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "RefID", id, 2)));
            CharaInfo info;
            info.m_charaId = charaId;
            info.m_rate =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "Probability", id, 2)));
            union {
                unsigned int bits;
                float value;
            } waitMin, waitMax;
            waitMin.bits =
                static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "DelayMin", id, 8)));
            info.m_waitMin = waitMin.value;
            waitMax.bits =
                static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "DelayMax", id, 8)));
            info.m_waitMax = waitMax.value;
            info.m_weights[0] =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "FrequencyA", id, 2)));
            info.m_weights[1] =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "FrequencyB", id, 2)));
            info.m_weights[2] =
                static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(fp, "FrequencyC", id, 2)));
            m_charaInfos.insert(mm::mtl::MapPair<unsigned short, CharaInfo>(charaId, info));
        }
    }
}

void GfBdatUniqueMotion::Impl::queryPreset(mm::mtl::FixedQueue<const PresetInfo*, 32>* presets, const PresetKey& key) {
    for (unsigned int i = 0; i < m_presets.size(); ++i) {
        if (m_presets[i].m_key.isContain(key)) {
            presets->push_back(&m_presets[i]);
        }
    }
}

// an inline definition clang does not inline: the original's queryPreset loads the presets' buffer again after the
// call, which clang does only when the callee's definition is not exact (an inline one: weak, so not known to only
// read memory); a plain inline definition is always inlined there, an out-of-line one lets the load be reused
__attribute__((noinline)) inline bool GfBdatUniqueMotion::PresetKey::isContain(const PresetKey& key) const {
    unsigned int j = 0;
    for (unsigned int i = 0; i < 6; ++i) {
        if (m_ids[i] == 0) {
            continue;
        }
        while (j < 6 && key.m_ids[j] != m_ids[i]) {
            ++j;
        }
        if (j >= 6) {
            return false;
        }
        ++j;
    }
    return true;
}

#line 180
GfBdatUniqueMotion::GfBdatUniqueMotion() {
    m_impl.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) Impl());
    m_impl->build();
}

#line 190
void GfBdatUniqueMotion::bdatRefresh() {
    m_impl.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) Impl());
    m_impl->build();
    GfGamePlayerUniqueScheduler::onReload();
}

void GfBdatUniqueMotion::queryPreset(mm::mtl::FixedQueue<const PresetInfo*, 32>* presets, const PresetKey& key) {
    if (GfBdatUniqueMotion* self = get()) {
        if (self->m_impl) {
            self->m_impl->queryPreset(presets, key);
        }
    }
}

const GfBdatUniqueMotion::CharaInfo* GfBdatUniqueMotion::getCharaInfo(unsigned short charaId) {
    if (GfBdatUniqueMotion* self = get()) {
        if (self->m_impl) {
            mm::mtl::Map<unsigned short, CharaInfo>::node* n = self->m_impl->m_charaInfos.find(charaId);
            return n == nullptr ? nullptr : &n->value.second;
        }
    }
    return nullptr;
}

// inline (as GfBdatLookAt's): the deleting destructor and both complete-object thunks of the original inline it, the
// deleting thunks do not; an out-of-line one is past the inliner's threshold for all of them
inline GfBdatUniqueMotion::~GfBdatUniqueMotion() {}

}  // namespace gf
