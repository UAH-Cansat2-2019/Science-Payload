/*
 * mechanisms.c
 *
 * Created: 6/9/2019 5:18:52 PM
 *  Author: quaz9
 */ 


void buzz_on(void)
{
	BUZZ_PORT.DIRSET |= 0b00000001;
	BUZZ_PORT.OUTSET |= 0b00000001;
	
}
void buzz_off(void)
{
		BUZZ_PORT.DIRSET |= 0b00000001;
		BUZZ_PORT.OUTSET &= 0b11111110;
}