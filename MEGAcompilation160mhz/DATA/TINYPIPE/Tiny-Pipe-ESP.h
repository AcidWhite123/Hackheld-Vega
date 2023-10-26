//         >>>>>  T-I-N-Y  P-I-P-E for ESP8285/ESP8266  GPL v3 <<<<<
//                    Programmer: Daniel C 2021
//             Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                    https://WWW.TINYJOYPAD.COM
//          https://sites.google.com/view/arduino-collection

//  tiny-Pipe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

//For Mega Tinyjoypad ESP8285/ESP8266
#include "CLASS_TPIPE.h"

//PUBLIC VAR
 uint8_t SEQUENCIALCHECK_TPIPE=0;//check all collision sprite in sequencial methode
 uint8_t BLINK_TPIPE=0; //BLINK 50% FPS
 uint8_t D_CHANGE_TPIPE=1;
 uint8_t D_CHANGE_B_TPIPE=0;

#define FRAME_CONTROL_TPIPE while((currentMillis-MemMillis)<33){currentMillis=millis();}MemMillis=currentMillis
#define FRAME_CONTROL_2_TPIPE while((currentMillis-MemMillis)<26){currentMillis=millis();}MemMillis=currentMillis

GamePlay_TPIPE GP;

//PUBLIC OBJ
SPRITE_TPIPE Main;
SPRITE_TPIPE Sprite[NO_SPR];

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////// main  ////////////////////////////////////
void loop_TPIPE() {
ESP.wdtDisable();
ESP.wdtFeed();
New_Game:;
NEW_GAME_TPIPE();
Next_Level:;
NEXT_LEVEL_TPIPE();
while(1){
ESP.wdtFeed();
if (!Main.GET_K()) {
if (TINYJOYPAD_RIGHT==0) {SHIELD_REMOVE_TPIPE();Main.RIGHTMOVE();}else
if (TINYJOYPAD_LEFT==0)  {SHIELD_REMOVE_TPIPE();Main.LEFTMOVE();}else{ Main.DECEL();}
}else{if (Main.GET_A()==0) {ADJ_GP_TPIPE();}}
REFRESH_TURTLE_TPIPE();
Main.GRAVITY(1);
HIT_BUMP_CHECK_TPIPE();
if (BUTTON_DOWN) {SHIELD_REMOVE_TPIPE();Main.JUMP();}else{if (Main.GET_CJ()==2) {Main.PUT_CJ(0);if (Target.GET_A()==2) {Target.PUT_A(0);}}}
CHECK_CYCLE_COLLISION_TPIPE();
RND_MIXER_TPIPE();
TIMER_FOR_NEW_TURTLE_TPIPE();
Tiny_Flip_TPIPE();
FRAME_CONTROL_TPIPE;
BLINK_TPIPE=(BLINK_TPIPE<1)?BLINK_TPIPE+1:0;
switch(GP.STATE){
  case 0:break;
  case 1:GP.Level=(GP.Level<97)?GP.Level+1:GP.Level;FADE_TPIPE(BACKGROUND_TPIPE,FADEOUT);goto Next_Level;break;
  case 2:SND_TPIPE(3);FADE_TPIPE(BACKGROUND_TPIPE,FADEOUT);goto New_Game;break;
  default:break;
}}}
////////////////////////////////// main end /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void SND_TPIPE(uint8_t SnD_){
switch(SnD_){
  case 0:Sound(10,40);Sound(60,40);Sound(110,40);Sound(170,40);Sound(220,40);break;
  case 1:for (uint8_t e=0;e<100;e=e+20){for (uint8_t r=e;r<e+100;r++){Sound(255-r,2);}}break;
  case 4:for (uint8_t r=10;r>1;r--){for (uint8_t e=100;e<200;e=e+5){Sound(e,r);}for (uint8_t e=100;e>2;e=e-5){Sound(e,r);}}break;
  case 3:PLAY_MUSIC(Music);break;
  case 2:PLAY_MUSIC(Music2);break;
  default:break;
}}

void UPDATE_DIGITAL_TPIPE(void){
if (GP.DIGIT1<9) {GP.DIGIT1++;}else{
 GP.DIGIT1=0;
if (GP.DIGIT2<9) {GP.DIGIT2++;} 
}}

void LOAD_LEVEL_TPIPE(uint8_t L_){
switch(L_){
  case (2):
  case (5):
  case (8):
  case (11):
  case (14):
  case (17):LIVES++;Sound(200,255);Sound(0,255);Sound(200,255);Sound(0,255);Sound(200,255);Sound(0,255);break;
  default:break;}
if (L_>20) {L_=20;}
GP.LevelXspeed=Mymap(L_,0,20,3,10);
GP.TOTAL_TURTLE_LEVEL=Mymap(L_,0,20,8,40);
GP.SPEED_POP_TURTLE=Mymap(L_,0,20,80,40);
GP.NOMOVE_TIME=Mymap(L_,0,20,255,60);
ADJ_GP_TPIPE();
}

