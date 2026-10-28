#ifndef ML_DRRESMDOTEXLIST_H
#define ML_DRRESMDOTEXLIST_H

namespace ml {
// A model texture list resource; DrMdoTextureMan keeps them in a list. Only what DrMdoTextureMan uses is recovered.
class DrResMdoTexList {
public:
    ~DrResMdoTexList();
    // the texture count: the first word of the texture data
    static unsigned int calcTextureMax(const unsigned char* data);

    unsigned char pad_0[0x8];
    DrResMdoTexList* m_pNext;  // 0x8: DrMdoTextureMan's list link (the name is not the original's)
};
}  // namespace ml

#endif
