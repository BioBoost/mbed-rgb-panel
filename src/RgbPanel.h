#pragma once

#include "mbed.h"

class RgbPanel {
    
  public:
    RgbPanel(
        PinName r0, PinName g0, PinName b0,
        PinName r1, PinName g1, PinName b1,
        PinName a, PinName b, PinName c, PinName d,
        PinName clk, PinName stb, PinName oe);
  
  public: 
    static const size_t BUFFER_SIZE = 1024;
    static const size_t HALF_BUFFER_SIZE = BUFFER_SIZE/2;
    uint32_t buffer[BUFFER_SIZE];
    
  public:
    void clear(void);
    void draw(void);

  private:
    inline void output_row(uint8_t address, const uint32_t * topBuffer, const uint32_t * bottomBuffer);
    inline void clear_row(uint8_t address);
    inline void select_row(uint8_t address);

  private:
    inline void clock(void);
    inline void latch(void);
    inline void enable_output(void);
    inline void disable_output(void);
    
  private:
    const uint8_t ROWS = 16;
    const uint8_t COLS = 32;

    BusOut rgb0;
    BusOut rgb1;
    BusOut demux;
    DigitalOut clk;
    DigitalOut stb;
    DigitalOut oe;
};