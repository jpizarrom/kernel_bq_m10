#pragma once
/// \file
/// \brief virtual to physical functions.  Need to change when port to kernel mode module.

#include "yl_mmu_common.h"
#include "yl_mmu_mapper.h"

#ifdef linux 
#if !defined(linux_user_mode) 
pa_t va_to_pa_after_mmap( va_t address );
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif


/// Should be replace by __pa( )
static INLINE pa_t va_to_pa( Mapper m, va_t va ) __attribute__((always_inline));

/// Should be replace by __va( )
static INLINE va_t pa_to_va( Mapper m, pa_t pa ) __attribute__((always_inline));

static INLINE pa_t 
va_to_pa( Mapper m, va_t va )
{
    if ( m->is_pa_given )
    {
        return m->GIVEN_PA_pa_base + (va - m->GIVEN_PA_va_base);
    }
    else
    {
#if defined(linux) && !defined(linux_user_mode) && (MMU_LOOKBACK_VA)
        return va_to_pa_after_mmap(va);
        // return (pa_t)(((va >> 10) & 0x3ff000) | (va & 0xfff) | ((va << 10) & 0xffc00000)) ;
#else
        return (pa_t)va;
#endif
    }
}

/// For comparison in rcache.
/// Should be real pa in real case. 
/// Though va will do, too.
static INLINE pa_t 
va_to_pa_for_rcache( va_t va )
{
    return (pa_t)va;
}

/// the base is missing, so the original va can't be acquired.
static INLINE va_t
pa_to_va( Mapper m, pa_t pa )
{
    //if ( m->is_pa_given )
    //{
    //    return m->GIVEN_PA_va_base + (pa - m->GIVEN_PA_pa_base);
    //}
    //else
    //{
#if defined(linux) && !defined(linux_user_mode) && (MMU_LOOKBACK_VA)
        YL_MMU_ASSERT(0);
        return 0;
        // return (va_t)(((pa >> 10) & 0x3ff000) | (pa & 0xfff) | ((pa << 10) & 0xffc00000)) ;
#else
        return (va_t)pa;
#endif        
    //}
}



#ifdef __cplusplus
}
#endif
