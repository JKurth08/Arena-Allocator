#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// I like using these for simplicity
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define ALIGN_BY        (sizeof(void*))
#define ALIGN_UP(n, p)  (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p) - 1)))
#define MIN(a, b)       ((a) < (b) ? (a) : (b))

typedef struct {
    u64 capacity;

    u64 pos;
} memory_arena;

void*   arenaCreate(u64 capacity);
void    arenaDestroy(memory_arena* arena);
void*   arenaPush(memory_arena* arena, u64 size);
void    arenaPop(memory_arena* arena, u64 size);
void    arenaRewindToPos(memory_arena* arena, u64 pos);
void    arenaClear(memory_arena* arena);