uint8_t Intro_TPIPE(void){
uint8_t t2_=0;
ESP.wdtDisable();
ESP.wdtFeed();
FADE_TPIPE(TITLE_TPIPE,FADEIN);
while(1){
ESP.wdtFeed();
FRAME_CONTROL_2_TPIPE;
INTRO_TPIPE((t2_<20)?1:0);
if (BUTTON_DOWN) {
while(1){
if (BUTTON_UP) { 
SND_TPIPE(0);
FADE_TPIPE(TITLE_TPIPE,FADEOUT);
return 0;}
}}
t2_=(t2_<40)?t2_+1:0;
}}

void ADJ_GP_TPIPE(void){
if (LIVES>0) {
Main.PUT_AD(0);
Main.PUT_W(7);
Main.PUT_H(7);
Main.RESET_GRAVITY();
Main.PUT_XSPEED(0);
Target.INIT(0,0,0);
if (GP.FIRSTTIME==1) {
Main.INIT(1,42,53);
GP.FIRSTTIME=0;
}else{
Main.INIT(2,53,7);
}}else{GP.STATE=2;}
}

void SHIELD_REMOVE_TPIPE(void){
if (Main.GET_A()==2) {Main.PUT_A(1);}
RND_MIXER_TPIPE();
}

void TIMER_FOR_NEW_TURTLE_TPIPE(void){
if ((GP.TIMER_RENEW)<(GP.SPEED_POP_TURTLE)) {
GP.TIMER_RENEW++;
}else{
GP.TIMER_RENEW=0;
CHECK_FOR_NEW_TURTLE_TPIPE();
}}

void CHECK_FOR_NEW_TURTLE_TPIPE(void){
if (GP.TOTAL_TURTLE_LEVEL>0) {
NEW_TURTLE_TPIPE();
}else{
CHECK_LEVEL_COMPLETED_TPIPE();
}}

void CHECK_LEVEL_COMPLETED_TPIPE(void){
for (uint8_t t=0;t<NO_SPR;t++){
if ((Sprite[t].GET_A()==0)) {
}else{goto EnD_;}
}
GP.STATE=1;
EnD_:;
}

void NEW_TURTLE_TPIPE(void){
uint8_t t;
for (t=0;t<NO_SPR;t++){
if (Sprite[t].GET_A()==0) {goto NexT;}
}
goto ENd;
NexT:;
Sprite[t].PUT_A(1);
Sprite[t].PUT_K(0);
switch (PSEUDO_RND_TPIPE()){
case(0):Sprite[t].PUT_X(24);Sprite[t].PUT_Y(-3);Sprite[t].PUT_XSPEED(GP.LevelXspeed);GP.TOTAL_TURTLE_LEVEL--;break;
case(1):Sprite[t].PUT_X(97);Sprite[t].PUT_Y(-3);Sprite[t].PUT_XSPEED(-GP.LevelXspeed);GP.TOTAL_TURTLE_LEVEL--;break;
default:break;
}
ENd:;
}

void CHECK_CYCLE_COLLISION_TPIPE(void){
if (Main.GET_A()!=1) goto ENd_2;
if (!Main.GET_K()) {
SEQUENCIALCHECK_TPIPE=(SEQUENCIALCHECK_TPIPE<(NO_SPR-1))?SEQUENCIALCHECK_TPIPE+1:0;
if (Sprite[SEQUENCIALCHECK_TPIPE].GET_A()) {
if (COLLISION_SIMPLIFIED(&Main,&Sprite[SEQUENCIALCHECK_TPIPE])) {KILL_SPRITE_TPIPE();}
}}
ENd_2:;
}

void KILL_SPRITE_TPIPE(void){
if (!Sprite[SEQUENCIALCHECK_TPIPE].GET_K()) {
Sound(100,2);Sound(240,2);
switch(Sprite[SEQUENCIALCHECK_TPIPE].GET_A()){
  case(0):break;
  case(1):SND_TPIPE(1);LIVES=(LIVES>0)?LIVES-1:0;Main.PUT_K(1);Main.PUT_YSPEED(-18);break;
  case(2):Sprite[SEQUENCIALCHECK_TPIPE].PUT_K(1);Sprite[SEQUENCIALCHECK_TPIPE].PUT_YSPEED(-18);break;
}}}

