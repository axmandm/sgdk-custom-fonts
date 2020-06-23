#include <genesis.h>
#include <string.h>
#include "sound.h"
#include "font.h"

/*The variable for the SFX used must be defined*/
#define GAME_OVER     65

/*Timer variables*/
int timer = 3;
char label_timer[6] = "TIMER\0";
char str_timer[3] = "0";

/*String handling*/
int sign(int x) {
    return (x > 0) - (x < 0);
}

/*Update the timer on screen*/
void updateTimer(){
  /*Convert the int to a char*/
	sprintf(str_timer,"%d",timer);

  /*Remove the text on screen*/
	VDP_clearText(1,2,3);

  /*Draw the timer at 1,2*/
	VDP_drawText(str_timer,1,2);
}

/*Joypad handling function*/
void handleJoyEvent(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (changed & ~state & BUTTON_START)
        {
            timer = 3;
            SYS_reset ();
        }
        if (changed & ~state & BUTTON_A)
        {
            timer = timer + 3;
        }
    }
}

int main()
{

  /*Load the custom font, and set the pallete to the colours of the font*/
  VDP_loadFont(custom_font.tileset, DMA);
  VDP_setPalette(PAL0, custom_font.palette->data);

  /*Main Loop*/
  while(TRUE)
  {

    JOY_setEventHandler(handleJoyEvent);

    /*Start playing the music*/
    XGM_startPlay(music);

    /*Initialize SFX - this refers to the sound files defined in sound.h and sound.res*/
    SND_setPCM_XGM(GAME_OVER, gameover, sizeof(gameover));

    while(timer >= 1)
    {

        /*Display the timer label at 1,1*/
        VDP_drawText(label_timer, 1, 1);

        /*Call the timer display function*/
        updateTimer();

        /*Decrement the timer*/
        timer--;

        /*Wait for 1s*/
        waitMs (1000);

    }

    if(timer >=0)
    {

      /*Remove the scoreboard*/
      VDP_clearTextArea(1,1,10,10);

      /*Stop the music*/
      XGM_stopPlay();

      /*Game Over Text*/
      VDP_drawText("Game Over!", 16, 11);
      XGM_startPlayPCM(GAME_OVER, 1, SOUND_PCM_CH2);

    }

    return 0;

  }

  /*Wait vsync - always last - if you don't wait for vsync it flickers*/
  VDP_waitVSync();

  return 0;

}
