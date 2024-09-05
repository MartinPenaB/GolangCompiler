/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: Jongyoung Choi, Martin Pena
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=

                    .*@**,,,,,,,,,,,,,,*&.
        .*@(%%.@,,,,/(,,,,,,,,,,,/%   /#,,*@,,,,*%
        .&,,**(,,,          ,,,,,          ,,,,#@/,,*.
        ,,,*@#,,, %@@        *,, /@@@       @,,,*,,,/,
        ,@,%,,,* (@@        ,,,@ #@        ,,,,,*#,
        /,,,,,,&        #,@@@@(&      #*,,,,,,,@
        &,,,,,,,,,,,,,,,..(@@*..%,,,,,,,,,,,,,,*.
        .#,,,,,,,,,,,,,,/..,&#%..,,,,,,,,,,,,,,,,,
        %,,,,,,,,,,,,,,,,.    *,,,,,,,,,,,,,,,,,,
        @,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*
        (,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,/
        ,*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,/
        ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,(
    ,....,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,&.../
    ,@##**,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,&*@&.
        *,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,(.
        %,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*.
        @,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*.
        &,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,(.
        @,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,@
        /,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
        .&,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,/
            .@,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*
            *,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,%
            ....&,,,,,,,,,,,,,,,,,,,,,,,,*(...,.
            ,.,..&*  .*&&(,,,,,,,,%@(*,    (..@%
            ..


                    (((((((((((((,          .(((((((((((((
                ,(((((((((((((((((((     ((((((((((((((((((((
(((((((((*  ./((((((((/ ((((((((((*  ,((((((((((
                ((((((((                ,(((((((           (((((((.
            (((((((.     (((((((((((((((((((             (((((((
    .,,,,,,*   (((((((     (((((((((((((((((((*            ,((((((*
            ((((((((          ((((((((((((((           ((((((((
                (((((((((,    ((((((((( ((((((((((     (((((((((/
                ((((((((((((((((((((     ((((((((((((((((((((,
                    ((((((((((((((          ,((((((((((((((

=---------------------------------------=
*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

 /* TIP: Do not change pragmas, unless necessary .......................................*/
 /*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
 /*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

 /* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/*apply bit:	|= flag*/
/*rst bit:		&= !flag*/
/*chk bit:		& flag*/
/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00   /* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: END = End of buffer flag */
#define END_FLAG 0x08       /* (0000.1000)_2 = (8)_10 */
/* TO_DO: BIT 2: REL = Relocation memory flag */
#define REL_FLAG 0x04       /* (0000.0100)_2 = (4)_10 */
/* TO_DO: BIT 1: EMP = Buffer empty flag */
#define EMP_FLAG 0x02       /* (0000.0010)_2 = (2)_10 */
/* TO_DO: BIT 0: FUL = Buffer full flag */
#define FUL_FLAG 0x01       /* (0000.0001)_2 = (1)_10 */


#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
    int32 mark;		    /* the offset to the mark position (in chars) */
	int32 read;			/* the offset to the get a char position (in chars) */
	int32 wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	string	content;			/* pointer to the beginning of character array (character buffer) */
	int32		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	int32		increment;			/* character array increment factor */
	int32		mode;				/* operational mode indicator */
	byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;				/* Offset / position field */
	int32		histogram[NCHAR];	/* Statistics of chars */
	int32		numReaderErrors;	/* Number of errors from Reader */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate(int32, int32, int32);
BufferPointer	readerAddChar(BufferPointer const, rune);
gos_bool		readerClear(BufferPointer const);
gos_bool		readerFree(BufferPointer const);
gos_bool		readerIsFull(BufferPointer const);
gos_bool		readerIsEmpty(BufferPointer const);
gos_bool		readerSetMark(BufferPointer const, int32);
int32			readerPrint(BufferPointer const);
int32			readerLoad(BufferPointer const, FILE* const);
gos_bool		readerRecover(BufferPointer const);
gos_bool		readerRetract(BufferPointer const);
gos_bool		readerRestore(BufferPointer const);
/* Getters */
rune			readerGetChar(BufferPointer const);
string			readerGetContent(BufferPointer const, int32);
int32			readerGetPosRead(BufferPointer const);
int32			readerGetPosWrte(BufferPointer const);
int32			readerGetPosMark(BufferPointer const);
int32			readerGetSize(BufferPointer const);
int32			readerGetInc(BufferPointer const);
int32			readerGetMode(BufferPointer const);
byte			readerGetFlags(BufferPointer const);
gos_void		readerPrintStat(BufferPointer const);
int32			readerNumErrors(BufferPointer const);

#endif