/*
  SSD1306_minimal.c - SSD1306 OLED Driver Library

      What is it?
        This library is derived from SSD1306OLED library, only for SSD1306 in I2C Mode.
        As the original library only supports Frame Buffered mode which requires to have
        at least 1024bytes of free RAM for a 128x64px display it is too big for smaller devices.

        So this a SSD1306 library that works great with ATTiny85 devices
*/

#include "SSD1306_minimal.h"

const uint8_t digital_font5x7[] PROGMEM =
 {
     0x00, 0x05, 0x07, 0x20,
     0x00, 0x00, 0x00, 0x00, 0x00, // char ' ' (0x20/32)
     0x00, 0x00, 0x2E, 0x00, 0x00, // char '!' (0x21/33)
     0x06, 0x00, 0x06, 0x00, 0x00, // char '"' (0x22/34)
     0x14, 0x7F, 0x14, 0x7F, 0x14, // char '#' (0x23/35)
     0x06, 0x49, 0x7F, 0x49, 0x30, // char '$' (0x24/36)
     0x24, 0x10, 0x08, 0x24, 0x00, // char '%' (0x25/37)
     0x36, 0x49, 0x36, 0x50, 0x00, // char '&' (0x26/38)
     0x00, 0x00, 0x00, 0x06, 0x00, // char ''' (0x27/39)
     0x00, 0x41, 0x36, 0x00, 0x00, // char '(' (0x28/40)
     0x00, 0x36, 0x41, 0x00, 0x00, // char ')' (0x29/41)
     0x00, 0x08, 0x00, 0x00, 0x00, // char '*' (0x2A/42)
     0x00, 0x08, 0x1C, 0x08, 0x00, // char '+' (0x2B/43)
     0x40, 0x20, 0x00, 0x00, 0x00, // char ',' (0x2C/44)
     0x00, 0x08, 0x08, 0x00, 0x00, // char '-' (0x2D/45)
     0x20, 0x00, 0x00, 0x00, 0x00, // char '.' (0x2E/46)
     0x00, 0x30, 0x06, 0x00, 0x00, // char '/' (0x2F/47)
     0x36, 0x41, 0x41, 0x36, 0x00, // char '0' (0x30/48)
     0x00, 0x00, 0x00, 0x36, 0x00, // char '1' (0x31/49)
     0x30, 0x49, 0x49, 0x06, 0x00, // char '2' (0x32/50)
     0x00, 0x49, 0x49, 0x36, 0x00, // char '3' (0x33/51)
     0x06, 0x08, 0x08, 0x36, 0x00, // char '4' (0x34/52)
     0x06, 0x49, 0x49, 0x30, 0x00, // char '5' (0x35/53)
     0x36, 0x49, 0x49, 0x30, 0x00, // char '6' (0x36/54)
     0x00, 0x01, 0x01, 0x36, 0x00, // char '7' (0x37/55)
     0x36, 0x49, 0x49, 0x36, 0x00, // char '8' (0x38/56)
     0x06, 0x49, 0x49, 0x36, 0x00, // char '9' (0x39/57)
     0x00, 0x14, 0x00, 0x00, 0x00, // char ':' (0x3A/58)
     0x20, 0x14, 0x00, 0x00, 0x00, // char ';' (0x3B/59)
     0x00, 0x08, 0x14, 0x22, 0x00, // char '<' (0x3C/60)
     0x00, 0x14, 0x14, 0x14, 0x00, // char '=' (0x3D/61)
     0x00, 0x22, 0x14, 0x08, 0x00, // char '>' (0x3E/62)
     0x00, 0x01, 0x31, 0x06, 0x00, // char '?' (0x3F/63)
     0x36, 0x49, 0x55, 0x59, 0x2E, // char '@' (0x40/64)
     0x36, 0x09, 0x09, 0x36, 0x00, // char 'A' (0x41/65)
     0x77, 0x49, 0x49, 0x36, 0x00, // char 'B' (0x42/66)
     0x36, 0x41, 0x41, 0x00, 0x00, // char 'C' (0x43/67)
     0x77, 0x41, 0x41, 0x36, 0x00, // char 'D' (0x44/68)
     0x36, 0x49, 0x49, 0x00, 0x00, // char 'E' (0x45/69)
     0x36, 0x09, 0x09, 0x00, 0x00, // char 'F' (0x46/70)
     0x36, 0x41, 0x51, 0x30, 0x00, // char 'G' (0x47/71)
     0x36, 0x08, 0x08, 0x36, 0x00, // char 'H' (0x48/72)
     0x00, 0x00, 0x36, 0x00, 0x00, // char 'I' (0x49/73)
     0x00, 0x40, 0x40, 0x36, 0x00, // char 'J' (0x4A/74)
     0x36, 0x08, 0x14, 0x22, 0x00, // char 'K' (0x4B/75)
     0x36, 0x40, 0x40, 0x00, 0x00, // char 'L' (0x4C/76)
     0x36, 0x01, 0x06, 0x01, 0x36, // char 'M' (0x4D/77)
     0x36, 0x04, 0x10, 0x36, 0x00, // char 'N' (0x4E/78)
     0x36, 0x41, 0x41, 0x36, 0x00, // char 'O' (0x4F/79)
     0x36, 0x09, 0x09, 0x06, 0x00, // char 'P' (0x50/80)
     0x36, 0x41, 0x21, 0x56, 0x00, // char 'Q' (0x51/81)
     0x36, 0x09, 0x19, 0x26, 0x00, // char 'R' (0x52/82)
     0x06, 0x49, 0x49, 0x30, 0x00, // char 'S' (0x53/83)
     0x00, 0x01, 0x37, 0x01, 0x00, // char 'T' (0x54/84)
     0x36, 0x40, 0x40, 0x36, 0x00, // char 'U' (0x55/85)
     0x36, 0x40, 0x36, 0x00, 0x00, // char 'V' (0x56/86)
     0x36, 0x40, 0x30, 0x40, 0x36, // char 'W' (0x57/87)
     0x36, 0x08, 0x08, 0x36, 0x00, // char 'X' (0x58/88)
     0x06, 0x48, 0x48, 0x36, 0x00, // char 'Y' (0x59/89)
     0x20, 0x51, 0x49, 0x45, 0x02, // char 'Z' (0x5A/90)
     0x77, 0x41, 0x41, 0x00, 0x00, // char '[' (0x5B/91)
     0x00, 0x06, 0x30, 0x00, 0x00, // char '\' (0x5C/92)
     0x00, 0x41, 0x41, 0x77, 0x00, // char ']' (0x5D/93)
     0x00, 0x02, 0x01, 0x02, 0x00, // char '^' (0x5E/94)
     0x00, 0x40, 0x40, 0x00, 0x00, // char '_' (0x5F/95)
     0x00, 0x01, 0x02, 0x00, 0x00, // char '`' (0x60/96)
     0x20, 0x54, 0x54, 0x38, 0x40, // char 'a' (0x61/97)
     0x00, 0x36, 0x48, 0x30, 0x00, // char 'b' (0x62/98)
     0x30, 0x48, 0x48, 0x00, 0x00, // char 'c' (0x63/99)
     0x30, 0x48, 0x48, 0x76, 0x00, // char 'd' (0x64/100)
     0x38, 0x54, 0x54, 0x08, 0x00, // char 'e' (0x65/101)
     0x08, 0x6C, 0x0A, 0x00, 0x00, // char 'f' (0x66/102)
     0x08, 0x54, 0x54, 0x38, 0x00, // char 'g' (0x67/103)
     0x36, 0x08, 0x08, 0x30, 0x00, // char 'h' (0x68/104)
     0x00, 0x34, 0x00, 0x00, 0x00, // char 'i' (0x69/105)
     0x00, 0x40, 0x34, 0x00, 0x00, // char 'j' (0x6A/106)
     0x36, 0x10, 0x28, 0x00, 0x00, // char 'k' (0x6B/107)
     0x36, 0x00, 0x00, 0x00, 0x00, // char 'l' (0x6C/108)
     0x30, 0x08, 0x10, 0x08, 0x30, // char 'm' (0x6D/109)
     0x30, 0x08, 0x08, 0x30, 0x00, // char 'n' (0x6E/110)
     0x30, 0x48, 0x48, 0x30, 0x00, // char 'o' (0x6F/111)
     0x78, 0x14, 0x14, 0x08, 0x00, // char 'p' (0x70/112)
     0x08, 0x14, 0x14, 0x68, 0x00, // char 'q' (0x71/113)
     0x30, 0x08, 0x08, 0x00, 0x00, // char 'r' (0x72/114)
     0x08, 0x54, 0x54, 0x20, 0x00, // char 's' (0x73/115)
     0x08, 0x2C, 0x48, 0x00, 0x00, // char 't' (0x74/116)
     0x30, 0x40, 0x40, 0x30, 0x00, // char 'u' (0x75/117)
     0x30, 0x40, 0x30, 0x00, 0x00, // char 'v' (0x76/118)
     0x30, 0x40, 0x20, 0x40, 0x30, // char 'w' (0x77/119)
     0x28, 0x10, 0x10, 0x28, 0x00, // char 'x' (0x78/120)
     0x08, 0x50, 0x50, 0x38, 0x00, // char 'y' (0x79/121)
     0x24, 0x34, 0x2C, 0x24, 0x00, // char 'z' (0x7A/122)
     0x08, 0x36, 0x41, 0x00, 0x00, // char '{' (0x7B/123)
     0x00, 0x36, 0x00, 0x00, 0x00, // char '|' (0x7C/124)
     0x00, 0x41, 0x36, 0x08, 0x00, // char '}' (0x7D/125)
     0x08, 0x08, 0x10, 0x10, 0x00, // char '~' (0x7E/126)
     0x36, 0x41, 0x36, 0x00, 0x00, // char '' (0x7F/127)
 };

