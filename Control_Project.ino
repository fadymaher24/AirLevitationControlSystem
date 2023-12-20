#define iN3 6
#define iN4 7
#define kp 0.897 //this value shall be set from the MATLAB pid tuner
#define ki 0.00492 //this value shall be set from the MATLAB pid tuner
#define kd 0.00152 //this value shall be set from the MATLAB pid tuner
#define trigPin 9
#define echoPin 11
float duration, distance;
double priError = 0;
double toError = 0;
int ENA =10;
int y;
double PIDvalue;
void setup(){
Serial.begin(9600);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
// configure the trigger pin to output mode
pinMode(trigPin, OUTPUT);
// configure the echo pin to input mode
pinMode(echoPin, INPUT);
float Gs = 0; //Intialze our system open loop system output to 0
}
void Ultrasonic(){
  digitalWrite(trigPin,1);
  delayMicroseconds(10);
  digitalWrite(trigPin,0);
  // measure duration of pulse from ECHO pin
  duration=pulseIn(echoPin,1); 
/  // calculate the distance
  distance= 0.017 * duration;
  // print the value to Serial Monitor
//  Serial.print("distance: ");
  Serial.print(distance);
  Serial.write(13);
  Serial.write(10);
 // Serial.println(" cm");
  delay(500);
}
void PID(){
int measured = 30 - distance; //suppose there is a measured value
int setPoint = 12.5; //set manually
double error = setPoint - measured; //Calculate the error which is difference between the measured
//value and the set point the use assigned
double Pvalue = error * kp; //calculate the P value
double Ivalue = (priError+error) * ki; //caculate the I value
double Dvalue = (error - priError) * kd; //calculate the D value
PIDvalue = Pvalue + Ivalue + Dvalue; //Sum of to get the PID controller
priError = error; //get the value calculated from the first loop then put in the next loop
toError += error; //get the value by increment the priError and += is the compound addition
//which does mean that toError = error + toError//
//Serial.println("PID Value:");
//Serial.println(PIDvalue); //print the PID value
  }
void Up(){ 
analogWrite(ENA,150); // 150
digitalWrite(iN3,1);
digitalWrite(iN4,0);
}
void loop(){
Ultrasonic();
PID();
y = map(PIDvalue,0,30,165,250);
//Serial.println("y:");
//Serial.println(y); //print the PID value
analogWrite(ENA,y); // 150
digitalWrite(iN3,1);
digitalWrite(iN4,0);
}
