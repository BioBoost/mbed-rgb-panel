#include "RgbPanel.h"

RgbPanel::RgbPanel(
  PinName _r0, PinName _g0, PinName _b0,
  PinName _r1, PinName _g1, PinName _b1,
  PinName _a, PinName _b, PinName _c, PinName _d,
  PinName _clk, PinName _stb, PinName _oe)
  :
  rgb0(_r0, _g0, _b0), rgb1(_r1, _g1, _b1),
  demux(_a, _b, _c, _d), clk(_clk), stb(_stb), oe(_oe) {

  clear();
}

void RgbPanel::clear() {
  memset(buffer, 0, sizeof(buffer[0])*BUFFER_SIZE);
  draw();
}

// The LAT (latch) signal marks the end of a row of data.
// OE (output enable) switches the LEDs off when transitioning from one row to the next. I think OE is also per shift register and not all at once
// The CLK (clock) signal marks the arrival of each bit of data.

void RgbPanel::draw() {
  clk = 0;
  stb = 0;

  oe = 1;     // disable output

  for (int row = 0; row < 16; row++) {
    // Fix ghosting by clearing previous selected row !
    // (Expensive as it doubles the time for drawing a panel)
    for (int i = 0; i < 32; i++) {
      rgb0 = 0;
      rgb1 = 0;
      clk = 1;      // Clock in
      clk = 0;      // Clock disable
    }
    stb = 1;        // End of row data
    stb = 0;        // Disable

    // Switch row
    oe = 1;         // Disable output
    demux = row;
    oe = 0;


    // Output actual data
    for (int i = 0; i < 32; i++) {
      rgb0 = buffer[(32*row) + i];
      rgb1 = buffer[(32*row) + i + (BUFFER_SIZE / 2)];

      clk = 1;      // Clock in
      clk = 0;      // Clock disable
    }

    stb = 1;        // End of row data
    stb = 0;        // Disable

  }



  oe = 0;   // enable output


}

inline void RgbPanel::clock() {
  clk = 0;
  clk = 1;
}

inline void RgbPanel::latch() {
  stb = 0;
  stb = 1;
}

inline void RgbPanel::blank() {
  oe = 1;
  oe = 0;
}
