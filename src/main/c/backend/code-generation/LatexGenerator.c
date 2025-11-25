#include "LatexGenerator.h"

static void _output(const char *format, ...)
static void _generateProgram(Program * program);
static void _generateCircuit(Circuit * circuit);
static void _generateNewPage();
static void _generateLeftSide(Element * element);
static void _generateTopSide(Element * element);
static void _generateRightSide(Element * element);
static void _generateBottomSide(Element * element);
static void _generateParallel(Parallel * parallel, size_t side);
static void _generateComponent(Component * component);
static void _generateValue(ParameterList * params);
static void _generateResistor(Identifier * id, ParameterList * params);
static void _generateMultiplier(UnitMultiplier multiplier);
static void _generateDcSource(Identifier * id, ParameterList * params);
static void _generateAcSource(Identifier * id, ParameterList * params);

void _generateAcSource(Identifier * id, ParameterList * params){
	_output("[sI");
	if (params->current != nullptr){
		_output(", ");
		_generateValue(params);
		_output("A$");
	}
	_output("] ")
	
}

void _generateDcSource(Identifier * id, ParameterList * params){
	_output("[battery1, ");
	if (params->current != nullptr){
		if(params->current->polarity == POSITIVE_FIRST){
			_output("invert, ");
		}
		params = params->next;
		if (params != nullptr){
			_generateValue(params);
			_output("A$");
		}
	}else{
		_output("invert");
	}
	_output("] ");
}

void _generateMultiplier(UnitMultiplier multiplier){
	switch (multiplier){
		case GIGA:
			_output("G");
			break;
		case MEGA:
			_output("M");
			break;
		case KILO:
			_output("k");
			break;
		case MILLI:
			_output("m");
			break;
		case MICRO:
			_output("\\mu ");
			break;
		case NANO:
			_output("n");
			break;
	}
}

void _generateValue(ParameterList * params){
	if (params != nullptr $$ params->current != nullptr){
		_output("l=$%s", params->current->value);
		params = params->next;
		if (params != nullptr){
			_generateMultiplier(params->current->unitMultiplier);
		}
	}
}

void _generateResistor(Identifier * id, ParameterList * params){
	switch (params->current->resistorType){
	case REGULAR:
		_output("[R");
		break;
	case PHOTORESISTOR:
		_output("[Rphoto");
		break;
	case THERMISTOR:
		_output("[Rthermistor");
		break;
	case POTENTIOMETER:
		_output("[Rpotentiometer"):
		break;
	}
	params = params->next;
	if (params != nullptr){
		_output(", ");
		_generateValue(params);
		_output("\\Omega$");
	}
	_output("] ");
}


void _generateComponent(Component * component){
	switch (component->type){
	case COMPONENT_RESISTOR:
		_generateResistor(component->id, component->parameterList);
		break;
	case COMPONENT_AC_SOURCE:
		_generateAcSource(component->id, component->parameterList);

	default:
		break;
	}
}


void _generateBottomSide(Element * element){
	_output("(4, 0) to");
	if (element->type == ELEMENT_COMPONENT){
		_generateComponent(element->component);
	}else if (element->type == ELEMENT_PARALLEL){
		_output("(0, 0)\n");
		_generateParallel(element->parallel, 3);
		return;
	}
	_output("(0, 0)\n");
}

void _generateRightSide(Element * element){
	_output("(4, 4) to");
	if (element->type == ELEMENT_COMPONENT){
		_generateComponent(element->component);
	}else if (element->type == ELEMENT_PARALLEL){
		_output("(4, 0)\n");
		_generateParallel(element->parallel, 2);
		return;
	}
	_output("(4, 0)\n");
}

void _generateTopSide(Element * element){
	_output("(0, 4) to");
	if (element->type == ELEMENT_COMPONENT){
		_generateComponent(element->component);
	}else if (element->type == ELEMENT_PARALLEL){
		_output("(4, 4)\n");
		_generateParallel(element->parallel, 1);
		return;
	}
	_output("(4, 4)\n");
}

void _generateLeftSide(Element * element){
	_output("(0, 0) to");
	if (element->type == ELEMENT_COMPONENT){
		_generateComponent(element->component);
	}else if (element->type == ELEMENT_PARALLEL){
		_output("(0, 4)\n");
		_generateParallel(element->parallel, 0);
		return;
	}
	_output("(0, 4)\n");
}

void _generateCircuit(Circuit * circuit){
	ElementList *elements = circuit->elementList;

    _generateLeftSide(elements ? elements->current : NULL);

    elements = elements ? elements->next : NULL;
    _generateTopSide(elements ? elements->current : NULL);

    elements = elements ? elements->next : NULL;
    _generateRightSide(elements ? elements->current : NULL);

	elements = elements ? elements->next : NULL;
    _generateBottomSide(elements ? elements->current : NULL);
}

void _generateNewPage(){
	_output("\newpage\n");
}

void _generateProgram(Program * program){
	size_t i = 0;
	CircuitList * list = program->circuitList;
	while (list != null){
		if (i > 0){
			_generateNewPage();
		}
		
		_generateCircuit(list->current);
		list = list->next;
		i++;
	}
}

void _output(const char *format, ...){
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    fflush(stdout);
    va_end(args);
}


 void executeGenerator(CompilerState * compilerState) {
 	logDebugging(_logger, "Generating final output...");
 	_generatePrologue();
 	_generateProgram(compilerState->abstractSyntaxtTree);
 	_generateEpilogue(compilerState->value);
 	logDebugging(_logger, "Generation is done.");
 }
