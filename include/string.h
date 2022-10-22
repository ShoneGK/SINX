/*************************************************************************/
/*                                 string.h                              */
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
/*                          A C standard library for                     */
/*                            string manipulation                        */
/*************************************************************************/
#pragma once

unsigned int strlen(const char *str)
{
  unsigned int length = 0;
  while (str[length])
    length++;
  return length;
}

void strncat(char *s, char c)
{
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
}

char *memset(char *dest, int val)
{
  unsigned char *ptr = dest;

  size_t len = strlen(dest);

  while (len-- > 0)
    *ptr++ = val;
  return dest;
}

void clearString(char *string)
{

  int length = strlen(string);

  for (int i = length; i = 0; i--)
  {

    string[i] = 0x00;
  }
}

/*
void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}
*/