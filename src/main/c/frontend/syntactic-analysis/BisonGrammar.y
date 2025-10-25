%{

#include "../../support/type/TokenLabel.h"
#include "AbstractSyntaxTree.h"
#include "BisonActions.h"

/**
 * The error reporting function for Bison parser.
 *
 * @todo Add location to the grammar and "pushToken" API function.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Error-Reporting-Function.html
 * @see https://www.gnu.org/software/bison/manual/html_node/Tracking-Locations.html
 */
void yyerror(const YYLTYPE * location, const char * message) {}

%}

// You touch this, and you die.
%define api.pure full
%define api.push-pull push
%define api.value.union.name SemanticValue
%define parse.error detailed
%locations

%union {
	/** Terminals. */

	TokenLabel token;
    Unit unit;

	/** Non-terminals. */

	Program * program;
    Circuit * circuit;
    CircuitList * circuitList;
    Element * element;
    ElementList * elementList, elementListOpt;
    Component * component;
    Parameter * parameter;
    ParameterList * componentParamsOpt, parameterList, parameterListOpt;
    Identifier * identifier;
    Branch * branch;
    BranchList * branchList;
    Parallel * parallel;
    Polarity * polarity;
    Current * current;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach for the AST root node ("program" non-terminal, in this
 * grammar), or it will drop the entire tree even if the parsing succeeds.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */

%destructor { destroyProgram($$); }        <program>
%destructor { destroyCircuit($$); }        <circuit>
%destructor { destroyCircuitList($$); }    <circuitList>
%destructor { destroyElement($$); }        <element>
%destructor { destroyElementList($$); }    <elementList>
%destructor { destroyParallel($$); }       <parallel>
%destructor { destroyBranch($$); }         <branch>
%destructor { destroyBranchList($$) }      <branchList>
%destructor { destroyComponent($$); }      <component>
%destructor { destroyParameter($$); }      <parameter>
%destructor { destroyParameterList($$); }  <parameterList>
%destructor { destroyIdentifier($$); }     <identifier>
%destructor { destroyPolarity($$); }       <polarity>
%destructor { destroyCurrent($$); }        <current>

/* ---------- Terminals. ---------- */
%token <token> ID
%token <token> CIRCUIT
%token <token> PARALLEL
%token <token> BRANCH
%token <token> SOURCE
%token <token> RESISTANCE
%token <token> CAPACITOR
%token <token> INDUCTANCE
%token <token> SWITCH
%token <token> VOLTMETER
%token <token> AMPEREMETER

%token <token> POSITIVE
%token <token> NEGATIVE

%token <token> DIRECT
%token <token> ALTERNATING

%token <unit> UNIT
%token <token> VALUE

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_BRACE
%token <token> CLOSE_BRACE
%token <token> COMMA

%%

/* ---------- Non-terminals. ---------- */
%type <program> program
%type <circuit> circuit
%type <circuitList> circuitList
%type <element> element
%type <elementList> elementList elementListOpt
%type <component> component
%type <parameter> parameter
%type <parameterList> componentParamsOpt parameterListOpt parameterList
%type <identifier> identifier
%type <branch> branch
%type <branchList> branchList
%type <parallel> parallel
%type <polarity> polarity
%type <current> current

%%

/* Program: one or more independent circuits */
program: circuitList                                 { $$ = ProgramSemanticAction($1); }
    ;

circuitList: 
      circuit                            	{ $$ = NewCircuitListSemanticAction($1); }
    | circuitList COMMA circuit             { $$ = AppendCircuitSemanticAction($1, $3); }
    ;

/* Circuit: "Circuit" ID { body } */
circuit: CIRCUIT identifier OPEN_BRACE elementListOpt CLOSE_BRACE		{ $$ = CircuitSemanticAction($2, $4); }
    ;

/* Element list inside a circuit or branch */
elementListOpt: 
      %empty                             	{ $$ = EmptyElementListSemanticAction(); }
	| elementList                           { $$ = $1; }
    ;

elementList:
	  element                                      { $$ = NewElementListSemanticAction($1); }
    | elementList COMMA element                    { $$ = AppendElementSemanticAction($1, $3); }
    ;

/* Elementos posibles */
element:
      component                                { $$ = ComponentElementSemanticAction($1); }
    | parallel                                 { $$ = ParallelElementSemanticAction($1); }
    ;

/* Parallel: "Parallel" { elementos } */
parallel:
      PARALLEL OPEN_BRACE branchList CLOSE_BRACE	{ $$ = ParallelSemanticAction($3); }
    ;

branchList: 
      branch COMMA branch                           { $$ = NewBranchListSemanticAction($1, $3); }
	| branchList COMMA branch                       { $$ = AppendBranchSemanticAction($1, $3); }
    ;

/* Branch: "Branch" ID { elementos } */
branch:
      BRANCH identifier OPEN_BRACE elementListOpt CLOSE_BRACE
                                                    { $$ = BranchSemanticAction($2, $4); }
    ;

/* Components: can have parenthesis, parameters (posibles parámetros) o no */
component:
      SOURCE identifier componentParamsOpt         { $$ = SourceComponentSemanticAction($2, $3); }
    | RESISTANCE identifier componentParamsOpt     { $$ = ResistanceComponentSemanticAction($2, $3); }
    | VOLTMETER identifier componentParamsOpt      { $$ = VoltmeterComponentSemanticAction($2, $3); }
    | AMPEREMETER identifier componentParamsOpt    { $$ = AmperemeterComponentSemanticAction($2, $3); }
    | INDUCTANCE identifier componentParamsOpt     { $$ = InductanceComponentSemanticAction($2, $3); }
    | CAPACITOR identifier componentParamsOpt      { $$ = CapacitorComponentSemanticAction($2, $3); }
    | SWITCH identifier componentParamsOpt         { $$ = SwitchComponentSemanticAction($2, $3); }
    ;

componentParamsOpt: %empty                                    	    { $$ = EmptyParameterListSemanticAction(); }
    | OPEN_PARENTHESIS parameterListOpt CLOSE_PARENTHESIS			{ $$ = $2; }
    ;

parameterListOpt: %empty                                    { $$ = EmptyParameterListSemanticAction(); }
    | parameterList                                    		{ $$ = $1; }
    ;

parameterList: parameter                                        { $$ = NewParameterListSemanticAction($1); }
    | parameterList COMMA parameter                           	{ $$ = AppendParameterSemanticAction($1, $3); }
    ;

parameter: 
      VALUE                                         { $$ = ParameterValueSemanticAction($1); }
    | UNIT                                          { $$ = ParameterUnitSemanticAction($1); }
    | polarity                                      { $$ = ParameterPolaritySemanticAction($1); }
    | current                                       { $$ = ParameterCurrentSemanticAction($1); }
    ;

identifier: ID                                            { $$ = IdentifierSemanticAction($1); }
    ;

polarity: 
      POSITIVE_                                      { $$ = PositivePolaritySemanticAction($1); }
    | NEGATIVE                                      { $$ = NegativePolaritySemanticAction($1); }

current:
      DIRECT                                        { $$ = DirectCurrentSemanticAction($1); }
    | ALTERNATING                                   { $$ = AlternatingCurrentSemanticAction($1); }

%%
