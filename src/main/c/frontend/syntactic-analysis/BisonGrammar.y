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

 	double real;
	TokenLabel token;

	/** Non-terminals. */

	Program * program;
    Circuit * circuit;
    Component * component;
    ComponentParams * params;
    Branch * branch;
    Parallel * parallel;
    Connection * connection;
    Identifier * identifier;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach for the AST root node ("program" non-terminal, in this
 * grammar), or it will drop the entire tree even if the parsing succeeds.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
%destructor { destroyProgram($$); } <program>
%destructor { destroyCircuit($$); } <circuit>
%destructor { destroyComponent($$); } <component>
%destructor { destroyConnection($$); } <connection>
%destructor { destroyParams($$); } <params>

/* ---------- Terminals. ---------- */
%token <token> ID
%token <token> CIRCUIT
%token <token> PARALLEL
%token <token> BRANCH
%token <token> BATTERY
%token <token> RESISTANCE
%token <token> CAPACITOR
%token <token> CONNECTION
%token <token> VOLTIMETER
%token <token> AMPERIMETER

%token <token> UNIT
%token <token> POLARITY
%token <real> VALUE

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> COMMA

%%

/* ---------- Non-terminals. ---------- */
%type <program> program
%type <circuit> circuit
%type <component> component
%type <params> component_params_opt
%type <identifier> identifier
%type <connection> connection
%type <branch> branch
%type <parallel> parallel
%type <value> value

%%

/* Program: one or more independent circuits */
program: circuitList                                 { $$ = ProgramSemanticAction($1); }
    ;

circuitList: circuit                              	{ $$ = NewCircuitListSemanticAction($1); }
    | circuitList COMMA circuitDecl                 { $$ = AppendCircuitSemanticAction($1, $3); }
    ;

/* Circuit: "Circuit" ID { body } */
circuitDecl: CIRCUIT identifier OPEN_BRACKET elementListOpt CLOSE_BRACKET		{ $$ = CircuitSemanticAction($2, $4); }
    ;

/* Element list inside a circuit or branch */
elementListOpt: %empty                             	{ $$ = EmptyElementListSemanticAction(); }
	| elementList                                  	{ $$ = $1; }
    ;

elementList:
	  element                                      	{ $$ = NewElementListSemanticAction($1); }
    | elementList COMMA element                    { $$ = AppendElementSemanticAction($1, $3); }
    ;

/* Elementos posibles */
element:
      componentDecl                                { $$ = ComponentElementSemanticAction($1); }
    | parallelDecl                                 { $$ = ParallelElementSemanticAction($1); }
    | connectionDecl                               { $$ = ConnectionElementSemanticAction($1); }
    ;

/* Parallel: "Parallel" { elementos } */
parallelDecl:
      PARALLEL OPEN_BRACE branchList CLOSE_BRACE	{ $$ = ParallelSemanticAction($3); }
    ;

branchList: branchDecl COMMA branchDecl                           { $$ = NewElementListSemanticAction($1, $2); }
	| branchList COMMA branchDecl                                  { $$ = AppendElementSemanticAction($1, $3); }
    ;

/* Branch: "Branch" ID { elementos } */
branchDecl:
      BRANCH identifier OPEN_BRACE elementListOpt CLOSE_BRACE
                                                    { $$ = BranchSemanticAction($2, $4); }
    ;

/* Connection: two ways:
   1- Full declaration: Connection id { ... }
   2- Reference: Connection id
*/
connectionDecl:
      CONNECTION identifier OPEN_BRACKET elementListOpt CLOSE_BRACKET
                                                      { $$ = ConnectionDefSemanticAction($2, $4); }
    | CONNECTION identifier                           { $$ = ConnectionRefSemanticAction($2); }
    ;

/* Components: can have parenthesis, parameters (posibles parámetros) o no */
componentDecl:
      BATTERY identifier componentParamsOpt        { $$ = BatteryComponentSemanticAction($2, $3); }
    | RESISTANCE identifier componentParamsOpt     { $$ = ResistanceComponentSemanticAction($2, $3); }
    | VOLTIMETER identifier componentParamsOpt     { $$ = VoltmeterComponentSemanticAction($2, $3); }
    | AMPERIMETER identifier componentParamsOpt    { $$ = AmperimeterComponentSemanticAction($2, $3); }
    | INDUCTANCE identifier componentParamsOpt     { $$ = InductanceComponentSemanticAction($2, $3); }
    | CAPACITOR identifier componentParamsOpt      { $$ = CapacitorComponentSemanticAction($2, $3); }
    | SWITCH identifier componentParamsOpt         { $$ = SwitchComponentSemanticAction($2, $3); }
    ;

componentParamsOpt: @empty                                    	{ $$ = DefaultParamsSemanticAction(); }
    | OPEN_PARENTHESIS paramListOpt CLOSE_PARENTHESIS			{ $$ = $2; }
    ;

paramListOpt: @empty                                    { $$ = EmptyParamsSemanticAction(); }
    | paramList                                    		{ $$ = $1; }
    ;

paramList: param                                        { $$ = NewParamsSemanticAction($1); }
    | paramList COMMA param                           	{ $$ = AppendParamSemanticAction($1, $3); }
    ;

param: VALUE                                         { $$ = ParamValueSemanticAction($1); }
    | UNIT                                          { $$ = ParamUnitSemanticAction($1); }
    | POLARITY                                      { $$ = ParamPolaritySemanticAction($1); }
    | RESISTOR_TYPE                                 { $$ = ParamResistorTypeSemanticAction($1); }
    | CURRENT_TYPE                                  { $$ = ParamCurrentTypeSemanticAction($1); }
    ;

/* Identifier (names of circuits/branches/components/connections) */
identifier: ID                                            { $$ = IdentifierSemanticAction($1); }
    ;

%%
