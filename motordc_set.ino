#define pinMotorA 9
#define pinMotorB 10
 
bool motorMaju = false;
bool motorHidup = false;
char chrKecepatan[5];
byte Kecepatan;
 
void setup() {
  Serial.begin(9600);
  Serial.println("Mengatur kecepatan motor DC 5V menggunakan PWM dilengkapi aksi maju-mundur");
  Serial.println("dengan rangkaian sederhana menggunakan Arduino dan 4 transistor");
  Serial.println("entri [M] untuk maju");
  Serial.println("entri [m] untuk mundur");
  Serial.println("entri [Kxxx] untuk set kecepatan, xxx = 0 s/d 255");
  Serial.println("entri [+] untuk menambah kecepatan 10 angka");
  Serial.println("entri [-] untuk kurangi kecepatan 10 angka");
  Serial.println("entri [B] untuk berhenti");

 
  pinMode(pinMotorA, OUTPUT);
  pinMode(pinMotorB, OUTPUT);
}
 
void loop() {
  if(Serial.available())
  {
    char c = Serial.read();
    if(c == 'M')
    {
      motorMaju = true;
      Serial.println("Motor maju");
      motorHidup = true;
    }
    else if(c == 'm')
    {
      motorMaju = false;
      Serial.println("Motor mundur");
      motorHidup = true;
    }
    else if(toupper(c) == 'K')
    {
      delay(10);
      Serial.readBytesUntil('\n', chrKecepatan, sizeof(chrKecepatan));
      Kecepatan = String(chrKecepatan).toInt();
      Serial.print("Set kecepatan = ");
      Serial.println(Kecepatan);
    }
    else if(c == '+')
    {
      if(Kecepatan <= 245)
      {
        Kecepatan += 10;
      }
      Serial.print("Set kecepatan = ");
      Serial.println(Kecepatan);
    }
    else if(c == '-')
    {
      if(Kecepatan >= 10)
      {
        Kecepatan -= 10;
      }
      Serial.print("Set kecepatan = ");
      Serial.println(Kecepatan);
    }
    else if(toupper(c) == 'B')
    {
      digitalWrite(pinMotorA, LOW);
      digitalWrite(pinMotorB, LOW);
      motorHidup = false;
      Serial.println("Motor berhenti");
    }
  }
  if(motorHidup)
  {
    if(motorMaju)
    {
      digitalWrite(pinMotorB, LOW);
      analogWrite(pinMotorA, Kecepatan);
    }
    else
    {
      digitalWrite(pinMotorA, LOW);
      analogWrite(pinMotorB, Kecepatan);
    }
  }
 
}
