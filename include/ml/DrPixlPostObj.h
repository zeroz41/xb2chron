#ifndef ML_DRPIXLPOSTOBJ_H
#define ML_DRPIXLPOSTOBJ_H

namespace ml { class DrMan; class DrPixlMan; class DrPixlPostMan; }

namespace ml {
// the post-process objects' base: the constructor keeps its three managers (the field names are not the original's)
class DrPixlPostObj {
public:
    DrPixlPostObj(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);

    DrMan* m_drMan;  // 0x0
    DrPixlMan* m_pixlMan;  // 0x8
    DrPixlPostMan* m_postMan;  // 0x10
};
}  // namespace ml

#endif
