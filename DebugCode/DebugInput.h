#ifndef DEBUGINPUT_H
#define DEBUGINPUT_H

#include <iostream>
#include "IInputManager.h"

class DebugInput{
public :
	DebugInput(std::shared_ptr<IInputManager> input):input_(input) {}

	void InputPritf();



	~DebugInput() = default;

	std::shared_ptr<IInputManager> input_;


};

#endif //DEBUGINPUT_H