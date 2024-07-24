#include "CBullet.h"
#include "CGameSprite.h"
#include "LessonX.h"
CBullet::CBullet(const int iType,const char* szName):CGameSprite(szName)
{
    //ctor
    m_iType=iType;
}

CBullet::~CBullet()
{
    //dtor
}

bool CBullet::IsMyBullet()
{
    m_iType=GetType();
    if (m_iType==0)
        return true;
    else
        return false;
}

void CBullet::OnColOtherSprite(CGameSprite* pOther)
{
   if (NULL==pOther)
   {
       return ;
   }
   if (IsMyBullet())
   {
       if (pOther->IsMyFighter())
           return ;
       SetHp(GetHp()- pOther->GetDamage());
       g_GameMain.m_pSmallExplosion->PlayEffect(pOther->GetSpritePositionX(),pOther->GetSpritePositionY(),0.f);
   }
   else
   {
       if (pOther->IsMyFighter()||pOther->IsMyBullet())
       {
           SetHp(GetHp()- pOther->GetDamage());
           g_GameMain.m_pSmallExplosion->PlayEffect(pOther->GetSpritePositionX(),pOther->GetSpritePositionY(),0.f);
       }
   }
}



