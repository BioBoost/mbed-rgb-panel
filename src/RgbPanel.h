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
    static const int BUFFER_SIZE = 1024;
    uint32_t buffer[BUFFER_SIZE];
    
  public:
    void clear();
    void draw();

  private:
    inline void clock();
    inline void latch();
    inline void blank();
    
  private:
    BusOut rgb0;
    BusOut rgb1;
    BusOut demux;
    DigitalOut clk;
    DigitalOut stb;
    DigitalOut oe;
};