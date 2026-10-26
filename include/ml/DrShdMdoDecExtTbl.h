#ifndef ML_DRSHDMDODECEXTTBL_H
#define ML_DRSHDMDODECEXTTBL_H

namespace ml {
// A material shader's extension table. Only what DrMdoSetup calls is declared.
class DrShdMdoDecExtTbl {
public:
    unsigned int getValGlobalParam(int idx);
};
}  // namespace ml

#endif
