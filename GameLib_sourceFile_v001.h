/* 
 * File:   GameLib_sourceFile_v001.h
 * Author: Maverick Plsek
 *
 * Created on April 24, 2024, 1:20 PM
 */

#ifndef GAMELIB_SOURCEFILE_V001
#define	GAMELIB_SOURCEFILE_V001

#ifdef	__cplusplus
extern "C" {
#endif

    void initTimer4(void);
    void pic24_init(void);
    void initGame(void);
    void startGame(int durationOfGame);
    void endGame(void);
    void delay_In_Seconds(int seconds);
    int time_of_Game_Generator(void);


#ifdef	__cplusplus
}
#endif

#endif	/* GAMELIB_SOURCEFILE_V001 */

