/* 
 * File:   LCD.c
 * Author: ahmed
 *
 * Created on March 2, 2023, 3:01 AM
 */
#include "LCD.h"

#if LCD_MODULE == MODULE_ENABLE

#if LCD_MODE == CHAR_LCD_8BIT_MODE
static Std_ReturnType lcd_8bit_set_cursor_pos(const char_lcd_t* lcd_obj, uint8 row, uint8 col);
#elif LCD_MODE == CHAR_LCD_4BIT_MODE
static Std_ReturnType lcd_4bit_set_cursor_pos(const char_lcd_t* lcd_obj, uint8 row, uint8 col);
static Std_ReturnType lcd_send_4bit(const char_lcd_t* lcd_obj, uint8 _data_command);
#endif
static Std_ReturnType lcd_send_enable_signal(const char_lcd_t* lcd_obj);
static void* my_memset(void* str, uint8 ch, uint8 str_size);

/* ---------------------- Function Definitions ----------------------*/
#if (LCD_MODE == CHAR_LCD_4BIT_MODE)
Std_ReturnType lcd_4bit_initialize(const char_lcd_t* lcd_obj)
{
   Std_ReturnType ret = E_NOT_OK;
    uint8 l_pin_counter = ZERO_INIT;
    if(NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = GPIO_pin_initialize(&(lcd_obj->RS_pin));
        ret = GPIO_pin_initialize(&(lcd_obj->E_pin));
        for(l_pin_counter=0; l_pin_counter < 4; l_pin_counter++)
        {
            ret = GPIO_pin_initialize(&(lcd_obj->lcd_data_pins[l_pin_counter]));
        }
        _delay_ms(20);
        ret = lcd_4bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINES_COMMAND);
        _delay_ms(5);
        ret = lcd_4bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINES_COMMAND);
        _delay_us(150);
        ret = lcd_4bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINES_COMMAND);
        
        ret = lcd_send_4bit(lcd_obj, 0x02); // start operation in 4-bit mode
        ret = lcd_4bit_send_command(lcd_obj, _LCD_CURSOR_OFF_DISPLAY_OFF);
        ret = lcd_4bit_send_command(lcd_obj, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd_obj, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd_obj, _LCD_ENTRY_MODE_INC_NO_SHIFT);
        ret = lcd_4bit_send_command(lcd_obj, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd_obj, DDRAM_START_ADDRESS);  // Set DDRAM to address 0, start at row 1 column 1
        ret = lcd_4bit_send_command(lcd_obj, _LCD_4BIT_MODE_2LINES_COMMAND);    // Set 4bit lcd mode
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_command(const char_lcd_t* lcd_obj, uint8 lcd_command)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = GPIO_pin_write_logic(&(lcd_obj->RS_pin), GPIO_LOW);
        ret = lcd_send_4bit(lcd_obj, (lcd_command >> 4));    // Send high Nibble
        ret = lcd_send_enable_signal(lcd_obj);               // Send enable signal
        ret = lcd_send_4bit(lcd_obj, lcd_command);           // Send low Nibble
        ret = lcd_send_enable_signal(lcd_obj);               // Send enable signal
    }
    
    return ret;
}
Std_ReturnType lcd_4bit_send_char_data(const char_lcd_t* lcd_obj, uint8 lcd_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = GPIO_pin_write_logic(&(lcd_obj->RS_pin), GPIO_HIGH);
        ret = lcd_send_4bit(lcd_obj, (lcd_data >> 4));       // Send high Nibble
        ret = lcd_send_enable_signal(lcd_obj);               // Send enable signal
        ret = lcd_send_4bit(lcd_obj, lcd_data);              // Send low Nibble
        ret = lcd_send_enable_signal(lcd_obj);               // Send enable signal
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_char_data_pos(const char_lcd_t* lcd_obj, uint8 row, uint8 col, uint8 lcd_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if (NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor_pos(lcd_obj, row, col);
        ret = lcd_4bit_send_char_data(lcd_obj, lcd_data);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string_data(const char_lcd_t* lcd_obj, uint8* str)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 index = ZERO_INIT;
    if (NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while('\0' != *(str+index))
        {
            ret = lcd_4bit_send_char_data(lcd_obj, *(str + index));
            index++;
        }     
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string_data_pos(const char_lcd_t* lcd_obj, uint8 row, uint8 col, const uint8* str)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 index = ZERO_INIT;
    if (NULL == lcd_obj || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor_pos(lcd_obj, row, col);
        while('\0' != *(str+index))
        {
            ret = lcd_4bit_send_char_data(lcd_obj, *(str + index));
            index++;
        }   
    }
    
    return ret;
}
Std_ReturnType lcd_4bit_send_custom_char(const char_lcd_t* lcd_obj, uint8 row, uint8 col, const uint8 _char[], uint8 mem_pos)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_counter = ZERO_INIT;
    if (NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        // set Address counter to CGRAM 
        ret = lcd_4bit_send_command(lcd_obj, (CGRAM_START_ADDRESS + (mem_pos * 8)));
        // sending the special character pattern to save in CGRAM
        for(l_counter=0; l_counter < 8; ++l_counter)
        {
            ret = lcd_4bit_send_char_data(lcd_obj, _char[l_counter]);
        }
        // Sending the Character Codes (DDRAM) that mapping Character Patterns (CGRAM Data)
        //0x00->1st character pattern, 0x01->2nd character pattern and so on.. until 0x07->eighth char pattern
        ret = lcd_4bit_send_char_data_pos(lcd_obj, row, col, mem_pos);
    }
    return ret;
}

#elif (LCD_MODE == CHAR_LCD_8BIT_MODE)
Std_ReturnType lcd_8bit_initialize(const char_lcd_t* lcd_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_pin_counter = ZERO_INIT;
    if(NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = GPIO_pin_initialize(&(lcd_obj->RS_pin));
        ret = GPIO_pin_initialize(&(lcd_obj->E_pin));
        for(l_pin_counter=0; l_pin_counter < 8; l_pin_counter++)
        {
            ret = GPIO_pin_initialize(&(lcd_obj->lcd_data_pins[l_pin_counter]));
        }
        _delay_ms(40);
        ret = lcd_8bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINES_COMMAND);
        _delay_ms(5);
        ret = lcd_8bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINES_COMMAND);
        _delay_us(110);
        ret = lcd_8bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINES_COMMAND);
        
        ret = lcd_8bit_send_command(lcd_obj, _LCD_CURSOR_OFF_DISPLAY_OFF);
        ret = lcd_8bit_send_command(lcd_obj, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd_obj, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd_obj, _LCD_ENTRY_MODE_INC_NO_SHIFT);
        ret = lcd_8bit_send_command(lcd_obj, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd_obj, DDRAM_START_ADDRESS);  // Set DDRAM to address 0, start at row 1 column 1
        ret = lcd_8bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINES_COMMAND);    // Set 8bit lcd mode
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_command(const char_lcd_t* lcd_obj, uint8 lcd_command)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_lcd_pin_counter = ZERO_INIT;
    
    if(NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        // Write 0 on Register select pin to accept command
        ret = GPIO_pin_write_logic(&(lcd_obj->RS_pin), GPIO_LOW);
        // Sending the command through data pins (D0 : D7)
        for(l_lcd_pin_counter=0; l_lcd_pin_counter < 8; l_lcd_pin_counter++)
        {
            ret = GPIO_pin_write_logic(&(lcd_obj->lcd_data_pins[l_lcd_pin_counter]), (lcd_command >> l_lcd_pin_counter & BIT_MASK));
        }
        // Send enable signal
        ret = lcd_send_enable_signal(lcd_obj);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_char_data(const char_lcd_t* lcd_obj, uint8 lcd_data)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_lcd_pin_counter = ZERO_INIT;
    if(NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        // Write 1 on Register select pin to accept data
        ret = GPIO_pin_write_logic(&(lcd_obj->RS_pin), GPIO_HIGH);
        // Sending the command through data pins (D0 : D7)
        for(l_lcd_pin_counter=0; l_lcd_pin_counter < 8; l_lcd_pin_counter++)
        {
            ret = GPIO_pin_write_logic(&(lcd_obj->lcd_data_pins[l_lcd_pin_counter]), ((lcd_data >> l_lcd_pin_counter) & BIT_MASK));
        }
        // Send enable signal
        ret = lcd_send_enable_signal(lcd_obj);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_char_data_pos(const char_lcd_t* lcd_obj, uint8 row, uint8 col, uint8 lcd_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor_pos(lcd_obj, row, col);
        ret = lcd_8bit_send_char_data(lcd_obj, lcd_data);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_string_data(const char_lcd_t* lcd_obj, uint8* str)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 index = 0;
    if(NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while('\0' != *(str+index))
        {
            ret = lcd_8bit_send_char_data(lcd_obj, *(str+index));
            index++;
        }
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_string_data_pos(const char_lcd_t* lcd_obj, uint8 row, uint8 col, uint8* str)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor_pos(lcd_obj, row, col);
        ret = lcd_8bit_send_string_data(lcd_obj, str);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_custom_char(const char_lcd_t* lcd_obj, uint8 row, uint8 col, uint8 _char[], uint8 mem_pos)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == lcd_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        Std_ReturnType ret = E_NOT_OK;
        uint8 l_counter = ZERO_INIT;
        if (NULL == lcd_obj)
        {
            ret = E_NOT_OK;
        }
        else
        {
            // set Address counter to CGRAM 
            ret = lcd_8bit_send_command(lcd_obj, (CGRAM_START_ADDRESS + (mem_pos * 8)));
            // sending the special character pattern to save in CGRAM, font = (5*8).
            for(l_counter=0; l_counter <= 7; ++l_counter)
            {
                ret = lcd_8bit_send_char_data(lcd_obj, _char[l_counter]);
            }
            ret = lcd_8bit_send_char_data_pos(lcd_obj, row, col, mem_pos);
        }
    
    }
    return ret;
}
#endif

/* ---------------------- Helper Functions ------------------------*/
/**
 * @brief this function used to set specific locations in a string with determined value
 * @param str
 * @param ch
 * @param str_size
 * @return pointer to void type
 */
static void* my_memset(void* str, uint8 ch, uint8 str_size)
{
    uint8 counter = 0;
    while(str_size--)
    {
        *((uint8*)str + counter) = ch;
        counter++;
    }
    return str;
}

Std_ReturnType LCD_convert_byte_to_string(uint8 data, uint8* str)
{
    // data range = 0:255. max size of the string is set to 4 (3 for data , 1 for '\0')
    Std_ReturnType ret = E_NOT_OK;
    uint8 index = 0;
    uint8 tens = 100;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
        str = (uint8* )my_memset(str, '\0', 4);
        // sprintf(str, "%i", data);    // this function return the number as string
        if (0 == data)
        {
            *(str) = 48;
        }
        else
        {
             while (tens > 0)
            {
                if ((data / tens) > 0)
                {
                    *(str + index) = ((data / tens) % 10) + 48;
                    index++;
                }
                tens = tens / 10;
            }
        }
    }
    return ret;
}

Std_ReturnType LCD_convert_short_to_string(uint16 data, uint8* str)
{
    // data range = 0:65535 max size of the string is set to 6 (5 for data , 1 for '\0')
    Std_ReturnType ret = E_NOT_OK;
    uint8 index = 0;
    uint16 tens = 10000;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
        str = (uint8* )my_memset(str, ' ', 5);
        str[5] = '\0';
        // sprintf(str, "%i", data);    // this function return the number as string
        if (0 == data)
        {
            *(str) = 48;
        }
        else
        {
             while (tens > 0)
            {
                if ((data / tens) > 0)
                {
                    *(str + index) = ((data / tens) % 10) + 48;
                    index++;
                }
                tens = tens / 10;
            }
        }
    }
    return ret;
}
    
