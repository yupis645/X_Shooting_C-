#ifndef DEBUGINPUT_H
#define DEBUGINPUT_H

class IInputManager;
class DIContainer;

#include <iostream>

class DebugInput{
public :
	DebugInput(std::shared_ptr<DIContainer> con);

	void InputPritf();



	~DebugInput() = default;

	std::shared_ptr<IInputManager> input_;


};

#endif //DEBUGINPUT_H