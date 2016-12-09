/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Mon Nov 28 14:22:27 EST 2016 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* Circuits_and3() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* and0 = new_AndGate(in0, in1);
	Gate* and1 = new_AndGate(Gate_getOutput(and0), in2);

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(and1);
	Gate** gates = new_Gate_array(2);
	gates[0] = and0;
	gates[1] = and1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

static void test2In1Out(Circuit *circuit, bool in0, bool in1) {
		Circuit_setInput(circuit, 0, in0);
		Circuit_setInput(circuit, 1, in1);
		//Circuit_dump(circuit);
		Circuit_update(circuit);
		bool out0 = Circuit_getOutput(circuit, 0);
		printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}

static void testAll2In1Out(Circuit *circuit) {
	test2In1Out(circuit, false, false);
	test2In1Out(circuit, false, true);
	test2In1Out(circuit, true, false);
	test2In1Out(circuit, true, true);
}

static void testAll3In1Out(Circuit *circuit) {
	test3In1Out(circuit, false, false, false);
	test3In1Out(circuit, false, false, true);
	test3In1Out(circuit, false, true, false);
	test3In1Out(circuit, false, true, true);
	test3In1Out(circuit, true, false, false);
	test3In1Out(circuit, true, false, true);
	test3In1Out(circuit, true, true, false);
	test3In1Out(circuit, true, true, true);
}

static Circuit* Circuits_a() {
	//init input values
	Value *in0 = new_Value(false);
	Value *in1 = new_Value(false);
	Value *in2 = new_Value(false);
	//init gates
	Gate *not0 = new_Inverter(in1);
	Gate *and0 = new_AndGate(in0, Gate_getOutput(not0));
	Gate *and1 = new_AndGate(in1, in2);
	Gate *or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1));

	//create arrays
	Value **inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value **outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or0);
	Gate **gates = new_Gate_array(4);
	gates[0] = not0;
	gates[1] = and0;
	gates[2] = and1;
	gates[3] = or0;

	return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

int main(int argc, char **argv) {
	Circuit* c = Circuits_and3();
	printf("Some input(s) false: should be false\n");
	test3In1Out(c, true, true, false);
	printf("All inputs true: should be true\n");
	test3In1Out(c, true, true, true);

	printf("%s\n", "==========================================");
	testAll3In1Out(Circuits_a());
	printf("%s\n", "==========================================");
	testAll3In1Out(Circuits_b());
	printf("%s\n", "==========================================");
	testAll2In1Out(Circuits_c());
}