// a 5x7 font table
//const unsigned char BasicFont[] PROGMEM = {
// This appears to be using Code Page 437
// Hex codes provided because you probably aren't
//  0x00, 0x00, 0x00, 0x00, 0x00, //    \x00
//  0x3E, 0x5B, 0x4F, 0x5B, 0x3E, // ☺  \x01
//  0x3E, 0x6B, 0x4F, 0x6B, 0x3E, // ☻  \x02
//  0x1C, 0x3E, 0x7C, 0x3E, 0x1C, // ♥  \x03
//  0x18, 0x3C, 0x7E, 0x3C, 0x18, // ♦  \x04
//  0x1C, 0x57, 0x7D, 0x57, 0x1C, // ♣  \x05
//  0x1C, 0x5E, 0x7F, 0x5E, 0x1C, // ♠  \x06
//  0x00, 0x18, 0x3C, 0x18, 0x00, // •  \x07
//  0xFF, 0xE7, 0xC3, 0xE7, 0xFF, // ◘  \x08
//  0x00, 0x18, 0x24, 0x18, 0x00, // ○  \x09
//  0xFF, 0xE7, 0xDB, 0xE7, 0xFF, // ◙  \x0a
//  0x30, 0x48, 0x3A, 0x06, 0x0E, // ♂  \x0b
//  0x26, 0x29, 0x79, 0x29, 0x26, // ♀  \x0c
//  0x40, 0x7F, 0x05, 0x05, 0x07, // ♪  \x0d
//  0x40, 0x7F, 0x05, 0x25, 0x3F, // ♫  \x0e
//  0x5A, 0x3C, 0xE7, 0x3C, 0x5A, // ☼  \x0f
//  0x7F, 0x3E, 0x1C, 0x1C, 0x08, // ►  \x10
//  0x08, 0x1C, 0x1C, 0x3E, 0x7F, // ◀  \x11
//  0x14, 0x22, 0x7F, 0x22, 0x14, // ↕  \x12
//  0x5F, 0x5F, 0x00, 0x5F, 0x5F, // ‼  \x13
//  0x06, 0x09, 0x7F, 0x01, 0x7F, // ¶  \x14
//  0x00, 0x66, 0x89, 0x95, 0x6A, // §  \x15
//  0x60, 0x60, 0x60, 0x60, 0x60, // ▬  \x16
//  0x94, 0xA2, 0xFF, 0xA2, 0x94, // ↨  \x17
//  0x08, 0x04, 0x7E, 0x04, 0x08, // ↑  \x18
//  0x10, 0x20, 0x7E, 0x20, 0x10, // ↓  \x19
//  0x08, 0x08, 0x2A, 0x1C, 0x08, // →  \x1a
//  0x08, 0x1C, 0x2A, 0x08, 0x08, // ←  \x1b
//  0x1E, 0x10, 0x10, 0x10, 0x10, // ∟  \x1c
//  0x0C, 0x1E, 0x0C, 0x1E, 0x0C, // ↔  \x1d
//  0x30, 0x38, 0x3E, 0x38, 0x30, // ▲  \x1e
//  0x06, 0x0E, 0x3E, 0x0E, 0x06, // ▼  \x1f
//  0x00, 0x00, 0x00, 0x00, 0x00, // SP  \x20
//  0x00, 0x00, 0x5F, 0x00, 0x00, // !  \x21
//  0x00, 0x07, 0x00, 0x07, 0x00, // "  \x22
//  0x14, 0x7F, 0x14, 0x7F, 0x14, // #  \x23
//  0x24, 0x2A, 0x7F, 0x2A, 0x12, // $  \x24
//  0x23, 0x13, 0x08, 0x64, 0x62, // %  \x25
//  0x36, 0x49, 0x56, 0x20, 0x50, // &  \x26
//  0x00, 0x08, 0x07, 0x03, 0x00, // '  \x27
//  0x00, 0x1C, 0x22, 0x41, 0x00, // (  \x28
//  0x00, 0x41, 0x22, 0x1C, 0x00, // )  \x29
//  0x2A, 0x1C, 0x7F, 0x1C, 0x2A, // *  \x2a
//  0x08, 0x08, 0x3E, 0x08, 0x08, // +  \x2b
//  0x00, 0x80, 0x70, 0x30, 0x00, // ,  \x2c
//  0x08, 0x08, 0x08, 0x08, 0x08, // -  \x2d
//  0x00, 0x00, 0x60, 0x60, 0x00, // .  \x2e
//  0x20, 0x10, 0x08, 0x04, 0x02, // /  \x2f
//  0x3E, 0x51, 0x49, 0x45, 0x3E, // 0  \x30
//  0x00, 0x42, 0x7F, 0x40, 0x00, // 1  \x31
//  0x72, 0x49, 0x49, 0x49, 0x46, // 2  \x32
//  0x21, 0x41, 0x49, 0x4D, 0x33, // 3  \x33
//  0x18, 0x14, 0x12, 0x7F, 0x10, // 4  \x34
//  0x27, 0x45, 0x45, 0x45, 0x39, // 5  \x35
//  0x3C, 0x4A, 0x49, 0x49, 0x31, // 6  \x36
//  0x41, 0x21, 0x11, 0x09, 0x07, // 7  \x37
//  0x36, 0x49, 0x49, 0x49, 0x36, // 8  \x38
//  0x46, 0x49, 0x49, 0x29, 0x1E, // 9  \x39
//  0x00, 0x00, 0x14, 0x00, 0x00, // :  \x3a
//  0x00, 0x40, 0x34, 0x00, 0x00, // ;  \x3b
//  0x00, 0x08, 0x14, 0x22, 0x41, // <  \x3c
//  0x14, 0x14, 0x14, 0x14, 0x14, // =  \x3d
//  0x00, 0x41, 0x22, 0x14, 0x08, // >  \x3e
//  0x02, 0x01, 0x59, 0x09, 0x06, // ?  \x3f
//  0x3E, 0x41, 0x5D, 0x59, 0x4E, // @  \x40
//  0x7C, 0x12, 0x11, 0x12, 0x7C, // A  \x41
//  0x7F, 0x49, 0x49, 0x49, 0x36, // B  \x42
//  0x3E, 0x41, 0x41, 0x41, 0x22, // C  \x43
//  0x7F, 0x41, 0x41, 0x41, 0x3E, // D  \x44
//  0x7F, 0x49, 0x49, 0x49, 0x41, // E  \x45
//  0x7F, 0x09, 0x09, 0x09, 0x01, // F  \x46
//  0x3E, 0x41, 0x41, 0x51, 0x73, // G  \x47
//  0x7F, 0x08, 0x08, 0x08, 0x7F, // H  \x48
//  0x00, 0x41, 0x7F, 0x41, 0x00, // I  \x49
//  0x20, 0x40, 0x41, 0x3F, 0x01, // J  \x4a
//  0x7F, 0x08, 0x14, 0x22, 0x41, // K  \x4b
//  0x7F, 0x40, 0x40, 0x40, 0x40, // L  \x4c
//  0x7F, 0x02, 0x1C, 0x02, 0x7F, // M  \x4d
//  0x7F, 0x04, 0x08, 0x10, 0x7F, // N  \x4e
//  0x3E, 0x41, 0x41, 0x41, 0x3E, // O  \x4f
//  0x7F, 0x09, 0x09, 0x09, 0x06, // P  \x50
//  0x3E, 0x41, 0x51, 0x21, 0x5E, // Q  \x51
//  0x7F, 0x09, 0x19, 0x29, 0x46, // R  \x52
//  0x26, 0x49, 0x49, 0x49, 0x32, // S  \x53
//  0x03, 0x01, 0x7F, 0x01, 0x03, // T  \x54
//  0x3F, 0x40, 0x40, 0x40, 0x3F, // U  \x55
//  0x1F, 0x20, 0x40, 0x20, 0x1F, // V  \x56
//  0x3F, 0x40, 0x38, 0x40, 0x3F, // W  \x57
//  0x63, 0x14, 0x08, 0x14, 0x63, // X  \x58
//  0x03, 0x04, 0x78, 0x04, 0x03, // Y  \x59
//  0x61, 0x59, 0x49, 0x4D, 0x43, // Z  \x5a
//  0x00, 0x7F, 0x41, 0x41, 0x41, // [  \x5b
//  0x02, 0x04, 0x08, 0x10, 0x20, // \  \x5c
//  0x00, 0x41, 0x41, 0x41, 0x7F, // ]  \x5d
//  0x04, 0x02, 0x01, 0x02, 0x04, // ^  \x5e
//  0x40, 0x40, 0x40, 0x40, 0x40, // _  \x5f
//  0x00, 0x03, 0x07, 0x08, 0x00, // `  \x60
//  0x20, 0x54, 0x54, 0x78, 0x40, // a  \x61
//  0x7F, 0x28, 0x44, 0x44, 0x38, // b  \x62
//  0x38, 0x44, 0x44, 0x44, 0x28, // c  \x63
//  0x38, 0x44, 0x44, 0x28, 0x7F, // d  \x64
//  0x38, 0x54, 0x54, 0x54, 0x18, // e  \x65
//  0x00, 0x08, 0x7E, 0x09, 0x02, // f  \x66
//  0x18, 0xA4, 0xA4, 0x9C, 0x78, // g  \x67
//  0x7F, 0x08, 0x04, 0x04, 0x78, // h  \x68
//  0x00, 0x44, 0x7D, 0x40, 0x00, // i  \x69
//  0x20, 0x40, 0x40, 0x3D, 0x00, // j  \x6a
//  0x7F, 0x10, 0x28, 0x44, 0x00, // k  \x6b
//  0x00, 0x41, 0x7F, 0x40, 0x00, // l  \x6c
//  0x7C, 0x04, 0x78, 0x04, 0x78, // m  \x6d
//  0x7C, 0x08, 0x04, 0x04, 0x78, // n  \x6e
//  0x38, 0x44, 0x44, 0x44, 0x38, // o  \x6f
//  0xFC, 0x18, 0x24, 0x24, 0x18, // p  \x70
//  0x18, 0x24, 0x24, 0x18, 0xFC, // q  \x71
//  0x7C, 0x08, 0x04, 0x04, 0x08, // r  \x72
//  0x48, 0x54, 0x54, 0x54, 0x24, // s  \x73
//  0x04, 0x04, 0x3F, 0x44, 0x24, // t  \x74
//  0x3C, 0x40, 0x40, 0x20, 0x7C, // u  \x75
//  0x1C, 0x20, 0x40, 0x20, 0x1C, // v  \x76
//  0x3C, 0x40, 0x30, 0x40, 0x3C, // w  \x77
//  0x44, 0x28, 0x10, 0x28, 0x44, // x  \x78
//  0x4C, 0x90, 0x90, 0x90, 0x7C, // y  \x79
//  0x44, 0x64, 0x54, 0x4C, 0x44, // z  \x7a
//  0x00, 0x08, 0x36, 0x41, 0x00, // {  \x7b
//  0x00, 0x00, 0x77, 0x00, 0x00, // |  \x7c
//  0x00, 0x41, 0x36, 0x08, 0x00, // }  \x7d
//  0x02, 0x01, 0x02, 0x04, 0x02, // ~  \x7e
//  0x3C, 0x26, 0x23, 0x26, 0x3C, // ⌂  \x7f
//  0x1E, 0xA1, 0xA1, 0x61, 0x12, // Ç  \x80
//  0x3A, 0x40, 0x40, 0x20, 0x7A, // ü  \x81
//  0x38, 0x54, 0x54, 0x55, 0x59, // é  \x82
//  0x21, 0x55, 0x55, 0x79, 0x41, // â  \x83
//  0x21, 0x54, 0x54, 0x78, 0x41, // ä  \x84
//  0x21, 0x55, 0x54, 0x78, 0x40, // à  \x85
//  0x20, 0x54, 0x55, 0x79, 0x40, // å  \x86
//  0x0C, 0x1E, 0x52, 0x72, 0x12, // ç  \x87
//  0x39, 0x55, 0x55, 0x55, 0x59, // ê  \x88
//  0x39, 0x54, 0x54, 0x54, 0x59, // ë  \x89
//  0x39, 0x55, 0x54, 0x54, 0x58, // è  \x8a
//  0x00, 0x00, 0x45, 0x7C, 0x41, // ï  \x8b
//  0x00, 0x02, 0x45, 0x7D, 0x42, // î  \x8c
//  0x00, 0x01, 0x45, 0x7C, 0x40, // ì  \x8d
//  0xF0, 0x29, 0x24, 0x29, 0xF0, // Ä  \x8e
//  0xF0, 0x28, 0x25, 0x28, 0xF0, // Å  \x8f
//  0x7C, 0x54, 0x55, 0x45, 0x00, // É  \x90
//  0x20, 0x54, 0x54, 0x7C, 0x54, // æ  \x91
//  0x7C, 0x0A, 0x09, 0x7F, 0x49, // Æ  \x92
//  0x32, 0x49, 0x49, 0x49, 0x32, // ô  \x93
//  0x32, 0x48, 0x48, 0x48, 0x32, // ö  \x94
//  0x32, 0x4A, 0x48, 0x48, 0x30, // ò  \x95
//  0x3A, 0x41, 0x41, 0x21, 0x7A, // û  \x96
//  0x3A, 0x42, 0x40, 0x20, 0x78, // ù  \x97
//  0x00, 0x9D, 0xA0, 0xA0, 0x7D, // ÿ  \x98
//  0x39, 0x44, 0x44, 0x44, 0x39, // Ö  \x99
//  0x3D, 0x40, 0x40, 0x40, 0x3D, // Ü  \x9a
//  0x3C, 0x24, 0xFF, 0x24, 0x24, // ¢  \x9b
//  0x48, 0x7E, 0x49, 0x43, 0x66, // £  \x9c
//  0x2B, 0x2F, 0xFC, 0x2F, 0x2B, // ¥  \x9d
//  0xFF, 0x09, 0x29, 0xF6, 0x20, // ₧  \x9e
//  0xC0, 0x88, 0x7E, 0x09, 0x03, // ƒ  \x9f
//  0x20, 0x54, 0x54, 0x79, 0x41, // á  \xa0
//  0x00, 0x00, 0x44, 0x7D, 0x41, // í  \xa1
//  0x30, 0x48, 0x48, 0x4A, 0x32, // ó  \xa2
//  0x38, 0x40, 0x40, 0x22, 0x7A, // ú  \xa3
//  0x00, 0x7A, 0x0A, 0x0A, 0x72, // ñ  \xa4
//  0x7D, 0x0D, 0x19, 0x31, 0x7D, // Ñ  \xa5
//  0x26, 0x29, 0x29, 0x2F, 0x28, // ª  \xa6
//  0x26, 0x29, 0x29, 0x29, 0x26, // º  \xa7
//  0x30, 0x48, 0x4D, 0x40, 0x20, // ¿  \xa8
//  0x38, 0x08, 0x08, 0x08, 0x08, // ⌐  \xa9
//  0x08, 0x08, 0x08, 0x08, 0x38, // ¬  \xaa
//  0x2F, 0x10, 0xC8, 0xAC, 0xBA, // ½  \xab
//  0x2F, 0x10, 0x28, 0x34, 0xFA, // ¼  \xac
//  0x00, 0x00, 0x7B, 0x00, 0x00, // ¡  \xad
//  0x08, 0x14, 0x2A, 0x14, 0x22, // «  \xae
//  0x22, 0x14, 0x2A, 0x14, 0x08, // »  \xaf
//  0xAA, 0x00, 0x55, 0x00, 0xAA, // ░  \xb0
//  0xAA, 0x55, 0xAA, 0x55, 0xAA, // ▒  \xb1
//  0xAA, 0xFF, 0xAA, 0xFF, 0xAA, // ▓  \xb2
//  0x00, 0x00, 0x00, 0xFF, 0x00, // │  \xb3
//  0x10, 0x10, 0x10, 0xFF, 0x00, // ┤  \xb4
//  0x14, 0x14, 0x14, 0xFF, 0x00, // ╡  \xb5
//  0x10, 0x10, 0xFF, 0x00, 0xFF, // ╢  \xb6
//  0x10, 0x10, 0xF0, 0x10, 0xF0, // ╖  \xb7
//  0x14, 0x14, 0x14, 0xFC, 0x00, // ╕  \xb8
//  0x14, 0x14, 0xF7, 0x00, 0xFF, // ╣  \xb9
//  0x00, 0x00, 0xFF, 0x00, 0xFF, // ║  \xba
//  0x14, 0x14, 0xF4, 0x04, 0xFC, // ╗  \xbb
//  0x14, 0x14, 0x17, 0x10, 0x1F, // ╝  \xbc
//  0x10, 0x10, 0x1F, 0x10, 0x1F, // ╜  \xbd
//  0x14, 0x14, 0x14, 0x1F, 0x00, // ╛  \xbe
//  0x10, 0x10, 0x10, 0xF0, 0x00, // ┐  \xbf
//  0x00, 0x00, 0x00, 0x1F, 0x10, // └  \xc0
//  0x10, 0x10, 0x10, 0x1F, 0x10, // ┴  \xc1
//  0x10, 0x10, 0x10, 0xF0, 0x10, // ┬  \xc2
//  0x00, 0x00, 0x00, 0xFF, 0x10, // ├  \xc3
//  0x10, 0x10, 0x10, 0x10, 0x10, // ─  \xc4
//  0x10, 0x10, 0x10, 0xFF, 0x10, // ┼  \xc5
//  0x00, 0x00, 0x00, 0xFF, 0x14, // ╞  \xc6
//  0x00, 0x00, 0xFF, 0x00, 0xFF, // ╟  \xc7
//  0x00, 0x00, 0x1F, 0x10, 0x17, // ╚  \xc8
//  0x00, 0x00, 0xFC, 0x04, 0xF4, // ╔  \xc9
//  0x14, 0x14, 0x17, 0x10, 0x17, // ╩  \xca
//  0x14, 0x14, 0xF4, 0x04, 0xF4, // ╦  \xcb
//  0x00, 0x00, 0xFF, 0x00, 0xF7, // ╠  \xcc
//  0x14, 0x14, 0x14, 0x14, 0x14, // ═  \xcd
//  0x14, 0x14, 0xF7, 0x00, 0xF7, // ╬  \xce
//  0x14, 0x14, 0x14, 0x17, 0x14, // ╧  \xcf
//  0x10, 0x10, 0x1F, 0x10, 0x1F, // ╨  \xd0
//  0x14, 0x14, 0x14, 0xF4, 0x14, // ╤  \xd1
//  0x10, 0x10, 0xF0, 0x10, 0xF0, // ╥  \xd2
//  0x00, 0x00, 0x1F, 0x10, 0x1F, // ╙  \xd3
//  0x00, 0x00, 0x00, 0x1F, 0x14, // ╘  \xd4
//  0x00, 0x00, 0x00, 0xFC, 0x14, // ╒  \xd5
//  0x00, 0x00, 0xF0, 0x10, 0xF0, // ╓  \xd6
//  0x10, 0x10, 0xFF, 0x10, 0xFF, // ╫  \xd7
//  0x14, 0x14, 0x14, 0xFF, 0x14, // ╪  \xd8
//  0x10, 0x10, 0x10, 0x1F, 0x00, // ┘  \xd9
//  0x00, 0x00, 0x00, 0xF0, 0x10, // ┌  \xda
//  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // █  \xdb
//  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, // ▄  \xdc
//  0xFF, 0xFF, 0xFF, 0x00, 0x00, // ▌  \xdd
//  0x00, 0x00, 0x00, 0xFF, 0xFF, // ▐  \xde
//  0x0F, 0x0F, 0x0F, 0x0F, 0x0F, // ▀  \xdf
//  0x38, 0x44, 0x44, 0x38, 0x44, // α  \xe0
//  0x7C, 0x2A, 0x2A, 0x3E, 0x14, // ß  \xe1
//  0x7E, 0x02, 0x02, 0x06, 0x06, // Γ  \xe2
//  0x02, 0x7E, 0x02, 0x7E, 0x02, // π  \xe3
//  0x63, 0x55, 0x49, 0x41, 0x63, // Σ  \xe4
//  0x38, 0x44, 0x44, 0x3C, 0x04, // σ  \xe5
//  0x40, 0x7E, 0x20, 0x1E, 0x20, // µ  \xe6
//  0x06, 0x02, 0x7E, 0x02, 0x02, // τ  \xe7
//  0x99, 0xA5, 0xE7, 0xA5, 0x99, // Φ  \xe8
//  0x1C, 0x2A, 0x49, 0x2A, 0x1C, // Θ  \xe9
//  0x4C, 0x72, 0x01, 0x72, 0x4C, // Ω  \xea
//  0x30, 0x4A, 0x4D, 0x4D, 0x30, // δ  \xeb
//  0x30, 0x48, 0x78, 0x48, 0x30, // ∞  \xec
//  0xBC, 0x62, 0x5A, 0x46, 0x3D, // φ  \xed
//  0x3E, 0x49, 0x49, 0x49, 0x00, // ε  \xee
//  0x7E, 0x01, 0x01, 0x01, 0x7E, // ∩  \xef
//  0x2A, 0x2A, 0x2A, 0x2A, 0x2A, // ≡  \xf0
//  0x44, 0x44, 0x5F, 0x44, 0x44, // ±  \xf1
//  0x40, 0x51, 0x4A, 0x44, 0x40, // ≥  \xf2
//  0x40, 0x44, 0x4A, 0x51, 0x40, // ≤  \xf3
//  0x00, 0x00, 0xFF, 0x01, 0x03, // ⌠  \xf4
//  0xE0, 0x80, 0xFF, 0x00, 0x00, // ⌡  \xf5
//  0x08, 0x08, 0x6B, 0x6B, 0x08, // ÷  \xf6
//  0x36, 0x12, 0x36, 0x24, 0x36, // ≈  \xf7
//  0x06, 0x0F, 0x09, 0x0F, 0x06, // °  \xf8
//  0x00, 0x00, 0x18, 0x18, 0x00, // ∙  \xf9
//  0x00, 0x00, 0x10, 0x10, 0x00, // ·  \xfa
//  0x30, 0x40, 0xFF, 0x01, 0x01, // √  \xfb
//  0x00, 0x1F, 0x01, 0x01, 0x1E, // ⁿ  \xfc
//  0x00, 0x19, 0x1D, 0x17, 0x12, // ²  \xfd
//  0x00, 0x3C, 0x3C, 0x3C, 0x3C, // ■  \xfe
//  0x00, 0x00, 0x00, 0x00, 0x00, // NBSP  \xff
//};


