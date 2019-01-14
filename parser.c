/***************************************************************************************
File Name		: parser.c
Compiler		: MS Visual Studio 2015
Author			: Tanishq Bansal (040883753)
Course			: CST 8152 - Compilers, Lab Section: 014
Assignment		: 3
Date			: 6th December, 2018
Professor		: Sv. Ranev
Purpose			: Parsing token and validating it using Grammar
Function List	: 
****************************************************************************************/

#include "parser.h"

/**************************************************************************************
Author			:	Svillen Ranev
***************************************************************************************/
void parser(Buffer * in_buf)
{
	lookahead = malar_next_token();
	program(); match(SEOF_T, NO_ATTR);
	gen_incode("PLATY: Source file parsed\n");
}


/**************************************************************************************
Author			:	Tanishq Bansal (040883753)
***************************************************************************************/
void match(int pr_token_code, int pr_token_attribute)
{
	int isSuccesful = 1;
	/*
	* if lookahead code matches with pr_token_code then check which code it matches to
	*/
	if (lookahead.code == pr_token_code)
	{
		if (pr_token_attribute != NO_ATTR)
		{
			switch (lookahead.code)
			{

				case KW_T:
				{
					if (kw_table[lookahead.attribute.get_int] == kw_table[pr_token_attribute])
					{
						if (lookahead.code != SEOF_T)
						{

							lookahead = malar_next_token();
							if (lookahead.code == ERR_T)
							{

								syn_printe();
								lookahead = malar_next_token();
								synerrno++;

							}
						}

					}
				}
				break;
				case LOG_OP_T:
				{

					if (lookahead.attribute.log_op == pr_token_attribute)
					{

						if (lookahead.code != SEOF_T)
						{

							lookahead = malar_next_token();
							if (lookahead.code == ERR_T)
							{

								syn_printe();
								lookahead = malar_next_token();
								synerrno++;

							}
						}

					}

				}
				break;
				case ART_OP_T:
				{

					if (lookahead.attribute.arr_op == pr_token_attribute)
					{

						if (lookahead.code != SEOF_T)
						{

							lookahead = malar_next_token();
							if (lookahead.code == ERR_T)
							{

								syn_printe();
								lookahead = malar_next_token();
								synerrno++;

							}
						}

					}

				}
				break;
				case REL_OP_T:
				{

					if (lookahead.attribute.rel_op == pr_token_attribute)
					{

						if (lookahead.code != SEOF_T)
						{

							lookahead = malar_next_token();
							if (lookahead.code == ERR_T)
							{

								syn_printe();
								lookahead = malar_next_token();
								synerrno++;

							}
						}

					}

				}
				break;
			}
		}
		else
		{

			if (lookahead.code != SEOF_T)
			{

				lookahead = malar_next_token();
				if (lookahead.code == ERR_T)
				{

					syn_printe();
					lookahead = malar_next_token();
					synerrno++;

				}
			}

		}

	}
	else
	{

		syn_eh(pr_token_code);

	}
	return;

}


 /**************************************************************************************
 Author				:	Tanishq Bansal
 ***************************************************************************************/
void syn_eh(int sync_token_code)
{

	syn_printe();
	synerrno++;

	while (lookahead.code != sync_token_code)
	{

		lookahead = malar_next_token();
		if (lookahead.code == SEOF_T && sync_token_code != SEOF_T)
		{

			exit(synerrno);

		}

	}
	if (lookahead.code != SEOF_T)
	{

		lookahead = malar_next_token();
		return;

	}
	return;
}


