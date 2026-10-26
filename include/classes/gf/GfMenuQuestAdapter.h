#ifndef CLASSES_GF_GFMENUQUESTADAPTER_H
#define CLASSES_GF_GFMENUQUESTADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuReferenceQuest.h"
#include "gf/QuestID.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuQuestList; }

namespace gf {
// table 0x7100B5D880; one of a quest's parameters (create's type): a text, a number, an icon, a task's log, a
// reward's text or whether to show
class GfMenuQuestAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    class ReferenceConverter;
    // inline: 3.0.1 has no copy of it
    GfMenuQuestAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_questId(), m_type(0), m_kind(0), m_created(false), m_rewardText(),
          m_converter(nullptr), m_reference() {}
    virtual ~GfMenuQuestAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuQuestAdapter* create(unsigned int handle, QuestID id, unsigned int type, bool changed);
    static GfMenuQuestAdapter* createFromReference(unsigned int handle,
                                                   mm::mtl::IntrusivePtr<GfMenuReferenceQuest> reference,
                                                   unsigned int type, bool changed);
    static GfMenuQuestAdapter* createFromList(unsigned int handle, GfMenuQuestList* list, int index,
                                              unsigned int type, bool changed);
    bool getParamText(QuestID id, unsigned int type, const char** text);
    bool getParamNumber(QuestID id, unsigned int type, unsigned int& number, unsigned int& max);
    bool getParamIcon(QuestID id, unsigned int type, unsigned int& icon);
    bool getParamRewardText(QuestID id, unsigned int type, mm::mtl::FixStr<64>& text);
    bool getParamDisp(QuestID id, unsigned int type);
    // takes the quest by value: create's stores extract its high half from the 64-bit argument register (ubfx x),
    // which only a by-value copy gives. The name is not the original's
    void setQuestID(QuestID id) { m_questId = id; }
    QuestID m_questId;
    unsigned int m_type;  // create's: which parameter
    // what update shows it as (s_paramKinds' entry for m_type): 0 text, 1 number, 2 icon, 3 a task's log, 4 a
    // reward's text, 5 disp; the names are not the original's
    unsigned int m_kind;
    bool m_created;  // create sets it, update clears it; the name is not the original's
    mm::mtl::FixStr<64> m_rewardText;  // what update last showed for a reward's text; the name is not the original's
    IConverter* m_converter;  // update takes the quest from it; owned
    // the task the task parameters look at (update takes it from the number); the names are not the original's
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_reference;
    unsigned int m_task;
};
}  // namespace gf

#endif
