/* 
 * File:   mcal_std_types.h
 * Author: HP
 *
 * Created on August 16, 2023, 2:05 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section: Includes */
#include "std_lib.h"
#include "compiler.h"


/* Section: Data Type Declarations */
typedef  unsigned char      uint8;
typedef  unsigned short     uint16;
typedef unsigned long       uint32;


typedef  signed char        sint8;
typedef signed short        sint16;
typedef signed long         sint32;

typedef float               float32; 
typedef double              float64;

typedef uint8               std_ReturnType; /* Standard type of uint8 according to AUTOSAR */

/* Section: Macro Definitions */
#define STD_HIGH            0x01
#define STD_LOW             0x00

#define STD_ON              0x01
#define STD_OFF             0x00

#define STD_ACTIVE          0x01
#define STD_IDLE            0x00

#define E_OK                (std_ReturnType)0x01  /*Standard type from Autosar that function executed correctly */
#define E_NOT_OK            (std_ReturnType)0x00  /*Standard from AUTOSAR that function failed  */


#define ZERO_INIT           0x00
#define One_INIT           0x01
/* Section: Macro Functions */


/* Section: Function Prototype */


#endif	/* MCAL_STD_TYPES_H */

