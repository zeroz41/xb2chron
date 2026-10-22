#ifndef CLASSES_UI_UIINPUTWHEEL_H
#define CLASSES_UI_UIINPUTWHEEL_H

#include "classes/ui/UIInputLayer.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace ui {
// table 0x7100B74C50
class UIInputWheel : public ::ui::UIInputLayer {
public:
    // the setup's own part follows the actions; the names are the UIO input table's columns
    // ui::UIObjFactory::setupObjectInput reads them from
    class WheelSetup : public InputSetup {
    public:
        unsigned short m_startAngle;  // "start_angle": where the selections start, in degrees
        unsigned short m_angleRange;  // "angle_range": the degrees they take
        unsigned char m_selectDir;    // "select_dir" (the constructor does not copy it)
    };

    UIInputWheel(unsigned int id, unsigned int handle, const WheelSetup& setup)
        : UIInputLayer(id, handle, setup), m_startAngle(setup.m_startAngle), m_angleRange(setup.m_angleRange),
          m_selectDir(0) {}
    virtual ~UIInputWheel();  // slot 0
    virtual EventData* getInputEventExt();  // slot 2
    virtual UIInputWheel* castUIInputWheel();  // slot 7
    virtual bool updateImpl();  // slot 9
    static UIInputWheel* create(unsigned int id, unsigned int handle, const WheelSetup& setup,
                                mm::mtl::IAllocator* allocator);

    unsigned short m_startAngle;
    unsigned short m_angleRange;
    unsigned char m_selectDir;  // the selections go the other way round; the constructor leaves it clear
};
}  // namespace ui

#endif
