/*************************************************************************/
/*                                driver.h                               */
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
/*           A simple keyboard driver under heavy construction           */
/*************************************************************************/
#pragma once

#include <drivers/keyboard/keys.h>
#include <iobyte.h>
#include <dtypes.h>
// #include <sinx/buffer.h>
#include <string.h>
// #include <sinx/panic.h>
#include <drivers/VGA/driver.h>
#include <drivers/kbd/kbd.h>
#include <string.h>
#include <sinx/tty.h>

unsigned int keyReadSleep = 25000000;
unsigned int lastCharDel = 0;

void wait_for_io(uint32_t timer_count)
{
  while (1)
  {
    asm volatile("nop");
    timer_count--;
    if (timer_count <= 0)
      break;
  }
}

char get_input_keycode()
{
  char ch = 0;
  while ((ch = inb(KEYBOARD_PORT)) != 0)
  {
    if (ch > 0)
      return ch;
  }
  return ch;
}

void debug()
{
  char keycode = 0;
  char ch = 0;
  while (1 == 1)
  {
    keycode = get_input_keycode();
    ch = get_ascii_char(keycode);
  }
}

void keyboardInstance()
{
  char ch = 0;
  char data = 0;
  char keycode = 0;
  char *textData;
  int readyToSend = true;

  while (1 == 1)
  {
    data = inb(KEYBOARD_PORT);

    if (data < 0)
    { // not pressed
      readyToSend = true;
    }

    if (data >= 0)
    { // pressed
      if (readyToSend == true)
      {
        readyToSend = false;
        keycode = get_input_keycode();
        if (keycode == KEY_ENTER)
        {
          puts("\n");
          execute_command(key_buffer);
          key_buffer[0] = '\0';
        }
        // for testing
        else if (keycode == KEY_FORESLHASH)
        {

          clearVGA();
          // puts(textData);
        }
        else if (keycode == KEY_BACKSPACE)
        {
          if (backspace_func(key_buffer))
            print_backspace();
        }
        else
        {
          char letter = get_ascii_char(keycode);
          join(key_buffer, letter);
          char str[2] = {letter, '\0'};
          puts(str);
          // strncat(textData, ch);
        }
      }
    }
  }
}
