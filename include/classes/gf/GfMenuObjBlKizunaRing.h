#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "gf/GfMenuTypes.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"

namespace gf { class GAME_VOICE_HANDLE; class GfMenuItemList; }
namespace ui { class UIObjectAcc; class UISelectObjList; class UICtrlFrame; }

namespace gf {
// table 0x7100B604F8
class GfMenuObjBlKizunaRing : public ::gf::GfMenuObject {
public:
    class BladeSkillInfoListener;
    class MainListener;
    class RingListener;
    class RingPadListener;
    class SkillDetailListener;
    // one released skill level of the blade's ring (getAchievementList's entries; the names are not the original's)
    struct Achievement {
        Achievement(unsigned short line, unsigned short level, unsigned short state)
            : m_line(line), m_level(level), m_state(state) {}
        unsigned short m_line;   // the ring's line (0-9; 9 is the ring's own)
        unsigned short m_level;  // the level it reaches
        unsigned short m_state;  // GfKizunaringBlade::getReleaseAchievement's state (1, 3)
    };

    // what registOpenParam hands the ring's full-screen layer (1.0.0's names; the field names are not the original's)
    struct OpenParam {
        unsigned short m_mode;   // 1: openForMercenary
        unsigned int m_value;    // openForMercenary's value
    };

    GfMenuObjBlKizunaRing(unsigned int handle);
    // 1.0.0's (out of line there), inlined into openForMercenary in 3.0.1: the layer parameter of menu 0x22
    static void registOpenParam(const OpenParam& param) {
        GfMenuTypes::Param layer;
        layer.m_halves.m_type = param.m_mode;
        layer.m_value = param.m_value;
        GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x22), layer);
    }
    // 1.0.0's (out of line there), inlined into its callers in 3.0.1: an event of that type and first parameter
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    virtual ~GfMenuObjBlKizunaRing();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static bool attach(GfMenuCallContext* context);  // opens the ring on that call context (false: it did not)
    // registers the full-screen layer's parameter (mode 1, the mercenary value) and changes to the ring's layer
    static void openForMercenary(unsigned int handle, unsigned int value, unsigned short group);
    static bool procAchieve(unsigned int handle, GfMenuObjBlKizunaRing* ring);
    static unsigned int getAchievementList(mm::mtl::FixedVector<Achievement, 50>& list, unsigned int& kind,
                                   unsigned int& flags);
    static void setupRing(ui::UIObjectAcc& acc);
    static void setupRingList(ui::UIObjectAcc& acc, ui::UISelectObjList* list);
    static void refreshRing(ui::UIObjectAcc& acc);
    static void dispDetail(ui::UIObjectAcc& acc, unsigned int index);
    static void movePointer(unsigned int handle, int index, ui::UISelectObjList* list);
    static void setupSkillDetail(ui::UIObjectAcc& acc);
    bool seqWaitVoice();
    bool seqComplete();
    bool seqEnd();
    bool seqAchieve();
    bool seqWait();

    // the names below are not the original's
    ui::UISelectObjList* m_ringList;           // initialize's
    ui::UICtrlFrame* m_ringFrame;              // RingListener's frame over the ring list
    bool pad_38;
    bool m_detailOpen;                         // SkillDetailListener toggles it
    int m_referenceNumber;                     // GfMenuReference::setReferenceNumber(1, ...)
    unsigned int m_selected;                   // the ring list's selection (-1: none)
    GfMenuCallContext* m_subContext;           // initialize's
    unsigned int m_achieveKind;                // getAchievementList's kind
    GfMenuCallContext* m_context;              // the constructor's
    mm::mtl::FixedVector<Achievement, 50> m_achievements;
    unsigned int m_achieveIndex;
    GfMenuSequence<GfMenuObjBlKizunaRing, 8> m_seq;
    int m_achieveStep;                         // seqAchieve's step (procAchieve starts it at 1)
    int m_completeStep;               // seqComplete counts it up
    unsigned int m_mode;                       // the layer parameter's menu id (1: openForMercenary)
    unsigned int m_mercenary;                  // the layer parameter's value
    GfMenuCallContext* m_callContext;          // initialize's
    GfMenuItemList* m_itemList;                // initialize's
    unsigned int pad_450;
    unsigned int m_achieveFlags;               // getAchievementList's flags
    GAME_VOICE_HANDLE* m_voice;
    unsigned int m_voiceBlade;
    long m_voiceRequest;                       // GfReqSmallCom request (-1: none)
};
}  // namespace gf

#endif