Std_ReturnType LCD_convert_int_to_string(uint32 data, uint8* str)
{
    // data range = 0:4294967296 max size of the string is set to 11 (10 for data , 1 for '\0')
    Std_ReturnType ret = E_NOT_OK;
    uint8 index = 0;
    uint32 tens = 1000000000;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
        str = (uint8* )my_memset(str, '\0', 11);
        // sprintf(str, "%i", data);    // this function return the number as string
        if (0 == data)
        {
            *(str) = 48;
        }
        else
        {
             while (tens > 0)
            {
                if ((data / tens) > 0)
                {
                    *(str + index) = ((data / tens) % 10) + 48;
                    index++;
                }
                tens = tens / 10;
            }
        }
    }
    return ret;
}

#if (LCD_MODE == CHAR_LCD_8BIT_MODE)
static Std_ReturnType lcd_8bit_set_cursor_pos(const char_lcd_t* lcd_obj, uint8 row, uint8 col)
{
    Std_ReturnType ret = E_OK;
    col--;  // to ensure zero indexing
    uint8 row1_offset = 0x00, 
            row2_offset = 0x40, 
            row3_offset = 0x14, 
            row4_offset = 0x40 + 0x14;
    switch(row)
    {
        case ROW1:
            ret = lcd_8bit_send_command(lcd_obj, DDRAM_START_ADDRESS + row1_offset + col);    // 0x80 + col
            break;
        case ROW2:
            ret = lcd_8bit_send_command(lcd_obj, DDRAM_START_ADDRESS + row2_offset + col);   // 0xC0 + col
            break;
        case ROW3:
            ret = lcd_8bit_send_command(lcd_obj, DDRAM_START_ADDRESS + row3_offset + col); // 0x94 + col
            break;
        case ROW4:
            ret = lcd_8bit_send_command(lcd_obj, DDRAM_START_ADDRESS + row4_offset + col); // 0xD4 + col
            break;
        default:
            break;
    }
    return ret;
}

