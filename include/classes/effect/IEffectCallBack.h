#ifndef CLASSES_EFFECT_IEFFECTCALLBACK_H
#define CLASSES_EFFECT_IEFFECTCALLBACK_H

namespace mm { class Mat44; }

namespace effect {

// what the effect system reads a caster's model through (SystemManager::es_set_param_cas and
// ptlib::renderer::getFramePos take one). fw::EffectCasterSend is the one the game passes: EffectManager hands
// its sends on with no pointer adjustment, so this is its primary base. The slots are fw::EffectCasterSend's
// (table 0x7100B413D0); that they are declared here, and their names here, are inferred.
class IEffectCallBack {
public:
    virtual ~IEffectCallBack() {}  // slot 0
    virtual void* getMdl() = 0;  // slot 2
    virtual const char* getStateName() = 0;  // slot 3
    virtual void* getBindData(unsigned int& size) = 0;  // slot 4
    virtual float getMdlFrame() = 0;  // slot 5
    virtual float getMdlScl() = 0;  // slot 6
    virtual bool getMdlMat(mm::Mat44&) = 0;  // slot 7
    virtual bool getEfpMat(mm::Mat44&, char const*) = 0;  // slot 8
};

}  // namespace effect

#endif
