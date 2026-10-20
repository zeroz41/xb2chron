#ifndef CLASSES_FW_ANIMRESASMRESOLVER_H
#define CLASSES_FW_ANIMRESASMRESOLVER_H

namespace fw {
// table 0x7100B40D70
class AnimResAsmResolver {
public:
    virtual void importBinding(char const*, unsigned int) const;  // slot 0
    virtual void restoreBinding(char const*, unsigned int) const;  // slot 1
    virtual void getSkekelton() const;  // slot 2
    virtual void getMirrorMapper() const;  // slot 3
    virtual void getSimpleMapper() const;  // slot 4
};
}  // namespace fw

#endif
