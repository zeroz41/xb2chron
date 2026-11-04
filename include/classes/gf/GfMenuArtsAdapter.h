#ifndef CLASSES_GF_GFMENUARTSADAPTER_H
#define CLASSES_GF_GFMENUARTSADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuArtsList; }

namespace gf {
// table 0x7100B59CE8; a driver's arts (GfDataDriverArts) at a level: its name, caption, icons, numbers
class GfMenuArtsAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    class ListReferenceDriverConverter;
    class ListReferenceDriverConverterReferenceIndex;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuArtsAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuArtsAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_artsId(0), m_level(0) {}
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuArtsAdapter* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                        bool changed);
    static GfMenuArtsAdapter* createFromList(unsigned int handle, unsigned int type, GfMenuArtsList* list, int index,
                                             unsigned int driverId, bool changed);
    static GfMenuArtsAdapter* createFromListReferenceDriver(unsigned int handle, unsigned int type,
                                                            GfMenuArtsList* list, int index, unsigned int reference,
                                                            bool changed);
    static GfMenuArtsAdapter* createFromListReferenceDriverReferenceIndex(
        unsigned int handle, unsigned int type, GfMenuArtsList* list,
        mm::mtl::IntrusivePtr<GfMenuReferenceNumber> index, unsigned int reference, bool changed);
    virtual ~GfMenuArtsAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuArtsAdapter* create(unsigned int handle, unsigned int type, unsigned int artsId,
                                     unsigned int driverId, unsigned int level, bool changed);
    bool update_ArtsName();
    bool update_ArtsDescription();
    bool update_ArtsIconType();
    bool update_ArtsIconEnhance();
    bool update_ArtsIconReact();
    bool update_ArtsIconRange();
    bool update_ArtsWp();
    bool update_ArtsIconLevel();
    bool update_ArtsNumLevel();
    bool update_ArtsReleseLv();
    bool update_ArtsTextType();
    bool update_ArtsTextRange();
    bool update_ArtsTextReact();
    bool update_ArtsNumDamage();
    bool update_ArtsNumRecast();  // 1.0.0's name (its type table's slot 14); the symbols call it fn_7100331D04
    bool update_ArtsEnhanceDescription();
    bool update_ArtsIconReleseLv();
    bool update_ArtsNumDamageNextLv();
    bool update_ArtsNumRecastNextLv();  // 1.0.0's name (its type table's slot 18); the symbols call it fn_7100331F88
    bool update_ArtsEnhanceDescriptionNextLv();
    bool update_ArtsDispLvMax();
    bool update_ArtsTextIndex();
    // 2.0.0's symbols name it. What it does: with add-on menu layer 3 usable (GfMenuObjUtil::isValidExpansion(3)),
    // shows the message GfDataDriverArts::getTalentCaptionID (GfBdatBtl::getArtsDrTalentCap, the TalentCap column)
    // gives for m_artsId
    // from GfDataBdat table 0x191; false otherwise or for message 0.
    bool update_IraArtsTalentCaption();
    // 2.0.0's symbols name it. What it does: as update_IraArtsTalentCaption, with
    // GfDataDriverArts::getCondTalentCaptionID (GfBdatBtl::getArtsDrCondCap, the CondCap column) for the message,
    // also from table 0x191.
    bool update_IraArtsTalentCond();
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the arts from it; owned
    unsigned int m_artsId;    // 0 shows nothing
    unsigned int m_driverId;  // most update_* show nothing for 0
    unsigned int m_level;
    // GfDataDriverArts::getLevelCap's second argument (update_ArtsReleseLv, update_ArtsIconReleseLv); with it 0
    // update_ArtsDispLvMax shows below the maximum level instead of at it. Nothing in the unit sets it (the
    // constructor leaves it); the name is not the original's
    unsigned int m_releaseIndex;
};
}  // namespace gf

#endif
