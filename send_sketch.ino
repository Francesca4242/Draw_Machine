#include <Stepper.h>
extern int x_total;
extern int y_total;
extern unsigned char colour_number [];
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(80, 16, 4, 2 , 5);
Stepper myStepper2(80, 14, 13, 15, 12);
void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  myStepper2.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
  delay(10000);

  
  for (int a=0; a<3; a++) {
    myStepper2.step(32*x_total+100);
    myStepper.step(-32*y_total-100);
    myStepper2.step(-32*x_total-100);
    myStepper.step(32*y_total+100);
  }
  myStepper2.step(+50);
  myStepper.step(-50);
  delay(10000);
  
}
int num_elements=x_total*y_total;
int pixel_number=0;
int colour_value=colour_number[pixel_number];
int lengt=0;
int frequency=0;
int line_start=0;
int x_total_new=x_total;
//float lengt=(float)(array_number*2)/255;
//float frequency=2/lengt;

void set_lengt_freq(int colour_value) {
  if (colour_value<=128 ){
    lengt=1;
    frequency=8;
  }
  else {
    lengt=8;
    frequency=1;
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  // step one revolution  in one direction:

  for (pixel_number=line_start; pixel_number<x_total_new; ) {
    Serial.println("a");
    Serial.println(pixel_number);
    colour_value=colour_number[pixel_number];
    set_lengt_freq(colour_value);
    for (int y=0; y<frequency; y++ ) {
      //Serial.println("clockwise");
      myStepper.step(32);
      //Serial.println("clockwise");
      myStepper2.step(lengt*2);
      //Serial.println("anti-clockwise");
      myStepper.step(-32);
      //Serial.println("clockwise");
      myStepper2.step(lengt*2);
    }
    pixel_number=pixel_number+1;
     
    //lengt=(float)(array_number*2)/255;
    //frequency=2/lengt;
    Serial.println("end of pixel_loop");
    Serial.println(pixel_number);
   }
    Serial.println("after bracket");
    Serial.println(pixel_number);
   //Serial.println("anti-clockwise");
   myStepper.step(-32);
   int total_lengt=x_total*16;
   line_start=x_total+line_start;
   
   myStepper2.step(-total_lengt*2);
   Serial.println(pixel_number);
   Serial.println(num_elements);
   if (x_total_new>=num_elements){   
    while (true){
      yield();
      Serial.println("done!");
    }
   }
   x_total_new=x_total_new+x_total;
}
