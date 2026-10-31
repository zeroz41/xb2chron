#ifndef NN_AOC_H
#define NN_AOC_H

namespace nn { namespace aoc {

// the SDK's add-on content list: writes up to `count` installed add-on indices from `offset` into `outIndices` and
// returns how many it wrote
int ListAddOnContent(int* outIndices, int offset, int count);

}}  // namespace nn::aoc

#endif
