#ifndef CLASSES_ML_IDRDRAWCALLBACK_H
#define CLASSES_ML_IDRDRAWCALLBACK_H

namespace ml { class IDrDrawWorkInfo; }

namespace ml {
// table 0x7100B7F968
class IDrDrawCallback {
public:
    virtual ~IDrDrawCallback();  // slot 0
    virtual void begin() {}  // slot 2
    virtual void end() {}  // slot 3
    virtual void apply(ml::IDrDrawWorkInfo const*) {}  // slot 4
    virtual void opacityRender(ml::IDrDrawWorkInfo const*) {}  // slot 5
    virtual void alphaRender(ml::IDrDrawWorkInfo const*) {}  // slot 6
    virtual void lastRender(ml::IDrDrawWorkInfo const*) {}  // slot 7
    virtual void blurRender(ml::IDrDrawWorkInfo const*) {}  // slot 8
    virtual void finalRender(ml::IDrDrawWorkInfo const*) {}  // slot 9
};
}  // namespace ml

#endif
