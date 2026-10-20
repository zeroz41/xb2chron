#ifndef CLASSES_WND_WINDBLENDER_H
#define CLASSES_WND_WINDBLENDER_H

namespace wnd { class UpdateInfo; }

namespace wnd {
// table 0x7100B81850
class WindBlender {
public:
    virtual void update(wnd::UpdateInfo const&);  // slot 0
};
}  // namespace wnd

#endif
