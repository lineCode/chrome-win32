#include "stdafx.h"
#include "CopyData.h"

CCopyData::CCopyData()
{
    ::memset(&m_CopyData, 0x00, sizeof(COPYDATASTRUCT));
}

CCopyData::~CCopyData()
{
    Reset();
}

const COPYDATASTRUCT CCopyData::Get()
{
    return m_CopyData;
}

void CCopyData::Reset()
{
    ::memset(&m_CopyData, 0x00, sizeof(COPYDATASTRUCT));
}
