// vim:sw=4:ai:aw
//
#ident	"@(#)Token.h	1.5	AKK - 20060526"
//

#ifndef	__TOKEN_H__
#define	__TOKEN_H__

#include <string>
#include <istream>
using std::string;	// import string
using std::istream;	// import istream

// Select a SH_LEVEL:
// #define SH_LEVEL	0	// basic
// #define SH_LEVEL	1	// versatile
// #define SH_LEVEL	2	// advanced
// #define SH_LEVEL	3	// sh script
#define SH_LEVEL	4	// ksh/bash


// een token uit de invoer
class	Token
{
public:
    // The different kinds of tokens.
    enum	token_t
    {
			// == basic ==
	END,		// end-of-input
			// Note: The code EOF is a macro defined elsewhere
	EOL,		// end-of-line
	SEQUENCE,	// ;		foo ; bar
	PIPE,		// |		run | in | tandem
	INPUT,		// <		input < from ...
	OUTPUT,		// >		output > to ....
	APPEND,		// >>		output >> after ...

#if	SH_LEVEL >= 1	// == versatile ==

	BACKGROUND,	// &		don't wait

#if	SH_LEVEL >= 2	// == advanced ==

	AND,		// &&		conditional execution
	OR,		// ||		conditional execution
	SUBS,		// (		( subshell )
	ENDS,		// )
	VAR,		// $word or one of $* $@ $# $0 ... $9 $? $! $$
			// Note: the text does NOT contain the $ character.
	EXPR,		// A word containing *, ? (simple wildcard)
			// Note: The [...] construct is NOT handled.

#if	SH_LEVEL >= 3	// == sh scripts ==
	HERE,		// <<		inline document
	BQUOTE,		// ` ... `	run subshell & replace
	BREAK,		// ;;		case ... in ... ;; ... ;; ... esac
	GROUP,		// {		{ ... ; ... }
	GRPEND,		// }

#if	SH_LEVEL >= 4	// == ksh/bash ==
	EVAL,		// $( ... )	run subshell & replace

#endif	// level 4
#endif	// level 3
#endif	// level 2
#endif	// level 1

	WORD		// anything else

	// NOTE Special words such as 'exit', 'cd' etc. are NOT handled
	// 	here, because their meaning is position dependent.
    };

private:
    token_t	type;
    string	text;

public:
    Token( token_t t ) : type(t) {}
    Token( token_t t, const string & s ) : type(t), text(s) {}

    token_t   getType() const	{ return type; }
    string  & getText()		{ return text; }
};

// de eigenlijke scanner
Token	* nextToken( istream & is );


#endif	/*TOKEN_H*/
