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
* File name: Parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferPointer	stringLiteralTable;
extern int32			line;
extern Token			tokenizer(gos_void);
extern string			keywordTable[KWT_SIZE];
static int32			syntaxErrorNumber = 0;

#define LANG_WRTE		"Println("
#define LANG_READ		"Scanln("
#define LANG_MAIN		"main("

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_func,
	KW_var,
	KW_if,
	KW_else,
	KW_for,
	KW_return,
	KW_package,
	KW_import,
	KW_type,
	KW_switch,
	KW_case,
	KW_default,
	KW_continue,
	KW_main,
	KW_int32,
	KW_float32,
	KW_string
};

/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 23

/* Parser */
typedef struct parserData {
	int32 parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
int32 numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
gos_void startParser();
gos_void matchToken(int32, int32);
gos_void syncErrorHandler(int32);
gos_void printError();
gos_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,
	BNF_comment,
	BNF_importdeclaration,
	BNF_optionalStatements,
	BNF_optionalVariableDeclarations,
	BNF_outputStatement,
	BNF_outputVariableList,
	BNF_packagedeclaration,
	BNF_program,
	BNF_statement,
	BNF_statements,
	BNF_statementsPrime,
	BNF_variableListDeclarations,
	BNF_variableListDeclaration,
	BNF_variableListDeclarationPrime,
	BNF_arithmetic,
	BNF_additive,
	BNF_substract
};

/* Define the list of keywords */
static string BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_comment",
	"BNF_importdeclaration",
	"BNF_optionalStatements",
	"BNF_optionalVariableDeclarations",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_packagedeclaration",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime",
	"BNF_variableListDeclarations",
	"BNF_variableListDeclaration",
	"BNF_variableListDeclarationPrime",
	"BNF_arithmetic",
	"BNF_additive",
	"BNF_substract"
	// Add missing strings for the other enum values here
};


/* TO_DO: Place ALL non-terminal function declarations */
gos_void comment();
gos_void importDeclaration();
gos_void optionalStatements();
gos_void optionalVariableDeclarations();
gos_void outputStatement();
gos_void outputVariableList();
gos_void packageDeclaration();
gos_void program();
gos_void statement();
gos_void statements();
gos_void statementsPrime();

gos_void variableListDeclarations();
gos_void variableListDeclaration();
gos_void variableListDeclarationsPrime();
#endif