#ifndef ML_DRENVIRONMENTMAN_H
#define ML_DRENVIRONMENTMAN_H

namespace ml {
class DrEnvColiMan;

// one per view; DrMan's constructor makes it (0x70 bytes) from the view's DrLightMan and DrFogMan
class DrEnvironmentMan {
public:
    unsigned char pad_0[0x18];
    DrEnvColiMan* m_envColiMan;  // ScnRenderDrEnvColi's (the name is not the original's)
};
}  // namespace ml

#endif
