#ifndef EventFunctionPtr_H
#define EventFunctionPtr_H

#include <iostream>
#include <string>
#include <cstring>
#include "Event.h"

using namespace std;

class EventFunctionPtr
{
	typedef void *InstancePtr;
	typedef void (*InternalFunction)(InstancePtr, Event*);

public:
	template <void (*Function)(Event*)>
	static EventFunctionPtr* create()
    {
		EventFunctionPtr* del = new EventFunctionPtr();
		del->Bind<Function>();
        return del;
    }
	template <class C, void (C::*Function)(Event*)>
	static EventFunctionPtr* create(C* obj)
    {
		EventFunctionPtr* del = new EventFunctionPtr();
		del->Bind<C, Function>(obj);
        return del;
    }

	template <void (*Function)(Event*)>
	void Bind(void)
	{
		mInst = NULL;
		mInternal = &Method<Function>;
	}
	template <class C, void (C::*Function)(Event*)>
	void Bind(C* obj)
	{
		mInst = obj;
		mInternal = &ClassMethod<C, Function>;
	}

	template <void (*Function)(Event*)>
	static void Method(InstancePtr, Event* ARG0)
	{
		return (Function)(ARG0);
	}
	template <class C, void (C::*Function)(Event*)>
	static void ClassMethod(InstancePtr ptr, Event* ARG0)
	{
		return (static_cast<C*>(ptr)->*Function)(ARG0);
	}

	void Invoke(Event* ARG0)
	{
		return mInternal(mInst, ARG0);
	}

private:

	EventFunctionPtr(void) {}

	InternalFunction mInternal;
	InstancePtr mInst;
};
#endif