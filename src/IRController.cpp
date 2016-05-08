/*
 * IRController.cpp
 *
 *  Created on: 7 May 2016
 *      Author: Kiljaeden
 */
#include "IRController.h"
#include <wiringPi.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
using namespace std;
#define MARGIN_SIGNAL 200
#define HIGH_SIGNAL 500
#define PULSE_SIGNAL 500
#define LOW_SIGNAL 1200

void IRController::readSchema(){
	cout << "wtf";
	string path = "/home/pi/airconCode/mitsubishi";
    auto dir = opendir(path.c_str());
    vector<string> fileList;
    struct dirent* ent;
    while ((ent = readdir (dir)) != NULL) {
    	string file = ent->d_name;
    	if(file.find(".rec") != std::string::npos) {
    		printf ("%s\n", ent->d_name);
    		fileList.push_back(file);
    	}
    }
    vector<vector<int> > signalList;
    for(auto file : fileList) {
        ifstream myfile (path + "/" + file);
        string line = fileList[0];
        ostringstream ss;
        if (myfile.is_open())
        {
        	getline(myfile, line);
          while ( getline (myfile,line))
          {

        	  cout << line << '\n';
        	  ss << line;
          }
          myfile.close();
        }
        line = "";
        vector<int> signals;
        string signalInput = ss.str();
        for (char s : signalInput) {
        	if(s == ' ') {
        		if(line != "") signals.push_back(stoi(line));
        		line = "";
        		continue;
        	}
        	line += s;

        }
        if(line != "") signals.push_back(stoi(line));
        signalList.push_back(signals);

    }
    for(int i = 0; i <signalList[0].size(); i++) {
    	int signal = 0;
    	for(auto list : signalList) {
    		signal += list[i];
    	}
    	signal /= signalList.size();
    	if(abs(signal - HIGH) < MARGIN_SIGNAL) signal = HIGH_SIGNAL;
    	else if(abs(signal - PULSE_SIGNAL) < MARGIN_SIGNAL) signal = PULSE_SIGNAL;
    	else if(abs(signal - LOW_SIGNAL) < MARGIN_SIGNAL) signal = LOW_SIGNAL;
    	IRSignal.push_back(signal);
    }
}

void IRController::emitSignal() {
	wiringPiSetup ();
	pinMode (5, OUTPUT) ;
	int count = 1;
	for (int signal : IRSignal)
	{
		cout << std::to_string(signal) + " ";
		if(count % 6 == 0) cout << endl;
		if(count++ % 2 != 0) {
			digitalWrite(5, HIGH);
			delayMicroseconds(signal);
		}
		else {
			digitalWrite (5, LOW);
			delayMicroseconds(signal);
		}
	}
	digitalWrite(5, LOW);
}

IRController::IRController() {
}

IRController::~IRController() {

}

