#pragma once

#include "StdAfx.h"
#include "BitStream.h"
#include <io.h>
#include <stdlib.h>

// CBitStream class definition
class CBitStream
{
public:
    // Public methods
    CBitStream(void);
    virtual ~CBitStream(void);
    void WriteBit(BYTE value);
    void ReadBit(BYTE& value);
    void WriteByte(BYTE value);
    void ReadByte(BYTE& value);
    void WriteWord(WORD value);
    void ReadWord(WORD& value);
    void WriteDWord(DWORD value);
    void ReadDWord(DWORD& value);
    void WriteData(LPBYTE lpData, long nLen);
    void ReadData(LPBYTE lpData, long nLen);
    void WriteData(LPWORD lpData, long nLen);
    void ReadData(LPWORD lpData, long nLen);
    void WriteData(LPDWORD lpData, long nLen);
    void ReadData(LPDWORD lpData, long nLen);
    void WriteBits(DWORD value, long nLen=32);
    void ReadBits(DWORD& value, long nLen=32);
    void LoadStream(LPTSTR lpszFileName);
    void SaveStream(LPTSTR lpszFileName);
    void LoadStream(LPBYTE lpStream, long nLen);
    void SaveStream(LPBYTE lpStream);
    LPBYTE GetStream()	{return m_lpStream;}
    DWORD GetStreamLength()	{return m_dwStreamOffset;}
    DWORD GetStreamTotalLength()	{return m_dwStreamLen;}
    DWORD GetCurrentPosition()	{return m_dwCurrentPosition;}
    void SetCurrentPosition(DWORD dwCurrentPosition)	{m_dwCurrentPosition = max(0, min(m_dwStreamOffset-1, dwCurrentPosition));}

private:
    // Private methods
    void _WriteBit(BYTE value);
    void _ReadBit(BYTE& value);

private:
    // Private members
    LPBYTE m_lpStream;
    DWORD m_dwStreamLen;
    DWORD m_dwStreamOffset;
    DWORD m_dwCurrentPosition;
    BYTE m_CurrentBit;

};





CBitStream::CBitStream(void)
{
    // Init members
    m_lpStream = NULL;
    m_dwStreamLen = 0;
    m_dwStreamOffset = 0;
    m_dwCurrentPosition = 0;
    m_CurrentBit = 0;
}

CBitStream::~CBitStream(void)
{
    // Free stream
    if (m_lpStream != NULL)
    {
        free(m_lpStream);
        m_lpStream = NULL;
        m_dwStreamLen = 0;
    }
}

void CBitStream::_WriteBit(BYTE value)
{
    // Check for current bit offset
    if ((m_CurrentBit % 8) == 0)
    {
        // Check for valid stream
        if (m_lpStream == NULL)
        {
            m_lpStream = (LPBYTE)malloc(sizeof(BYTE));
            m_dwStreamLen = 1;
            m_lpStream[m_dwStreamLen-1] = 0;
            m_CurrentBit = 0;
            m_dwStreamOffset = 0;
        }
        else
        {
            m_CurrentBit = 0;
            m_dwStreamLen++;
            m_lpStream = (LPBYTE)realloc(m_lpStream, m_dwStreamLen*sizeof(BYTE));
            m_lpStream[m_dwStreamLen-1] = 0;
        }
    }

    // Write single BIT
    m_lpStream[m_dwStreamLen-1] |= ((value & 0x80) >> m_CurrentBit);
    m_dwStreamOffset++;
    m_dwCurrentPosition = m_dwStreamOffset - 1;
    m_CurrentBit++;
}

void CBitStream::_ReadBit(BYTE& value)
{
    // Check for valid position
    value = 0x00;
    if (m_dwCurrentPosition < m_dwStreamOffset)
    {
        // Read single BIT
        DWORD currentByte = m_dwCurrentPosition >> 3;
        BYTE currentBit = (BYTE)(m_dwCurrentPosition % 8);
        value = ((BYTE)(m_lpStream[currentByte] << currentBit) >> 7);
        m_dwCurrentPosition = max(0, min(m_dwStreamOffset-1, m_dwCurrentPosition+1));
    }
}

