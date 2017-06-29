#ifndef CEF_CLIENT_APP_H
#define CEF_CLIENT_APP_H

#include "include\cef_app.h"
#include "MyV8Handler.h"

class CCefClientApp : public CefApp, 
    public CefRenderProcessHandler
{
public:
    CCefClientApp();
    virtual ~CCefClientApp();

    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() {
        return this;
    }
    
    /// CefRenderProcessHandler
    virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) OVERRIDE;


protected:
    //CefRefPtr<CefV8Handler> m_v8Handler;
    CefRefPtr<MyV8Handler> m_v8Handler;

    IMPLEMENT_REFCOUNTING(CCefClientApp);
};  /// end of class CCefClientApp
#endif  /// end of define CEF_CLIENT_APP_H
