/*
 * testMain.cpp
 *
 *  Created on: 30 Apr 2016
 *      Author: Kiljaeden
 */
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <IRController.h>
using namespace std;

int main(void) {
	IRController ir;
	ir.readSchema();
	ir.emitSignal();
}



