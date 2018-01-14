#include "MapleMini.h"
#include "mbed.h"

char x[300],y[30],z[30],l[30],m[30];

int main()
{
    confSysClock();     //Configure system clock (72MHz HSE clock, 48MHz USB clock)

    Serial      sim800(PA_2, PA_3);
    DigitalOut  myled(LED1);

    sim800.baud(9600);


    sim800.printf("ATE0\r\n");                          //Command for the TURN OFF the repated terms(ECHO).
    sim800.scanf("%s",x);                               //Take response in string x given by the "sim800".

    sim800.printf("AT+CGATT?\r\n");                     //To check the GPRS is attached or not.
    sim800.scanf("%s%s",x,y);

    sim800.printf("AT+CIPSHUT\r\n");                    //To reset the IP session if any.
    sim800.scanf("%s%s",x,y);

    sim800.printf("AT+SAPBR=3,1,Contype,GPRS\r\n");     //To Set the connection type to GPRS.
    sim800.scanf("%s",x);

    sim800.printf("AT+SAPBR=3,1,APN,www\r\n");          //To Set the APN to to "www" , It might be different for you, and depends on the network.
    sim800.scanf("%s",x);

    sim800.printf("AT+SAPBR =1,1\r\n");                 //To Enable the GPRS.
    sim800.scanf("%s",x);

    sim800.printf("AT+SAPBR =2,1\r\n");                 //To get the IP address.
    sim800.scanf("%s%s%s",x,y,z);


    sim800.printf("AT+HTTPINIT\r\n");                   //To enable the HTTP mode.
    sim800.scanf("%s",x);

    sim800.printf("AT+HTTPPARA=CID,1\r\n");             //To sets up HTTP parameters for the HTTP call.
    sim800.scanf("%s",x);


    float lng,lat = 0;
    while(lat == 0)
    {
        sim800.printf("AT+CIPGSMLOC=1,1\r\n");          //To check the Location of GSM in Co-Ordinates(Longitude,Latitude).
        sim800.scanf("%s%s%s",x,y,z);
        sscanf(y,"0,%f,%f",&lng,&lat);                  //To sperate out the value of longitude and latitude from the string 'y'.
    }

    while(1)
    {
        myled = 1;      // turn the on-board LED on
        wait_ms(200);   // wait 200 milliseconds
        myled = 0;      // turn the on-board LED off
        wait_ms(1000);  // wait 1000 milliseconds
    }
}
