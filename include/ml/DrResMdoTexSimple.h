#ifndef ML_DRRESMDOTEXSIMPLE_H
#define ML_DRRESMDOTEXSIMPLE_H

namespace ml {
// A simple texture resource; DrMdoTexSimpleMan keeps them in lists. Only what DrMdoTexSimpleMan uses is recovered.
class DrResMdoTexSimple {
public:
    ~DrResMdoTexSimple();

    unsigned char pad_0[0x8];
    DrResMdoTexSimple* m_pNext;  // 0x8: DrMdoTexSimpleMan's list link (the name is not the original's)
};
}  // namespace ml

#endif
