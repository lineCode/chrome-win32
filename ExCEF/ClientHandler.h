// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "include/cef_client.h"
#include <list>

class CClienteHandler : public CefClient,
                      public CefDisplayHandler,
                      public CefLifeSpanHandler,
                      public CefJSDialogHandler,
                      public CefLoadHandler
                      
{
public:
    CClienteHandler();
    virtual ~CClienteHandler();

    // Provide access to the single global instance of this object.
    static CClienteHandler* GetInstance();

    // CefClient methods:
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
        return this;
    }

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
        return this;
    }

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
        return this;
    }

    virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() OVERRIDE {
        return this;
    }

    // CefDisplayHandler methods:
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                        const CefString& title) OVERRIDE;

    // CefLifeSpanHandler methods:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;



    // CefLoadHandler methods:
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                    CefRefPtr<CefFrame> frame,
                    ErrorCode errorCode,
                    const CefString& errorText,
                    const CefString& failedUrl) OVERRIDE;

    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        int httpStatusCode) OVERRIDE;

    /// Javascript Alert Dialog Handler 
    virtual bool OnJSDialog(CefRefPtr<CefBrowser> browser,
        const CefString& origin_url,
        const CefString& accept_lang,
        JSDialogType dialog_type,
        const CefString& message_text,
        const CefString& default_prompt_text,
        CefRefPtr<CefJSDialogCallback> callback,
        bool& suppress_message);

    // Request that all existing browser windows close.
    void CloseAllBrowsers(bool force_close);

    bool IsClosing() const { return is_closing_; }
    time_t GetQuitMessageLoopTime() const { return m_tQuitMessageLoop; }

    CefRefPtr<CefBrowser> GetBrowser(int _nId);
    bool IsLoading();
    void StopLoad();
    void SetOwner(CWnd *_pWndOwner)
    {
        m_pWndOwner = _pWndOwner;
    }

    void CloseAllJsAlertDialog();

private:
    // List of existing browser windows. Only accessed on the CEF UI thread.
    typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
    BrowserList browser_list_;

    bool is_closing_;
    CWnd *m_pWndOwner;
    time_t m_tQuitMessageLoop;
    std::vector<CDialogEx *> m_vDlgJsAlert;
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(CClienteHandler);
};

#endif  // CLIENT_HANDLER_H