void INVERT_TURTLE_TPIPE(uint8_t No_SPR,uint8_t VAL_SPR){
switch(VAL_SPR){
  case(1):Sprite[No_SPR].PUT_NOMOVETIMER(GP.NOMOVE_TIME);Sprite[No_SPR].PUT_A(2);Sprite[No_SPR].PUT_AD(6);Sprite[No_SPR].PUT_F(0);Sprite[No_SPR].PUT_YSPEED(-14);break;
  case(2):Sprite[No_SPR].PUT_NOMOVETIMER(0);Sprite[No_SPR].PUT_A(1);Sprite[No_SPR].PUT_YSPEED(-14);break;
  default:break;
 }}

uint8_t HIT_BUMP_CHECK_TPIPE(void){
const uint8_t OFFSET_x=3;
if (Target.GET_A()==1) {
for (uint8_t t=0;t<NO_SPR;t++){
if (Sprite[t].GET_A()) {
if (COLLISION_1VS1(Target.GET_X()+OFFSET_x,Target.GET_X()+OFFSET_x,Target.GET_Y()+OFFSET_x,Target.GET_Y()+Target.GET_H(),Sprite[t].GET_X()+1,Sprite[t].GET_X()+Sprite[t].GET_W()-2,Sprite[t].GET_Y(),Sprite[t].GET_Y()+Sprite[t].GET_H())){
INVERT_TURTLE_TPIPE(t,Sprite[t].GET_A());
Sound(240,10);
goto ending;
}}}}else{
if (GP.POWER<0) return 0;
if (Main.GET_K()==0) {
if (Main.GET_YSPEED()<0) {
if (COLLISION_1VS1(63,63,46,46,Main.GET_X()+1,Main.GET_X()+Main.GET_W()-2,Main.GET_Y(),Main.GET_Y()+1)){
Main.PUT_Y(Main.GET_Y()+1);
Main.RESET_GRAVITY();
GP.POWER=(GP.POWER!=-1)?GP.POWER-1:-1;
GP.EARTQUAKE=8;
ALL_INVERT_TURTLE_TPIPE();
}}}
return 0;}
ending:;
Target.PUT_A(2);
return 0;
}

void ALL_INVERT_TURTLE_TPIPE(void){
for (uint8_t t=0;t<NO_SPR;t++){
if (Sprite[t].GET_YSPEED()<11) {
  if (Sprite[t].GET_Y()>0) {INVERT_TURTLE_TPIPE(t,Sprite[t].GET_A());}}
}}

void INIT_TURTLE_TPIPE(void){
for (uint8_t t=0;t<NO_SPR;t++){
Sprite[t].INIT(0,0,0);
}}

void CHANGE_DIRECTION_TPIPE(void){
D_CHANGE_TPIPE=(D_CHANGE_TPIPE<160)?D_CHANGE_TPIPE+1:0;
if (D_CHANGE_TPIPE==0) {Sprite[D_CHANGE_B_TPIPE].PUT_XSPEED(-Sprite[D_CHANGE_B_TPIPE].GET_XSPEED());if (D_CHANGE_B_TPIPE<(NO_SPR-1)) {D_CHANGE_B_TPIPE++;}else{D_CHANGE_B_TPIPE=0;}  }
}

void REFRESH_TURTLE_TPIPE(void){
CHANGE_DIRECTION_TPIPE();
for (uint8_t t=0;t<NO_SPR;t++){
if (Sprite[t].GET_A()==0){goto SKIPP_;}
if (Sprite[t].GET_A()==1){
if (!Sprite[t].GET_K()) {Sprite[t].AUTO_MOVE();}
}else{
NO_MOVE_TIMER_TPIPE(t);
}
if (Sprite[t].GET_Y()==-3){
if (Sprite[t].GET_X()<30){goto SKIPP_;}
if (Sprite[t].GET_X()>91){goto SKIPP_;}
}
Sprite[t].GRAVITY(0);
SKIPP_:;
}}

void NO_MOVE_TIMER_TPIPE(uint8_t SPR_){
if (Sprite[SPR_].GET_NOMOVETIMER()==1) {
Sprite[SPR_].PUT_NOMOVETIMER(0);Sprite[SPR_].PUT_A(1);
}else{
if (Sprite[SPR_].GET_NOMOVETIMER()>1) {Sprite[SPR_].PUT_NOMOVETIMER(Sprite[SPR_].GET_NOMOVETIMER()-1);}
}}

uint8_t ANIM_TPIPE(SPRITE_TPIPE *SP_){
return SP_->GET_F()+SP_->GET_AD();
}

