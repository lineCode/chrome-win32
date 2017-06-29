#include "stdafx.h"
#include "CefClientApp.h"


CCefClientApp::CCefClientApp()
{
}

CCefClientApp::~CCefClientApp()
{
}

/**
    https://bitbucket.org/chromiumembedded/cef/wiki/JavaScriptIntegration
*/
void CCefClientApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefV8Context> context)
{
    DBGA("Current Browser Id [%d]", browser->GetIdentifier());


    // Retrieve the context's window object.
    CefRefPtr<CefV8Value> object = context->GetGlobal();

    // Create an instance of my CefV8Handler object.
    m_v8Handler = new MyV8Handler();
    m_v8Handler->SetOwnerBrowserID(browser->GetIdentifier());

    // Create the "myfunc" function.
    CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("myfunc", m_v8Handler);
    CefRefPtr<CefV8Value> postMessageFunc = CefV8Value::CreateFunction("PostMessage", m_v8Handler);

    // Add the "myfunc" function to the "window" object.
    object->SetValue("myfunc", func, V8_PROPERTY_ATTRIBUTE_NONE);
    object->SetValue("PostMessage", postMessageFunc, V8_PROPERTY_ATTRIBUTE_NONE);
}

/**
class MyV8Handler : public CefV8Handler 
{
public:
    MyV8Handler() {}

virtual bool Execute(const CefString& name,
                    CefRefPtr<CefV8Value> object,
                    const CefV8ValueList& arguments,
                    CefRefPtr<CefV8Value>& retval,
                    CefString& exception) OVERRIDE 
{
    if (name == "myfunc") 
    {
        // Return my string value.
        retval = CefV8Value::CreateString("My Value!");
        return true;
    }

    // Function does not exist.
    return false;
}

    // Provide the reference counting implementation for this class.
    IMPLEMENT_REFCOUNTING(MyV8Handler);
};


void MyRenderProcessHandler::OnContextCreated(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefV8Context> context) 
{
    // Retrieve the context's window object.
    CefRefPtr<CefV8Value> object = context->GetGlobal();

    // Create an instance of my CefV8Handler object.
    CefRefPtr<CefV8Handler> handler = new MyV8Handler();

    // Create the "myfunc" function.
    CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("myfunc", handler);

    // Add the "myfunc" function to the "window" object.
    object->SetValue("myfunc", func, V8_PROPERTY_ATTRIBUTE_NONE);
}

<script language="JavaScript">
alert(window.myfunc()); // Shows an alert box with "My Value!"
</script>




========================================================









void CCefClientHandler::OnContextCreated(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefV8Context> context) 
{
    REQUIRE_UI_THREAD();

    if (1)
    {
        std::string urlStr = frame->GetURL();
        //http://dev.test.service.tmonplus.co.kr/cashier/login
        if (urlStr.rfind("saving") != std::string::npos) 
        {
            // Retrieve the context's window object.
            CefRefPtr<CefV8Value> object = context->GetGlobal();
            // Create an instance of my CefV8Handler object.
            if (NULL == m_hLogIn)
            {
                m_hLogIn = new CMyV8Handler();
            }

            // Create the "myfunc" function.
            CefRefPtr<CefV8Value> LoginIDFunc = CefV8Value::CreateFunction(JS_CALLBACK_LOGINID, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));
            CefRefPtr<CefV8Value> CloseFunc = CefV8Value::CreateFunction(JS_CALLBACK_HIDE_CEF, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));
            CefRefPtr<CefV8Value> ShowFunc = CefV8Value::CreateFunction(JS_CALLBACK_SHOW_CEF, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));
            CefRefPtr<CefV8Value> BlinkFunc = CefV8Value::CreateFunction(JS_CALLBACK_BLINK_ICON, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));
            CefRefPtr<CefV8Value> ExcuteSettingResultFunc = CefV8Value::CreateFunction(JS_CALLBACK_EXCUTE_SETTING_RESULT, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));
            CefRefPtr<CefV8Value> BranchSettingInfo = CefV8Value::CreateFunction(JS_CALLBACK_SETTING_INFO, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));
            CefRefPtr<CefV8Value> TouchCustomerView = CefV8Value::CreateFunction(JS_CALLBACK_TOUCH_CUSTOMER_VIEW, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));
            CefRefPtr<CefV8Value> UploadClientLog = CefV8Value::CreateFunction(JS_CALLBACK_UPLOAD_LOG, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));
            CefRefPtr<CefV8Value> PointSaveStatus = CefV8Value::CreateFunction(JS_CALLBACK_POINT_SAVE_STATUS, static_cast<CefRefPtr<CefV8Handler>>(m_hLogIn));

            // Add the "myfunc" function to the "window" object.
            object->SetValue(JS_CALLBACK_LOGINID, LoginIDFunc, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_HIDE_CEF, CloseFunc, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_SHOW_CEF, ShowFunc, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_BLINK_ICON, BlinkFunc, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_EXCUTE_SETTING_RESULT, ExcuteSettingResultFunc, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_SETTING_INFO, BranchSettingInfo, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_TOUCH_CUSTOMER_VIEW, TouchCustomerView, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_UPLOAD_LOG, UploadClientLog, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_POINT_SAVE_STATUS, PointSaveStatus, V8_PROPERTY_ATTRIBUTE_NONE);
        }
        else if (urlStr.rfind("login") != std::string::npos) 
        {
            CefRefPtr<CefV8Value> object = context->GetGlobal();
            // Create an instance of my CefV8Handler object.
            if (NULL == m_hLogOut)
            {
                m_hLogOut = new CMyV8Handler();
            }
            CefRefPtr<CefV8Value> BranchSettingInfo = CefV8Value::CreateFunction(JS_CALLBACK_SETTING_INFO, static_cast<CefRefPtr<CefV8Handler>>(m_hLogOut));
            CefRefPtr<CefV8Value> LogOutFunc = CefV8Value::CreateFunction(JS_CALLBACK_LOG_OUT, static_cast<CefRefPtr<CefV8Handler>>(m_hLogOut));
            CefRefPtr<CefV8Value> ExcuteSettingResultFunc = CefV8Value::CreateFunction(JS_CALLBACK_EXCUTE_SETTING_RESULT, static_cast<CefRefPtr<CefV8Handler>>(m_hLogOut));
            CefRefPtr<CefV8Value> ManagerModeFunc = CefV8Value::CreateFunction(JS_CALLBACK_MANAGER_MODE, static_cast<CefRefPtr<CefV8Handler>>(m_hLogOut));

            object->SetValue(JS_CALLBACK_LOG_OUT, LogOutFunc, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_SETTING_INFO, BranchSettingInfo, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_EXCUTE_SETTING_RESULT, ExcuteSettingResultFunc, V8_PROPERTY_ATTRIBUTE_NONE);
            object->SetValue(JS_CALLBACK_MANAGER_MODE, ManagerModeFunc, V8_PROPERTY_ATTRIBUTE_NONE);
        }
    }
}


#include "stdafx.h"
#include "..\include\MyV8Handler.h"
#include "..\..\TMonPlusClient.h"
#include "..\..\TMonPlusClientDlg.h"

#include "..\..\define.h"
#include "..\..\..\default\include\String.h"
#include "..\..\..\default\include\Logger.h"
#include "..\..\TMonPlusManager.h"
#include "..\..\ObserveDir.h"

#include "..\..\SetAutosavingDlg.h"
#include "..\..\TabletSoundDlg.h"


#include "..\include\LoginCB.h"
#include "..\include\LogoutCB.h"
#include "..\include\HideClientWindowCB.h"
#include "..\include\ExcuteSettingResultCB.h"
#include "..\include\BranchSettingInfoCB.h"
#include "..\include\PointSaveStatusCB.h"
#include "..\include\TouchCustomerViewCB.h"
#include "..\include\ManagerModeCB.h"
#include "..\include\ShowClientWindowCB.h"
#include "..\include\BlinkClientIconCB.h"
#include "..\include\UploadClientLogCB.h"
#include "..\include\ExcuteCB.h"


#include <assert.h>
CMyV8Handler::CMyV8Handler()
{}

CMyV8Handler::~CMyV8Handler()
{}


bool CMyV8Handler::Execute(const CefString& name,
    CefRefPtr<CefV8Value> object,
    const CefV8ValueList& arguments,
    CefRefPtr<CefV8Value>& retval,
    CefString& exception)
{
    Json::Value root;
    Json::Reader reader;

    CefRefPtr<CefV8Value> v;
    CefString s;
    std::string jsonData, methodName;

    if( true == name.empty())
    {
        DEBUGLOGA("JavaScript Name Empty!");
        return false;
    }
    else
    {
        methodName = name.ToString();
        DEBUGLOGA("%s CALL",methodName.c_str());

        if ( 0 < arguments.size() )
        {
            v = arguments.at(0);
            s = v->GetStringValue();
            jsonData = s.ToString();
            jsonData = CPP::UTF8ToAnsi(jsonData);

            DEBUGLOGA("Parameter [%s]", jsonData.c_str());
        }

        if (name == JS_CALLBACK_LOGINID)
        {
            DEBUGLOGA("TMonPlus LogIn !");
            CExcuteCB* pLoginCB = new CLoginCB;
            pLoginCB->ExcuteCallBackFunc(jsonData);

            delete pLoginCB;
        }
        else if(name == JS_CALLBACK_LOG_OUT)
        {
            DEBUGLOGA("TMonPlus LogOut !");
            CExcuteCB* pLogoutCB= new CLogoutCB;
            pLogoutCB->ExcuteCallBackFunc(jsonData);

            delete pLogoutCB;
        }
        else if(name == JS_CALLBACK_HIDE_CEF)
        {
            CExcuteCB* pHideClientWindowCB = new CHideClientWindowCB;
            pHideClientWindowCB->ExcuteCallBackFunc(jsonData);

            delete pHideClientWindowCB;
        }
        else if(name == JS_CALLBACK_SHOW_CEF)
        {
            CExcuteCB* pShowClientWindowCB = new CShowClientWindowCB;
            pShowClientWindowCB->ExcuteCallBackFunc(jsonData);

            delete pShowClientWindowCB;
        }
        else if(name == JS_CALLBACK_BLINK_ICON)
        {
            CExcuteCB* pBlinkClientIconCB = new CBlinkClientIconCB;
            pBlinkClientIconCB->ExcuteCallBackFunc(jsonData);

            delete pBlinkClientIconCB;
        }
        else if(name == JS_CALLBACK_EXCUTE_SETTING_RESULT)
        {
            CExcuteCB* pExcuteSettingResultCB = new CExcuteSettingResultCB;
            pExcuteSettingResultCB->ExcuteCallBackFunc(jsonData);

            delete pExcuteSettingResultCB;
        }
        else if(name == JS_CALLBACK_SETTING_INFO)
        {
            CExcuteCB* pBranchSettingInfoCB= new CBranchSettingInfoCB;
            pBranchSettingInfoCB->ExcuteCallBackFunc(jsonData);

            delete pBranchSettingInfoCB;
        }
        else if(name == JS_CALLBACK_TOUCH_CUSTOMER_VIEW)
        {
            CExcuteCB* pTouchCustomerViewCB = new CTouchCustomerViewCB;
            pTouchCustomerViewCB->ExcuteCallBackFunc(jsonData);

            delete pTouchCustomerViewCB;
        }
        else if(name == JS_CALLBACK_MANAGER_MODE)
        {
            CExcuteCB* pManagerModeCB = new CManagerModeCB;
            pManagerModeCB->ExcuteCallBackFunc(jsonData);

            delete pManagerModeCB;
        } 
        else if (name == JS_CALLBACK_UPLOAD_LOG)
        {
            CExcuteCB* pUploadClientLogCB = new CUploadClientLogCB;
            pUploadClientLogCB->ExcuteCallBackFunc(jsonData);

            delete pUploadClientLogCB;
        }
        else if (name == JS_CALLBACK_POINT_SAVE_STATUS)
        {
            CExcuteCB* pPointSaveStatusCB = new CPointSaveStatusCB;
            pPointSaveStatusCB->ExcuteCallBackFunc(jsonData);

            delete pPointSaveStatusCB;
        }
        return true;
    }
    // Function does not exist.
    return false;
}

*/


