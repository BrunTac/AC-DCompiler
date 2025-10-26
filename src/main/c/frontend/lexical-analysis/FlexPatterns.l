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
extern CompilationStatus ComplexValueLexemeAction();
extern CompilationStatus RealValueLexemeAction();
extern CompilationStatus LeaveMultilineCommentLexemeAction();
extern CompilationStatus ParenthesisLexemeAction(TokenLabel label);
extern CompilationStatus BraceLexemeAction(TokenLabel label);
extern CompilationStatus CommaLexemeAction();
extern CompilationStatus KeywordLexemeAction(TokenLabel label);
extern CompilationStatus IdentifierLexemeAction(TokenLabel label);
extern CompilationStatus UnitLexemeAction(Unit unit);
extern CompilationStatus ResistorTypeLexemeAction(ResistorType resistorType);
extern CompilationStatus SwitchStateLexemeAction(SwitchState switchState);
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

REAL_VALUE_PATTERN          {NUMBER}
COMPLEX_VALUE_PATTERN       ({COMPLEX_PART1}|{COMPLEX_PART2})

GIGA_PATTERN                (GIGA|giga|Giga|G)
MEGA_PATTERN                (MEGA|mega|Mega|M)
KILO_PATTERN                (KILO|kilo|Kilo|k)
BASE_PATTERN                (BASE|base|Base)
MILLI_PATTERN               (MILLI|milli|Milli|m)
MICRO_PATTERN               (MICRO|micro|Micro|u|µ|μ)
NANO_PATTERN                (NANO|nano|Nano|n)

REGULAR_PATTERN             (REGULAR|regular|Regular)
POTENTIOMETER_PATTERN       (POTENTIOMETER|potentiometer|Potentiometer)
THERMISTOR_PATTERN          (THERMISTOR|thermistor|Thermistor)
PHOTORESISTOR_PATTERN       (PHOTORESISTOR|photoresistor|Photoresistor)

OPEN_PATTERN                (OPEN|open|Open)
CLOSED_PATTERN              (CLOSED|closed|Closed)

IDENT                       [A-Za-z_][A-Za-z0-9_]*
WHITESPACE                  [[:space:]]+

%%

"/*"                                     { return EnterMultilineCommentLexemeAction(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>"*/"                  { return LeaveMultilineCommentLexemeAction(); }
<MULTILINE_COMMENT>[^*]+                 { return IgnoredLexemeAction(); }
<MULTILINE_COMMENT>.                     { return IgnoredLexemeAction(); }

"("                                      { return ParenthesisLexemeAction(OPEN_PARENTHESIS); }
")"                                      { return ParenthesisLexemeAction(CLOSE_PARENTHESIS); }

"{"                                      { return BraceLexemeAction(OPEN_BRACE); }
"}"                                      { return BraceLexemeAction(CLOSE_BRACE); }

","                                      { return CommaLexemeAction(); }

{REAL_VALUE_PATTERN}                     { return RealValueLexemeAction(); }
{COMPLEX_VALUE_PATTERN}                  { return ComplexValueLexemeAction(); }

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

{GIGA_PATTERN}                           { return UnitLexemeAction(GIGA); }
{MEGA_PATTERN}                           { return UnitLexemeAction(MEGA); }
{KILO_PATTERN}                           { return UnitLexemeAction(KILO); }
{BASE_PATTERN}                           { return UnitLexemeAction(BASE); }
{MILLI_PATTERN}                          { return UnitLexemeAction(MILLI); }
{MICRO_PATTERN}                          { return UnitLexemeAction(MICRO); }
{NANO_PATTERN}                           { return UnitLexemeAction(NANO); }

{REGULAR_PATTERN}                        { return ResistorTypeLexemeAction(REGULAR); }
{POTENTIOMETER_PATTERN}                  { return ResistorTypeLexemeAction(POTENTIOMETER); }
{THERMISTOR_PATTERN}                     { return ResistorTypeLexemeAction(THERMISTOR); }
{PHOTORESISTOR_PATTERN}                  { return ResistorTypeLexemeAction(PHOTORESISTOR); }

{OPEN_PATTERN}                           { return SwitchStateLexemeAction(OPEN); }
{CLOSED_PATTERN}                         { return SwitchStateLexemeAction(CLOSED); }

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