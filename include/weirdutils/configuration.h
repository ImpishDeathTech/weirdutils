/*
 * configuration.h
 *
 * BSD 3-Clause License
 * 
 * Copyright (c) 2022, Christopher Stephen Rafuse
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#ifndef IDT_WEIRD_UTILS_CONFIGURATION_H
#define IDT_WEIRD_UTILS_CONFIGURATION_H

#define IDT_WEIRD_UTILS_VERSION_MAJOR 0
#define IDT_WEIRD_UTILS_VERSION_MINOR 1
#define IDT_WEIRD_UTILS_VERSION_PATCH 3


/* some definitions to make the c++ objects usable
 * from .dll or .so land
 */

typedef void* dlptr_t; // pointer type for raw data pointers produced by the dlsymbol function

// Unix Implementatioan
#if defined(__unix__)

    #if defined(__linux__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
        #define IDT_WEIRD_UTILS_UNIX
        #define IDT_WEIRD_API __attribute__((__visibility__("default")))

        #include <dlfcn.h>
        #include <stdint.h>

        /* Realocations are preformed at an implementation-dependant time 
         * 
         * @FreeBSD Manual : 
         *      Each external function reference is resolved when the function is first called.
         */
        #define DL_LAZY 0x00000001
        
        /* Realocations are preformed when the object is loaded
         * 
         * @FreeBSD Manual :
         *      All external function references are bound immediately by dlopen().
         *      RTLD_LAZY (DL_LAZY) is normally preferred, for reasons of efficiency.  However, RTLD_NOW (DL_NOW) is useful to ensure that any undefined symbols are discovered
         *      during the call to dlopen() (dlhandle()/dlhandlex()).
         */
        #define DL_NOW 0x00000002
        
        // One of the following flags may be ORed into the mode argument

        /* All symbols are not made available for realocation processing by other modules
         * 
         * @FreeBSD Manual :
         *      Symbols from this shared object and its directed acyclic graph (DAG) of needed objects will be available for resolving unde-
	  *      fined references from all other shared objects.
         */
        #define DL_LOCAL 0x00000000

        /* All symbols are made available for realocation processing by other modules
         *
         * @FreeBSD Manual :
	 *      Symbols in this shared object and its DAG of needed objects will be available for resolving undefined references only from
	 *      other objects in the same DAG.  This is the default, but it may be specified explicitly with this flag.  
         */
        #define DL_GLOBAL 0x00000100
            
        /* @FreeBSD Manual :
         *      Prevents unload of the loaded object on dlclose() (dlfree()).	
	 *      The same behaviour may be requested by -z nodelete option of the static linker ld.
         */
        #define DL_NODELETE 0x00001000

         /* @FreeBSD Manual : 
          *     Only return valid handle for the object if it is already loaded in the process address space, otherwise NULL is returned.
	  *     Other mode flags may be specified, which will be applied for promotion for the found object.
          */
        #define DL_NOLOAD 0x00000004

        typedef void*       dlhandle_t; // the module file handle
        typedef const char* dlcstr_t;   // a portable type definition of the cstring
        typedef uint32_t    dword_t;    // a portable type definition of a dword 

    #else
        #error weirdutils not implemented for this unix system
    #endif

// Windows implementation
#elif defined(_WIN32)
    #define IDT_WEIRD_UTILS_WIN32

    #include <Windows.h>

    // unix placeholders
    #define DL_LAZY     0x00000000
    #define DL_NOW      DL_LAZY
    #define DL_LOCAL    DL_LAZY
    #define DL_GLOBAL   DL_LAZY
    #define DL_NODELETE DL_LAZY
    #define DL_NOLOAD   DL_LAZY

    // Windows portable of the above
    typedef HMODULE     dlhandle_t;
    typedef LPCSTR      dlcstr_t;
    typedef DWORD       dword_t;

    #if defined(DL_EXPORT)
        #define IDT_WEIRD_API __declspec(dllexport)
    #else
        #define IDT_WEIRD_API __declspec(dllimport)
    #endif

#else
    #error weirdutils not implemented for this operating system
#endif

#endif // IDT_WEIRD_UTILS_CONFIGURATION_H
