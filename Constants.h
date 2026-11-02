#pragma once
#define PIN_BUTTON 2
// The compiler will now replace any mention of pin_button with the value 7 at compile time
#define PIN_AUTOPLAY 1

#define SPRITE_RUN1 1
#define SPRITE_RUN2 2
#define SPRITE_JUMP 3
#define SPRITE_JUMP_UPPER '.'        
#define SPRITE_JUMP_LOWER 4
#define SPRITE_TERRAIN_EMPTY ' '      
#define SPRITE_TERRAIN_SOLID 5
#define SPRITE_TERRAIN_SOLID_RIGHT 6
#define SPRITE_TERRAIN_SOLID_LEFT 7

#define HERO_HORIZONTAL_POSITION 1

#define TERRAIN_WIDTH 16
#define TERRAIN_EMPTY 0
#define TERRAIN_LOWER_BLOCK 1
#define TERRAIN_UPPER_BLOCK 2

#define HERO_POSITION_OFF 0          
#define HERO_POSITION_RUN_LOWER_1 1 
#define HERO_POSITION_RUN_LOWER_2 2

#define HERO_POSITION_JUMP_1 3       
#define HERO_POSITION_JUMP_2 4       
#define HERO_POSITION_JUMP_3 5       
#define HERO_POSITION_JUMP_4 6       
#define HERO_POSITION_JUMP_5 7       
#define HERO_POSITION_JUMP_6 8       
#define HERO_POSITION_JUMP_7 9       
#define HERO_POSITION_JUMP_8 10

#define HERO_POSITION_RUN_UPPER_1 11
#define HERO_POSITION_RUN_UPPER_2 12

// Create the connections from the LCD to the Arduino
