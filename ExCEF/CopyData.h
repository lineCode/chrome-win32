#pragma once

#include "MemFileEx.h"

class CCopyData
{
public:
    CCopyData();
    virtual ~CCopyData();

    const COPYDATASTRUCT Get();

    void Reset();

protected:
    CMemFileEx m_memFile;
    COPYDATASTRUCT m_CopyData;
};

