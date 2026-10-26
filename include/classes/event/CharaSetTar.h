#ifndef CLASSES_EVENT_CHARASETTAR_H
#define CLASSES_EVENT_CHARASETTAR_H

#include "classes/event/ICmd.h"
#include "mm/Vec2.h"

namespace event {
// table 0x7100B3E4F8
class CharaSetTar : public ::event::ICmd {
public:
    virtual ~CharaSetTar() {}  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    static const mm::Vec2 LENS_LIMIT;  // calcLensUV's bounds
    static const mm::Vec2 JOY_LIMIT;
};
}  // namespace event

#endif
