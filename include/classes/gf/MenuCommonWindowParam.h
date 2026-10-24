#ifndef CLASSES_GF_MENUCOMMONWINDOWPARAM_H
#define CLASSES_GF_MENUCOMMONWINDOWPARAM_H

namespace gf {
// the parameters of a common (message) window, GfMenuManager::openCommonWindow's; 0x50 bytes
// (GfPlayComMenuCommonFromParam::create copies them whole). Its fields are not known yet.
class MenuCommonWindowParam {
public:
    unsigned char pad_0[0x50];
};
}  // namespace gf

#endif
