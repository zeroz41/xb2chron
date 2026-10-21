#ifndef CLASSES_GF_GFMENUEXCTASKADAPTER_H
#define CLASSES_GF_GFMENUEXCTASKADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BCB8
class GfMenuExcTaskAdapter {
public:
    class ListConverter;
    virtual ~GfMenuExcTaskAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