void CBitStream::WriteBit(BYTE value)
{
    // Write single BIT
    BYTE bitValue = ((value & 0x01) << 7);
    _WriteBit(bitValue);
}

void CBitStream::ReadBit(BYTE& value)
{
    // Read single BIT
    _ReadBit(value);
}

void CBitStream::WriteByte(BYTE value)
{
    // Write single BYTE
    BYTE currentOffset = 0;
    BYTE mask = 0x80;
    BYTE bitValue = 0;
    for (long i=0; i<8; i++)
    {
        bitValue = ((value & mask) << currentOffset);
        _WriteBit(bitValue);
        mask = mask >> 1;
        currentOffset++;
    }
}

void CBitStream::ReadByte(BYTE& value)
{
    // Read single BYTE
    value = 0x00;
    BYTE currentOffset = 7;
    BYTE bitValue;
    for (long i=0; i<8; i++)
    {
        _ReadBit(bitValue);
        value |= (bitValue << currentOffset);
        currentOffset--;
    }
}

void CBitStream::WriteWord(WORD value)
{
    // Write single WORD
    BYTE currentOffset = 0;
    WORD mask = 0x8000;
    BYTE bitValue = 0;
    for (long i=0; i<16; i++)
    {
        bitValue = (BYTE)(((value & mask) << currentOffset) >> 8);
        _WriteBit(bitValue);
        mask = mask >> 1;
        currentOffset++;
    }
}

void CBitStream::ReadWord(WORD& value)
{
    // Read single WORD
    value = 0x0000;
    BYTE currentOffset = 15;
    BYTE bitValue;
    for (long i=0; i<16; i++)
    {
        _ReadBit(bitValue);
        value |= (bitValue << currentOffset);
        currentOffset--;
    }
}

void CBitStream::WriteDWord(DWORD value)
{
    // Write single DWORD
    BYTE currentOffset = 0;
    DWORD mask = 0x80000000;
    BYTE bitValue = 0;
    for (long i=0; i<32; i++)
    {
        bitValue = (BYTE)(((value & mask) << currentOffset) >> 24);
        _WriteBit(bitValue);
        mask = mask >> 1;
        currentOffset++;
    }
}

void CBitStream::ReadDWord(DWORD& value)
{
    // Read single DWORD
    value = 0x00000000;
    BYTE currentOffset = 31;
    BYTE bitValue;
    for (long i=0; i<32; i++)
    {
        _ReadBit(bitValue);
        value |= (bitValue << currentOffset);
        currentOffset--;
    }
}

void CBitStream::WriteData(LPBYTE lpData, long nLen)
{
    // Check for valid data
    if (lpData != NULL)
    {
        // Write variable-length data
        for (long i=0; i<nLen; i++)
        {
            // Write single BYTE
            WriteByte(lpData[i]);
        }
    }
}

void CBitStream::ReadData(LPBYTE lpData, long nLen)
{
    // Check for valid data
    if (lpData != NULL)
    {
        // Read variable-length data
        for (long i=0; i<nLen; i++)
        {
            // Read single BYTE
            ReadByte(lpData[i]);
        }
    }
}

void CBitStream::WriteData(LPWORD lpData, long nLen)
{
    // Check for valid data
    if (lpData != NULL)
    {
        // Write variable-length data
        for (long i=0; i<nLen; i++)
        {
            // Write single WORD
            WriteWord(lpData[i]);
        }
    }
}

void CBitStream::ReadData(LPWORD lpData, long nLen)
{
    // Check for valid data
    if (lpData != NULL)
    {
        // Read variable-length data
        for (long i=0; i<nLen; i++)
        {
            // Read single WORD
            ReadWord(lpData[i]);
        }
    }
}