/**************************************************************************************
Author			:	Svillen Ranev
***************************************************************************************/
/* error printing function for Assignment 3 (Parser), F18 */
void syn_printe()
{
	Token t = lookahead;

	printf("PLATY: Syntax error:  Line:%3d\n", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code)
	{
		case  ERR_T: /* ERR_T     0   Error token */
			printf("%s\n", t.attribute.err_lex);
			break;
		case  SEOF_T: /* 1 - Source end-of-file token */
			printf("SEOF_T\t\t%d\t\n", t.attribute.seof);
			break; 
		case  AVID_T: /* AVID_T    2   Arithmetic Variable identifier token */
		case  SVID_T:/* SVID_T    3  String Variable identifier token */
			printf("%s\n", t.attribute.vid_lex);
			break;
		case  FPL_T: /* FPL_T     4  Floating point literal token */
			printf("%5.1f\n", t.attribute.flt_value);
			break;
		case INL_T: /* INL_T      5   Integer literal token */
			printf("%d\n", t.attribute.get_int);
			break;
		case STR_T:/* STR_T     6   String literal token */
			printf("%s\n", b_location(str_LTBL, t.attribute.str_offset));
			break;

		case SCC_OP_T: /* 7   String concatenation operator token */
			printf("NA\n");
			break;

		case  ASS_OP_T:/* ASS_OP_T  8   Assignment operator token */
			printf("NA\n");
			break;
		case  ART_OP_T:/* ART_OP_T  9   Arithmetic operator token */
			printf("%d\n", t.attribute.get_int);
			break;
		case  REL_OP_T: /*REL_OP_T  10   Relational operator token */
			printf("%d\n", t.attribute.get_int);
			break;
		case  LOG_OP_T:/*LOG_OP_T 11  Logical operator token */
			printf("%d\n", t.attribute.get_int);
			break;

		case  LPR_T: /*LPR_T    12  Left parenthesis token */
			printf("NA\n");
			break;
		case  RPR_T: /*RPR_T    13  Right parenthesis token */
			printf("NA\n");
			break;
		case LBR_T: /*    14   Left brace token */
			printf("NA\n");
			break;
		case RBR_T: /*    15  Right brace token */
			printf("NA\n");
			break;

		case KW_T: /*     16   Keyword token */
			printf("%s\n", kw_table[t.attribute.get_int]);
			break;

		case COM_T: /* 17   Comma token */
			printf("NA\n");
			break;
		case EOS_T: /*    18  End of statement *(semi - colon) */
			printf("NA\n");
			break;
		default:
			printf("PLATY: Scanner error: invalid token code: %d\n", t.code);
	}/*end switch*/
}/* end syn_printe()*/

 /**************************************************************************************
 Author				:	Tanishq Bansal
 ***************************************************************************************/
void gen_incode(char * temp)
{

	printf("%s", temp);

}

/**************************************************************************************
Author				:	Tanishq Bansal
***************************************************************************************/
void program(void)
{
	match(KW_T, PLATYPUS);
	match(LBR_T, NO_ATTR);
	opt_statements();
	match(RBR_T, NO_ATTR);
	gen_incode("PLATY: Program parsed\n");

}


/**************************************************************************************
<program> -> PLATYPUS { <opt_statements> }),
FIRST(<program>= {KW_T (PLATYPUS)})
****************************************************************************************/
void opt_statements()
{
	/* FIRST set: {AVID_T,SVID_T,KW_T(but not … see above),e} */
	switch (lookahead.code)
	{
		case AVID_T:
		case SVID_T: statements(); break;
		case KW_T:
			/* check for PLATYPUS, ELSE, THEN, REPEAT, TRUE, FALSE here
			and in statements_p()*/
			if (lookahead.attribute.get_int != PLATYPUS
				&& lookahead.attribute.get_int != ELSE
				&& lookahead.attribute.get_int != THEN
				&& lookahead.attribute.get_int != REPEAT
				&& lookahead.attribute.get_int != TRUE
				&& lookahead.attribute.get_int != FALSE)
			{
				statements();
				break;
			}
		default: /*empty string – optional statements*/;
			gen_incode("PLATY: Opt_statements parsed\n");
	}
}

