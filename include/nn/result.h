#ifndef NN_RESULT_H
#define NN_RESULT_H

namespace nn {

// NintendoSDK's result code: zero is success
class Result {
public:
    bool IsSuccess() const { return m_value == 0; }
    bool IsFailure() const { return !IsSuccess(); }
    unsigned int m_value;
};

}  // namespace nn

#endif
