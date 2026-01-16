#include <EEPROM.h>
/*
 * 
 * 
 *0.4 working on adding nLoop, and EndOf
 *only save the value to eeprom when you change channel, also save which channel is connected.
 *This has been replaced with save only when save is pressed ;)
 *0.5 nLoop should work, EndOf should work, check CVinput, and if the opamp can be other than mcp6002
 *HAVE TO FIX EnvelopeWrite2 as it is wrong!
 *0.6 -changed the exponent of decay and release as they seem to have been reversed.
 *0.7 -fixed envelopeWrite2, and the shape menu so it works as it should...
 *v0.8 0.5 doesnt work on lengthmultiplication
 *v0.81 fixed a bunch of compiler errors.
 *v0.82 removed all serial debug, for better response to short trigs.
 *v0.83 Thank you to Jos Bouten who found an error which made ADSR2 Slopes not being able to change. Fixed in this version.
 */
 
 
 
 
