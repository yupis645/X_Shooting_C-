#include "DebugInput.h"



#include "conioex.h"
#include "Geometry.h"
#include "common.h"

using  InputFlag = IInputManager::InputFlag;
using  InputMode = IInputManager::InputMode;


void DebugInput::InputPritf()
{
	auto is = [this](InputFlag flag, InputMode mode) { return input_->IsFlagSet(flag, mode); };
	auto f = [this, is](InputFlag flag, InputMode mode) {return is(flag, mode) ? "true" : "false"; };

	//方向キーをfloat値で0～1を取得する
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 28), 0,
		"		GetAxis ( %f , %f )", input_->GetAxis().x, input_->GetAxis().y);
	//各ビットフラグの状態の目次。下に同じカテゴリが続く
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 25), 0,
		"Input Flags Bit = press:%d , pushdown:%d , pushup:%d , toggle:%d ,  ", input_->GetFlags(InputMode::press), input_->GetFlags(InputMode::pushdown), input_->GetFlags(InputMode::pushup), input_->GetFlags(InputMode::toggle));


	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 22), 0, "left   = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::left, InputMode::press), f(InputFlag::left, InputMode::pushdown), f(InputFlag::left, InputMode::pushup), f(InputFlag::left, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 20), 0, "right  = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::right, InputMode::press), f(InputFlag::right, InputMode::pushdown), f(InputFlag::right, InputMode::pushup), f(InputFlag::right, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 18), 0, "down   = %5s,%5s ,%5s ,%5s  \n ",
		f(InputFlag::down, InputMode::press), f(InputFlag::down, InputMode::pushdown), f(InputFlag::down, InputMode::pushup), f(InputFlag::down, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 16), 0, "up     = %5s,%5s ,%5s ,%5s  \n ",
		f(InputFlag::up, InputMode::press), f(InputFlag::up, InputMode::pushdown), f(InputFlag::up, InputMode::pushup), f(InputFlag::up, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 14), 0, "select = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::select, InputMode::press), f(InputFlag::select, InputMode::pushdown), f(InputFlag::select, InputMode::pushup), f(InputFlag::select, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 12), 0, "cancel = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::cancel, InputMode::press), f(InputFlag::cancel, InputMode::pushdown), f(InputFlag::cancel, InputMode::pushup), f(InputFlag::cancel, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 10), 0, "pose   = %5s,%5s ,%5s ,%5s  \n ",
		f(InputFlag::pose, InputMode::press), f(InputFlag::pose, InputMode::pushdown), f(InputFlag::pose, InputMode::pushup), f(InputFlag::pose, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 8), 0, "shot   = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::shot, InputMode::press), f(InputFlag::shot, InputMode::pushdown), f(InputFlag::shot, InputMode::pushup), f(InputFlag::shot, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 6), 0, "bom     = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::bom, InputMode::press), f(InputFlag::bom, InputMode::pushdown), f(InputFlag::bom, InputMode::pushup), f(InputFlag::bom, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 4), 0, "esc    = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::esc, InputMode::press), f(InputFlag::esc, InputMode::pushdown), f(InputFlag::esc, InputMode::pushup), f(InputFlag::esc, InputMode::toggle));
}
