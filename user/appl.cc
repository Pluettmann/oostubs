/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"

         
void Application::action () {
    int wait;
    int count = 0;
    Keyboard keyboard;
    keyboard.plugin();

    kout.setpos(0,0);

    kout << "Appl: First!";
    kout.flush();

    while (1){
        kout.setpos(0,1);
        kout << "Appl: Doing important stuff(" << count++ << ")";
        kout.flush();

        wait =  10000000;
        while (wait > 0) wait--;
    }
}