uint8_t Main_Blitz_TPIPE(uint8_t XPASS,uint8_t YPASS){
if ((Main.GET_A()==2)&&(BLINK_TPIPE!=0)) {return 0x00;}
if (XPASS<18) return 0;
if (XPASS>109) return 0;
return blitzSprite(Main.GET_X(),Main.GET_Y(),XPASS,YPASS,ANIM_TPIPE(&Main),MAIN_TPIPE);
}

uint8_t Sprites_Turtle_TPIPE(uint8_t XPASS,uint8_t YPASS){ 
uint8_t Add_=0;
for (uint8_t t=0;t<NO_SPR;t++) {
  if (XPASS<18) goto Next_;
if (XPASS>109) goto Next_;
if (!Sprite[t].GET_A()) goto Next_;
if ( COLLISION_1VS1(Sprite[t].GET_X(),Sprite[t].GET_X()+Sprite[t].GET_W(),Sprite[t].GET_Y(),Sprite[t].GET_Y()+Sprite[t].GET_H(),XPASS,XPASS,YPASS*8,((YPASS+1)*8))) {
Add_|= blitzSprite(Sprite[t].GET_X(),Sprite[t].GET_Y(),XPASS,YPASS,ANIM_TPIPE(&Sprite[t]),TURTLE_TPIPE);
}
Next_:;
}
return Add_;
}

uint8_t Power_TPIPE(uint8_t XPASS,uint8_t YPASS){
if (GP.POWER<0) return 0x00;
return (YPASS==5)?SPEED_BLITZ(61,5,XPASS,YPASS,GP.POWER,POWER_TPIPE):0x00;
}

uint8_t RECUPE_TPIPE(uint8_t XPASS,uint8_t YPASS){
return Main_Blitz_TPIPE(XPASS,YPASS)|
Back_TPIPE(XPASS,YPASS)|
Power_TPIPE(XPASS,YPASS)|
Sprites_Turtle_TPIPE(XPASS,YPASS);
}

uint8_t Back_TPIPE(uint8_t XPASS,uint8_t YPASS){
return pgm_read_byte(&BACKGROUND_TPIPE[XPASS+((YPASS)*128)]);
}

void Tiny_Flip_TPIPE(void){
uint8_t y,x,x2;
if (GP.EARTQUAKE!=0) {
Sound(10,1);
GP.EARTQUAKE--; 
GP.EARTQUAKE_INVERT=(GP.EARTQUAKE_INVERT==0)?1:0;
}else{GP.EARTQUAKE_INVERT=0;}
for (y = 0; y < 8; y++){ 
for (x = 0; x < 128; x++){ 
if ((x>16)&&(x<111)) {x2=x+GP.EARTQUAKE_INVERT;}else{x2=x;}
display.buffer[(x+(y*128))]=(RECUPE_TPIPE(x2,y));
}}
display.display(); 
}

void INTRO_TPIPE(uint8_t FLIP_MODE_){
uint8_t y,x;
for (y = 0; y < 8; y++){ 
for (x = 0; x < 128; x++){ 
display.buffer[(x+(y*128))]=(((FLIP_MODE_==1)?SPEED_BLITZ(38,5,x,y,0,START_TPIPE):0)|(pgm_read_byte(&TITLE_TPIPE[x+((y)*128)])));
}}
display.display(); 
}

void DRAW_LEVEL_TPIPE(void){
uint8_t y,x;
for (y = 0; y < 8; y++){ 
for (x = 0; x < 128; x++){ 
display.buffer[(x+(y*128))]=(SPEED_BLITZ(44,3,x,y,0,LEVEL_TPIPE)|SPEED_BLITZ(75,3,x,y,GP.DIGIT2,police_TPIPE)|SPEED_BLITZ(80,3,x,y,GP.DIGIT1,police_TPIPE));
}
}
UPDATE_DIGITAL_TPIPE();
display.display(); 
}

void GP_INIT_TPIPE(void){
GP.TIMER_RENEW=0;
GP.POWER=2;
GP.EARTQUAKE=0;
GP.EARTQUAKE_INVERT=0;
}

void NEW_GAME_TPIPE(void){
LIVES=3;
GP.Level=0;
GP.DIGIT1=1;
GP.DIGIT2=0;
INIT_TURTLE_TPIPE();
Intro_TPIPE();
}

void NEXT_LEVEL_TPIPE(void){
GP.FIRSTTIME=1;
GP.STATE=0;
GP_INIT_TPIPE();
LOAD_LEVEL_TPIPE(GP.Level);
My_delay_ms(250);
DRAW_LEVEL_TPIPE();
SND_TPIPE(2);
My_delay_ms(250);
FADE_TPIPE(BACKGROUND_TPIPE,FADEIN);
}
