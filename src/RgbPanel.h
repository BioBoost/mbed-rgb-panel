#pragma once

#include "mbed.h"


class RgbPanel
{
    private: 
    static const int BUFFER_SIZE = 1024;
    
    public:
    RgbPanel(
        PinName r0, PinName g0, PinName b0,
        PinName r1, PinName g1, PinName b1,
        PinName a, PinName b, PinName c, PinName d,
        PinName clk, PinName stb, PinName oe);
    
    int buffer[BUFFER_SIZE];
    
    void clear();
    void draw();
    
    private:
    BusOut rgb0;
    BusOut rgb1;
    BusOut demux;
    DigitalOut clk;
    DigitalOut stb;
    DigitalOut oe;
    
    inline void clock();
    inline void latch();
    inline void blank();
    
};