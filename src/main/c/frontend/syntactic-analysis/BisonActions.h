#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../support/logging/Logger.h"
#include "../../support/type/CompilerState.h"
#include "../../support/type/ModuleDestructor.h"
#include "../../support/type/TokenLabel.h"
#include "AbstractSyntaxTree.h"
#include "BisonParser.h"
#include <stdlib.h>

/** Initialize module's internal state. */
ModuleDestructor initializeBisonActionsModule();

/**
 * Bison semantic actions.
 */

Program * ProgramSemanticAction(CircuitList * circuitList);
CircuitList * NewCircuitListSemanticAction(Circuit * circuit);
CircuitList * AppendCircuitSemanticAction(CircuitList * circuitList, Circuit * circuit);
Circuit * CircuitSemanticAction(Identifier * identifier, ElementList * elementList);
ElementList * EmptyElementListSemanticAction();
ElementList * NewElementListSemanticAction(Element * element);
ElementList * AppendElementSemanticAction(ElementList * elementList, Element * element);
Element * ComponentElementSemanticAction(Component * component);
Element * ParallelElementSemanticAction(Parallel * parallel);
Parallel * ParallelSemanticAction(BranchList * branchList);
BranchList * NewBranchListSemanticAction(Branch * leftBranch, Branch * rightBranch);
BranchList * AppendBranchSemanticAction(BranchList * branchList, Branch * branch);
Branch * BranchSemanticAction(Identifier * identifier, ElementList * elementList);
Component * SourceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * ResistanceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * VoltmeterComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * AmperemeterComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * InductanceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * CapacitorComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * SwitchComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
ParameterList * EmptyParameterListSemanticAction();
ParameterList * NewParameterListSemanticAction(Parameter * parameter);
ParameterList * AppendParameterSemanticAction(ParameterList * parameterList, Parameter * parameter);
Parameter * ParameterValueSemanticAction(const char * value);
Parameter * ParameterUnitSemanticAction(Unit * unit);
Parameter * ParameterPolaritySemanticAction(Polarity * polarity);
Parameter * ParameterCurrentSemanticAction(Current * current);
<<<<<<< HEAD
Identifier * IdentifierSemanticAction(const char * id);

Current * DirectCurrentSemanticAction(Current * current);
Current * AlternatingCurrentSemanticAction(Current * current);
=======
Identifier * IdentifierSemanticAction(const char * identifier);
Polarity * PositiveFirstPolaritySemanticAction(PolarityType * polarity);
Polarity * NegativeFirstPolaritySemanticAction(PolarityType * polarity);
Current * DirectCurrentSemanticAction(CurrentType * current);
Current * AlternatingCurrentSemanticAction(CurrentType * current);
>>>>>>> fa604e405f122c826478b9f1629d5634c9a4494a

#endif
