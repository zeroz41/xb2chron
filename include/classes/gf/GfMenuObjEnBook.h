#ifndef CLASSES_GF_GFMENUOBJENBOOK_H
#define CLASSES_GF_GFMENUOBJENBOOK_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf { class GfMenuIDList; class GfMenuModelView; class GfMenuMsgList; }
namespace ui { class UICtrlCursorSelect; class UISelectObjList; }

namespace gf {
// table 0x7100B61DD8
class GfMenuObjEnBook : public ::gf::GfMenuObject {
public:
    class DetailListener;
    class EnListListener;
    class FamilySelListener;
    class GenusSelListener;
    class IndexListener;
    class LocationSelListener;
    class MainListener;
    class TopListener;
    GfMenuObjEnBook(unsigned int handle);
    virtual ~GfMenuObjEnBook();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    void setupFamilyMsgList();
    void refreshFamilyList();
    void setupGenusMsgList();
    void refreshGenusMsgList();
    void setupEnBookIDList();
    void refreshEnBookList();
    bool seqWaitLoading();
    bool seqStartTop();
    bool seqDeleteEnmey();
    bool seqCreateEnmey();
    bool seqFadeOutEnmey();

    // The constructor zeroes 0x24..0x8C; the destructor releases 0x30..0x78 (last to first).
    // setupEnBookIDList: 0 lists every enemy of the enemy book table, 1 those of m_family and m_genus (the names
    // are not the original's)
    int m_listMode;
    unsigned int m_family;  // 0x28 the enemy family (GfBdatRsc::getRscEnTypeFamily) listed
    unsigned int m_genus;   // 0x2C the genus name (GfBdatRsc::getRscEnGenusNAME) listed
    ui::UISelectObjList* pad_30;      // initialize creates it
    ui::UICtrlCursorSelect* pad_38;   // initialize creates it on pad_30
    GfMenuMsgList* m_familyList;      // 0x40 setupFamilyMsgList fills it (the name is not the original's)
    ui::UISelectObjList* pad_48;      // initialize creates it
    GfMenuMsgList* m_genusList;       // 0x50 (the name is not the original's)
    ui::UISelectObjList* pad_58;      // initialize creates it
    GfMenuIDList* pad_60;
    GfMenuIDList* m_enBookList;      // 0x68 setupEnBookIDList fills it (the name is not the original's)
    ui::UISelectObjList* pad_70;      // initialize creates it
    ui::UISelectObjList* pad_78;      // initialize creates it
    GfMenuModelView* m_modelView;     // 0x80 initialize creates it, finalize deletes it (the name is not the original's)
    unsigned int pad_88;
    GfMenuSequence<GfMenuObjEnBook, 8> m_seq;  // 0x90 (the name is not the original's)
    bool pad_320;
};
}  // namespace gf

#endif