unsigned char getFlash( const unsigned char * mem, unsigned int idx  ){
  return pgm_read_byte( &(mem[idx]) );
}

void sendCommand(unsigned char command)
{
  tw_begin();                       		//initialize I2C
  tw_beginTransmission(SlaveAddress); 		// begin I2C communication

  tw_write(SSD1306OLED_Command_Mode);	     // Set OLED Command mode
  tw_write(command);

  tw_endTransmission(1);    		     	// End I2C communication
}

void sendData(unsigned char Data)
{
  tw_begin();                    //initialize I2C
  tw_beginTransmission(SlaveAddress); // begin I2C transmission
  tw_write(SSD1306OLED_Data_Mode);            // data mode
  tw_write(Data);
  tw_endTransmission(1);                    // stop I2C transmission
}

void init()
{

	//tw_begin();

	//delay(5);	//wait for OLED hardware init
	// constructor(128, 64);
	//SlaveAddress = address;

	sendCommand(SSD1306OLED_Display_Off_Cmd);    				/*display off*/

	sendCommand(Set_Multiplex_Ratio_Cmd);    					/*multiplex ratio*/
	sendCommand(0x3F);    										/*duty = 1/64*/

	sendCommand(Set_Display_Offset_Cmd);    					/*set display offset*/
	sendCommand(0x00);


	sendCommand(Set_Memory_Addressing_Mode_Cmd); 				//set addressing mode
	sendCommand(HORIZONTAL_MODE); 								//set horizontal addressing mode

	sendCommand(0xB0); 										//set page address
	sendCommand(0x00); 										//set column lower address
	sendCommand(0x10); 										//set column higher address



	sendCommand(0x40);    										/*set display starconstructort line*/

	sendCommand(Set_Contrast_Cmd);    							/*contract control*/
	sendCommand(0xcf);    										/*128*/

	sendCommand(Segment_Remap_Cmd);   						 	/*set segment remap*/

	sendCommand(COM_Output_Remap_Scan_Cmd);    				/*Com scan direction*/

	sendCommand(SSD1306OLED_Normal_Display_Cmd);    			/*normal / reverse*/

	sendCommand(Set_Display_Clock_Divide_Ratio_Cmd);    		/*set osc division*/
	sendCommand(0x80);

	sendCommand(Set_Precharge_Period_Cmd);    					/*set pre-charge period*/
	sendCommand(0xf1);

	sendCommand(Set_COM_Pins_Hardware_Config_Cmd);    			/*set COM pins*/
	sendCommand(0x12);

	sendCommand(Set_VCOMH_Deselect_Level_Cmd);    				/*set vcomh*/
	sendCommand(0x30);

	sendCommand(Deactivate_Scroll_Cmd);

	sendCommand(Charge_Pump_Setting_Cmd);    					/*set charge pump enable*/
	sendCommand(Charge_Pump_Enable_Cmd);

	sendCommand(SSD1306OLED_Display_On_Cmd);    				/*display ON*/
}

