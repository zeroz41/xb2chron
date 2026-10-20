#ifndef CLASSES_WND_GLOBALWIND_H
#define CLASSES_WND_GLOBALWIND_H

namespace wnd { class UpdateInfo; }

namespace wnd {
// table 0x7100B81800
class GlobalWind {
public:
    virtual void update(wnd::UpdateInfo const&);  // slot 0
};
}  // namespace wnd

#endif
