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

void RgbPanel::clear(void) {
  memset(buffer, 0, sizeof(buffer[0])*BUFFER_SIZE);
  draw();
}

void RgbPanel::draw(void) {
  clk = 0;
  stb = 0;

  for (int row = 0; row < ROWS+1; row++) {
    // Fix ghosting by clearing previous selected row !
    // (Expensive as it doubles the time for drawing a panel)

    clear_row(row-1);

    // Last line get's more 'on' time, that's why it appears more bright.
    // Fix this by iterating once more but not writing actual rgb data.
    if (row == ROWS) break;

    output_row(row, (buffer+(COLS*row)), (buffer+(COLS*row)+HALF_BUFFER_SIZE));
  }
}

inline void RgbPanel::output_row(uint8_t address, const uint32_t * topBuffer, const uint32_t * bottomBuffer) {
  select_row(address);

  for (uint8_t i = 0; i < COLS; i++) {
    rgb0 = topBuffer[i];
    rgb1 = bottomBuffer[i];
    clock();
  }
  latch();
}


inline void RgbPanel::clear_row(uint8_t address) {
  select_row(address);

  for (int i = 0; i < COLS; i++) {
    rgb0 = 0;
    rgb1 = 0;
    clock();
  }
  latch();
}

inline void RgbPanel::select_row(uint8_t address) {
  // Switch row
  disable_output();
  demux = address;
  enable_output();
}

// The CLK (clock) signal marks the arrival of each bit of data.
inline void RgbPanel::clock(void) {
  clk = 1;
  clk = 0;
}

// The LAT (latch) signal marks the end of a row of data.
inline void RgbPanel::latch(void) {
  stb = 1;
  stb = 0;
}

// OE (output enable) switches the LEDs off when transitioning from one row to the next.
inline void RgbPanel::enable_output(void) {
  oe = 0;
}

inline void RgbPanel::disable_output(void) {
  oe = 1;
}
