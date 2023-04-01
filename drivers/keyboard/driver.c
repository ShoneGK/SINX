#include "driver.h"

#include <drivers/keyboard/keys.h>
#include <iobyte.h>
#include <dtypes.h>
// #include <sinx/buffer.h>
#include <string.h>
// #include <sinx/panic.h>
#include <drivers/VGA/driver.h>

#include <string.h>
#include <sinx/tty.h>

unsigned int keyReadSleep = 25000000;
unsigned int lastCharDel = 0;

static char key_buffer[256];
#define BACKSPACE_KEY 0x0E

static void keyboard_callback()
{
    while (1 == 1)
    {
        uint8_t scancode = inb(0x60);

        if (scancode == BACKSPACE_KEY)
        {
            if (backspace_func(key_buffer))
            {
                print_backspace();
            }
        }
        else
        {
            char letter = get_ascii_char(scancode);
            join(key_buffer, letter);
            char str[2] = {letter, '\0'};
            puts(str);
        }
    }
}

int backspace_func(char buffer[])
{
    int len = strlen(buffer);
    if (len > 0)
    {
        buffer[len - 1] = '\0';
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_backspace()
{

    int newCursor = getVGACursor() - 2;

    putc(' ', newCursor);
    setVGACursor(newCursor);
}


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
