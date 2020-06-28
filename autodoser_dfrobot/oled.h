U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI

namespace oled {
void initialise() {
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
}
}

void draw(char* to_draw) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, to_draw);
}

void display_alternate(float phAverage, float ecAverage) {
  char phAverageChar[8];
  dtostrf(phAverage, 6, 2, phAverageChar);

  char ecAverageChar[8];
  dtostrf(ecAverage, 6, 2, ecAverageChar);

  u8g.firstPage();
  do {
    draw(phAverageChar);
  } while ( u8g.nextPage() );

  delay(500);
  u8g.firstPage();
  do {
    draw(ecAverageChar);
  } while ( u8g.nextPage() );
}
