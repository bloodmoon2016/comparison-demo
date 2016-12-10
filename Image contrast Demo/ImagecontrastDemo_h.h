

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Oct 06 21:03:22 2016
 */
/* Compiler settings for ImagecontrastDemo.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __ImagecontrastDemo_h_h__
#define __ImagecontrastDemo_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IImagecontrastDemo_FWD_DEFINED__
#define __IImagecontrastDemo_FWD_DEFINED__
typedef interface IImagecontrastDemo IImagecontrastDemo;

#endif 	/* __IImagecontrastDemo_FWD_DEFINED__ */


#ifndef __ImagecontrastDemo_FWD_DEFINED__
#define __ImagecontrastDemo_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImagecontrastDemo ImagecontrastDemo;
#else
typedef struct ImagecontrastDemo ImagecontrastDemo;
#endif /* __cplusplus */

#endif 	/* __ImagecontrastDemo_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ImagecontrastDemo_LIBRARY_DEFINED__
#define __ImagecontrastDemo_LIBRARY_DEFINED__

/* library ImagecontrastDemo */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ImagecontrastDemo;

#ifndef __IImagecontrastDemo_DISPINTERFACE_DEFINED__
#define __IImagecontrastDemo_DISPINTERFACE_DEFINED__

/* dispinterface IImagecontrastDemo */
/* [uuid] */ 


EXTERN_C const IID DIID_IImagecontrastDemo;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("072139EB-DCE9-49BE-A510-D748DA0081F5")
    IImagecontrastDemo : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IImagecontrastDemoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IImagecontrastDemo * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IImagecontrastDemo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IImagecontrastDemo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IImagecontrastDemo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IImagecontrastDemo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IImagecontrastDemo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IImagecontrastDemo * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IImagecontrastDemoVtbl;

    interface IImagecontrastDemo
    {
        CONST_VTBL struct IImagecontrastDemoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImagecontrastDemo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IImagecontrastDemo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IImagecontrastDemo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IImagecontrastDemo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IImagecontrastDemo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IImagecontrastDemo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IImagecontrastDemo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IImagecontrastDemo_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ImagecontrastDemo;

#ifdef __cplusplus

class DECLSPEC_UUID("CD9729C6-53E9-459D-A876-96ED23ADD7CE")
ImagecontrastDemo;
#endif
#endif /* __ImagecontrastDemo_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


