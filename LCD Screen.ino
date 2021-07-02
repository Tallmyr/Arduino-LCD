/*

*/

void setup()
{

#define RS 22
#define RW 24
#define E 26
#define D0 28
#define D1 30
#define D2 32
#define D3 34
#define D4 36
#define D5 38
#define D6 40
#define D7 42

  Serial.begin(9600);

  pinMode(RS, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  // Define Output
  char output[] = "Simon kan koda!";

  // Init display
  send_command(false, false, 0b00000001); //Clear Display
  send_command(false, false, 0b00000010); //Return Home
  send_command(false, false, 0b00001111); //Dispay on, cursor on, blinking on

  // Send text
  generate_text(output);

  // Stop blinking and stuff
  send_command(false, false, 0b00001100); //Display on, cursor off, blinking off
}

void generate_text(char *ascii_str)
{
  int len = strlen(ascii_str);
  int ascii_number[len];
  int i;

  string2bytes(ascii_str, ascii_number);

  for (i = 0; i < len; i++)
  {
    send_command(true, false, ascii_number[i]);
  }
}

void string2bytes(char *input, int *output)
{
  int loop;
  int i;

  loop = 0;
  i = 0;

  while (input[loop] != '\0')
  {
    output[i++] = input[loop++];
  }
}

/*
<bool> rs - Register Select. False for instructions, True for Data.
<bool> rw - Read/Write. Read not implemented here, always set false in order to write.
<int> data - 8 bit data for instruction when RS is false, or 8 bit ascii character when RS is set true.
*/
void send_command(bool rs, bool rw, int data)
{

  //Control Signals
  if (rs == true)
  {
    digitalWrite(RS, HIGH);
  }
  if (rw == true)
  {
    digitalWrite(RW, HIGH);
  }

  // Set Data signals
  digitalWrite(D7, HIGH && (data & 0b10000000));
  digitalWrite(D6, HIGH && (data & 0b01000000));
  digitalWrite(D5, HIGH && (data & 0b00100000));
  digitalWrite(D4, HIGH && (data & 0b00010000));
  digitalWrite(D3, HIGH && (data & 0b00001000));
  digitalWrite(D2, HIGH && (data & 0b00000100));
  digitalWrite(D1, HIGH && (data & 0b00000010));
  digitalWrite(D0, HIGH && (data & 0b00000001));

  // Toggle Enable
  digitalWrite(E, HIGH);
  delay(1);
  digitalWrite(E, LOW);

  // Disable all signals
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(RW, LOW);
  digitalWrite(RS, LOW);
}

void loop()
{
}
