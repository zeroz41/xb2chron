#ifndef CLOUD_CLOUDOBJREDUCTION_H
#define CLOUD_CLOUDOBJREDUCTION_H

namespace cloud {
class CloudObjReduction {
public:
    // returns s_nPixelOfs (CloudMan::getPixelMem forwards to it unchanged, so it is static)
    static unsigned int getPixelMem(unsigned int& mem, unsigned int width, unsigned int height);
};
}  // namespace cloud

#endif
