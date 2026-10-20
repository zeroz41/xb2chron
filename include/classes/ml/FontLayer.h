#ifndef CLASSES_ML_FONTLAYER_H
#define CLASSES_ML_FONTLAYER_H

namespace ml {
// table 0x7100B763C0
class FontLayer {
public:
    virtual ~FontLayer();  // slot 0
    unsigned char pad_8[0x8];  // fields: size from its derived classes
};
}  // namespace ml

#endif
