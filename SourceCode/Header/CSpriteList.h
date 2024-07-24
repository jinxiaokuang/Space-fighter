#ifndef CSPRITELIST_H
#define CSPRITELIST_H
#include "CommonClass.h"
#include "CGameSprite.h"
struct SpriteStruct
{
    CGameSprite* pSprite;
    SpriteStruct* pNext;
    SpriteStruct* pPrev;
};
class CSpriteList
{
    public:
        CSpriteList(const char* szName);
        CSpriteList();
        virtual ~CSpriteList();

        int GetListSize() { return m_iListSize; }
        void SetListSize(int val) { m_iListSize = val; }
        SpriteStruct* AddSprite(CGameSprite*pSprite);
        CGameSprite* GetSprite(const int iLndex);
        CGameSprite* GetSprite(const char* szName);
        void DeleteSprite(const char* szName,bool bDeletelmage);
        void DeleteSprite(CGameSprite* pSprite,bool bDeletelmage);
        void DeleteAllSprite(bool bDeletelmage);
    protected:

    private:
        int m_iListSize;
        SpriteStruct* m_pListHeader;
};

#endif // CSPRITELIST_H
