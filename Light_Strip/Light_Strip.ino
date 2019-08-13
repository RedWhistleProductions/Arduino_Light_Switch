/* 
 *  This is a heavily modified version of the sample code released by Radio Shack
 *  for use with a RBG LED light strip.
 */

#include <avr/pgmspace.h>
unsigned long Lights[10];

#define DATA_1 (PORTC |=  0X01)    // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)    // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)    // for UNO

const unsigned long Red = 0x0000ff;
const unsigned long Blue = 0x00ff00;
const unsigned long Green = 0xff0000;
const unsigned long Yellow = 0xff00ff;
const unsigned long Violet = 0x00ffff;
const unsigned long Cyan = 0xffff00;
const unsigned long Orange = 0x8000ff;
const unsigned long White = 0xffffff;
const unsigned long Off = 0x000000;
const unsigned long Increment = 0x010101;

unsigned long All_Off[10] ={Off, Off, Off, Off, Off, Off, Off, Off, Off, Off};  
unsigned long WHITE[10] = {White, White, White, White, White, White, White, White, White, White};
unsigned long RED[10] = {Red, Red, Red, Red, Red, Red, Red, Red, Red, Red};
unsigned long ORANGE[10] = {Orange, Orange,Orange,Orange,Orange,Orange,Orange,Orange,Orange,Orange};
unsigned long YELLOW[10] = {Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow};
unsigned long GREEN[10] = {Green, Green, Green, Green, Green, Green, Green, Green, Green, Green};
unsigned long BLUE[10] = {Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue};
unsigned long CYAN[10] = {Cyan, Cyan, Cyan, Cyan, Cyan, Cyan, Cyan, Cyan, Cyan, Cyan};
unsigned long VIOLET[10]={Violet,Violet,Violet,Violet,Violet,Violet,Violet,Violet,Violet,Violet};
unsigned long RAINBOW[10]={Red, Orange,Yellow,Green,Blue,Cyan,Violet,Violet,Violet,Violet};



// ***********************************************************************************************************
// *
// *                            Main Loop 
// *
// *
// ***********************************************************************************************************
void loop() 
{  
   while (Serial.available() == 0);
  {
    int val = Serial.read()- '0';
    
    switch(val){
      case 0:
        Serial.println("Off");
        Preset(All_Off);
      break;
      
      case 1:
        Serial.println("White");
        Preset(WHITE);
        //Preset(DimWhite);
       break;
       
       case 2:
         Serial.println("Red");
         Preset(RED);
        break;
        
        case 3:
          Serial.println("Orange");
          Preset(ORANGE);
         break;
         
         case 4:
           Serial.println("Yellow");
           Preset(YELLOW);
          break;
          
          case 5:
            Serial.println("Green");
            Preset(GREEN);
            break;
           case 6:
             Serial.println("Blue");
             Preset(BLUE);
             break;
             
            case 7:
              Serial.println("Indigo");
             Preset(CYAN);
             break;
             
            case 8:
              Serial.println("Violet");
              Preset(VIOLET);
             break;
             
             case 9:
               Serial.println("Rainbow");
               Preset(RAINBOW);
              break;
              
              case 'l' - '0':
                Serial.println("Pick a light");
                lightSelect();
              break;
       
       default:
         Serial.println("Options Menu");
         Serial.println("");
         Serial.println("[0]  Off");
         Serial.println("[1]  White"); 
         Serial.println("[2]  Red");
         Serial.println("[3]  Orange");
         Serial.println("[4]  Yellow");
         Serial.println("[5]  Green");
         Serial.println("[6]  Blue");
         Serial.println("[7]  Indigo");
         Serial.println("[8]  Violet");
         Serial.println("[9]  Rainbow");    
        break;
    };
     delay(1000);
     Serial.flush();
  }
}

void lightSelect(){
  Serial.flush();
  while (Serial.available() == 0);
  int lightNumber = Serial.read()- '0';
  while (Serial.available() == 0);
  Serial.flush();
  int lightColor = Serial.read()-  '0';
  
  switch(lightColor){
    case 0:
      SetColor(lightNumber, Off);
    break;

    case 1:
      SetColor(lightNumber, White);
    break;

    case 2:
      SetColor(lightNumber, Red);
     break;
    
    case 3:
      SetColor(lightNumber, Orange);
    break;
    
    case 4:
      SetColor(lightNumber, Yellow);
    break;
        
    case 5:
      SetColor(lightNumber, Green);
    break;
    
    case 6:
      SetColor(lightNumber, Blue);
    break;
        
    case 7:
      SetColor(lightNumber, Cyan);
    break;
        
    case 8:
      SetColor(lightNumber, Violet);
    break;
        
    default:
    break;
  };
  
}

// ***********************************************************************************************************
// *
// *                            Power Up Init.
// *
// *
// ***********************************************************************************************************
void setup() {                
  Preset(GREEN);
  STRIP_PINOUT;        // set output pin - DEBUG: should auto detect which mother board for use

  reset_strip();
  
  
  Update();
  Serial.begin(9600); 
}

void Preset(unsigned long preset[10]){
    for(int i = 0; i <10; i++){
      SetColor(i, preset[i]);
    }
}

/*******************************************************************************
 * Function Name  : send_1M_pattern
 * Description    : Transmit pattern to whole 1 meter strip
 *                  
 * Input          : pointer to ROM pattern; pattern length; frame rate
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_1M_pattern(const unsigned long data[][10], int pattern_no, int frame_rate)
{
  int i=0;
  int j=0;
  uint32_t temp_data;

  for (i=0;i<pattern_no;i++)
  {
    noInterrupts();
    for (j=0;j<10;j++)
    {
      temp_data=pgm_read_dword_near(&data[i][j]);
      send_strip(temp_data);
    }
    interrupts();

    delay(frame_rate);
  }
}

void SetColor(int LightNumber, const unsigned long Color)
{
  int j=0;
 // uint32_t temp_data;
  Lights[LightNumber] = Color;

    noInterrupts();
    for (j=0;j<10;j++)
    {
      //temp_data = Lights[j];
      send_strip(Lights[j]);
      send_strip(Lights[j]);
    }
    interrupts();
}

/*******************************************************************************
 * Function Name  : send_strip
 * Description    : Transmit 24 pulse to LED strip
 *                  
 * Input          : 24-bit data for the strip
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_strip(uint32_t data)
{
  int i;
  unsigned long j=0x800000;
  
 
  for (i=0;i<24;i++)
  {
    if (data & j)
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");  
      __asm__("nop\n\t");              
      DATA_0;
    }
    else
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      DATA_0;   
       __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");           
    }

    j>>=1;
  }


  
}

/*******************************************************************************
 * Function Name  : reset_strip
 * Description    : Send reset pulse to reset all color of the strip
 *                  
 * Input          : None
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void	reset_strip()
{
  DATA_0;
  delayMicroseconds(20);
}

void Update()
{
   int j=0;
   noInterrupts();
   for (j=0;j<10;j++)
   {
     send_strip(Lights[j]);
   }
   interrupts(); 
}





