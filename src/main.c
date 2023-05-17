#include <STC15Fxx.h>

#include <pinout.h>
#include <delay.h>
#include <uart.h>

#define CMD_LED 0x31

unsigned int state;

BYTE get_cmd()
{
    while (!REND && P55 != SWITCH_PRESSED)
        ;

    REND = 0;

    if (P55 == SWITCH_PRESSED)
    {
        while (P55 == SWITCH_PRESSED)
            ;
        return CMD_LED;
    }

    return RBUF;
}
void main()
{
    uart_init(BAUD_9600_110592);
    uart_send_string("VK STC15W204S KY-002_PIO P55 - KY-002 Signal V1.0\n");
    uart_send_string("Shock and led switches\n");

    state = LED_BUILDIN = LED_BUILDIN_ON;
    while (1)
    {
        if (get_cmd() == CMD_LED)
        {
            state ^= LED_BUILDIN_ON;
            LED_BUILDIN = state;
            uart_send_string("KY-002 shocks\n");
            delay_ms(200);
        }
    }
}

INTERRUPT(tm0, 1)
{
    uart_handle();
}