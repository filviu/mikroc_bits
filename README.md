adc2_mikroc
===========

 Open source ADC read function for mikroc

Yes, I know, mikroC has it’s own ADC library, but as always I am a sucker for open source. So I decided to write my own adc read function, so I can better understand the PIC ADC converter operation. And, in the good spirit of open source I decided to share my code. The following code is the ADC on LCD example supplied by MikroElectronika with their EasyPic5 board, and it’s written in MikroC Pro. Of interest are the ADC related initializations and the adc_read2 function. (adc_read is mikroC’s own function).

Code is tested on the EasyPic5 board, but should work on other boards and / or compilers with minimal modifications. 

Please note that I only checked for the first 4 channels in the adc_read2 function. It’s easy to check for the other ADC channels using this table:

CHS3 | CHS2 |	CHS1 |	CHS0 |	Channel 	Pin
0 	0 	0 	0 	0 	RA0/AN0
0 	0 	0 	1 	1 	RA1/AN1
0 	0 	1 	0 	2 	RA2/AN2
0 	0 	1 	1 	3 	RA3/AN3
0 	1 	0 	0 	4 	RA5/AN4
0 	1 	0 	1 	5 	RE0/AN5
0 	1 	1 	0 	6 	RE1/AN6
0 	1 	1 	1 	7 	RE2/AN7
1 	0 	0 	0 	8 	RB2/AN8
1 	0 	0 	1 	9 	RB3/AN9
1 	0 	1 	0 	10 	RB1/AN10
1 	0 	1 	1 	11 	RB4/AN11
1 	1 	0 	0 	12 	RB0/AN12
1 	1 	0 	1 	13 	RB5/AN13
