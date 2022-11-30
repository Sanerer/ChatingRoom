#include <type_traits>

class MemoryHandler {
public:
    MemoryHandler();

    MemoryHandler(const MemoryHandler&) = delete;
    MemoryHandler& operator=(const MemoryHandler&) = delete;

    void* Allocate(std::size_t size);
    void Deallocate(void* pointer);

private:
    std::aligned_storage<1024> storage_;
    bool is_use_;
};