/**********************************************************************************************************************/
/* Author:      P. Luettmann, J. Telljohann                                                                           */
/* Version:     2.0                                                                                                   */
/* License:     none                                                                                                  */
/**********************************************************************************************************************/


#include "user/appl.h"
#include "user/loop.h"
#include "user/idle.h"
#include "user/writer.h"

#include "machine/plugbox.h"
#include "machine/pic.h"

#include "device/cgastr.h"
#include "device/watch.h"

#include "guard/guard.h"

#include "syscall/guarded_organizer.h"
#include "syscall/guarded_buzzer.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_semaphore.h"

#include "meeting/bellringer.h"

#define STACK_SIZE 1024

Guarded_Keyboard keyboard;
CGA_Stream kout;
Plugbox plugbox;
Guard guard;
PIC pic;
CPU cpu;
Guarded_Organizer guarded_organizer;
Bellringer bellringer;
Guarded_Semaphore waiter(1);

unsigned char stack1[STACK_SIZE];
unsigned char stack2[STACK_SIZE];
unsigned char stack3[STACK_SIZE];
unsigned char stack4[STACK_SIZE];

Idle idle(stack3+STACK_SIZE);


int main()
{

    kout.setpos(0,0);
    for(int i = 0; i < 25; i++){
        for(int j = 0; j< 80; j++){
            kout.print(" ", 1);
        }
    }
    kout.setpos(0,0);
    kout << "Press any key to start!";
    kout.flush();

    Watch watch(1000); // 1 ms

    Application appl(stack1+STACK_SIZE);
    Loop loop1(stack2+STACK_SIZE);
    Writer writer(stack4+STACK_SIZE);

    guard.enter();

    guarded_organizer.Organizer::ready(appl);
    guarded_organizer.Organizer::ready(loop1);
    guarded_organizer.Organizer::ready(writer);

    keyboard.plugin();
    watch.windup();


    cpu.enable_int();


    guarded_organizer.schedule();

    // Ein Betriebssystem sollte eben nicht plötzlich enden (^.^)
    while(1);
}
