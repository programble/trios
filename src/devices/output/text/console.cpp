#include <devices/output/text/console.h>

namespace Devices { namespace Output { namespace Text { namespace Console {
    const u32 columns = 80;
    const u32 rows = 25;

    u16 *video_ram = (u16*) 0xB8000;

    struct { u8 x; u8 y; } cursor;

    Color foreground = gray;
    Color background = black;

    bool initialized = false;

    void update_cursor();
    
    void init()
    {
        cursor.x = 0;
        cursor.y = 24;
        update_cursor();

        initialized = true;
        print("console output initialized\n");
    }

    void update_cursor()
    {
        u32 x = cursor.y * columns + cursor.x;
        Port::out(0x3D4, 14);
        Port::out(0x3D5, x >> 8);
        Port::out(0x3D4, 15);
        Port::out(0x3D5, x);
    }

    void scroll()
    {
        // Move everything up 1 line
        for (u16 i = columns; i < columns * rows; i++)
            video_ram[i - columns] = video_ram[i];
        // Blank the last line
        for (u8 i = 0; i < columns; i++)
            put(' ', i, rows - 1);
    }

    void clear()
    {
        for (u8 y = 0; y < rows; y++)
            for (u8 x = 0; x < columns; x++)
                put(' ', x, y);
        cursor.x = 0;
        cursor.y = 0;
        update_cursor();
    }

    void put(char c, u8 x, u8 y)
    {
        u16 z = (background << 12) | (foreground << 8) | c;
        video_ram[y * columns + x] = z;
    }

    void put(const string s, u8 x, u8 y)
    {
        for (; *s; s++, x++)
            put(*s, x, y);
    }

    void print(char c)
    {
        switch (c) {
            case '\t':
                cursor.x = cursor.x - (cursor.x % 8) + 8;
                break;
            case '\n':
                cursor.y++;
            case '\r':
                cursor.x = 0;
                break;
            case '\b':
                if (cursor.x == 0) {
                    cursor.y--;
                    cursor.x = columns - 1;
                } else cursor.x--;
                put(' ', cursor.x, cursor.y);
                break;
            default:
                put(c, cursor.x, cursor.y);
                cursor.x++;
        }

        // End of line
        if (cursor.x >= columns) {
            cursor.x -= columns;
            cursor.y++;
        }

        // Last line
        if (cursor.y >= rows) {
            scroll();
            cursor.y = rows - 1;
        }

        update_cursor();
    }

    void print(const string s)
    {
        for (; *s; s++)
            print(*s);
    }
}}}}
