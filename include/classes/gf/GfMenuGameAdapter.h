#ifndef CLASSES_GF_GFMENUGAMEADAPTER_H
#define CLASSES_GF_GFMENUGAMEADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BE10
class GfMenuGameAdapter {
public:
    virtual ~GfMenuGameAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // the adapter it makes for a UI object (by its handle), of a type (an index into its plugin setups)
    static GfMenuGameAdapter* create(unsigned int handle, unsigned int type, bool);
};
}  // namespace gf

#endif
