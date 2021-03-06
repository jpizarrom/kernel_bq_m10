#pragma once
/// \file
/// \brief Mapper is the main object of this module.

/**
 * Usage:
 * See test project.
 *
 */

#include "yl_mmu_common.h"
#include "yl_mmu_mapper_public_class.h"
#include "yl_mmu_rcache.h"

#ifdef __cplusplus
extern "C" {
#endif



/********************* Data Sturcture *****************/

// Though we can use this way, but it's inconvenient for debugging
//typedef struct Mapper_ MapperRec, *Mapper;


/********************* Public Function Declarations *****************/
// page_space0 is just a convenient field to store un-aligned page_space
void 
Mapper_init( Mapper m, 
             const g3d_va_t g3d_va_base,    ///< Starting address for our own G3dVa
             const G3dMemory page_mem,            ///< hw see the physical, and address in lvl.1 table is physical.
             const void * meta_space,             ///< virtual
             const int cache_enable );            ///< The 4k cache

void 
Mapper_init_mirror( Mapper m, 
             const g3d_va_t g3d_va_base,    ///< Starting address for our own G3dVa
             const G3dMemory page_mem,            ///< hw see the physical, and address in lvl.1 table is physical.
             const void * meta_space,             ///< virtual
             const G3dMemory page_mem_mirror,     ///< mirror means va to va
             const int cache_enable );            ///< The 4k cache

void Mapper_uninit( Mapper m );

void 
Mapper_free_all_memory( Mapper m );

/**
 The priority:
 A). Section Mapping ( Make HW faster )
 B). Small page packing ( Use TLB wisely, and save some addressing space )
 C). Find free but potentially space (around 2* size ~  4*size) ( Fast )
 D). Search for just-fit page (around size ~ 2*size) 

 Note that (A) & (C) will facilitate (B)
 Note that (D) is the final way to get suitable memory.
*/

/// g3d_va = map( va, size )
g3d_va_t
Mapper_map( Mapper m, 
            const va_t va, 
            const size_t size, 
            const YL_BOOL could_be_section,
            const unsigned int flag);

/// unmap( g3d_va )
void Mapper_unmap(Mapper m, g3d_va_t g3d_va, size_t size);

/******** Helpers ********/

/// Helper. Get the unaligned page table passed in.
void * Mapper_get_page_space0( Mapper m )        __attribute__((const));
/// Helper. Get the aligned page table passed in.
void * Mapper_get_page_space( Mapper m )        __attribute__((const));
/// Helper. Get meta table passed in.
void * Mapper_get_meta_space( Mapper m )        __attribute__((const));
/// Helper. Map a g3d_va address to pa by lookup the page table.
pa_t Mapper_g3d_va_to_pa(Mapper m, g3d_va_t g3d_va);

#if MMU_MIRROR
pa_t Mapper_g3d_va_to_g3d_va(Mapper m, g3d_va_t g3d_va);
#endif

#if MMU_LOOKBACK_VA 
va_t Mapper_g3d_va_to_va(Mapper m, g3d_va_t g3d_va);
#endif

/// Debug. Get the number of Rcache entries used.
static INLINE size_t Mapper_get_used_cache( Mapper m )        __attribute__((const,always_inline));


/* Implementation */
static INLINE size_t 
Mapper_get_used_cache( Mapper m )
{
    return Rcache_get_use_count( & m->Rcache );
}

/// For PATTERN
g3d_va_t Mapper_map_given_pa(Mapper m, va_t va, pa_t pa, size_t size, YL_BOOL could_be_section, unsigned int flag);

#ifdef __cplusplus
}
#endif
