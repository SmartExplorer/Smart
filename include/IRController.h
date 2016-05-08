/*
 * IRController.h
 *
 *  Created on: 7 May 2016
 *      Author: Kiljaeden
 */

#ifndef _IRCONTROLLER_H_
#define _IRCONTROLLER_H_
#include <iostream>
#include <unordered_map>
#include <vector>

class IRController {
public:
	IRController();
	~IRController();
	void readSchema();
	void emitSignal();
	std::unordered_map<std::string, std::vector<int> > schema;
private:
	std::vector<int> IRSignal;

};


#endif /* INCLUDE_IRCONTROLLER_H_ */
