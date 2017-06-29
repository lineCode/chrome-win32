
#pragma once


class CMemFileEx : public CMemFile
{
public:
    CMemFileEx();
    virtual ~CMemFileEx();

    void* GetBuffer();
};

