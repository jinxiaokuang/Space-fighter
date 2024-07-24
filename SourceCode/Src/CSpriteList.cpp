#include "CSpriteList.h"
#include "CGameSprite.h"
CSpriteList::CSpriteList(const char* szName)
{
    //ctor
}
CSpriteList::CSpriteList()
{

}
CSpriteList::~CSpriteList()
{
    //dtor
}
int m_iListSize=0;
SpriteStruct* m_pListHeader=NULL;

CGameSprite* CSpriteList::GetSprite(const char*szName)
{
    SpriteStruct* pPtr=m_pListHeader;
    while (NULL!=pPtr)
    {
        if (strcmp(pPtr->pSprite->GetName(),szName)==0)
            return pPtr->pSprite;
        pPtr=pPtr->pNext;
    }
    return NULL;
}

CGameSprite* CSpriteList::GetSprite(const int ilndex)
{
    int iLoop=0;
    SpriteStruct* pPtr=m_pListHeader;
    while (NULL!=pPtr)
    {
        if (iLoop==ilndex)
            return pPtr->pSprite;
        iLoop++;
        pPtr=pPtr->pNext;
    }
    return NULL;
}

SpriteStruct*CSpriteList::AddSprite(CGameSprite* pSprite)
{
    if (NULL==pSprite)
        return NULL;
    SpriteStruct* pPtr=new SpriteStruct;
    pPtr->pSprite=pSprite;
    pPtr->pNext=NULL;
    pPtr->pPrev=NULL;
    if (NULL==m_pListHeader)
    {
        m_pListHeader=pPtr;
    }
    else
    {
        SpriteStruct* pTemp=m_pListHeader;
        while (NULL!=pTemp->pNext)
        {
            pTemp=pTemp->pNext;
        }
        pPtr->pPrev=pTemp;
        pTemp->pNext=pPtr;
    }
    m_iListSize++;
    return pPtr;
}
void CSpriteList::DeleteSprite(const char* szName,bool bDeletelmage)
{
    SpriteStruct* pPtr=NULL;
        for (pPtr=m_pListHeader;NULL!=pPtr;pPtr=pPtr->pNext)
        {
            if (strcmp(szName,pPtr->pSprite->GetName())==0)
            {
                if (NULL!=pPtr->pNext)
                {
                    pPtr->pNext->pPrev=pPtr->pPrev;
                }
                if (NULL!=pPtr->pPrev)
                {
                    pPtr->pPrev->pNext=pPtr->pNext;
                }
                if (pPtr==m_pListHeader)
                {
                    m_pListHeader=m_pListHeader->pNext;
                }
                if (bDeletelmage)
                {
                    pPtr->pSprite->DeleteSprite();
                }
                delete pPtr;
                m_iListSize--;
                return ;
            }
        }
}

void CSpriteList::DeleteSprite(CGameSprite* pSprite,bool bDeletelmage)
{
    SpriteStruct* pPtr=NULL;
    for (pPtr=m_pListHeader;NULL!=pPtr;pPtr=pPtr->pNext)
    {
        if (pPtr->pSprite==pSprite)
        {
            if (NULL!=pPtr->pNext)
                {
                    pPtr->pNext->pPrev=pPtr->pPrev;
                }
                if (NULL!=pPtr->pPrev)
                {
                    pPtr->pPrev->pNext=pPtr->pNext;
                }
                if (pPtr==m_pListHeader)
                {
                    m_pListHeader=m_pListHeader->pNext;
                }
                if (bDeletelmage)
                {
                    pPtr->pSprite->DeleteSprite();
                }
                delete pPtr;
                m_iListSize--;
                return ;
        }
    }
}

void CSpriteList::DeleteAllSprite(bool bDeletelmage)
{
    SpriteStruct* pPtr=NULL;
    SpriteStruct* pPtrhNext=m_pListHeader;
    while (NULL!=pPtrhNext)
    {
        pPtr=pPtrhNext;
        pPtrhNext=pPtrhNext->pNext;
        if (bDeletelmage)
            pPtr->pSprite->DeleteSprite();
        delete pPtr;
    }
    m_pListHeader=NULL;
    m_iListSize=0;
}







