
/*
 * dlfunctions.c
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

#include <weirdutils/dlfunctions.h>
#include <weirdutils/configuration.h>
#include <stdio.h>

dlhandle_t dlhandlex(dlcstr_t modName_, dword_t modeFlag_) {
#if defined(IDT_WEIRD_UTILS_UNIX)
    return dlopen(modName_, modeFlag_);

#elif defined(IDT_WEIRD_UTILS_WIN32)
    if (!modeFlag_)
        return LoadLibrary(modName_);
    
    return LoadPackagedLibrary(modName_ modeFlag_);
#endif
}


dlhandle_t dlhandle(dlcstr_t modName_) {
#if defined(IDT_WEIRD_UTILS_UNIX)
    return dlopen(modName_, RTLD_LAZY);

#elif defined(IDT_WEIRD_UTILS_WIN32)
    return LoadLibrary(modName_);
#endif
}


dlptr_t dlsymbol(dlhandle_t mod_, dlcstr_t sym_) {
#if defined(IDT_WEIRD_UTILS_UNIX)
    return dlsym(mod_, sym_);

#elif defined(IDT_WEIRD_UTILS_WIN32)
    return GetProcAddress(mod_, sym_);
#endif
}


#if defined(IDT_WEIRD_UTILS_WIN32)
dlcstr_t dlerror(void) {
    return GetLastError();
}
#endif



int dlfree(dlhandle_t mod_) {
    if (mod_) {
#if defined(IDT_WEIRD_UTILS_UNIX)
        return dlclose(mod_);
    
#elif defined(IDT_WEIRD_UTILS_WIN32)
        if (!FreeLibrary(mod_))
            return -1;
        else return 0;
#endif
    }
    return -1;
}
