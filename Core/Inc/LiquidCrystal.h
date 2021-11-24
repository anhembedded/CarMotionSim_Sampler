#ifndef LiquidCrystal_h
#define LiquidCrystal_h

#include "../USER_API/UHAL/uhal_stm32f407_platform.hpp"
#include <cinttypes>
#include "../USER_API/UHAL/Print.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

class LiquidCrystal : public uhal_stm32f407_platform, public Print {
public:
  LiquidCrystal(uint16_t rs, uint16_t enable,
		uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3,
		uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7);
  LiquidCrystal(uint16_t rs, uint16_t rw, uint16_t enable,
		uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3,
		uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7);
  LiquidCrystal(uint16_t rs, uint16_t rw, uint16_t enable,
		uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3);
  LiquidCrystal(uint16_t rs, uint16_t enable,
		uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3);

  void init(uint16_t fourbitmode, uint16_t rs, uint16_t rw, uint16_t enable,
	    uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3,
	    uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7);
    
  void begin(uint16_t cols, uint16_t rows, uint16_t charsize = LCD_5x8DOTS);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void setRowOffsets(int row1, int row2, int row3, int row4);
  void createChar(uint16_t, uint16_t[]);
  void setCursor(uint16_t, uint16_t); 
  virtual size_t write(uint8_t);
  void command(uint16_t);
  
  using Print::write;
private:
  void send(uint16_t, uint16_t);
  void write4bits(uint16_t);
  void write8bits(uint16_t);
  void pulseEnable();

  uint16_t _rs_pin; // LOW: command.  HIGH: character.
  uint16_t _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
  uint16_t _enable_pin; // activated by a HIGH pulse.
  uint16_t _data_pins[8];

  uint16_t _displayfunction;
  uint16_t _displaycontrol;
  uint16_t _displaymode;

  uint16_t _initialized;

  uint16_t _numlines;
  uint16_t _row_offsets[4];
};

#endif