#elif (LCD_MODE == CHAR_LCD_4BIT_MODE)
static Std_ReturnType lcd_4bit_set_cursor_pos(const char_lcd_t* lcd_obj, uint8 row, uint8 col)
{
    Std_ReturnType ret = E_OK;
    col--;  // to ensure zero indexing
    uint8 row1_offset = 0x00, 
            row2_offset = 0x40, 
            row3_offset = 0x14, 
            row4_offset = 0x40 + 0x14;
    switch(row)
    {
        case ROW1:
            ret = lcd_4bit_send_command(lcd_obj, DDRAM_START_ADDRESS + row1_offset + col);    // 0x80 + col
            break;
        case ROW2:
            ret = lcd_4bit_send_command(lcd_obj, DDRAM_START_ADDRESS + row2_offset + col);   // 0xC0 + col
            break;
        case ROW3:
            ret = lcd_4bit_send_command(lcd_obj, DDRAM_START_ADDRESS + row3_offset + col); // 0x94 + col
            break;
        case ROW4:
            ret = lcd_4bit_send_command(lcd_obj, DDRAM_START_ADDRESS + row4_offset + col); // 0xD4 + col
            break;
        default:
            break;
    }
    return ret;
}

static Std_ReturnType lcd_send_4bit(const char_lcd_t* lcd_obj, uint8 _data_command)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_pin_counter = ZERO_INIT;
    for (l_pin_counter = 0; l_pin_counter < 4; l_pin_counter++)
    {
        ret = GPIO_pin_write_logic(&(lcd_obj->lcd_data_pins[l_pin_counter]), ((_data_command >> l_pin_counter) & BIT_MASK));
    }
    return ret;
}
#endif

static Std_ReturnType lcd_send_enable_signal(const char_lcd_t* lcd_obj)
{
    Std_ReturnType ret = E_OK;
    ret = GPIO_pin_write_logic(&(lcd_obj->E_pin), GPIO_HIGH);
    _delay_us(5);
    ret = GPIO_pin_write_logic(&(lcd_obj->E_pin), GPIO_LOW);
    return ret;
}


#endif
