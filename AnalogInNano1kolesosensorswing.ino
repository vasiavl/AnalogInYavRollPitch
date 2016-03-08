

const int analogInRollPin = A2; // резистор джоя по Roll
const int sensorSwingPin = A5; // датчик положения рулевых колес
const int analogInPitchPin = A4; // пин для резистора по Pitch

 #define LRPin               8//5// управляет реверсом мотора руля  #define forward_agoPinR    
  #define forward_agoPinR      7// управляет реверсом правого двигателя
  
  #define analogWriteRPin        9  // ШИМ на рулевой мотор
  #define analogWritePRYPinR      11// ШИМ на правый ходовой мотор

 

      
int sensorSwing = 0;//, outputSwingR, outputSwingL  ,returnSensorSwing
int Roll,tvist,tvistFlag,flagY,flagYF;        
int outputRoll = 0;
int outputRollR = 0;
int Pitch = 0;        
int outputPitch = 0;
int outputPitchD = 0;
int R,Rdriv = 0;// шим правого двигателя

int forwardR,forwardL,flag,flagP,  flagForwardR =0;//состояние реверса двигателей и флаги  переключения состояний

void setup() {
   
    pinMode(forward_agoPinR, OUTPUT);
   // pinMode(forward_agoPinL, OUTPUT);
    pinMode(LRPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {                               

  Roll = analogRead(analogInRollPin); 
  Pitch = analogRead(analogInPitchPin);
  forwardR=  digitalRead(forward_agoPinR);
  sensorSwing=analogRead(sensorSwingPin );
  tvistFlag= digitalRead( LRPin);
  
   
  outputPitch = map(Pitch, 540, 1023, 0, 125); 
  outputPitchD = map(Pitch, 460, 0, 0, 125); 
  outputRoll =  map(Roll, 460, 0, 100, 200);
  outputRollR =  map(Roll, 560, 1023, 100, 200);


                                                                                        
                                                                                                                                                              
   if (460>Pitch)
   {       outputPitch= 0;
           if (LOW==forwardR)
              { flagForwardR=flag=HIGH ;}
              R= outputPitchD;
   }  
 if (Pitch>565 )
  {             outputPitchD= 0;
          if (HIGH==forwardR)
          { flagForwardR =flag= LOW ; }
              R= outputPitch;                                                        
    }    
    if ((565>Pitch)&& (Pitch >460))
    {       Rdriv=R=0;
        { 
              if ( LOW==forwardR){ flagForwardR= HIGH;  }
                                                                   
         }           
      }
          
   if  (Roll>560)// left  Ydiff
  {    
    if  (HIGH== tvistFlag){tvistFlag= LOW;  }
    tvist=outputRollR ;

     if ( Roll- sensorSwing <=60)tvist=0 ;
   }      
  if  (560>Roll&& Roll>460)//timeY=0 ;
   { if  ( 560 > sensorSwing && sensorSwing >460) tvist=0 ; 
     if  ( 560 < sensorSwing){tvistFlag= HIGH; tvist= map(sensorSwing ,560,1023,80,180) ; }
     if  ( 460 >sensorSwing){tvistFlag= LOW; tvist= map(sensorSwing ,460,0,80,180); }
   }  
  
  if  (460>Roll)//right
   {   if  (LOW==tvistFlag) {tvistFlag= HIGH; }
      tvist=outputRoll ;

       if (sensorSwing-Roll<=20 )tvist=0 ;   
   }
   
 if (flag !=flagP  ){Rdriv=R=0; flagP=flag; }
 if (flagY !=flagYF){Rdriv=0; flagYF=flagY; }
   if  (Rdriv-R >20)  { Rdriv=Rdriv-10;} 
   else {if (R-Rdriv>20)Rdriv=Rdriv+10;
        else Rdriv=R;  }
    
     digitalWrite( LRPin, tvistFlag);

     digitalWrite( forward_agoPinR,flagForwardR );     
     analogWrite(analogWriteRPin, tvist); 
     analogWrite(analogWritePRYPinR, Rdriv);

                                                       
 
   Serial.print("\n \t sensorSwing= " );                       
   Serial.print(sensorSwing );                     
 
    Serial.print("\n Roll = " );                       
  Serial.print(Roll);      
  Serial.print("\t outputRoll = ");      
  Serial.print(outputRoll); 
   Serial.print("\t outputRollR = ");      
  Serial.print(outputRollR); 
//  Serial.print("\n Pitch = " );                       
//  Serial.print(Pitch);      
//  Serial.print("\t outputPitch = ");      
//  Serial.print(outputPitch); 
//  Serial.print("  R = " );                       
//  Serial.print(R); 
//  Serial.print("\t Rdriv = " );                       
//  Serial.print(Rdriv);
//  Serial.print("\n                outputPitchD = ");      
//  Serial.print(outputPitchD); 
//  
//  Serial.print("\n forwardR = ");            
//  Serial.print(  forwardR); 
//  
// Serial.print("\t flag=") ;            
//  Serial.print(  flag); 
// Serial.print("\t flagP=") ;            
//  Serial.println(  flagP); 

//Serial.print("\n tvistFlag=") ;            
//  Serial.print(  tvistFlag); 
// Serial.print("\t tvist=") ;            
//  Serial.print(  tvist); 
// 
//  
//  delay(2550);   

}
