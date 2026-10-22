#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"
#include "classes/ui/UIInputLayer.h"
#include "classes/ui/UIInputPad.h"
#include "fw/PadData.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIInputLayer.h"
#include "classes/ui/UIInputPad.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ui/UIUtil.h"

namespace ui {

UIInputPad::UIInputPad(unsigned int id, unsigned int handle, const PadSetup& setup)
    : UIInputLayer(id, handle, setup), m_padActions(setup.m_actions), m_param(setup.m_param), m_padNext(0),
      m_padPrev(0), m_lineSelectionMax(0), m_lineNum(0), m_pageSize(0), m_repeatCount(0), m_eventExt(0), m_loop(false) {
    const PadParam& param = setup.m_param;
    // the UI pad buttons that move the selection, by the setup's pad type
    int next = 0;
    int prev = 0;
    int lineNext = 0;
    int linePrev = 0;
    int pageNext = 0;
    int pagePrev = 0;
    switch (param.m_padSelect) {
    case 1:
        next = 8;
        prev = 7;
        pageNext = 9;
        pagePrev = 10;
        break;
    case 2:
        next = 9;
        prev = 10;
        break;
    case 3:
        next = 14;
        prev = 11;
        break;
    case 4:
        next = 20;
        prev = 19;
        break;
    case 5:
        next = 21;
        prev = 22;
        break;
    case 6:
        next = 9;
        prev = 10;
        lineNext = 8;
        linePrev = 7;
        break;
    case 7:
        next = 15;
        prev = 12;
        break;
    case 8:
        next = 24;
        prev = 23;
        break;
    case 9:
        next = 25;
        prev = 26;
        break;
    }
    m_padNext = UIUtil::convUIPadToFWPad(next, true);
    m_padPrev = UIUtil::convUIPadToFWPad(prev, true);
    m_padLineNext = UIUtil::convUIPadToFWPad(lineNext, true);
    m_padLinePrev = UIUtil::convUIPadToFWPad(linePrev, true);
    m_padPageNext = UIUtil::convUIPadToFWPad(pageNext, true);
    m_padPagePrev = UIUtil::convUIPadToFWPad(pagePrev, true);
    m_lineSelectLoop = param.m_loop;
}

UIInputPad::~UIInputPad() {}

UIInputPad* UIInputPad::create(unsigned int id, unsigned int handle, const PadSetup& setup,
                               mm::mtl::IAllocator* allocator) {
#line 114
    return new (allocator, 16, __FILE__, __LINE__) UIInputPad(id, handle, setup);
}

void UIInputPad::setLineSelectionMax(unsigned int max) {
    if (m_padLineNext != 0 && m_padLinePrev != 0) {
        unsigned int num = m_selectMax / max;
        if (m_selectMax % max != 0) {
            num++;
        }
        if (num > 1) {
            m_lineSelectionMax = max;
            m_lineNum = num;
        }
    }
}

// 0x7100679FC4 (setLineSelectionMax without the one-line check, 3.0.1's) is not here yet: no evidence names it

void UIInputPad::setLineSelectLoop(bool loop) {
    m_lineSelectLoop = loop;
}

void UIInputPad::setPageSize(unsigned int size) {
    if (m_padPageNext != 0 && m_padPagePrev != 0) {
        m_pageSize = size;
    }
}

void UIInputPad::setLoop(bool loop) {
    m_loop = loop;
}

// 0x710067A02C (the setup's select text unless looping, 3.0.1's) is not here yet: no evidence names it

bool UIInputPad::updateImpl() {
    if (m_selectMax == 0) {
        return false;
    }
    const fw::PadData* pad = UIUtil::getPadData();
    int select = m_select;
    unsigned int count = 0;
    bool next = false;
    if ((pad->m_down & m_padNext) != 0 || (m_param.m_repeat != 0 && (pad->m_repeat & m_padNext) != 0)) {
        next = true;
        count = m_lineSelectionMax != 0 ? m_lineSelectionMax : m_selectMax;
    } else if ((pad->m_down & m_padPrev) != 0 || (m_param.m_repeat != 0 && (pad->m_repeat & m_padPrev) != 0)) {
        count = m_lineSelectionMax != 0 ? m_lineSelectionMax : m_selectMax;
    } else if (m_lineSelectionMax != 0) {
        if ((pad->m_down & m_padLineNext) != 0 || (m_param.m_repeat != 0 && (pad->m_repeat & m_padLineNext) != 0)) {
            count = m_selectMax / m_lineSelectionMax;
        } else if ((pad->m_down & m_padLinePrev) != 0 ||
                   (m_param.m_repeat != 0 && (pad->m_repeat & m_padLinePrev) != 0)) {
            count = m_selectMax / m_lineSelectionMax;
        }
    } else if (m_pageSize != 0) {
        if ((pad->m_down & m_padPageNext) != 0 || (m_param.m_repeat != 0 && (pad->m_repeat & m_padPageNext) != 0)) {
            next = true;
            count = m_selectMax / m_pageSize + 1;
        } else if ((pad->m_down & m_padPagePrev) != 0 ||
                   (m_param.m_repeat != 0 && (pad->m_repeat & m_padPagePrev) != 0)) {
            count = m_selectMax / m_pageSize + 1;
        }
    }
    if (m_lineSelectionMax != 0) {
        count = m_lineSelectionMax;
    }
    unsigned int step = 1;
    if (m_param.m_shift && m_param.m_repeat != 0) {
        if ((pad->m_btn & m_padNext) != 0 || (pad->m_btn & m_padPrev) != 0) {
            if (m_repeatCount > 120) {
                step = 100;
            } else {
                step = m_repeatCount++ > 60 ? 10 : 1;
            }
        } else {
            m_repeatCount = 0;
        }
    }
    if (count == 0) {
        return false;
    }
    if (step >= count) {
        step = count - 1;
    }
    // the first selectable place step, 2 * step, ... away; none deselects
    int no;
    unsigned int i = step;
    bool enable = false;
    while (!enable) {
        if (i >= count) {
            return changeSelect(-1, 0);
        }
        no = moveSelect(*pad, i, select);
        enable = isEnableSelect(no);
        i += step;
    }
    if (changeSelect(no, next)) {
        return true;
    }
    return hasEventExt();
}


int UIInputPad::moveSelect(const fw::PadData& pad, unsigned int step, int select) {
    if ((pad.m_down & m_padNext) != 0 || (m_param.m_repeat != 0 && (pad.m_repeat & m_padNext) != 0)) {
        return fixSelectNo(select + step, false, (pad.m_down & m_padNext) != 0);
    }
    if ((pad.m_down & m_padPrev) != 0 || (m_param.m_repeat != 0 && (pad.m_repeat & m_padPrev) != 0)) {
        return fixSelectNo(select - step, false, (pad.m_down & m_padPrev) != 0);
    }
    if (m_lineSelectionMax != 0) {
        if ((pad.m_down & m_padLineNext) != 0 || (m_param.m_repeat != 0 && (pad.m_repeat & m_padLineNext) != 0)) {
            return fixSelectNo(select + m_lineSelectionMax * step, true, (pad.m_down & m_padLineNext) != 0);
        }
        if ((pad.m_down & m_padLinePrev) != 0 || (m_param.m_repeat != 0 && (pad.m_repeat & m_padLinePrev) != 0)) {
            return fixSelectNo(select - m_lineSelectionMax * step, true, (pad.m_down & m_padLinePrev) != 0);
        }
    } else if (m_pageSize != 0) {
        if ((pad.m_down & m_padPageNext) != 0 || (m_param.m_repeat != 0 && (pad.m_repeat & m_padPageNext) != 0)) {
            select += m_pageSize * step;
            if (select >= (int)m_selectMax) {
                select = m_selectMax - 1;
            }
            return fixSelectNo(select, false, (pad.m_down & m_padPageNext) != 0);
        }
        if ((pad.m_down & m_padPagePrev) != 0 || (m_param.m_repeat != 0 && (pad.m_repeat & m_padPagePrev) != 0)) {
            select -= m_pageSize * step;
            if (select < 0) {
                select = 0;
            }
            return fixSelectNo(select, false, (pad.m_down & m_padPagePrev) != 0);
        }
    }
    return select;
}

// fixSelectNo (0x710067A41C): not identical yet (wip/ui_input_pad.cpp: the wrapping return of a line move from
// the first line and the blocks that set the event are laid out apart from the original)

}  // namespace ui
