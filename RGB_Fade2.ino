#define LED_RED 9
#define LED_BLUE 10
#define LED_GREEN 11

#define SPEED 35
#define SPEEDACC 2

void setLED(int hue, int l)
{
  int col[3] = { 0,0,0 };
  getRGB(hue, 255, l, col);
  ledWrite(col[0], col[1], col[2]);
}

void getRGB(int hue, int sat, int val, int colors[3])
{
  // hue: 0-359, sat: 0-255, val (lightness): 0-255
  int r, g, b, base;

  if (sat == 0)
  { // Achromatic color (gray).
    colors[0]=val;
    colors[1]=val;
    colors[2]=val;
  } 
  else
  {
    base = ((255 - sat) * val)>>8;
    switch(hue/60) {
    case 0:
      r = val;
      g = (((val-base)*hue)/60)+base;
      b = base;
      break;
    case 1:
      r = (((val-base)*(60-(hue%60)))/60)+base;
      g = val;
      b = base;
      break;
    case 2:
      r = base;
      g = val;
      b = (((val-base)*(hue%60))/60)+base;
      break;
    case 3:
      r = base;
      g = (((val-base)*(60-(hue%60)))/60)+base;
      b = val;
      break;
    case 4:
      r = (((val-base)*(hue%60))/60)+base;
      g = base;
      b = val;
      break;
    case 5:
      r = val;
      g = base;
      b = (((val-base)*(60-(hue%60)))/60)+base;
      break;
    }
    colors[0]=r;
    colors[1]=g;
    colors[2]=b;
  }
}

void ledWrite(int r, int g, int b)
{
  analogWrite(LED_RED, 255-r);
  analogWrite(LED_GREEN, 255-g);
  analogWrite(LED_BLUE, 255-b);
}

void setup()
{
  randomSeed(analogRead(0));
}

int hue2 = 0;
double light2 = 128;
double fadeAmount = 1;
void loop()
{
  setLED(hue2, (int) light2);
  hue2++;
  if(hue2 == 360)
  {
    hue2 = 0;
  }
  light2 = light2 + fadeAmount;
  if (light2 < 52 || light2 > 193) //76..178
  {
    fadeAmount = -fadeAmount;
  }
  delay(random(SPEED, SPEED * SPEEDACC));
}

