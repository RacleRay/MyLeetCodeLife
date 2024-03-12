#ifndef __MEMORYPOOL__H__
#define __MEMORYPOOL__H__


#include <climits>
#include <cstddef>
#include <cstdint>
#include <utility>

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
    MemoryPool() noexcept = default;

    ~MemoryPool() noexcept;

    MemoryPool(const MemoryPool& memoryPool) noexcept = delete;
    MemoryPool& operator=(const MemoryPool& memoryPool) = delete;
    template <class U> 
    MemoryPool(const MemoryPool<U>& memoryPool) noexcept = delete;

    MemoryPool(MemoryPool&& memoryPool) noexcept;
    MemoryPool& operator=(MemoryPool&& memoryPool) noexcept;

public:
    pointer address(reference value) const noexcept;
    const_pointer address(const_reference value) const noexcept;

    // Can only allocate 1 block at a time.
    // pointer allocate(size_type n = 1, const_pointer hint = 0);   
    // void deallocate(pointer p, size_type n = 1);
    pointer allocate(size_type n = 1, const_pointer hint = 0);
    void deallocate(pointer p, size_type n = 1);

    size_type max_size() const noexcept;

    template <class U, class... Args>
    void construct(U* p, Args&&... args);

    template <class U>
    void destroy(U* p);


    template <class ...Args>
    pointer new_element(Args&&... args);

    void delete_element(pointer p);

    template <typename U> 
    struct rebind {
        typedef MemoryPool<U> other;
    };

private:
    union Slot_ {
        value_type element;
        Slot_ *next;
    };

    typedef char* data_pointer_;
    typedef Slot_ slot_type_;
    typedef Slot_* slot_pointer_;

    slot_pointer_ current_block_{nullptr};    // current block is the first block being used
    slot_pointer_ current_slot_{nullptr};     // current slot is the first slot not being used
    slot_pointer_ last_slot_{nullptr};        // last slot to be used
    slot_pointer_ free_slots_{nullptr};       // freed slots can be used again

    size_type num_blocks_{0};

    size_type pad_pointer(data_pointer_ p, size_type align) const noexcept;  // align p to align
    void allocate_block();           // allocate a new block to memory pool

    static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
};


//=================================================================================
// constructor and destructor
//=================================================================================

// template<typename T, size_t BlockSize>
// MemoryPool<T, BlockSize>::MemoryPool(const MemoryPool& memoryPool) noexcept
// {
//     MemoryPool();   
// }

// template<typename T, size_t BlockSize>
// template <class U>
// MemoryPool<T, BlockSize>::MemoryPool(const MemoryPool<U>& memoryPool) noexcept
// {
//     MemoryPool();   
// }

template<typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::MemoryPool(MemoryPool&& memoryPool) noexcept
{
    current_block_ = memoryPool.current_block_;
    current_slot_ = memoryPool.current_slot_;
    last_slot_ = memoryPool.last_slot_;
    free_slots_ = memoryPool.free_slots_;
    num_blocks_ = memoryPool.num_blocks_;

    memoryPool.current_block_ = nullptr;
    memoryPool.current_slot_ = nullptr;
    memoryPool.last_slot_ = nullptr;
    memoryPool.free_slots_ = nullptr;
    memoryPool.num_blocks_ = 0;
}

template<typename T, size_t BlockSize>
MemoryPool<T, BlockSize>& MemoryPool<T, BlockSize>::operator=(MemoryPool&& memoryPool) noexcept
{
    if (this != &memoryPool) {
        MemoryPool<T, BlockSize>(std::move(memoryPool));
    }
    return *this;
}

template<typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::~MemoryPool() noexcept {
    slot_pointer_ curr = current_block_;
    while (curr != nullptr) {
        slot_pointer_ next = curr->next;
        // void * is no need to invoke destructor, only free memory.
        operator delete(reinterpret_cast<void *>(curr));
        curr = next;
    }

    current_block_ = nullptr;
    current_slot_ = nullptr;
    last_slot_ = nullptr;
    free_slots_ = nullptr;
    num_blocks_ = 0;
}


//=================================================================================
// member functions
//=================================================================================

template<typename T, size_t BlockSize>
typename MemoryPool<T, BlockSize>::pointer 
MemoryPool<T, BlockSize>::address(reference value) const noexcept
{
    return &value;    
}

template<typename T, size_t BlockSize>
typename MemoryPool<T, BlockSize>::const_pointer 
MemoryPool<T, BlockSize>::address(const_reference value) const noexcept
{
    return &value;    
}


// | memory pool of a fixed slot size |
// | ----------------------------- |
// | ptr to next block | slot | slots... |
// | ptr to next block | slot | slots... |
// | ptr to next block | slot | slots... |
// 
// | list of free slot ptr to used slot  |
template<typename T, size_t BlockSize>
void
MemoryPool<T, BlockSize>::allocate_block() {
    data_pointer_ new_block = reinterpret_cast<data_pointer_>(operator new(BlockSize));

    // ptr to next block
    reinterpret_cast<slot_pointer_>(new_block)->next = current_block_;
    current_block_ = reinterpret_cast<slot_pointer_>(new_block);
    num_blocks_++;

    // ptr to slot
    data_pointer_ body = new_block + sizeof(slot_pointer_);
    size_type body_padding = pad_pointer(body, alignof(slot_pointer_));

    current_slot_ = reinterpret_cast<slot_pointer_>(body + body_padding);
    last_slot_ = reinterpret_cast<slot_pointer_>(new_block + BlockSize - sizeof(slot_type_) + 1);
}


template<typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::pointer
MemoryPool<T, BlockSize>::allocate(size_type n, const_pointer hint) {
    if (free_slots_ != nullptr) {
        pointer result = reinterpret_cast<pointer>(free_slots_);
        free_slots_ = free_slots_->next;
        return result;
    }
    else {
        if (current_slot_ >= last_slot_) {
            allocate_block();
        }
        return reinterpret_cast<pointer>(current_slot_++);
    }
}

template<typename T, size_t BlockSize>
void MemoryPool<T, BlockSize>::deallocate(pointer p, size_type n) {
    if (p != nullptr) {
        reinterpret_cast<slot_pointer_>(p)->next = free_slots_;
        free_slots_ = reinterpret_cast<slot_pointer_>(p);
    }
}


template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::size_type
MemoryPool<T, BlockSize>::max_size() const noexcept {
    return num_blocks_;
}


template <typename T, size_t BlockSize>
template <class U, class... Args>
void MemoryPool<T, BlockSize>::construct(U* p, Args&&... args) {
    new (p) U(std::forward<Args>(args)...);
}

template <typename T, size_t BlockSize>
template <class U>
void MemoryPool<T, BlockSize>::destroy(U* p) {
    p->~U();
}


template <typename T, size_t BlockSize>
template <class ...Args>
typename MemoryPool<T, BlockSize>::pointer
MemoryPool<T, BlockSize>::new_element(Args&&... args) {
    pointer p = allocate();
    construct(p, std::forward<Args>(args)...);
    return p;
}


template <typename T, size_t BlockSize>
void MemoryPool<T, BlockSize>::delete_element(pointer p) {
    if (p != nullptr) {
        destroy(p);
        deallocate(p);
    }
}


template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::size_type
MemoryPool<T, BlockSize>::pad_pointer(data_pointer_ p, size_type align)
const noexcept
{
  uintptr_t result = reinterpret_cast<uintptr_t>(p);
  return ((align - result) % align);
}

}  // namespace MPL

// #include "MemoryPool.inl"


#endif  //!__MEMORYPOOL__H__