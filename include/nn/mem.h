#ifndef NN_MEM_H
#define NN_MEM_H

// NintendoSDK 3.5.0's nn::mem, as far as the module imports it.
namespace nn { namespace mem {

// 0x48 bytes (ssd::SystemCorePlatform holds three, each after the 0x10-byte block it manages); its first byte
// says whether Initialize ran: the destructor finalizes only then
class StandardAllocator {
public:
    ~StandardAllocator() {
        if (m_Initialized) {
            Finalize();
        }
    }

    void Initialize(void* address, unsigned long size);
    void Finalize();
    void* Allocate(unsigned long size);
    void* Allocate(unsigned long size, unsigned long alignment);
    void Free(void* address);

private:
    bool m_Initialized;
    unsigned char pad_1[0x47];
};

}}  // namespace nn::mem

#endif