/**************************************************************************************
<statements> -> <statement><statements’>
FIRST(<statements>) = { AVID_T, SVID_T, KW_T(IF), KE_T(WHILE), KW_T(READ), KW_T(WRITE)}
****************************************************************************************/
void statements(void)
{

	statement();
	statements_prime();

}

/**************************************************************************************
<statement> - > <assignment statement> | <selection statement> | <iteration statement> | <output statement>

FIRST(<statement>) = { FIRST(<assignment statement>), FIRST(<selection statement>),
FIRST(<iteration statement>), FIRST(<input statement>),
FIRST(<output statement>)} = { AVID_T,SVID_T,KW_T(IF), KW_T(WHILE) , KW_T(READ) , KW_T(WRITE)}
****************************************************************************************/
void statement(void)
{

	switch (lookahead.code)
	{

		case AVID_T:
		case SVID_T:
			assignment_statements();
			break;
		case KW_T:
			if (lookahead.attribute.get_int == IF)
			{

				selection_statement();
			}
			else if (lookahead.attribute.get_int == WHILE)
			{

				iteration_statement();

			}
			else if (lookahead.attribute.get_int == READ)
			{

				input_statement();

			}
			else if (lookahead.attribute.get_int == WRITE)
			{

				output_statement();
			}

			break;


		default: syn_printe();
	}

}

/**************************************************************************************
<statements’> -> <statement><statements’> | E
FIRST(<statement’>) = {AVID_T,SVID_T,KW_T(IF) , KW_T(WHILE) , KW_T(READ) , KW_T(WRITE), E}
****************************************************************************************/
void statements_prime(void)
{

	switch (lookahead.code)
	{

		case AVID_T:
		case SVID_T:
			statements();
			break;
		case KW_T:
			if (lookahead.attribute.get_int != PLATYPUS
				&& lookahead.attribute.get_int != ELSE
				&& lookahead.attribute.get_int != THEN
				&& lookahead.attribute.get_int != REPEAT
				&& lookahead.attribute.get_int != TRUE
				&& lookahead.attribute.get_int != FALSE)
			{
				statements();
				break;
			}
		default: gen_incode("");

	}

}

/**************************************************************************************
<assignment statement> -> <assignment expression>;
FIRST(<assignment>)= { AVID_T , SVID_T , EOS_T}
****************************************************************************************/
void assignment_statements(void)
{

	assignment_expression();
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: Assignment statement parsed\n");

}

/**************************************************************************************
<assignment expression > -> AVID_T = <arithmetic expression> | SVID_T = <string expression>
FIRST(<assignment expression>) = {AVID_T , SVID_T}
****************************************************************************************/
void assignment_expression(void)
{

	switch (lookahead.code)
	{

		case AVID_T: match(AVID_T, NO_ATTR);
			match(ASS_OP_T, NO_ATTR);
			arithmetic_expression();
			gen_incode("PLATY: Assignment expression (arithmetic) parsed\n");
			break;
		case SVID_T: match(SVID_T, NO_ATTR);
			match(ASS_OP_T, NO_ATTR);
			string_expression();
			gen_incode("PLATY: Assignment expression (string) parsed\n");
			break;

		default:syn_printe();

	}

}

