#ifndef ML_SCNRENDERDRENVCOLI_H
#define ML_SCNRENDERDRENVCOLI_H

namespace mm { class Vec3; }

namespace ml {
// a test of a position against a view's environment collision (fw::RenderParam::isRoom and getWindIndex build one
// on the stack; 8 bytes; the parameter names are not the original's)
class ScnRenderDrEnvColi {
public:
    explicit ScnRenderDrEnvColi(int view);
    ~ScnRenderDrEnvColi();
    // whether pos (within range) hits the environment collision; isRoom and getWindId then read what it hit
    bool testEnvColi(const mm::Vec3& pos, float range);
    bool isRoom() const;
    int getWindId() const;

    unsigned char pad_0[0x8];
};
}  // namespace ml

#endif
