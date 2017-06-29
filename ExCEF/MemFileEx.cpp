#include "stdafx.h"
#include "MemFileEx.h"

CMemFileEx::CMemFileEx()
{

}

CMemFileEx::~CMemFileEx() 
{

}

void* CMemFileEx::GetBuffer()
{
    return m_lpBuffer;
}

;