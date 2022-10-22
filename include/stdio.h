/*************************************************************************/
/*                                 stdio.h                               */
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
/*                      A C standard library for printing                */
/*                          text to the screen                           */
/*************************************************************************/
#include <sinx/buffer.h>
#include <dtypes.h>

// printf yoinked from some guy on the internet :P
void printf(const char *fmt, ...)
{
    const char digits[] = "0123456789abcdef";
    va_list ap;
    char buf[10];
    char *s;
    unsigned char u;
    int c, i, pad;

    va_start(ap, fmt);
    while ((c = *fmt++) != 0)
    {
        if (c == '%')
        {
            c = *fmt++;
            if (c == 'l')
                c = *fmt++;
            switch (c)
            {
            case 'c':
                putc(va_arg(ap, int));
                continue;
            case 's':
                s = va_arg(ap, char *);
                if (s == (void *)0)
                    s = (char *)"<NULL>";
                for (; *s; s++)
                    putc((int)*s);
                continue;
            case '%':
                putc('%');
                continue;
            case 'd':
            case 'i':
                c = 'u';
            case 'u':
            case 'x':
            case 'X':
                u = va_arg(ap, unsigned);
                s = buf;
                if (c == 'u')
                {
                    do
                        *s++ = digits[u % 10U];
                    while (u /= 10U);
                }
                else
                {
                    pad = 0;
                    for (i = 0; i < 8; i++)
                    {
                        if (pad)
                            *s++ = '0';
                        else
                        {
                            *s++ = digits[u % 16U];
                            if ((u /= 16U) == false)
                                pad = 1;
                        }
                    }
                }
                while (--s >= buf)
                    putc((int)*s);
                continue;
            }
        }
        putc((int)c);
    }
    putn();
    va_end(ap);
}
