
// Pin out for my setup
// This was tested on an Arduino Uno with RGB LED in outputs 9-12
// (Beware of beginner mistakes)
int red_LED = 11;
int green_LED = 10;
int blue_LED = 9;
int ground_LED = 12;

// State values of Lorenz system
float x1, y1, z1, x, y, z,  dt;


void setup()  {
  Serial.begin(9600);  // For debugging and tuning

  pinMode(red_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);
  pinMode(ground_LED, OUTPUT);
  digitalWrite(12, LOW);

  // Give start value to speed up start
  x = -3;
  y = -4;
  z =  21;
}


void step() {
  float dt = 0.0001;
  float x1=x + ( -10.0*x  + 10.0*y    ) * dt;
  float y1=y + ( 28.0*x   - y - x*z ) * dt;
  float z1=z + ( -(8/3)*z + x*y      ) * dt;
  x=x1;
  y=y1;
  z=z1;
}

void loop()  {
  int i;

  for(i=0; i<100; i++) {
    step();
  }

  // Map the Lorenz system state values into the color cube of the LED
  int x_byte = constrain(int((x+10)*10), 0, 255);
  int y_byte = constrain(int((y+10)*10), 0, 255);
  int z_byte = constrain(int(z*7), 0, 255);

  // Debug print
  Serial.print("x=");
  Serial.print(x_byte);
  Serial.print(" y=");
  Serial.print(y_byte);
  Serial.print(" z=");
  Serial.println(z_byte);

  // set the brightness of RGB LED
  analogWrite(red_LED, x_byte);
  analogWrite(green_LED, y_byte);
  analogWrite(blue_LED, z_byte);

  // wait for 30 milliseconds
  delay(30);
}
