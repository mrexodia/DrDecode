#ifndef _HWBP_H
#define _HWBP_H

#include <windows.h>

#pragma pack(push)
#pragma pack(1)

enum class HWBP_MODE
{
    MODE_DISABLED=0, //00
    MODE_LOCAL=1, //01
    MODE_GLOBAL=2 //10
};

enum class HWBP_TYPE
{
    TYPE_EXECUTE=0, //00
    TYPE_WRITE=1, //01
    TYPE_READWRITE=3 //11
};

enum class HWBP_SIZE
{
    SIZE_1=0, //00
    SIZE_2=1, //01
    SIZE_8=2, //10
    SIZE_4=3 //11
};

struct DR7
{
    BYTE HWBP_MODE[4];
    BYTE HWBP_TYPE[4];
    BYTE HWBP_SIZE[4];
};

#define BITSET(a,x) (a|=1<<x)
#define BITCLEAR(a,x) (a&=~(1<<x))
#define BITTOGGLE(a,x) (a^=1<<x)
#define BITGET(a,x) (a&(1<<x))

bool hwbpSet(HANDLE hThread, ULONG_PTR hwbpAddr, int hwbpIndex, HWBP_TYPE hwbpType, HWBP_SIZE hwbpSize);
bool hwbpDel(HANDLE hThread, int hwbpIndex);
ULONG_PTR dr7uint(DR7* dr7);
void uintdr7(ULONG_PTR dr7, DR7* ret);

#pragma pack(pop)

#endif // _HWBP_H
