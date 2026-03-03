#include "Arena.h"

#define ARENA_BASE_POSITION (sizeof(memory_arena))
#define ARENA_ALIGN (sizeof(void*)) // size of void pointer for consistency 

void* arenaCreate(u64 capacity) {
    memory_arena* arena = (memory_arena*)malloc(capacity);
    arena->capacity = capacity;
    arena->pos = ARENA_BASE_POSITION;

    return arena;
}

void arenaDestroy(memory_arena* arena) {
    free(arena);
}

void arenaClear(memory_arena* arena) {
    arena->pos = ARENA_BASE_POSITION;
}

void* arenaPush(memory_arena* arena, u64 size) {
    if (!arena || size == 0) {
        return NULL;
    }
    u64 align_pos = ALIGN_UP(arena->pos, ARENA_ALIGN); // align pos up to 8 bytes (on my 64 system)
    u64 new_pos = align_pos + size;

    if (new_pos >= arena->capacity) {
        return NULL;
    }

    arena->pos = new_pos;
    u8* arena_out = (u8*)arena + align_pos; // return the pointer pointing to the START of the allocation
    return arena_out;
}

void arenaPop(memory_arena* arena, u64 size) {
    if (!arena) {
        return;
    }
    if (size == 0) {
        return; // do nothing
    }
    if (size > arena->pos - ARENA_BASE_POSITION) {
        size = 0; // we cant pop beyond range
    }
    arena->pos -= size;
}

void arenaRewindToPos(memory_arena* arena, u64 pos) {
    if (!arena) {
        return;
    }
    u64 popToPos;
    if (pos > arena->pos) { 
        popToPos = 0; 
    }
    else { 
        popToPos = arena->pos - pos; 
    }
    arenaPop(arena, popToPos);
}
