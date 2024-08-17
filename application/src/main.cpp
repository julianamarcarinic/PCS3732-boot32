#include <mbed.h>
#include <stdio.h>

BufferedSerial ser(PB_10, PC_5, 115200);
FileHandle *mbed::mbed_override_console(int fd) {
    return &ser;
}
 

int main(){

    printf("APP Start ...");

    return 0;
}