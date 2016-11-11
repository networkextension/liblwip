/**
 * @file sys.c
 * @author Ambroz Bizjak <ambrop7@gmail.com>
 * 
 * @section LICENSE
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//#include <system/BTime.h>

#include "lwip/sys.h"
#include <sys/time.h>
#include <stdarg.h>
#include <pthread.h>
u32_t sys_now (void)
{
    struct timeval tv;
    ASSERT(gettimeofday(&tv, NULL) == 0)
    long long r = ((int64_t)tv.tv_sec * 1000 + (int64_t)tv.tv_usec/1000);
    return (uint32_t)r;

    //return btime_gettime();
}
/*
void lwiplog (const char *fmt, ...)
{
#ifdef DEBUG
    char buf[128];
    va_list vl;
    va_start(vl, fmt);
    vsnprintf(buf, 128, fmt, vl);
    va_end(vl);
    fprintf(stdout, "[%d]:%s\n",pthread_mach_thread_np(pthread_self()),buf);
    
#endif
    
}
 */
void lwipassertlog(const char *fmt, ...)
{
#ifdef DEBUG
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char content[256];
    vsnprintf(content, 256, fmt, arg_ptr);
    va_end(arg_ptr);
    //surfLog(content, , 0);
    //[AxLogger log:[NSString stringWithFormat:@"%s",content] level:AxLoggerLevelInfo category:@"cfunc" file:@__FILE__  line:__LINE__ ud:@{@"test":@"test"} tags:@[@"test"] time:[NSDate date]];
    //NSLog(@"%s",content);
    fprintf(stdout, "%s",content);
#endif
}
 
