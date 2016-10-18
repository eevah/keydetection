#include "TaskProgressListener.h"

#pragma once

class Task
{

public:
	static const int DEFAULT_TASK_PRIORITY = 10;

	virtual bool isReady() = 0;
	virtual void run() = 0;
	virtual void execute() = 0;
	virtual void *getResult() = 0;
	virtual int getTaskPriority() = 0;
	virtual void cancel() = 0;
	virtual bool isCancelled() = 0;
	virtual bool isDone() = 0;
	virtual bool isCancellable() = 0;

	virtual void addProgressListener(TaskProgressListener *listener) = 0;
	virtual void removeProgressListener(TaskProgressListener *listener) = 0;
	virtual bool isIndefiniteTask() = 0;
	virtual void setProgress(float progress) = 0;
	virtual float getCurrentProgress() = 0;
};
