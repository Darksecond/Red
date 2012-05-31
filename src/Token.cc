// vim:sw=4:ai:aw
//
static char sccsid[] = "@(#)Token.cc	1.5	AKK - 20060526";
//

#include "Token.h"

#include <cctype>	// C: character typing
#include <cstring>	// C: string functions


inline	// Is C a whitespace character ?
bool	isBlank(char c) { return ((c==' ')|(c=='\t')); }

// The list of all characters that terminate a "word".
#if	SH_LEVEL >= 3	// plus: `{}
static	char specials[] = "\n\r(){}&;|<>$` \t";
#elif	SH_LEVEL >= 2	// plus: $()
static	char specials[] = "\n\r()&;|<>$ \t";
#elif	SH_LEVEL >= 2	// plus: &
static	char specials[] = "\n\r&;|<> \t";
#else			// basic:
static	char specials[] = "\n\r;|<> \t";
#endif

inline	// Does C occur in the list of specials ?
bool	isSpecial( char c ) { return (strchr(specials,c) != 0); }


// Note: The "if (!is.get(c)) ..." construct used below
// 	 is needed to handle "unexpected EOF" situations.


Token	* nextToken( istream & is )
{
    string  s;
    char    c = -1;

    // Worth the trouble ?
    if (!is.good())
	return new Token( Token::END );

    // Get one character
    if (!is.get( c ))
	return new Token( Token::END );

    // Skip any white space ...
    while (isBlank(c)) {
	if (!is.get( c ))
	    return new Token( Token::END );
    }

    // What have we got now ?
    switch (c) {	// A special case ?

	case '\n': case '\r':
	    return new Token( Token::EOL );

	case ';':	// Can be either ; or ;;
#if	SH_LEVEL >= 3	/* sh scripting */
	    if (!is.get( c ))	// lookahead
		return new Token( Token::SEQUENCE );
	    if (c == ';')
		return new Token( Token::BREAK );
	    is.putback( c );
#endif			/* sh script */
	    return new Token( Token::SEQUENCE );

#if	SH_LEVEL >= 1	/* versatile */
	case '&':	// Can be either & or &&
#if	SH_LEVEL >= 2	/* advanced */
	    if (!is.get( c ))	// lookahead
		return new Token( Token::BACKGROUND );
	    if (c == '&')
		return new Token( Token::AND );
	    is.putback( c );
#endif	/* advanced */
	    return new Token( Token::BACKGROUND );
#endif	/* versatile */

	case '|':	// Can be either | or ||
#if	SH_LEVEL >= 2	/* advanced */
	    if (!is.get( c ))	// lookahead
		return new Token( Token::PIPE );
	    if (c == '|')
		return new Token( Token::OR );
	    is.putback( c );
#endif	/* advanced */
	    return new Token( Token::PIPE );

	case '>':	// Can be either > or >>
	    if (!is.get( c ))	// lookahead
		return new Token( Token::OUTPUT );
	    if (c == '>')
		return new Token( Token::APPEND );
	    is.putback( c );
	    return new Token( Token::OUTPUT );

	case '<':	// Can be either < or <<
#if	SH_LEVEL >= 3 	/* sh scripting */
	    if (!is.get( c ))	// lookahead
		return new Token( Token::INPUT );
	    if (c == '<')
		return new Token( Token::HERE );
	    is.putback( c );
#endif	/* sh scripting */
	    return new Token( Token::INPUT );

#if	SH_LEVEL >= 2	/* advanced */
	case '(':	//
	    return new Token( Token::SUBS );
	case ')':	//
	    return new Token( Token::ENDS );

	case '$':	// variables: $something
	    if (!is.get( c ))	// lookahead
		return new Token( Token::WORD, "" );	// just a $ ?
#if	SH_LEVEL >= 4 	/* ksh/bash magic */
	    // The $( pair is a special one
	    if (c == '(')
		return new Token( Token::EVAL );
#endif	/* ksh/bash magic */
	    // The following non-letter pairs are common
	    //     $* $@ $# $0 ... $9 $? $! $$
	    if (strchr("*@#0123456789?!$", c) != NULL) {
		s += c;
		return new Token( Token::VAR, s );
	    }
	    // Having handled all the special cases,
	    // we now expect a true word
	    // which MUST begin with a letter.
	    if (!isalpha(c)) {
		is.putback(c);			// Can not use this one
		return new Token( Token::WORD, "" );	// just a $ ?
	    }
	    // Oke, seems good ...
	    // Collect an alfanumeric string
	    do {
		s += c;
		if (!is.get(c))
		    goto done;	// Skip the putback
	    } while ( isalnum(c) || (c == '_'));
	    is.putback(c);
	done:
	    return new Token( Token::VAR, s );
#endif	/* advanced */

#if	SH_LEVEL >= 3	/* sh scripts */
	case '{':	//
	    return new Token( Token::GROUP );

	case '}':	//
	    return new Token( Token::GRPEND );

	case '`':	// back-quote
	    return new Token( Token::BQUOTE );
#endif	/* sh scripts */

    } // end switch

    // Assume it is just a word;
    // Read any text upto something special.
    Token::token_t  type = Token::WORD;

    do {
	s += c;
	if (!is.get( c ))
	    goto final;	// Skips the 'putback' action
#if	SH_LEVEL >= 2	/* advanced */
	// A (simple) wildcard character ?
	if (strchr("*?", c) != NULL)
	    type = Token::EXPR;
#endif	/* advanced */
    } while (!isSpecial(c));

    is.putback( c );

final:
    return new Token( type, s );
}
