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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

gos_void startParser() {
	/* TO_DO: Initialize Parser data */
	int32 i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
gos_void matchToken(int32 tokenCode, int32 tokenAttribute) {
	
	int32 matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
	case REL_T:
	case ART_T:
	case LOG_T:
		if (lookahead.attribute.codeType != tokenAttribute) {
			printf("codeType: %d\n", lookahead.attribute.codeType);
			printf("tokenAttribute: %d\n", tokenAttribute);
			printf("matchFlag = 0\n");
			matchFlag = 0;
		}
			
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printf("ERR_T\n");
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
gos_void syncErrorHandler(int32 syncTokenCode) {
	printf("syncErrorHandler\n");
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
gos_void printError() {
	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {CMT_T, MNID_T (main&), SEOF_T}.
 ***********************************************************
 */
gos_void program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case KW_T:
		/*packageDeclaration();
		importDeclaration();*/
		matchToken(KW_T, KW_func);
		/*optionalVariableDeclarations();*/
	case MID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
				matchToken(MID_T, NO_ATTR);
				matchToken(RPR_T, NO_ATTR);
				matchToken(LBR_T, NO_ATTR);
				optionalStatements();
				matchToken(RBR_T, NO_ATTR);
				break;
			}
		else {
			
;			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
gos_void comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(CMT_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */


//gos_void additive() {
//	psData.parsHistogram[BNF_optionalStatements]++;
//
//	switch (lookahead.code) {
//	case ART_T:
//		matchToken(ART_T, NO_ATTR);
//
//		break;
//	case ASS_T:
//		f();
//		break;
//	default:
//
//		; // Empty
//	}
//}

gos_void arithmetic() {

	

	switch (lookahead.code) {
	case INL_T:
		//printf("1");
		matchToken(INL_T, NO_ATTR);
		arithmetic();
		break;
	case ART_T:
		if (lookahead.attribute.codeType == OP_ADD) {
			//printf("+");
			matchToken(ART_T, OP_ADD);
			psData.parsHistogram[BNF_additive]++;
			printf("%s: Additive expression parsed\n", STR_LANGNAME);
		}
		else if (lookahead.attribute.codeType == OP_SUB) {
			//printf("-");
			matchToken(ART_T, OP_SUB);
			psData.parsHistogram[BNF_substract]++;
			printf("%s: Substract expression parsed\n", STR_LANGNAME);
		}
		
		if(lookahead.code==INL_T)
			arithmetic();
		else
			matchToken(INL_T, NO_ATTR);
		break;
	default:
		psData.parsHistogram[BNF_arithmetic]++;
		printf("%s: Arithmetic expression parsed\n", STR_LANGNAME);
		
		; // Empty
	}
}

gos_void assignment() {

	switch (lookahead.code) {
	case ASS_T:
		//printf("=");
		matchToken(ASS_T, NO_ATTR);
		if(lookahead.code==INL_T)
			arithmetic();
		else
			matchToken(INL_T, NO_ATTR);
		break;
	default:
		
		
		; // Empty
	}
	
}

gos_void declaration() {
	
	switch (lookahead.code) {
	case VAR_T:
		//printf("var a");
		matchToken(VAR_T, NO_ATTR);
		assignment();
	default:
		
		; // Empty
	}
	
}

gos_void optionalStatements() {
	
	switch (lookahead.code) {
	
	case KW_T:
		if (lookahead.attribute.codeType == KW_var) {
			matchToken(KW_T, KW_var);
			if (lookahead.code == VAR_T){
				declaration();
				optionalStatements();
			}
			else
				matchToken(VAR_T, NO_ATTR);
		}
		printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
		psData.parsHistogram[BNF_optionalStatements]++;
		break;
	
	case CMT_T:
		comment();
	/*case KW_T:
		optionalVariableDeclarations();
	case VAR_T:
		optionalVariableDeclarations();*/
	case MID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 8) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 7) == 0)) {
			statements();
			optionalStatements();
			printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
			psData.parsHistogram[BNF_optionalStatements]++;
			break;
		}
	default:
		
		; // Empty
	}
	
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
gos_void statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
gos_void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case MID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 8) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
gos_void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		default:
			printError();
		}
		break;
	case MID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 8) == 0) {
			outputStatement();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
gos_void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MID_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
gos_void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * Package declaration
 * BNF: <package_declaration> -> KW_T (KW_package) KW_T (KW_main)
 * FIRST(<package_declaration>) = { KW_T (KW_package) }
 ***********************************************************
 */
gos_void packageDeclaration() {
	psData.parsHistogram[BNF_packagedeclaration]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	default:
		matchToken(KW_T, KW_package);
		matchToken(KW_T, KW_main);
		printf("%s%s\n", STR_LANGNAME, ": package declaration parsed");
	}
}

