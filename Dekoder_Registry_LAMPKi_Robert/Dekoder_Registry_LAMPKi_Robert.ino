//Author Romuald Milewski
// Dekoder for Pedal or Registry and Registers Leds and Pistons Leds for pipe organ
// Arduino Mega and Mega2560
#include <MIDI.h>   // Add Midi Library
 
//#define LED 13 
//#define LED2 12// Arduino Board LED is on Pin 13

#define decoder_channel 1 // the selected MIDI channel on which the decoder works
#define decoder_channel_registry 1 // the selected MIDI channel on which the decoder works
#define decoder_channel_Pistons 13 // the selected MIDI channel on which the decoder works
 
int pins[] = {30, 31, 28, 29, 26, 27, 24, 25, 22, 23, 20, 21, 18, 19, 16, 17, 14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3};        

int pins_reg[] = {36, 37, 34, 35, 32, 33,   A14, A15, A12, A13, A10, A11, A8, A9, A6, A7, A4, A5, A2, A3, A0, A1};

int pins_Pistons[] = {46, 47, 44, 45, 42, 43, 40, 41, 38, 39};           

int pitch_store = 84;
int end_pin = 0;
// dla I manuału tak:

//int pins[] = {3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12,     19, 18, 21, 20, 23, 22, 25, 24, 27, 26, 29, 28, 31, 30,    A14, A15, A12, A13, A10, A11, A8, A9, A6, A7, A4, A5, A2, A3, A0, A1,   46, 47, 44, 45, 42, 43, 40, 41, 38, 39, 36, 37, 34, 35, 32, 33};
// 15, 14, 17, 16, 
// 

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();
 
void setup() {
  
     // setup pins for output ( Pedal )
  for (int i = 0; i < sizeof(pins) / sizeof(pins[0]); ++i) {
    pinMode(pins[i], OUTPUT);
    digitalWrite (pins[i], LOW);
  }    
     // setup pins_reg for output ( Registry in pedal )
  for (int i = 0; i < sizeof(pins_reg) / sizeof(pins_reg[0]); ++i) {
    pinMode(pins_reg[i], OUTPUT);
    digitalWrite (pins_reg[i], LOW);    
    
  }

    // setup pins_Pistons for output
for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i) {
    pinMode(pins_Pistons[i], OUTPUT);
    digitalWrite (pins_Pistons[i], LOW); // Ustawienie wszystkich pin na stan wysoki
    
  }
digitalWrite (pins_Pistons[0], HIGH); // Ustawienie pierwszegi pina (D2) na stan LOW, by podswietoić piston 0 czyli kasownik 
 
      // self-test  jesli potrzebny
//  for (int i = 0; i < sizeof(pins) / sizeof(pins[0]); ++i) {
//    digitalWrite(pins[i], HIGH);
//    delay(300); // Czas trwania stanu wysokiego - 300 ms
//    digitalWrite(pins[i], LOW);
//    delay(50);  // Dodatkowy czas dla lepszego zobaczenia efektu
//  }



  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it
  // to respond to notes on channel 2 only.
  MIDI.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
}
 
void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.
}
 
// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity

void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
 if (channel == decoder_channel){
  if (pitch >= 36 && pitch <= (36 + ( sizeof(pins) / sizeof(pins[0] )))){
   for (int i = 0; i < sizeof(pins) / sizeof(pins[0]); ++i) {
    if (pitch == 36+i) {
     digitalWrite (pins[i], HIGH); // Set Arduino board pins to high
    } 
   } 
  } 
 } 
 
 if (channel == decoder_channel_registry) {
  if (pitch >= 36 && pitch <= (36 + ( sizeof(pins_reg) / sizeof(pins_reg[0] )))){
   for (int i = 0; i < sizeof(pins_reg) / sizeof(pins_reg[0]); ++i) {
    if (pitch == 36+i) {
     digitalWrite (pins_reg[i], HIGH); // Set Arduino board pins_reg to high
    }
   }    
  }
 } 

if (channel == decoder_channel_Pistons) {  

// obsługa pistonow 1 do 8

   if (pitch >= 76 && pitch <= 83){
       pitch_store = pitch;
       // gaszenie wszystkich lampek podświetlenia
       for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i){ 
          digitalWrite (pins_Pistons[i], LOW); 
       }
       // zapalenie włąsciwej lampki podświetlającej pistony  od 1 do 8 
       for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i) {
          if (pitch == 76+i) {
          digitalWrite (pins_Pistons[i+1], HIGH); // włącza wlasciwą lampkę 
          } 
       }
   } 

