%top{

#include "../../support/type/CompilationStatus.h"
#include "../../support/type/FlexContext.h"
#include "../../support/type/TokenLabel.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"

}

%{

/**
 * @see https://westes.github.io/flex/manual/Definitions-Section.html#Definitions-Section
 */

extern CompilationStatus EnterMultilineCommentLexemeAction(FlexContext context);
extern CompilationStatus EOFLexemeAction();
extern CompilationStatus IgnoredLexemeAction();
extern CompilationStatus ValueLexemeAction();
extern CompilationStatus LeaveMultilineCommentLexemeAction();
extern CompilationStatus ParenthesisLexemeAction(TokenLabel label);
extern CompilationStatus BraceLexemeAction(TokenLabel label);
extern CompilationStatus CommaLexemeAction();
extern CompilationStatus KeywordLexemeAction(TokenLabel label);
extern CompilationStatus IdentifierLexemeAction(TokenLabel label);
extern CompilationStatus UnitLexemeAction(TokenLabel label);
extern CompilationStatus ResistorTypeLexemeAction(TokenLabel label);
extern CompilationStatus SwitchStateLexemeAction(TokenLabel label);
extern CompilationStatus PolarityLexemeAction(TokenLabel label);
extern CompilationStatus UnknownLexemeAction();

%}

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */

%x MULTILINE_COMMENT

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

/* Reusable patterns */
DIGIT                       [0-9]
INTEGER                     {DIGIT}+
FRAC                        \.{DIGIT}+
EXP                         ([eE][+-]?{DIGIT}+)
NUMBER                      {DIGIT}+({FRAC})?({EXP})?

IMAG_UNIT                   [ij]
SIGN                        [+-]

IMAG_PART1                  ({NUMBER}?{IMAG_UNIT})
COMPLEX_PART1               ({NUMBER}([[:space:]]*{SIGN}[[:space:]]*{NUMBER}?{IMAG_UNIT})?)
COMPLEX_PART2               ({IMAG_PART1}([[:space:]]*{SIGN}[[:space:]]*{NUMBER})?)

VALUE_PATTERN               ({COMPLEX_PART1}|{COMPLEX_PART2})
UNIT_PATTERN                (?:GIGA|giga|G|MEGA|mega|M|KILO|kilo|K|BASE|base|MILLI|milli|m|MICRO|micro|[uµμ]|NANO|nano|n)
RESISTOR_TYPE_PATTERN       (REGULAR|regular|Regular|PHOTORESISTOR|photoresistor|Photoresistor|THERMISTOR|thermistor|Thermistor|POTENTIOMETER|potentiometer|Potentiometer)
SWITCH_STATE_PATTERN        (OPEN|open|Open|CLOSED|closed|Closed)

IDENT                       [A-Za-z_][A-Za-z0-9_]*
WHITESPACE                  [[:space:]]+

%%

"/*"                                    { return EnterMultilineCommentLexemeAction(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>"*/"                 { return LeaveMultilineCommentLexemeAction(); }
<MULTILINE_COMMENT>[^*]+                { return IgnoredLexemeAction(); }
<MULTILINE_COMMENT>.                    { return IgnoredLexemeAction(); }

"("                                     { return ParenthesisLexemeAction(OPEN_PARENTHESIS); }
")"                                     { return ParenthesisLexemeAction(CLOSE_PARENTHESIS); }

"{"                                     { return BraceLexemeAction(OPEN_BRACE); }
"}"                                     { return BraceLexemeAction(CLOSE_BRACE); }

","                                     { return CommaLexemeAction(); }

{VALUE_PATTERN}                         { return ValueLexemeAction(); }

"Circuit"                                { return KeywordLexemeAction(CIRCUIT); }
"Parallel"                               { return KeywordLexemeAction(PARALLEL); }
"Branch"                                 { return KeywordLexemeAction(BRANCH); }
"ACSource"                               { return KeywordLexemeAction(AC_SOURCE); }
"DCSource"                               { return KeywordLexemeAction(DC_SOURCE); }
"Resistor"                               { return KeywordLexemeAction(RESISTOR); }
"Capacitor"                              { return KeywordLexemeAction(CAPACITOR); }
"Voltmeter"                              { return KeywordLexemeAction(VOLTMETER); }
"Amperemeter"                            { return KeywordLexemeAction(AMPEREMETER); }
"Inductance"                             { return KeywordLexemeAction(INDUCTANCE); }
"Switch"                                 { return KeywordLexemeAction(SWITCH); }

{UNIT_PATTERN}                           { return UnitLexemeAction(UNIT_TOKEN); }
{RESISTOR_TYPE_PATTERN}                  { return ResistorTypeLexemeAction(RESISTOR_TYPE_TOKEN); }
{SWITCH_STATE_PATTERN}                   { return SwitchStateLexemeAction(SWITCH_STATE_TOKEN); }
"+|-"                                    { return PolarityLexemeAction(POSITIVE_FIRST_TOKEN); }
"-|+"                                    { return PolarityLexemeAction(NEGATIVE_FIRST_TOKEN); }

{IDENT}                                  { return IdentifierLexemeAction(ID); }

{WHITESPACE}                             { return IgnoredLexemeAction(); }
.                                        { return UnknownLexemeAction(); }

<<EOF>>                                  { return EOFLexemeAction(); }

%%

/**
 * @see https://westes.github.io/flex/manual/User-Code-Section.html#User-Code-Section
 */

#include "FlexActions.h"
#include "FlexExport.h"