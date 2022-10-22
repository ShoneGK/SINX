/*************************************************************************/
/*                                 buffer.h                              */
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
/*                  An advanced "buffer" system to control               */
/*                      text displayed on the screen                     */
/*************************************************************************/
#pragma once

#include <dtypes.h>
#include <drivers/gpu/colorizer.h>

const static size_t bufferRows = 80;
const static size_t bufferColumns = 25;

struct bufferEntry *videoBuffer = (struct bufferEntry *)0xb8000;
size_t currentBufferRow = 0;
size_t currentBufferColumn = 0;
uint8_t bufferColor = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

struct bufferEntry
{
    uint8_t character;
    uint8_t color;
};

void clearBufferRow(size_t row)
{
    struct bufferEntry empty = (struct bufferEntry){
        character : ' ',
        color : bufferColor,
    };

    for (size_t col = 0; col < bufferRows; col++)
    {
        videoBuffer[col + bufferRows * row] = empty;
    }
}

void clearBuffer()
{
    for (size_t i = 0; i < bufferColumns; i++)
    {
        clearBufferRow(i);
    }
}

void putn()
{
    currentBufferRow = 0;

    if (currentBufferColumn < bufferColumns - 1)
    {
        currentBufferColumn++;
        return;
    }

    for (size_t row = 1; row < bufferColumns; row++)
    {
        for (size_t col = 0; col < bufferRows; col++)
        {
            struct bufferEntry character = videoBuffer[col + bufferRows * row];
            videoBuffer[col + bufferRows * (row - 1)] = character;
        }
    }

    clearBufferRow(bufferRows - 1);
}

void putc(unsigned char c)
{
    if (c == '\n')
    {
        putn();
        return;
    }

    if (currentBufferRow > bufferRows)
    {
        putn();
    }

    videoBuffer[currentBufferRow + bufferRows * currentBufferColumn] = (struct bufferEntry){
        character : (uint8_t)c,
        color : bufferColor,
    };

    currentBufferRow++;
}

void puts(char *str)
{
    for (size_t i = 0; 1; i++)
    {
        char character = (size_t)str[i];

        if (character == '\0')
        {
            return;
        }

        putc(character);
    }
}

void setBufferColor(uint8_t foreground, uint8_t background)
{
    bufferColor = foreground + (background << 4);
}