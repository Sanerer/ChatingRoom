#include "memory_handler.h"
#include <vcruntime_new.h>

MemoryHandler::MemoryHandler() : is_use_(false) {}

void* MemoryHandler::Allocate(std::size_t size) {
    if (!is_use_ && size < sizeof(storage_)) {
        is_use_ = true;
        return &storage_;
    }

    return ::operator new(size);
}

void MemoryHandler::Deallocate(void* pointer) {
    if (pointer == &storage_) {
        is_use_ = false;
        return;
    }

    ::operator delete(pointer);
}