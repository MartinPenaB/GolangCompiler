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
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern BufferPointer stringLiteralTable;	/* String literal table */
int32 line;								/* Current line number of the source code */
extern int32 errorNumber;				/* Defined in platy_st.c - run-time error number */

extern int32 stateType[NUM_STATES];
extern string keywordTable[KWT_SIZE];
extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern int32 transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static BufferPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

int32 startScanner(BufferPointer psc_buf) {
	/* TO_DO: Start histogram */
	for (int32 i=0; i<NUM_TOKENS;i++)
		scData.scanHistogram[i] = 0;
	/* Basic scanner initialization */
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(gos_void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	rune c;						/* input symbol */
	int32 state = 0;			/* initial state of the FSM */
	int32 lexStart;				/* start offset of a lexeme in the input char buffer (array) */
	int32 lexEnd;				/* end offset of a lexeme in the input char buffer (array)*/

	int32 lexLength;			/* token length */
	int32 i;					/* counter */
	/*
	sofia_char newc;			// new char
	*/

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		/* Cases for spaces */
		case ' ':	//Space
		case '\t':	//Tab encounter
		case '\f':	//Form feed
			break;
		case '\n':	//New line
			line++;
			break;

		/* Cases for symbols */
		case '(':
			currentToken.code = LPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '{':
			currentToken.code = LBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '}':
			currentToken.code = RBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case ':':
			currentToken.code = DEC_T;	/* Declariation Type in Golang */
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case ',':
			currentToken.code = CMA_T;	/* Comma between words */
			scData.scanHistogram[currentToken.code]++;
			return currentToken;

			/* Symbols that can contain multiple conditions */

		case '!':	//relational opeator of NOT EQUAL
			if (readerGetChar(sourceBuffer) == '=') {
				currentToken.code = REL_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.relationalOperator = OP_NE;
				return currentToken;
			}
			else {	//logical operator of NOT 
				currentToken.code = LOG_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.logicalOperator = OP_NOT;
				return currentToken;
			}

		case '/':
			if (readerGetChar(sourceBuffer) == '/') {

				while ((c = readerGetChar(sourceBuffer) != '\n'));
				line++;
				//readerGetChar(sourceBuffer);  // Consume the second '/'
				//while (1) {
				//	c = readerGetChar(sourceBuffer);
				//	if (c == '\n') {
				//		line++;
				//		break;  // Exit loop when newline is encountered
				//	}
				//}
				currentToken.code = CMT_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}
			/*else if (readerGetChar(sourceBuffer) == ' ') {
				currentToken.code = ART_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.arithmeticOperator = OP_DIV;
				return currentToken;
			}*/
			currentToken.code = ART_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.arithmeticOperator = OP_DIV;
			return currentToken;

		case '&':
			if (readerGetChar(sourceBuffer) == '&') {
				currentToken.code = LOG_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.logicalOperator = OP_AND;
				return currentToken;
			}
			else if (readerGetChar(sourceBuffer) == ' ') {
				currentToken.code = REF_T;	/* Reference Variable Keyword */
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}

			currentToken.code = REF_T;	/* Reference Variable  Keyword */
			scData.scanHistogram[currentToken.code]++;
			return currentToken;


			/* Arithmetic Operator */
		case '+':
			currentToken.code = ART_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.arithmeticOperator = OP_ADD;
			return currentToken;
		case '-':
			currentToken.code = ART_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.arithmeticOperator = OP_SUB;
			return currentToken;
		case '*':
			currentToken.code = ART_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.arithmeticOperator = OP_MUL;
			return currentToken;

			/* Relational Operator */
		case '=':
			if (readerGetChar(sourceBuffer) == '='){
				currentToken.code = REL_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.relationalOperator = OP_EQ;
				return currentToken;
			}
			else {
				currentToken.code = ASS_T; 
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}			
		case '>':
			currentToken.code = REL_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.relationalOperator = OP_GT;
			return currentToken;
		case '<':
			currentToken.code = REL_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.relationalOperator = OP_LT;
			return currentToken;

		/* Logical Operator */
		case '|':
			if (readerGetChar(sourceBuffer) == '|') {
				currentToken.code = LOG_T;
				scData.scanHistogram[currentToken.code]++;
				currentToken.attribute.logicalOperator = OP_OR;
				return currentToken;
			}

		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((int32)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			readerRestore(lexemeBuffer); //xxx
			return currentToken;
		} // switch

	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */

int32 nextState(int32 state, rune c) {
	int32 col;
	int32 next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	//assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*	[A-z],  [0-9],     /,     _,     .,	    ",    \n,     (,  SEOF,    O  */
/*	 A(0),   D(1),  C(2),  U(3),  P(4),  Q(5),  N(6),  L(7),  L(8),  L(9) */

int32 nextClass(rune c) {
	int32 val = -1;
	switch (c) {
	case CHRCOL2:
		val = 2;
		break;
	case CHRCOL3:
		val = 3;
		break;
	case CHRCOL4:
		val = 4;
		break;
	case CHRCOL5:
		val = 5;
		break;
	case CHRCOL6:
		val = 6;
		break;
	case CHRCOL7:
		val = 7;
		break;
	case CHARSEOF0:
		val = 8;
		break;
	case CHARSEOF255:
		val = 8;
		break;
	default:
		if (isalpha(c))
			val = 0;
		else if (isdigit(c))
			val = 1;
		else
			val = 9;
	}
	return val;
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for COM */

Token funcCMT(string lexeme) {
	Token currentToken = { 0 };
	int32 i = 0, len = (int32)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
	}
	currentToken.code = CMT_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(string lexeme) {
	Token currentToken = { 0 };
	long gos_long; //Need to determine which data type I should use.
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		gos_long = atol(lexeme);
		if (gos_long >= 0 && gos_long <= SHRT_MAX) {
			currentToken.code = INL_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.intValue = (int32)gos_long;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}

/*
 ************************************************************
 * Acceptance State Function FPL
 *		Function responsible to identify FPL (Floating literals).
 * - It is necessary respect the limit (ex: 4-byte float in C).
 * - In the case of larger lexemes, error shoul be returned.
 * - Only first ERR_LEN characters are accepted and eventually,
 *   additional three dots (...) should be put in the output.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for FPL */

Token funcFPL(string lexeme) {
	Token currentToken = { 0 };
	gos_double tdouble = atof(lexeme);
	if (tdouble == 0.0 || tdouble >= FLT_MIN && tdouble <= FLT_MAX) {
		currentToken.code = FLT_T;
		scData.scanHistogram[currentToken.code]++;
		currentToken.attribute.floatValue = (float32)tdouble;
	}
	else {
		currentToken = (*finalStateTable[ESNR]) (lexeme);
	}
		return currentToken;
}

/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcID(string lexeme) {	//Add a condition 
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	rune lastch = lexeme[length - 1];
	int32 isID = GOS_FALSE;

	switch (lastch) {
		case CHRCOL7:
			currentToken.code = MID_T;
			scData.scanHistogram[currentToken.code]++;
			isID = GOS_TRUE;
			break;
		default:
			// Test Keyword
			lexeme[length - 1] = '\0';
			currentToken = funcKEY(lexeme);
			break;
	}
	if (isID == GOS_TRUE) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Variable ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Variable */

Token funcVID(string lexeme) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	char lastch = lexeme[length - 1];
	int32 isVID = GOS_FALSE;
	int32 vidindex = -1;
	int32 i = 0;

	for (i = 0; i < length; i++) {
		if (lexeme[i] < 0 || lexeme[i] >= 255) {
			isVID = GOS_FALSE;
			break;
		}
		isVID = GOS_TRUE;
	}

	if (isVID == GOS_TRUE) {
		currentToken.code = VAR_T;
		scData.scanHistogram[currentToken.code]++;
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	else {
		currentToken.code = ERR_T;
		scData.scanHistogram[currentToken.code]++;
	}
	return currentToken;
}

/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(string lexeme) {
	Token currentToken = { 0 };
	int32 i = 0, len = (int32)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			scData.scanHistogram[currentToken.code]++;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		scData.scanHistogram[currentToken.code]++;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = STR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(string lexeme) {
	Token currentToken = { 0 };
	int32 kwindex = -1, j = 0;
	int32 len = (int32)strlen(lexeme);
	lexeme[len - 1] = '\0';

	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		scData.scanHistogram[currentToken.code]++;
		currentToken.attribute.codeType = kwindex;
	}
	else {
		currentToken.code = VAR_T;
		scData.scanHistogram[currentToken.code]++;
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(string lexeme) {
	Token currentToken = { 0 };
	int32 i = 0, len = (int32)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ERR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

gos_void printToken(Token t) {
	extern string keywordTable[]; /* link to keyword table in */
	switch (t.code) {
	case RTE_T:	//Run-time error token
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T: //Error token
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T: //Source EOF token
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MID_T:
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case VAR_T:
		printf("VAR_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case INL_T:
		printf("INL_T\t\t%d\n", t.attribute.intValue);
		break;
	case FLT_T:
		printf("FPL_T\t\t%f\n", t.attribute.floatValue);
		break;
	case STR_T:
		printf("STR_T\t\t%d\t ", (int32)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (int32)t.attribute.codeType));
		break;
	case LPR_T:
		printf("LPR_T\t\t(\n");
		break;
	case RPR_T:
		printf("RPR_T\t\t)\n");
		break;
	case LBR_T:
		printf("LBR_T\t\t{\n");
		break;
	case RBR_T:
		printf("RBR_T\t\t}\n");
		break;
	case DEC_T:
		printf("DEC_T\t\t:\n");
		break;
	case REF_T:
		printf("REF_T\t\t&\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case CMT_T:
		printf("CMT_T\t\t\n");
		break;
	case CMA_T:
		printf("CMA_T\t\t,\n");
		break;
	case ART_T:
		switch (t.attribute.arithmeticOperator) {
		case 0:
			printf("ART_T\t\t+\n");
			break;
		case 1:
			printf("ART_T\t\t-\n");
			break;
		case 2:
			printf("ART_T\t\t*\n");
			break;
		case 3:
			printf("ART_T\t\t/\n");
			break;
		}
		break;
	case REL_T:
		switch (t.attribute.relationalOperator) {
		case 0:
			printf("REL_T\t\t=\n");
			break;
		case 1:
			printf("REL_T\t\t!=\n");
			break;
		case 2:
			printf("REL_T\t\t>\n");
			break;
		case 3:
			printf("REL_T\t\t<\n");
			break;
		}
		break;
	case LOG_T:
		switch (t.attribute.logicalOperator) {
		case 0:
			printf("LOG_T\t\t&&\n");
			break;
		case 1:
			printf("LOG_T\t\t||\n");
			break;
		case 2:
			printf("LOG_T\t\t!\n");
			break;
		}
		break;
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
gos_void printScannerData(ScannerData scData) {
	/* Print Scanner statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_TOKENS; cont++) {
		if (scData.scanHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", tokenStrTable[cont], "]=", scData.scanHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
