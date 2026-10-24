#ifndef ML_DRSHDCUBECAPFILTER_H
#define ML_DRSHDCUBECAPFILTER_H

namespace ml {
class DrMan;

// The constructor only stores the renderer; other fields and members are not declared yet.
class DrShdCubeCapFilter {
public:
    DrShdCubeCapFilter(DrMan* drMan);
    ~DrShdCubeCapFilter();  // empty; its owners' destructors call it

    DrMan* m_pDrMan;  // 0x0 (the name is not the original's)
};

}  // namespace ml

#endif
