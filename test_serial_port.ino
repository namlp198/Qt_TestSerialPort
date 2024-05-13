String m_strCmd = "";
String m_strInputData = "";
bool m_bIsDataComplete = false;
const int ledPin = 13;


void setup() {
   // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ledPin, OUTPUT);
  // put your setup code here, to run once:

  // initialize serial
  Serial.begin(9600);
  // reserve 200 bytes for the m_strInputData
  m_strCmd.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(m_bIsDataComplete){
    if(m_strCmd == "ON"){
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(ledPin, HIGH);
      delay(100);
      Serial.println("SET pin 13");
    }
    else if (m_strCmd == "OFF"){
       digitalWrite(LED_BUILTIN, LOW);
       digitalWrite(ledPin, LOW);
       delay(100);
       Serial.println("RESET pin 13");
    }

    m_bIsDataComplete = false;
    m_strInputData = "";
    m_strCmd = "";
  }
}

/*
SerialEvent occurs whenever a new data comes is the hardware serial RX. This
routine is run between each time loop() runs, so using delay inside loop can
delay respone. Multiple bytes of data may be available.
*/
void serialEvent(){
  while(Serial.available()){
    // get the new byte:
    char inChar = (char)Serial.read();

    // if the incoming character is a newline, set a flag so the main loop can
    // do somthing about it:
    if(inChar == '\n'){
      m_bIsDataComplete = true;
      m_strCmd = m_strInputData;
      return;
    }

     // add it to the m_strInputData
    m_strInputData += inChar;
  }
}

