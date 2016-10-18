#pragma once


class TaskProgressListener
{

	/// <param name="percentDone"> between 0.0 and 1.0 </param>
public:
	virtual void setProgress(float percentDone) = 0;

	virtual void isComplete() = 0;

};