#pragma once
#include "include/cef_v8.h"

class MyV8Handler : public CefV8Handler
{
public:
    MyV8Handler(void);
    virtual ~MyV8Handler(void);

    virtual bool Execute(const CefString& name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList& arguments,
        CefRefPtr<CefV8Value>& retval,
        CefString& exception) OVERRIDE;

    void OnPostMessage(const std::string& _sJson);
    void SetOwnerBrowserID(int _nOwnerID);

protected:
    int m_nOwnerBrowserID;

public:
    // Provide the reference counting implementation for this class.
    IMPLEMENT_REFCOUNTING(MyV8Handler);
};


