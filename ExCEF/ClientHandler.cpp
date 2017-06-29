// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "stdafx.h"
#include "ClientHandler.h"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "DlgJsAlert.h"
#include "ExCEF.h"

extern CExCEFApp theApp;

namespace {

CClienteHandler* g_instance = NULL;

}  // namespace

CClienteHandler::CClienteHandler()
    : is_closing_(false) 
{
    DCHECK(!g_instance);
    m_pWndOwner = NULL;
    g_instance = this;
    m_tQuitMessageLoop = 0;
}

CClienteHandler::~CClienteHandler() 
{
    g_instance = NULL;
}

// static
CClienteHandler* CClienteHandler::GetInstance() 
{
    return g_instance;
}

void CClienteHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) 
{
    CEF_REQUIRE_UI_THREAD();

    // Add to the list of existing browsers.
    browser_list_.push_back(browser);
}

bool CClienteHandler::DoClose(CefRefPtr<CefBrowser> browser) 
{
    CEF_REQUIRE_UI_THREAD();

    // Closing the main window requires special handling. See the DoClose()
    // documentation in the CEF header for a detailed destription of this
    // process.
    if (browser_list_.size() == 1) {
        // Set a flag to indicate that the window close should be allowed.
        is_closing_ = true;
    }

    // Allow the close. For windowed browsers this will result in the OS close
    // event being sent.
    return false;
}

void CClienteHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) 
{
    CEF_REQUIRE_UI_THREAD();

    // Remove from the list of existing browsers.
    BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            DBGA("Close Browser Id [%d]\n", browser->GetIdentifier());
            browser_list_.erase(bit);
            break;
        }
    }


    if (browser_list_.empty()) {
        // All browser windows have closed. Quit the application message loop.
        DBGA("All browser windows have closed, so call CefQuitMessageLoop()");
        CefQuitMessageLoop();
        m_tQuitMessageLoop = time(0);
    }
}

void CClienteHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    int httpStatusCode)
{
    CEF_REQUIRE_UI_THREAD();

    theApp.m_pMainWnd->PostMessage(UM_LOAD_END);
    DBGA("Url [%s] httpStatusCode [%d]", browser->GetMainFrame()->GetURL().ToString().c_str(), httpStatusCode);
}

void CClienteHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                ErrorCode errorCode,
                                const CefString& errorText,
                                const CefString& failedUrl) 
{
    CEF_REQUIRE_UI_THREAD();

    // Don't display an error for downloaded files.
    if (errorCode == ERR_ABORTED)
        return;

    // Display a load error message.
    std::stringstream ss;
    ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL " << std::string(failedUrl) <<
        " with error " << std::string(errorText) << " (" << errorCode <<
        ").</h2></body></html>";
    frame->LoadString(ss.str(), failedUrl);
}

bool CClienteHandler::OnJSDialog(CefRefPtr<CefBrowser> browser,
    const CefString& origin_url,
    const CefString& accept_lang,
    JSDialogType dialog_type,
    const CefString& message_text,
    const CefString& default_prompt_text,
    CefRefPtr<CefJSDialogCallback> callback,
    bool& suppress_message)
{
    CDlgJsAlert *pDlg = new CDlgJsAlert(m_pWndOwner);
 
    pDlg->Create(IDD_JS_ALERT, m_pWndOwner);
    pDlg->SetJsAlertMsg(message_text.ToWString().c_str());
    pDlg->CenterWindow(m_pWndOwner);
    pDlg->ShowWindow(SW_SHOW);
    m_vDlgJsAlert.push_back(pDlg);

    /// customer javascript dialog를 표시하기 위해서 true 값을 리턴한다.
    return true;
}

void CClienteHandler::CloseAllBrowsers(bool force_close) 
{
    if (!CefCurrentlyOn(TID_UI)) {
        // Execute on the UI thread.
        CefPostTask(TID_UI,
            base::Bind(&CClienteHandler::CloseAllBrowsers, this, force_close));
        return;
    }

    if (browser_list_.empty())
        return;

    BrowserList::const_iterator it = browser_list_.begin();
    for (; it != browser_list_.end(); ++it)
        (*it)->GetHost()->CloseBrowser(force_close);
}

void CClienteHandler::CloseAllJsAlertDialog()
{
    std::vector<CDialogEx *>::iterator it = m_vDlgJsAlert.begin();
    for (;it != m_vDlgJsAlert.end(); it++)
    {
        CDialogEx* pDlg = *it;
        pDlg->DestroyWindow();
        delete pDlg;
    }
}

void CClienteHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
	const CefString& title) 
{
    CEF_REQUIRE_UI_THREAD();

    CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
    WCHAR wszCaption[MAX_PATH] = {0};
    GetWindowText(hwnd, wszCaption, MAX_PATH);

    DBGW(L"caption [%s] title [%s]", wszCaption, std::wstring(title).c_str());
    SetWindowText(hwnd, std::wstring(title).c_str());
}

CefRefPtr<CefBrowser> CClienteHandler::GetBrowser(int _nId)
{
    BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) 
    {
        CefRefPtr<CefBrowser> it = *bit;
        if (it->GetIdentifier() == _nId)
        {
            return it;
        }
    }
    return NULL;
}

bool CClienteHandler::IsLoading()
{
    BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) 
    {
        CefRefPtr<CefBrowser> it = *bit;
        if (it->IsLoading() == true) 
        {
            DBGA("Current Browser IsLoading Id [%d] Loading [%d]", it->GetIdentifier(), it->IsLoading());
            return true;
        }
    }

    return false;
}

void CClienteHandler::StopLoad()
{
    BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) 
    {
        CefRefPtr<CefBrowser> it = *bit;
        if (it->IsLoading() == true) 
        {
            DBGA("Call StopLoad(), Current Browser Id [%d]", it->GetIdentifier());
            it->StopLoad();
        }
    }
}

