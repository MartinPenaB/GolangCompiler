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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Svillen Ranev / Paulo Sousa
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *************************************************************
 */

BufferPointer readerCreate(int32 size, int32 increment, int32 mode) {
	BufferPointer readerPointer;
	/* TO_DO: Adjust the values according to parameters */
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	/* TO_DO: Defensive programming */
	if (size <= 0)
		size = READER_DEFAULT_SIZE;
	if (increment <= 0)
		increment = READER_DEFAULT_INCREMENT;
	if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI)
		mode = MODE_FIXED;
	readerPointer->content = (string)malloc(size);
	/* TO_DO: Defensive programming */
	if (!readerPointer->content)
		return NULL;
	/* TO_DO: Initialize the histogram */
	for (int i = 0; i < NCHAR; i++)
		readerPointer->histogram[i] = 0;

	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* TO_DO: Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;
	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->flags |= EMP_FLAG;
	/* NEW: Cleaning the content */
	if (readerPointer->content)
		readerPointer->content[0] = READER_TERMINATOR;

	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;

	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
BufferPointer readerAddChar(BufferPointer const readerPointer, rune ch) {
	string tempReader = NULL;
	int32 newSize = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	if (ch < 0)
		return NULL;
	/* TO_DO: Reset Realocation */
	readerPointer->flags &= !REL_FLAG;
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (int32)sizeof(rune) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		readerPointer->flags &= !FUL_FLAG;
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags &= !FUL_FLAG;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size)
				return NULL;
			newSize = newSize > READER_MAX_SIZE ? READER_MAX_SIZE : newSize;
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size)
				return NULL;
			newSize = newSize > READER_MAX_SIZE ? READER_MAX_SIZE : newSize;
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = realloc(readerPointer->content, newSize);
		/* TO_DO: Defensive programming */
		if (!tempReader)
			return NULL;
		/* TO_DO: Check Relocation */
		if (tempReader != readerPointer->content)readerPointer->flags |= REL_FLAG;

		readerPointer->content = tempReader;
		readerPointer->size = newSize;
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[ch]++;

	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_bool readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return GOS_FALSE;
	/* TO_DO: Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG;
	readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;

	return GOS_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_bool readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return GOS_FALSE;
	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);

	return GOS_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_bool readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return GOS_FALSE;
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags & EMP_FLAG)
		return GOS_TRUE;

	// If neither condition is met, buffer is not full
	return GOS_FALSE;
}



/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_bool readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return GOS_FALSE;
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags & EMP_FLAG)
		return GOS_TRUE;

	// If neither condition is met, buffer is not full
	return GOS_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_bool readerSetMark(BufferPointer const readerPointer, int32 mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || !(mark >= 0 && mark <= readerPointer->position.wrte))
		return GOS_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return GOS_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerPrint(BufferPointer const readerPointer) {
	int32 cont = 0;
	rune c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if (!readerPointer)
		return READER_ERROR;
	c = readerGetChar(readerPointer);
	if (c < 0 || c >= NCHAR)
		c = 0;
	/* TO_DO: Check flag if buffer EOB has achieved */
	if (readerPointer->flags & END_FLAG)
		return cont;
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
		if (c < 0 || c >= NCHAR)
			c = 0;
		if (readerPointer->flags & END_FLAG)
			break;
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerLoad(BufferPointer const readerPointer, FILE* const fileDescriptor) {
	int32 size = 0;
	rune c;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !fileDescriptor)
		return READER_ERROR;
	c = (rune)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}

	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_bool readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return GOS_FALSE;
	/* TO_DO: Recover positions */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;

	return GOS_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_bool readerRetract(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || !(readerPointer->position.read > 0))
		return GOS_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->position.read--;

	return GOS_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_bool readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return GOS_FALSE;
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;

	return GOS_TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rune readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->position.read == readerPointer->position.wrte) {
		/* TO_DO: Set EOB flag */
		readerPointer->flags |= END_FLAG;
		return '\0';
	} else {
		/* TO_DO: Reset EOB flag */
		readerPointer->flags &= !END_FLAG;
	}
	if (readerPointer->position.wrte > 0)
		return readerPointer->content[readerPointer->position.read++];

	return READER_TERMINATOR;
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
string readerGetContent(BufferPointer const readerPointer, int32 pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || !(pos >= 0 && pos <= readerPointer->position.wrte))
		return NULL;
	/* TO_DO: Return content (string) */
	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return wrte */
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return mark */
	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerGetInc(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
byte readerGetFlags(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return flags */
	return readerPointer->flags;
}


/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
gos_void readerPrintStat(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return;
	/* TO_DO: Print the histogram */
	for (int i = 0; i < NCHAR; i++)
		if (readerPointer->histogram[i] > 0)
			printf("B[%c]=%d",i, readerPointer->histogram[i]);
}


/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
int32 readerNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Returns the number of errors */
	return readerPointer->numReaderErrors;
}
