/*************************************************************************/
/*                                dtypes.h                               */
/*************************************************************************/
/*                         ______     ______   __  __                    */
/*                        /\  ___\   /\  ___\ /\_\_\_\                   */
/*                        \ \___  \  \ \  __\ \/_/\_\/_                  */
/*                         \/\_____\  \ \_\     /\_\/\_\                 */
/*                          \/_____/   \/_/     \/_/\/_/                 */
/*                                                                       */
/*************************************************************************/
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
/*                      A simple types system to control                 */
/*                          unsigned ints and more                       */
/*************************************************************************/
#pragma once

#define NULL (void *)0
#define va_start(ap, X) __builtin_va_start(ap, X)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)

#define false 0
#define true 1

typedef _Bool bool;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long size_t;

typedef __builtin_va_list va_list;