void CBitStream::WriteData(LPDWORD lpData, long nLen)
{
    // Check for valid data
    if (lpData != NULL)
    {
        // Write variable-length data
        for (long i=0; i<nLen; i++)
        {
            // Write single DWORD
            WriteDWord(lpData[i]);
        }
    }
}

void CBitStream::ReadData(LPDWORD lpData, long nLen)
{
    // Check for valid data
    if (lpData != NULL)
    {
        // Read variable-length data
        for (long i=0; i<nLen; i++)
        {
            // Read single DWORD
            ReadDWord(lpData[i]);
        }
    }
}

void CBitStream::WriteBits(DWORD value, long nLen)
{
    // Write single BITs
    long _nLen = max(0, min(32, nLen));
    BYTE currentOffset = (BYTE)(_nLen - 1);
    DWORD mask = (0x00000001 << (_nLen - 1));
    BYTE bitValue = 0;
    for (long i=0; i<_nLen; i++)
    {
        bitValue = ((BYTE)((value & mask) >> currentOffset) << 7);
        _WriteBit(bitValue);
        mask = mask >> 1;
        currentOffset--;
    }
}

void CBitStream::ReadBits(DWORD& value, long nLen)
{
    // Read single BITs
    value = 0x00000000;
    long _nLen = max(0, min(32, nLen));
    BYTE currentOffset = 31;
    BYTE bitValue;
    for (long i=0; i<_nLen; i++)
    {
        _ReadBit(bitValue);
        value |= (bitValue << currentOffset);
        currentOffset--;
    }
}

void CBitStream::LoadStream(LPTSTR lpszFileName)
{
    // Check for valid file name
    if (lpszFileName != NULL)
    {
        // Free stream
        if (m_lpStream != NULL)
        {
            free(m_lpStream);
            m_lpStream = NULL;
            m_dwStreamLen = 0;
        }

        // Read stream from file
        FILE* file = _tfopen(lpszFileName, _T("rb"));
        if (file != NULL)
        {
            m_dwStreamLen = filelength(file->_file);
            m_lpStream = (LPBYTE)malloc(m_dwStreamLen*sizeof(BYTE));
            fread(m_lpStream, sizeof(BYTE), m_dwStreamLen, file);
            fclose(file);
            m_dwStreamOffset = m_dwStreamLen << 3;
            m_dwCurrentPosition = m_dwStreamOffset - 1;
            m_CurrentBit = 0;
        }
    }
}

void CBitStream::SaveStream(LPTSTR lpszFileName)
{
    // Check for valid file name
    if (lpszFileName != NULL)
    {
        // Check for valid stream
        if (m_lpStream != NULL)
        {
            // Write stream to file
            FILE* file = _tfopen(lpszFileName, _T("wb"));
            if (file != NULL)
            {
                fwrite(m_lpStream, sizeof(BYTE), m_dwStreamLen, file);
                fclose(file);
            }
        }
    }
}

void CBitStream::LoadStream(LPBYTE lpStream, long nLen)
{
    // Check for valid memory buffer
    if (lpStream != NULL)
    {
        // Free stream
        if (m_lpStream != NULL)
        {
            free(m_lpStream);
            m_lpStream = NULL;
            m_dwStreamLen = 0;
        }

        // Read stream from memory buffer
        m_dwStreamLen = nLen;
        m_lpStream = (LPBYTE)malloc(m_dwStreamLen*sizeof(BYTE));
        memcpy(m_lpStream, lpStream, m_dwStreamLen*sizeof(BYTE));
        m_dwStreamOffset = m_dwStreamLen << 3;
        m_dwCurrentPosition = m_dwStreamOffset - 1;
        m_CurrentBit = 0;
    }
}

void CBitStream::SaveStream(LPBYTE lpStream)
{
    // Check for valid memory buffer
    if (lpStream != NULL)
    {
        // Check for valid stream
        if (m_lpStream != NULL)
        {
            // Write stream to memory buffer
            memcpy(lpStream, m_lpStream, m_dwStreamLen*sizeof(BYTE));
        }
    }
}

