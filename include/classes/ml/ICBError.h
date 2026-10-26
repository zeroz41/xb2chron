#ifndef CLASSES_ML_ICBERROR_H
#define CLASSES_ML_ICBERROR_H

namespace ml { class CERR_STRUCT; }
namespace ml { enum ERR_DECIDE : int; }

namespace ml {
// the listener of an error ErrViewer shows (1.0.0's ErrViewer::reqError takes one, ml::ICBError*): callbackError asks
// it through slot 2 whether the error is still to be shown, passing the error's handle. DevFileTh's base
// TUnk_B76D88 (table 0x7100B76D88) has the same three slots and DevFileTh::icbError returns true; they are likely
// this class
class ICBError {
public:
    virtual ~ICBError();  // slot 0
    virtual bool icbError(CERR_STRUCT* handle) = 0;  // slot 2
    virtual void icbDecide(CERR_STRUCT* handle, ERR_DECIDE decide) = 0;  // slot 3
};
}  // namespace ml

#endif