/*
 ************************************************************
 * Import declaration
 * BNF: <opt_variable list> -> KW_T (KW_import) "fmt"
 * FIRST(<opt_variable_list>) = { KW_T (KW_import }
 ***********************************************************
 */
gos_void importDeclaration() {
	psData.parsHistogram[BNF_importdeclaration]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case KW_T:
		matchToken(KW_T, KW_import);
		printf("%s%s\n", STR_LANGNAME, ": import declaration parsed");
	}
}

gos_void assignmentStatement() {

}

gos_void assignmentExpression() {

}

gos_void additiveArithmeticExpression() {

}

gos_void optionalVariableDeclarations() {
	psData.parsHistogram[BNF_optionalVariableDeclarations]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case KW_T:
		printf("Hello testing KW_T\n\n");
		matchToken(KW_T, KW_var);
		variableListDeclarations();
	case VAR_T:
		printf("Hello testing VAR_T\n\n");
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": optional variable declaration parsed");
}

gos_void variableListDeclarations() {
	psData.parsHistogram[BNF_variableListDeclarations]++;
	variableListDeclaration();
	variableListDeclarationsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Variable Declarations parsed");
}

gos_void variableListDeclaration() {
	psData.parsHistogram[BNF_variableListDeclaration]++;
	switch (lookahead.code){
	case VAR_T:
		;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Variable Declaration parsed");
}

gos_void variableListDeclarationsPrime() {
	psData.parsHistogram[BNF_variableListDeclarationPrime]++;
	switch (lookahead.code) {

	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Variable Declarations Prime parsed");
}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
gos_void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

/*
* ----------------------------------------------------------
* Below are the codes that needs to be further implemeneted.
* ----------------------------------------------------------
*/
//gos_void optVarListDeclarations() {
//	psData.parsHistogram[BNF_optVarListDeclarations]++;
//	switch (lookahead.code) {
//	default:
//		; // Empty
//	}
//	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
//}
//
//gos_void varListDeclarations() {
//	psData.parsHistogram[BNF_varListDeclarations];
//	varListDeclaration();
//	varListDeclarationPrime();
//	printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations parsed");
//}
//
//gos_void varListDeclaration() {
//	printf("");
//}
//
//gos_void varListDeclarationPrime() {
//	printf("");
//}
//
//gos_void intVarListDeclaration() {
//	psData.parsHistogram[BNF_intVarListDeclaration]++;
//	switch (lookahead.code) {
//	case CMT_T:
//		comment();
//	default:
//		matchToken(KW_T, KW_var);
//		//varList();
//		matchToken(KW_T, KW_int32);
//		printf("%s%s\n", STR_LANGNAME, ": Integer Var List Declaration parsed");
//	}
//}
//
//gos_void fltVarListDeclaration() {
//	psData.parsHistogram[BNF_fltVarListDeclaration]++;
//	switch (lookahead.code) {
//	case CMT_T:
//		comment();
//	default:
//		matchToken(KW_T, KW_var);
//		varList();
//		matchToken(KW_T, KW_float32);
//		printf("%s%s\n", STR_LANGNAME, ": Float Var List Declaration parsed");
//	}
//}
//
//gos_void strVarListDeclaration() {
//	psData.parsHistogram[BNF_fltVarListDeclaration]++;
//	switch (lookahead.code) {
//	case CMT_T:
//		comment();
//	default:
//		matchToken(KW_T, KW_var);
//		varList();
//		matchToken(KW_T, KW_string);
//		printf("%s%s\n", STR_LANGNAME, ": String Var List Declaration parsed");
//	}
//}
//
//gos_void varList() {
//	psData.parsHistogram[BNF_varList]++;
//	printf("%s%s\n", STR_LANGNAME, ": Variable List parsed");
//}
//
//gos_void arithmeticExpression() {
//	psData.parsHistogram[BNF_arithmeticExpression]++;
//	printf("%s%s\n", STR_LANGNAME, ": Arithmetic Expression parsed");
//}
//
//gos_void assignmentExpression() {
//	psData.parsHistogram[BNF_assignmentExpression]++;
//	printf("%s%s\n", STR_LANGNAME, ": Assignment Expression parsed");
//}
//
//gos_void assignmentStatement() {
//	psData.parsHistogram[BNF_assignmentStatement]++;
//	printf("%s%s\n", STR_LANGNAME, ": Assignment Expression parsed");
//}