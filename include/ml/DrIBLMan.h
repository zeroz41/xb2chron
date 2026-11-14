#ifndef ML_DRIBLMAN_H
#define ML_DRIBLMAN_H

namespace ml {
// one per view in DrMan (0x140); its update is in the DrEnvironmentAnim unit. Only what DrMan calls is declared.
class DrIBLMan {
public:
    void update();
};
}  // namespace ml

#endif
