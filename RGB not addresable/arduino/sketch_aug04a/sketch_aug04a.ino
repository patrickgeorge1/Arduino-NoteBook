#define RED 11
#define GREEN 10
#define BLUE 9
#define NR_OF_COLOR_MODES 4
#define TIME_OF_C0LOR_MODES 5000
#define RAINBOW_STATES 58


int color_mode = 0;
int color_index = 0;
unsigned long last_time_color_change = 0;

void setup() {
  Serial.begin (9600);
  Serial.setTimeout(10);
}

void serialEvent() {
  
   int luminosity = Serial.readString().toInt(); 
   calm_to_fury(luminosity);

//   switch(color_mode) {
//      case 0:
//        white_bounce(luminosity);
//        break;
//        
//      case 1:
//        rgb_wheel(luminosity);
//        break;
//        
//      case 2:
//        random_color(luminosity);
//        break;
//
//      case 3:
//        rgb_proportion_luminosity(luminosity);
//        break;
//    }
}

void white_bounce(int luminosity) {
   int red = 33 * luminosity / 100;
   int green = 33 * luminosity / 100;
   int blue = 33 * luminosity / 100;

   analogWrite(RED, red);
   analogWrite(GREEN, green);
   analogWrite(BLUE, blue);
}

void rgb_wheel(int luminosity) {
    //                                                               R -> O                  O -> G                                           G -> V                                       V -> A                                     A -> I               I -> V
    //  index as 0 -> 57
    int r[] = { 100, 98, 96, 94, 90, 88, 86, 84, 80, 78, 75, 72, 70, 68, 66, 64, 61, 58, 55, 52, 50, 47, 45, 41, 38, 35, 30, 25, 20, 15, 10, 5,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  3,  6,  9,  13,  20,  24,  28,  32,  36, 37, 38, 39, 40, 41 }; 
    int g[] = { 0,   2,  4,  6,  8,  10, 12, 14, 16, 18, 20, 23, 26, 30, 33, 35, 38, 41, 44, 47, 50, 53, 55, 59, 61, 65, 70, 75, 80, 85, 90, 95, 100, 95, 90, 80, 70, 60, 50, 40, 30, 20, 10,   0,  0,  0,  0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0 };
    int b[] = { 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  5, 10, 20, 30, 40, 50, 60, 70, 80, 100, 97, 94, 91,  87,  80,  76,  72,  67,  63, 63, 62, 61, 60, 59 };

    int red   =  r[color_index] * luminosity / 100;
    int green =  g[color_index] * luminosity / 100;
    int blue  =  b[color_index] * luminosity / 100;
    color_index = (color_index + 1) % RAINBOW_STATES;

    analogWrite(RED, red);
    analogWrite(GREEN, green);
    analogWrite(BLUE, blue);
}

void random_color(int luminosity) {
    int red = random(0, 100);
    int blue = random(0, 100 - red);
    int green = 100 - (red + blue);

    red = red * luminosity / 100;
    green = green * luminosity / 100;
    blue = blue * luminosity / 100;

    analogWrite(RED, red);
    analogWrite(GREEN, green);
    analogWrite(BLUE, blue);
}

void rgb_proportion_luminosity(int luminosity) {
   int red = map(0, 255, 20, 50, luminosity);
   int green = map(0, 255, 50, 10, luminosity);
   int blue = map(0, 255, 30, 40, luminosity);

   red = red * luminosity / 100;
   green = green * luminosity / 100;
   blue = blue * luminosity / 100;
   
   analogWrite(RED, red);
   analogWrite(GREEN, green);
   analogWrite(BLUE, blue);
}

void calm_to_fury(int luminosity) {
      int red = map(0, 255, 0, 44, luminosity);
      int blue = 56;
      int green = 100 - (red + blue);
      
      red = red * 255 / 100;
      green = green * 255 / 100;
      blue = blue * 255 / 100;
      
      analogWrite(RED, red);
      analogWrite(GREEN, green);
      analogWrite(BLUE, blue);
}

void loop() {
    // loop through color modes every 
//    if (millis() - TIME_OF_C0LOR_MODES > 3500) {
//        last_time_color_change = millis();
//        color_mode = (color_mode + 1) %  NR_OF_COLOR_MODES;
//    }
}
