#ifndef CLASSES_UI_UIINPUTPAD_H
#define CLASSES_UI_UIINPUTPAD_H

#include "classes/ui/UIInputLayer.h"

namespace fw { struct PadData; }
namespace mm { namespace mtl { class IAllocator; }}

namespace ui {
// table 0x7100B74B70
class UIInputPad : public ::ui::UIInputLayer {
public:
    // how the pad moves the selection (12 bytes the constructor copies whole); the names are the UIO input
    // table's columns ui::UIObjFactory::setupObjectInput reads them from
    struct PadParam {
        unsigned char m_loop;  // "loop": past an end the selection comes round (with m_lineSelectLoop) on a press,
                               // or on a repeat when m_repeat is 2
        unsigned short m_repeat;  // "repeat": 0, only presses move the selection; else held buttons repeat too
        unsigned char m_shift;    // "shift": a held button moves it faster the longer it is held
        unsigned short m_padSelect;   // "pad_select": which buttons move it (1 to 9; the constructor picks them)
        unsigned short m_selectText;  // "select_text": the message the operation guide shows (getSelectTextID reads it)
        unsigned short m_keySort;     // "key_sort"
    };
    class PadSetup : public InputSetup {
    public:
        PadParam m_param;
    };

    UIInputPad(unsigned int id, unsigned int handle, const PadSetup& setup);
    virtual ~UIInputPad();  // slot 0
    // these four follow fixSelectNo (in ui_input_pointer.cpp's range, as config/XC2_301/splits.txt has it)
    virtual EventData* getInputEventExt();  // slot 2
    virtual bool hasEventExt() const;  // slot 3
    virtual void clearExt();  // slot 5
    virtual UIInputPad* castUIInputPad();  // slot 6
    virtual bool updateImpl();  // slot 9
    static UIInputPad* create(unsigned int id, unsigned int handle, const PadSetup& setup,
                              mm::mtl::IAllocator* allocator);
    void setLineSelectionMax(unsigned int max);
    void setLineSelectionMaxForce(unsigned int max);  // setLineSelectionMax without the one-line check
    void setLineSelectLoop(bool loop);
    void setPageSize(unsigned int size);
    void setHideSelect(bool hide);
    unsigned short getSelectTextID() const;  // m_param.m_selectText, 0 while m_hideSelect
    int moveSelect(const fw::PadData& pad, unsigned int step, int select);
    int fixSelectNo(int select, bool line, bool press);

    mm::mtl::FixedVector<ActionInfo, 27> m_padActions;  // the setup's actions again; the name is not the original's
    PadParam m_param;
    unsigned char pad_3D4[0x4];
    // the buttons that move the selection (UIUtil::convUIPadToFWPad's bits): by one, by a line, by a page; the
    // names are not the original's
    unsigned int m_padNext;
    unsigned int m_padPrev;
    unsigned int m_padLineNext;
    unsigned int m_padLinePrev;
    unsigned int m_padPageNext;
    unsigned int m_padPagePrev;
    unsigned int m_lineSelectionMax;  // the selections on a line, 0 for one column (setLineSelectionMax)
    unsigned int m_lineNum;           // the lines they make
    unsigned char m_lineSelectLoop;   // setLineSelectLoop
    unsigned int m_pageSize;          // setPageSize
    unsigned int m_repeatCount;       // the frames a button has been held (m_param.m_shift); the name is not the original's
    unsigned char pad_404[0x4];
    EventData m_eventExt;  // 9: the selection hit an end and stayed (m_param0 says which)
    bool m_hideSelect;     // setHideSelect; getSelectTextID gives no message while it is set
};
}  // namespace ui

#endif
