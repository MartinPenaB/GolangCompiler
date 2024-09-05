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
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */
#define FLM_LEN 8	/* maximum number of digiys for FL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 21

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MID_T,		/*  1: Method ID token */
	VAR_T,		/*  2: Variable name token */
	INL_T,		/*  3: Integer literal token */
	FLT_T,		/*  4: Float literal token */
	STR_T,		/*  5: String literal token */
	LPR_T,		/*  6: Left parenthesis token */
	RPR_T,		/*  7: Right parenthesis token */
	LBR_T,		/*  8: Left brace token */
	RBR_T,		/*  9: Right brace token */
	DEC_T,		/* 10: Declaration token */
	REF_T,		/* 11: Reference token */
	KW_T,		/* 12: Keyword token */
	CMT_T,		/* 13: Comment token */
	CMA_T,		/* 14: Comma token */
	ART_T,		/* 15: Artimetic token */
	REL_T,		/* 16: Relational token */
	LOG_T,		/* 17: Logical token */
	ASS_T,		/* 18: Assignment token */
	RTE_T,		/* 19: Run-time error token */
	SEOF_T,		/* 20: Source end-of-file token */
};


/* TO_DO: Define the list of keywords */
static string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MID_T",	
	"VAR_T",		
	"INL_T",
	"FLT_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"DEC_T",
	"REF_T",
	"KW_T",
	"CMT_T",
	"CMA_T",
	"ART_T",
	"REL_T",
	"LOG_T",
	"ASS_T",
	"RTE_T",
	"SEOF_T",
};

#include "limits.h"

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator; // +, -, *, /
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator; // ==, !=, >, <
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator; // && || !
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	int32 codeType;						/* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */	
	int32 intValue;						/* integer literal attribute (value) */
	int32 keywordIndex;					/* keyword index in the keyword table */
	int32 contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	float32 floatValue;					/* floating-point literal attribute (value) */
	rune idLexeme[VID_LEN + 1];			/* variable identifier token attribute */
	rune errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	byte flags;						/* Flags information */
	union {
		int32 intValue;				/* Integer value */
		float32 floatValue;			/* Float value */
		string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	int32 code;					/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	int32 scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '/'	 //comment
#define CHRCOL3 '_'	 //Underline
#define CHRCOL4 '.'	 //dot
#define CHRCOL5 '"'	 //semicolon
#define CHRCOL6 '\n' //Line
#define CHRCOL7 '('	 //left parenthesis
#define CHRCOL8 '-'  //Dash line for Go-Simple

/* These constants will be used on VID / MID function */
#define VAR_REF '&'

/* TO_DO: Error states and illegal state */
#define ESNR	15		/* Error state with no retract */
#define ESWR	16		/* Error state with retract */
#define FS		 7		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		17
#define CHAR_CLASSES	10

/* TO_DO: Transition table - type of states defined in separate table */
static int32 transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*			 [A-z],  [0-9],   /,    _,    .,	",  \n,    (,    SEOF,    O	  */
	/*			  A(0),   D(1),C(2), U(3), P(4), Q(5), N(6),  L(7),  L(8), L(9)   */
	/* S00 */	{	  1,   10,	  5, ESNR, ESNR,	8, ESNR, ESNR,  ESWR,  ESNR},	// S0: NOAS
	/* S01 */	{     1,    1,	  4,    1,    4,    4,    4,    3,  ESWR,     4},	// S1: NOAS
	/* S02 */	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,    FS,	 FS},	// S2: ASNR (VID)
	/* S03 */	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,    FS,	 FS},	// S3: ASWR (MID)
	/* S04 */	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	  FS,    FS},	// S4: ASWR (KEY)
	/* S05 */	{  ESNR, ESNR,	  6, ESNR, ESNR, ESNR, ESNR, ESNR,  ESWR,  ESNR},	// S5: NOAS
	/* S06 */	{     6,    6,    6,    6,    6,    6,	  7,    6,  ESWR,     6},	// S6: NOAS
	/* S07 */	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	  FS,    FS},	// S7: ASNR (SLC)
	/* S08 */	{     8,    8,    8,    8,    8,    9,	  8,    8,	ESWR,     8},	// S8: NOAS
	/* S09 */   {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	  FS,    FS},	// S9: ASNR (SL)
	/* S10 */	{    11,   10,   11,   11,   12,   11,   11,   11,	ESWR,    11},	// S10: NOAS
	/* S11 */	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	  FS,    FS},	// S11: ASNR (IL)
	/* S12 */	{  ESNR,   13, ESNR, ESNR, ESNR, ESNR, ESNR, ESNR,	ESWR,  ESNR},	// S12: NOAS
	/* S13 */	{    14,   13,   14,   14,   14,   14,	 14,   14,	ESWR,    14},	// S13: NOAS
	/* S14 */	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	  FS,    FS},	// S14: ASNR (FL)

	/* S15 */	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	  FS,    FS},	// S15: (Err1)
	/* S16 */	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,	  FS,    FS}	// S16: (Err2)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static int32 stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (VID) - Variable */
	FSNR, /* 03 (MID) - Methods */
	FSNR, /* 04 (KEY) - Keywords */
	NOFS, /* 05 */
	NOFS, /* 06 */
	FSNR, /* 07 (SLC) */
	NOFS, /* 08 */
	FSNR, /* 09 (SL) */
	NOFS, /* 10 */
	FSWR, /* 11 (IL) */
	NOFS, /* 12 */
	NOFS, /* 13 */
	FSWR, /* 14 (FL) */
	FSNR, /* 15 (Err1 - no retract) */
	FSWR  /* 16 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
int32				startScanner(BufferPointer psc_buf);
static int32		nextClass(rune c);					/* character class function */
static int32		nextState(int32, rune);				/* state machine function */
gos_void			printScannerData(ScannerData scData);
Token				tokenizer(gos_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(string lexeme);

/* Declare accepting states functions */
Token funcSL	(string lexeme);
Token funcIL	(string lexeme);
Token funcID	(string lexeme);
Token funcCMT   (string lexeme);
Token funcKEY	(string lexeme);
Token funcErr	(string lexeme);
Token funcFPL	(string lexeme);

// Why is there no funcIL and funcKey for the below finalStateTable

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* VID	[02] */
	funcID,		/* MID	[03] */
	funcKEY,	/* KEY  [04] */
	NULL,		/* -	[05] */	
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	NULL,		/* -    [08] */
	funcSL,		/* SL   [09] */
	NULL,		/* -	[10] */
	funcIL,		/* IL   [11] */	
	NULL,		/* -	[12] */
	NULL,		/* -    [13] */
	funcFPL,	/* FIL	[14] */
	funcErr,	/* ERR1 [15] */
	funcErr		/* ERR2 [16] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 17

/* TO_DO: Define the list of keywords */
static string keywordTable[KWT_SIZE] = {
	"func",		/* KW00 */
	"var",		/* KW01 */
	"if",		/* KW02 */
	"else",		/* KW03 */
	"for",		/* KW04 */
	"return",	/* KW05 */
	"package",	/* KW06 */
	"import",	/* KW07 */
	"type",		/* KW08 */
	"switch",	/* KW09 */
	"case",		/* KW10 */
	"default",	/* KW11 */
	"continue", /* KW12 */
	"main",		/* KW13 */
	"int32",	/* KW14 */
	"float32",	/* KW15 */
	"string"	/**/
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	rune indentationCharType;
	int32 indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
int32 numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
