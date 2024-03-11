#ifndef __MEMORYPOOL__H__
#define __MEMORYPOOL__H__


#include <climits>
#include <cstddef>

namespace MPL {
    
template <typename T, size_t BlockSize = 4096>
class MemoryPool {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef const T*        const_pointer;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;

public:
    MemoryPool() noexcept;
    MemoryPool(const MemoryPool& memoryPool) noexcept;
    MemoryPool(MemoryPool&& memoryPool) noexcept;
    template <class U> MemoryPool(const MemoryPool<U>& memoryPool) noexcept;

    ~MemoryPool() noexcept;

    MemoryPool& operator=(const MemoryPool& memoryPool) = delete;
    MemoryPool& operator=(MemoryPool&& memoryPool) noexcept;

public:
    pointer address(reference value) const noexcept;
    const_pointer address(const_reference value) const noexcept;

    // Can only allocate 1 block at a time.
    // pointer allocate(size_type n = 1);   
    // void deallocate(pointer p, size_type n = 1);
    pointer allocate();
    void deallocate(pointer p);

    size_type max_size() const noexcept;

    template <class U, class... Args>
    void construct(U* p, Args&&... args);

    template <class U>
    void destroy(U* p);


    template <class ...Args>
    pointer new_element(Args&&... args);

    void delete_element(pointer p);

private:
    union Slot_ {
        value_type element;
        Slot_ *next;
    };

    typedef char* data_pointer_;
    typedef Slot_ slot_type_;
    typedef Slot_* slot_pointer_;

    slot_pointer_ current_block_;    // current block is the first block being used
    slot_pointer_ current_slot_;     // current slot is the first slot not being used
    slot_pointer_ last_slot_;        // last slot to be used
    slot_pointer_ free_slots_;       // freed slots can be used again

    size_type pad_pointer(data_pointer_ p, size_type align) const noexcept;  // align p to align
    void allocate_block();           // allocate a new block to memory pool

    static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
};

}  // namespace MPL


#endif  //!__MEMORYPOOL__H__