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
Component * ACSourceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * DCSourceComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * ResistorComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * VoltmeterComponentSemanticAction(Identifier * identifier);
Component * AmperemeterComponentSemanticAction(Identifier * identifier);
Component * InductorComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * CapacitorComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
Component * SwitchComponentSemanticAction(Identifier * identifier, ParameterList * parameterList);
ParameterList * EmptyParameterListSemanticAction();
ParameterList * NewParameterListSemanticAction(Parameter * parameter);
ParameterList * AppendParameterSemanticAction(ParameterList * parameterList, Parameter * parameter);
ParameterList * AppendParameterListSemanticAction(ParameterList * baseParameterList, ParameterList * newParameterList);
Parameter * ParameterValueSemanticAction(const char ** value);
Parameter * ParameterUnitMultiplierSemanticAction(UnitMultiplier unitMultiplier);
Parameter * ParameterResistorTypeSemanticAction(ResistorType resistorType);
Parameter * ParameterSwitchStateSemanticAction(SwitchState switchState);
Parameter * ParameterPolaritySemanticAction(Polarity * polarity);
Identifier * IdentifierSemanticAction(const char ** identifier);

#endif
