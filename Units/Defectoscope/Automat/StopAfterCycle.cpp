#include "stdafx.h"
#include "StopAfterCycle.h"
#include "LogMessages.h"
#include "LogBuffer.h"

void StopAfterCycle()
{
	if(app.StopAfterCycle())
	{
		  ResetEvent(App::ProgrammContinueEvent);
		  Log::Mess<LogMess::ContinueCycle>();
		  WaitForSingleObject(App::ProgrammContinueEvent, 60 * 60 * 1000);
	}
}