/**************************************************************************************
<selection statement> -> IF TRUE( <conditional expression> ) THEN { <opt_statements> }
ELSE{ <opt_statement> };
FIRST(<selection statement>) = { KW_T(IF)}
****************************************************************************************/
void selection_statement(void)
{

	match(KW_T, IF);
	match(KW_T, TRUE);
	match(LPR_T, NO_ATTR);
	conditional_expression();
	match(RPR_T, NO_ATTR);
	match(KW_T, THEN);
	match(LBR_T, NO_ATTR);
	opt_statements();
	match(RBR_T, NO_ATTR);
	match(KW_T, ELSE);
	match(LBR_T, NO_ATTR);
	opt_statements();
	match(RBR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: Selection statement parsed\n");

}

/**************************************************************************************
<iteration statement> -> WHILE <pre-condition> ( <conditional expression> )
REPEAT { <statements> };
FIRST( <iteration statement> ) = { KWT_T(WHILE) }
****************************************************************************************/
void iteration_statement(void)
{

	match(KW_T, WHILE);
	precondition();
	match(LPR_T, NO_ATTR);
	conditional_expression();
	match(RPR_T, NO_ATTR);
	match(KW_T, REPEAT);
	match(LBR_T, NO_ATTR);
	statements();
	match(RBR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: Iteration statement parsed\n");

}
/**************************************************************************************
<pre-condition> -> TRUE | FALSE
FIRST(<pre-condition>) = { TRUE | FALSE }
****************************************************************************************/
void precondition(void)
{

	switch (lookahead.code)
	{
		case KW_T:

			switch (lookahead.attribute.get_int)
			{

				case TRUE: match(KW_T, TRUE);
					break;
				case FALSE: match(KW_T, FALSE);
					break;

				default: syn_printe();

			}
			break;
	}

}

/**************************************************************************************
<output statement> -> WRITE ( <output list> );
FIRST(<output statement>) = { KW_T( WRITE ) }
****************************************************************************************/
void output_statement(void)
{

	match(KW_T, WRITE);
	match(LPR_T, NO_ATTR);
	output_list();
	match(RPR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: Output statement parsed\n");

}

/**************************************************************************************
<input statement> -> READ ( <variable list> );
FIRST( <input statement> ) = { KW_T(READ) }
****************************************************************************************/
void input_statement(void)
{

	match(KW_T, READ);
	match(LPR_T, NO_ATTR);
	variable_list();
	match(RPR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: Input statement parsed\n");

}

/**************************************************************************************
<conditional expression> -> <Logical OR expression>
FIRST( <conditional expression> ) =  { AVID_T, FPL_T, INL_T, SVID_T, STR_T}
****************************************************************************************/
void conditional_expression(void)
{

	logical_or_expression();
	gen_incode("PLATY: Conditional expression parsed\n");

}

/**************************************************************************************
<logical OR expression> -> <logical AND expression> <logical OR expression’>
FIRST(<logical OR expression>) = { AVID_T, FPL_T, INL_T, SVID_T, STR_T }
****************************************************************************************/
void logical_or_expression(void)
{

	logical_and_expression();
	logical_or_expression_prime();

}

/**************************************************************************************
<logical OR expression’> -> .OR. <logical OR expression> <logical OR expression’> | E
FIRST( <logical OR expression’> ) = { LOG_OP_T(OR), E }
****************************************************************************************/
void logical_or_expression_prime(void)
{

	switch (lookahead.code)
	{

		case LOG_OP_T:
			switch (lookahead.attribute.log_op)
			{
				case OR:
					match(LOG_OP_T, OR);
					logical_and_expression();
					logical_or_expression_prime();
					gen_incode("PLATY: Logical OR expression parsed\n");
					break;
				default: gen_incode("");

			}
			break;

	}


}

/**************************************************************************************
<logical AND expression> -> <relational expression> <logical AND expression’>
FIRST( <logical AND expression> ) = { AVID_T, FPL_T, INL_T, SVID_T, STR_T }
****************************************************************************************/
void logical_and_expression(void)
{

	relational_expression();
	logical_and_expression_prime();

}

/**************************************************************************************
<relational expression> -> <primary a_relational expression> <relational expression_a>
| <primary s_relational expression> <relational expression_s>
FIRST(<relational expression>) = { AVID_T, FPL_T, INL_T, SVID_T, STR_T }
****************************************************************************************/
void relational_expression(void)
{

	switch (lookahead.code)
	{

		case AVID_T:
		case FPL_T:
		case INL_T:
			primary_a_relational_expression();
			a_relational_expression();
			primary_a_relational_expression();
			break;
		case SVID_T:
		case STR_T:
			primary_s_relational_expression();
			s_relational_expression();
			primary_s_relational_expression();
			break;

		default: syn_printe();
	}

	gen_incode("PLATY: Relational expression parsed\n");

}
/**************************************************************************************
<primary s_relational expression> -> <primary string expression>
FIRST( <primary s_relational expression> ) = { SVID_T, STR_T }
****************************************************************************************/
void primary_s_relational_expression(void)
{

	primary_string_expression();
	gen_incode("PLATY: Primary s_relational expression parsed\n");

}

/**************************************************************************************
<relations expression_s> -> = = < primary s_relational expression > | <> < primary s_relational expression >
| < <primary s_relational expression> | > <primary s_relational expression>
FIRST( <s_relational expression> ) = { REL_OP(EQ), REL_OP(NE), REL_OP(GT), REL_OP(LT) }
****************************************************************************************/

void s_relational_expression(void)
{

	switch (lookahead.code)
	{

		case REL_OP_T:

			switch (lookahead.attribute.rel_op)
			{

				case EQ: match(REL_OP_T, EQ);
					break;
				case NE: match(REL_OP_T, NE);
					break;
				case GT: match(REL_OP_T, GT);
					break;
				case LT: match(REL_OP_T, LT);
					break;
				default:/*printf("IN DEFAULT");*/ syn_printe();

			}
			break;

	}

}

/**************************************************************************************
<primary string expression> -> SVID_T | STR_T
FIRST(<primary string expression>) = { SVID_T, STR_T}
****************************************************************************************/
void primary_string_expression(void)
{

	switch (lookahead.code)
	{

		case SVID_T: match(SVID_T, NO_ATTR);
			break;
		case STR_T: match(STR_T, NO_ATTR);
			break;
		default: syn_printe();
	}
	gen_incode("PLATY: Primary string expression parsed\n");

}

/**************************************************************************************
<primary a_relational expression> -> AVID_T | FPL_T | INL_T
FIRST(<primary a_relaitonal expression>) = { AVID_T, FPL_T, INL_T}
****************************************************************************************/

void primary_a_relational_expression(void)
{

	switch (lookahead.code)
	{

		case AVID_T: match(AVID_T, NO_ATTR);
			break;
		case FPL_T:match(FPL_T, NO_ATTR);
			break;
		case INL_T: match(INL_T, NO_ATTR);
			break;
		default: syn_printe();

	}
	gen_incode("PLATY: Primary a_relational expression parsed\n");

}

/**************************************************************************************
<relational expression_a> -> == < primary a_relational expression >
| <> < primary a_relational expression > | < <primary a_relational expression>
| > <primary a_relational expression>
FIRST(<a_ relational expression>) = { REL_OP(EQ), REL_OP(NE), REL_OP(GT	), REL_OP(LT)}
****************************************************************************************/
void a_relational_expression(void)
{

	switch (lookahead.code)
	{

		case REL_OP_T:
			switch (lookahead.attribute.rel_op)
			{

				case EQ: match(REL_OP_T, EQ);
					break;
				case NE: match(REL_OP_T, NE);
					break;
				case GT: match(REL_OP_T, GT);
					break;
				case LT: match(REL_OP_T, LT);
					break;
				default: syn_printe();

			}
			break;

	}

}
/**************************************************************************************
<logical AND expression’> -> .AND. <relational expression> <logical AND expression’> | E
FIRST(<logical And expression’>) = { LOG_OP_T(AND), E}
****************************************************************************************/
void logical_and_expression_prime(void)
{

	switch (lookahead.code)
	{

		case LOG_OP_T:
			switch (lookahead.attribute.log_op)
			{

				case AND:
					match(LOG_OP_T, AND);
					relational_expression();
					logical_and_expression_prime();
					gen_incode("PLATY: Logical AND expression parsed\n");
					break;
				default:gen_incode("");

			}
			break;

	}
}

/**************************************************************************************
<string expression> -> <primary string expression> <string expression’>
FIRST(<string expression>) = {SVID_T, STR_T}
****************************************************************************************/
void string_expression(void)
{

	primary_string_expression();
	string_expression_prime();

}

/**************************************************************************************
<string expression’> -> # <primary string expression> <string expression’> | E
FIRST(<string expression’>) = { SCC_OP_T, E }
****************************************************************************************/
void string_expression_prime(void)
{

	switch (lookahead.code)
	{

		case SCC_OP_T: match(SCC_OP_T, NO_ATTR);
			primary_string_expression();
			string_expression_prime();
			break;
		default: gen_incode("PLATY: String expression parsed\n");

	}

}
/**************************************************************************************
<arithmetic expression> -> <unary arithmetic expression> | <additive arithmetic expression>
First(<arithmetic expression>) = { ART_OP_T, AVID_T, FPL_T, INL_T, LPR_T}
****************************************************************************************/
void arithmetic_expression(void)
{

	switch (lookahead.code)
	{
		case ART_OP_T:
			unary_arithmetic_expression();
			gen_incode("PLATY: Unary arithmetic expression parsed\n");
			break;
		case AVID_T:
		case FPL_T:
		case INL_T:
		case LPR_T:
			additive_arithmetic_expression();
			break;
		default:
			syn_printe();
	}
	gen_incode("PLATY: Arithmetic expression parsed\n");


}

/**************************************************************************************
<additive arithmetic expression> -> <multiplicative arithmetic expression> < additive arithmetic expression’>
FIRST(<additive arithmetic expression>) = {AVID_T, FPL_T, INL_T, LPR_T}
****************************************************************************************/

void additive_arithmetic_expression(void)
{
	multiplicative_arithmetic_expression();
	additive_arithmetic_expression_prime();

}

/**************************************************************************************
<multiplicative arithmetic expression> -> <primary arithmetic expression>
< multiplicative arithmetic expression’>
FIRST(<multiplicative arithmetic expression>) ={ AVID_T, FPL_T, INL_T, LPR_T}
****************************************************************************************/

void multiplicative_arithmetic_expression(void)
{
	primary_arithmetic_expression();
	multiplicative_arithmetic_expression_prime();

}

/**************************************************************************************
< multiplicative arithmetic expression’> -> * <primary arithmetic expression>
< multiplicative arithmetic expression’> | / <primary arithmetic expression>
< multiplicative arithmetic expression’> | E
FIRST(<multiplicative arithmetic expression’>) = { ART_OP_T(MULT) , ART_OP_T(DIV) , E}
****************************************************************************************/
void multiplicative_arithmetic_expression_prime()
{
	switch (lookahead.code)
	{
		case ART_OP_T:
			switch (lookahead.attribute.arr_op)
			{
				case MULT:
					match(ART_OP_T, MULT);
					primary_arithmetic_expression();
					multiplicative_arithmetic_expression_prime();
					gen_incode("PLATY: Multiplicative arithmetic expression parsed\n");
					break;
				case DIV:
					match(ART_OP_T, DIV);
					primary_arithmetic_expression();
					multiplicative_arithmetic_expression_prime();
					gen_incode("PLATY: Multiplicative arithmetic expression parsed\n");
					break;

			}
			break;
		default: gen_incode("");
	}
}

/**************************************************************************************
<additive arithmetic expression’> -> + <multiplicative arithmetic expression>
<additive arithmetic expression’> | - <multiplicative arithmetic expression>
<additive arithmetic expression’> | E
FIRST(<additive arithmetic expression’>) = {ART_OP_T(PLUS), ART_OP_T(MINUS), E}
****************************************************************************************/
void additive_arithmetic_expression_prime(void)
{
	switch (lookahead.code)
	{
		case ART_OP_T:
			switch (lookahead.attribute.arr_op)
			{
				case MINUS:match(ART_OP_T, MINUS);
					additive_arithmetic_expression();
					gen_incode("PLATY: Additive arithmetic expression parsed\n");
					break;
				case PLUS:match(ART_OP_T, PLUS);
					additive_arithmetic_expression();
					gen_incode("PLATY: Additive arithmetic expression parsed\n");
					break;
			}
			break;
		default: gen_incode("");
	}

}

/**************************************************************************************
<unary arithmetic expression> -> - <primary arithmetic expression> | + <primary arithmetic expression>
FIRST(<unary arithmetic expression>) = {ART_OP_T(MINUS), ART_OP_T(PLUS)}
****************************************************************************************/
void unary_arithmetic_expression(void)
{

	switch (lookahead.code)
	{

		case ART_OP_T:
			switch (lookahead.attribute.arr_op)
			{

				case PLUS: match(ART_OP_T, PLUS);
					primary_arithmetic_expression();
					break;
				case MINUS: match(ART_OP_T, MINUS);
					primary_arithmetic_expression();
					break;
				default:gen_incode("");

			}
			break;
		default:gen_incode("");

	}

}

/**************************************************************************************
<primary arithmetic expression> -> AVID | FPL | INT | ( <arithmetic expression> )
FIRST(< primary arithmetic expression >) = { AVID_T, FPL_T, INL_T, LPR_T }
****************************************************************************************/
void primary_arithmetic_expression(void)
{

	switch (lookahead.code)
	{
		case LPR_T:
			match(LPR_T, NO_ATTR);
			arithmetic_expression();
			match(RPR_T, NO_ATTR);
			break;
		case AVID_T: match(AVID_T, NO_ATTR);
			break;
		case FPL_T: match(FPL_T, NO_ATTR);
			break;
		case INL_T: match(INL_T, NO_ATTR);
			break;
		default: syn_printe();

	}
	gen_incode("PLATY: Primary arithmetic expression parsed\n");

}

/**************************************************************************************
<variable list> -> <variable identifier> <variable list’>
FIRST( <variable list> ) = { FIRST(<variable identifier>) } = { AVID_T, SVID_T }
****************************************************************************************/
void variable_list(void)
{

	variable_identifier();
	variable_list_prime();

}

/**************************************************************************************
<variable list’> -> <variable list’>, <variable identifier> | E
FIRST(<variable list’>) = { COM_T, E }
****************************************************************************************/
void variable_list_prime(void)
{

	switch (lookahead.code)
	{

		case COM_T: match(COM_T, NO_ATTR);
			variable_list();
			break;
		default: gen_incode("PLATY: Variable list parsed\n");
	}

}

/**************************************************************************************
<variable identifier> -> <arithmetic variable identifier> | <string variable identifier>
FIRST(<variable identifier>) = {AVID_T, SVID_T}
****************************************************************************************/
void variable_identifier(void)
{

	switch (lookahead.code)
	{

		case AVID_T: match(AVID_T, NO_ATTR);
			break;
		case SVID_T: match(SVID_T, NO_ATTR);
			break;
		default: syn_printe();
	}
}
/**************************************************************************************
<output list> -> <opt_variable list> | STR_T
<opt_variable list> -> <variable list> | E
FIRST(<opt_variable list>) = {AVID_T, E}
FIRST(<output list>) = { FIRST(variable list) , STR_T , E } = { AVID_T, SVID_T, STR_T, E}
****************************************************************************************/
void output_list(void)
{

	switch (lookahead.code)
	{

		case AVID_T: variable_list(); break;
		case SVID_T: variable_list(); break;
		case STR_T: match(STR_T, NO_ATTR);
			gen_incode("PLATY: Output list (string literal) parsed\n");
			break;
		default: gen_incode("PLATY: Output list (empty) parsed\n");
	}
}


