**************************************
*                                    *
*  Support amx load from .so x86_64  *
*                                    *
**************************************

Set: amx/amx.c and amx/amx.h support for offset address for native functions, marked as D:C1
Reason: AMX_FUNCSTUB->address size is 4, but pointer size in x86_64 is 8
Warning: amx_Register from .so execute is nominal once, but without .so work as early
Uses: define PAM_X86_64_DL for compiler, copy amx.c and amx.h to local amx folder

Into amx.h
>241
#if !defined SUPPORT_CELL64_IN_DYNAMIC_LIBRARY && defined PAM_X86_64_DL /* D:C1 */
  /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
  #if PAWN_CELL_SIZE==64 && (defined _I64_MAX || defined INT64_MAX || defined HAVE_I64) /* if cell size 64 */
    #define SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* if defined PAM_X86_64_DL in command defines, then support code activated */
  #endif
#endif

>310
  #ifdef SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* D:C1 */
    /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
    ucell offset; /* offset for memory pointer of native functions */
  #endif /* SUPPORT_CELL64_IN_DYNAMIC_LIBRARY */

>503
#ifdef SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* D:C1 */
  /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
  ucell support_x86_64_so_get_offset(const AMX_NATIVE_INFO *nativelist, int number); /* calculate offset */
#endif /* SUPPORT_CELL64_IN_DYNAMIC_LIBRARY */

Into amx.c
>558
#ifdef SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* D:C1 */
 /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
 if(amx->offset == 0) /* if amx_Register called from not .so */
#endif /* SUPPORT_CELL64_IN_DYNAMIC_LIBRARY */

>590
  #ifdef SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* D:C1 */
    /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
    ucell tmpfunc = (ucell)f + amx->offset;
    memcpy(&f, &tmpfunc, sizeof(ucell)); /* set absolute address */
    //(ucell)f = (ucell)f + amx->offset; /* set absolute address */ /* error! */
  #endif /* SUPPORT_CELL64_IN_DYNAMIC_LIBRARY */

>1357
  #ifdef SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* D:C1 */
    /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
    amx->offset = 0; /* changes in amx_Register & uses amx_Callback */
  #endif /* SUPPORT_CELL64_IN_DYNAMIC_LIBRARY */

>1913
  #ifdef SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* D:C1 */
    /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
    amx->offset = support_x86_64_so_get_offset(list, number);
  #endif /* SUPPORT_CELL64_IN_DYNAMIC_LIBRARY */

>1932
       #ifdef SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* D:C1 */
        /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
        func->address=(uint32_t)((ucell)funcptr-amx->offset); /* set retive address about offset */
       #else /* Original */
        func->address=(ucell)funcptr;
       #endif /* SUPPORT_CELL64_IN_DYNAMIC_LIBRARY */

>3833
#ifdef SUPPORT_CELL64_IN_DYNAMIC_LIBRARY /* D:C1 */
  /* support -fPIC x86_64 amx from .so (1 amx_Register only) */
  ucell support_x86_64_so_get_offset(const AMX_NATIVE_INFO *nativelist, int number){ /* calculate offset */
    AMX_NATIVE_INFO *infoptr = nativelist;
    ucell min_offset = UINT64_MAX;
    if(nativelist == NULL) return 0;
    while((ucell)(infoptr->func)!=NULL && (number==-1 || number-->0)){ /* search minimum from addresses, it is offset */
      if((ucell)(infoptr->func) < min_offset)
        min_offset = (ucell)(infoptr->func);
      infoptr++;
    }
    return (min_offset > UINT32_MAX) ? min_offset : 0; /* return 0, if min_offset include in 32bit, it's not .so */
  }
#endif /* SUPPORT_CELL64_IN_DYNAMIC_LIBRARY */