// obsługa kasownik (0)
   
   if (pitch == 84){
       pitch_store = pitch;
       // gaszenie wszystkich lampek podświetlenia
       for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i){ 
          digitalWrite (pins_Pistons[i], LOW); 
       }
       // zapalenie włąsciwej lampki podświetlającej dla pistonu 0 (kasownik) 
       digitalWrite (pins_Pistons[0], HIGH); // zapala lampkę 0
           
       
   } 
     
// obsługa Crescendo (C)
   
   if (pitch == 88){ 
       // gaszenie wszystkich lampek podświetlenia
       for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i){ 
          digitalWrite (pins_Pistons[i], LOW); 
       }
       // zapalenie włąsciwej lampki podświetlającej dla pistonu 0 (kasownik) 
       end_pin = sizeof(pins_Pistons) / sizeof(pins_Pistons[0]) - 1;
       digitalWrite (pins_Pistons[end_pin], HIGH); // zapala ostatnią  lampkę (C) 
           
       
   }      

/* W TEJ WERSJI TĘ SEKSCJĘ KODU ZAKOMENTOWANO --------------------------------------------------
// obsługa Anuluj Crescendo (A)
   
   if (pitch == 89){ 
       // gaszenie wszystkich lampek podświetlenia
       for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i){ 
          digitalWrite (pins_Pistons[i], HIGH); 
       }
       
       // zapalenie na powrót włąsciwej lampki podświetlającej pistony  od 1 do 8 lub (0)
       if (pitch_store >= 76 && pitch_store <= 83){
         for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i) {
            if (pitch_store == 76+i) {
              digitalWrite (pins_Pistons[i+1], LOW); // włącza wlasciwą lampkę (1 do 8)
            } 
         }
       }
       
       if (pitch_store == 84){
           digitalWrite (pins_Pistons[0], LOW); // włącza wlasciwą lampkę (0)
       }
   } 
   */     
 
/* W TEJ WERSJI TĘ SEKSCJĘ KODU ZAKOMENTOWANO --------------------------------------------------
// obsługa Next (>)
   
   if (pitch == 85){ 

       pitch_store++;
       if (pitch_store > 83){
        pitch_store = 76;
       }
     
       // gaszenie wszystkich lampek podświetlenia
       for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i){ 
          digitalWrite (pins_Pistons[i], HIGH); 
       }
       
       // zapalenie na powrót włąsciwej lampki podświetlającej pistony  od 1 do 8 lub (0)
       if (pitch_store >= 76 && pitch_store <= 83){
         for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i) {
            if (pitch_store == 76+i) {
              digitalWrite (pins_Pistons[i+1], LOW); // włącza wlasciwą lampkę (1 do 8)
            } 
         }
       }
       
       if (pitch_store == 84){
           digitalWrite (pins_Pistons[0], LOW); // włącza wlasciwą lampkę (0)
       }
   }  

// obsługa Prew (<) (-)
   
   if (pitch == 86){ 

       pitch_store--;
       if (pitch_store < 76){
        pitch_store = 83;
       }
     
       // gaszenie wszystkich lampek podświetlenia
       for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i){ 
          digitalWrite (pins_Pistons[i], HIGH); 
       }
       
       // zapalenie na powrót włąsciwej lampki podświetlającej pistony  od 1 do 8 lub (0)
       if (pitch_store >= 76 && pitch_store <= 83){
         for (int i = 0; i < sizeof(pins_Pistons) / sizeof(pins_Pistons[0]); ++i) {
            if (pitch_store == 76+i) {
              digitalWrite (pins_Pistons[i+1], LOW); // włącza wlasciwą lampkę (1 do 8)
            } 
         }
       }
       
       if (pitch_store == 84){
           digitalWrite (pins_Pistons[0], LOW); // włącza wlasciwą lampkę (0)
       }
   } 
    
// W TEJ WERSJI POWYŻSZĄ SEKSCJĘ KODU ZAKOMENTOWANO --------------------------------------------------
  */     
 } 


// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity


}
 
// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity

void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {
 if (channel == decoder_channel) {  
   if (pitch >= 36 && pitch <= (36 + ( sizeof(pins) / sizeof(pins[0] )))){
     for (int i = 0; i < sizeof(pins) / sizeof(pins[0]); ++i) {
       if (pitch == 36+i) {
         digitalWrite (pins[i], LOW); // Set Arduino board pins_reg to low
       } 
     }
   }  
 } 
 if (channel == decoder_channel_registry) {  
  if (pitch >= 36 && pitch <= (36 + ( sizeof(pins_reg) / sizeof(pins_reg[0] )))){
     for (int i = 0; i < sizeof(pins_reg) / sizeof(pins_reg[0]); ++i) {
       if (pitch == 36+i) {
          digitalWrite (pins_reg[i], LOW); // Set Arduino board pins_reg to low
       } 
     }
  }
 } 
}  
