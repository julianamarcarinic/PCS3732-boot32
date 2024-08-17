#include <mbed.h>
#include <stdio.h>

BufferedSerial ser(PB_10, PC_5, 115200);
FileHandle *mbed::mbed_override_console(int fd) {
    return &ser;
}

typedef void (*pFunction)(void);
 

static void go_to_application(){

    uint32_t JumpAddress;
	pFunction Jump_To_Application;
	printf("BOOTLOADER Start \r\n");

    ThisThread::sleep_for(100ms);
    JumpAddress = *(uint32_t *) (0x08010000 + 4 );
    Jump_To_Application = (pFunction) JumpAddress;

    HAL_RCC_DeInit(); // Reset RCC (Reset and Clock Control)
    HAL_DeInit();     // De-initialize the HAL

    __set_MSP(*(uint32_t *)0x08010000);

    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

    Jump_To_Application();
}

int main(){

    go_to_application();
    while (1)
    {
        printf("ue\n");
    }
    

    return 0;
}