void clipArea(unsigned char col, unsigned char row, unsigned char w, unsigned char h){

	tw_begin();                    						//initialize I2C
	tw_beginTransmission(SlaveAddress); 				// begin I2C transmission
	tw_write(SSD1306OLED_Command_Mode);            		// data mode
	tw_write(Set_Column_Address_Cmd);
	tw_write(0);

	tw_write(col);
	tw_write(col+w-1);

	tw_endTransmission(1);                    			// stop I2C transmission

	tw_begin();                    						//initialize I2C
	tw_beginTransmission(SlaveAddress); 				// begin I2C transmission
	tw_write(SSD1306OLED_Command_Mode);            		// data mode
	tw_write(Set_Page_Address_Cmd);
	tw_write(0);

	tw_write(row);
	tw_write(row+h-1);

	tw_endTransmission(1);                    			// stop I2C transmission

}

void cursorTo(unsigned char col, unsigned char row){
  clipArea(col, row, 128-col, 8-row);
}

void startScreen(){

  sendCommand(0x00 | 0x0);  // low col = 0
  sendCommand(0x10 | 0x0);  // hi col = 0
  sendCommand(0x40 | 0x0); // line #0

}

void clear() {

	sendCommand(0x00 | 0x0);  // low col = 0
	sendCommand(0x10 | 0x0);  // hi col = 0
	sendCommand(0x40 | 0x0); // line #0

	clipArea(0,0,128,8);

	for (uint16_t i=0; i<=((128*64/8)/16); i++){
		// send a bunch of data in one xmission
		tw_beginTransmission(SlaveAddress);
		tw_write(SSD1306OLED_Data_Mode);            // data mode
		for (uint8_t k=0;k<16;k++){
			tw_write( 0 );
		}
		tw_endTransmission(1);
	}

}


