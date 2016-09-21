/*
 *
 *	Target: PIC18F25K22
 *	Internal RC Oscillator
 *
 */

#define BT_UART_Baud_Default 115200

void InitPorts()
{
	ANSELC = 0;
    ANSELB = 0;

    TRISC = 0x00; 
    TRISB = 0x00;

    LATB = 0x00;
    LATC = 0x00;
}

void main()
{
	OSCCON = 0x62;

	InitPorts();

	LATB.RB0 = 1;

	UART1_Init(BT_UART_Baud_Default);
	Delay_ms(100);

	//Wake
	LATC.RC1 = 1;

	LATB.RB1 = 1;

	UART1_Write_Text("+\r");           //Echo on
    UART1_Write_Text("sf,2\r");        //Complete factory reset
    UART1_Write_Text("r,1\r");
    Delay_ms(250);
    UART1_Write_Text("sr,10008000\r"); //Support MLDP, enable OTA (peripheral mode is enabled by default)
    UART1_Write_Text("r,1\r");         //reboot to apply settings

    //Wait for "CMD"
    Delay_ms(2500);

    UART1_Write_Text("a\r");           //Start advertising

    LATB.RB2 = 1;
}