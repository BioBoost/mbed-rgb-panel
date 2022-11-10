#include "rgbpanel.h"

RgbPanel::RgbPanel(
    PinName _r0, PinName _g0, PinName _b0,
    PinName _r1, PinName _g1, PinName _b1,
    PinName _a, PinName _b, PinName _c, PinName _d,
    PinName _clk, PinName _stb, PinName _oe)
    :
    rgb0(_r0, _g0, _b0), rgb1(_r1, _g1, _b1),
    demux(_a, _b, _c, _d), clk(_clk), stb(_stb), oe(_oe)
{
    clear();
}


void RgbPanel::clear()
{
    for(int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 0x00;
    }
}

void RgbPanel::draw()
{
    for(int row = 0; row < 16; row++) {
        demux = row - 1;
        //wait_us(1000); // disable row ghosting
        for(int i = 0; i < 32; i++) {
            rgb0 = buffer[(32*row) + i];
            rgb1 = buffer[(32*row) + i + (BUFFER_SIZE / 2)];
            clock();
        }
        latch();
        
    }
    blank();
}

inline void RgbPanel::clock()
{
    clk = 1;
    clk = 0;
}
inline void RgbPanel::latch()
{
    stb = 1;
    stb = 0;
}
inline void RgbPanel::blank()
{
    oe = 1;
    oe = 0;
}