void displayX(int off) {
  sendCommand(0x00 | 0x0);  // low col = 0
  sendCommand(0x10 | 0x0);  // hi col = 0
  sendCommand(0x40 | 0x0); // line #0

    for (uint16_t i=0; i<=((128*64/8)/16); i++)
    {
      // send a bunch of data in one xmission
      tw_beginTransmission(SlaveAddress);
      tw_write(SSD1306OLED_Data_Mode);            // data mode
      for (uint8_t k=0;k<16;k++){
        tw_write((uint8_t) i*16 + k + off);
      }
      tw_endTransmission(1);
    }
}



void printChar( unsigned char ch ){

    unsigned char data[5];

	//address = hex value of char * 5
	//get 5 bytes

    data[0]= getFlash(digital_font5x7, (ch*5)-156 );
    data[1]= getFlash(digital_font5x7, (ch*5) - 156 + 1);
    data[2]= getFlash(digital_font5x7, (ch*5) - 156 + 2);
    data[3]= getFlash(digital_font5x7, (ch*5) - 156 + 3);
    data[4]= getFlash(digital_font5x7, (ch*5) - 156 + 4);

    tw_beginTransmission(SlaveAddress);
    tw_write(SSD1306OLED_Data_Mode);            // data mode

    tw_write( 0x00 );
    tw_write( data[0] );
    tw_write( data[1] );
    tw_write( data[2] );
    tw_write( data[3] );
    tw_write( data[4] );
    tw_write( 0x00 );

    tw_endTransmission(1);

}

void printString( char * pText ){
  unsigned char i;
  unsigned char len = strlen( pText );

  for (i=0;i<len;i++){
     printChar( pText[i] );
  }

}


void drawImage( const unsigned char * img, unsigned char col, unsigned char row, unsigned char w, unsigned char h ){
  unsigned int i,data;

  clipArea( col, row, w, h);

  for (i=0;i< (w*h);i++){

      data= getFlash( img, i);

      tw_beginTransmission(SlaveAddress);
     tw_write(SSD1306OLED_Data_Mode);            // data mode

      tw_write((uint8_t) data );
      tw_endTransmission(1);

  }

}
