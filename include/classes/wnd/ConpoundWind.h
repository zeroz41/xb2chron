#ifndef CLASSES_WND_CONPOUNDWIND_H
#define CLASSES_WND_CONPOUNDWIND_H

namespace wnd { class UpdateInfo; }

namespace wnd {
// table 0x7100B81868
class ConpoundWind {
public:
    virtual void update(wnd::UpdateInfo const&);  // slot 0
};
}  // namespace wnd

#endif
