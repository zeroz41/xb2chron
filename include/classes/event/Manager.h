#ifndef CLASSES_EVENT_MANAGER_H
#define CLASSES_EVENT_MANAGER_H

#include "classes/ml/IWorkBackground.h"
#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace event { class Manager; }
namespace ml { class EventView; }

namespace event {
// table 0x7100B3E2F8
class Manager : public ::mm::mtl::PtrSingleton< ::event::Manager>, public ::ml::IWorkEvent, public ::ml::IWorkBackground {
public:
    virtual ~Manager();  // slot 0
    virtual void OnKeyDown(ml::EventView*);  // slot 2
    virtual void bkgHomeMenu(bool);  // slot 3
    bool end();  // returns whether an event was playing
    bool isPlaying() const { return m_playing; }

    unsigned int m_playing : 1;  // end and stop act only while it is set; GfGameTalk::isPlaying returns it
    unsigned int pad_18_1 : 31;  // the rest of the word, which isPlaying loads whole
};
}  // namespace event

#endif
