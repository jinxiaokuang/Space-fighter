#include "CEnemyFighter.h"
#include "stdio.h"
#include "CommonClass.h"
#include "LessonX.h"
#include "CGameSprite.h"

CEnemyFighter::CEnemyFighter(const char* szName): CGameSprite(szName)
{
    //ctor
    m_fCanFileAfterCreated  =3.f;
    m_fBulletCreateTime     =1.f;
    m_fFloatTime            =0.f;
    m_bFloatUp              =true;
}

CEnemyFighter::~CEnemyFighter()
{
    //dtor
}

void CEnemyFighter::ClassTick ( float fDeltaTime )
{
     m_fCreateTime-=fDeltaTime ;
     if (m_fCreateTime<=0.f)
     {
         m_fCreateTime =(float)CSystem::RandomRange(5,10);
         int iPosBase = CSystem::RandomRange((int)CSystem::GetScreenTop()+10,(int)CSystem::GetScreenBottom()-10);
         char szName[MAX_NAME_LEN];
         sprintf(szName,"HorizontalSprite_%d", m_iCreatedSpriteCount);
         m_iCreatedSpriteCount++;
         CEnemyFighter* pSprite = new CEnemyFighter (szName );
         pSprite->CloneSprite ("HorizontalSprite_Template");
         g_GameMain.AddSprite(pSprite);
         int iRandom = CSystem::RandomRange (iPosBase-10, iPosBase+10);
         float fPosX =(int)CSystem::GetScreenRight()+20.f;
         pSprite->SetSpritePosition(fPosX ,(float)iRandom );
         pSprite->SetSpriteLinearVelocityX(-10.f);
         pSprite->SetSpriteWorldLimit(WORLD_LIMIT_NULL,CSystem::GetScreenLeft()-10.f, CSystem::GetScreenTop(), CSystem::GetScreenRight()+200.f, CSystem::GetScreenBottom());
         pSprite->SetSpriteCollisionActive(true,true);
         pSprite->SetHp(300);
         pSprite->SetScore(100);
         pSprite->SetType(true);
     }
}

void CEnemyFighter::LoopTick(float fDeltaTime)
{
    m_fCanFileAfterCreated-=fDeltaTime;
    if (m_fCanFileAfterCreated<=0.f)
    {
        m_fBulletCreateTime-=fDeltaTime;
        if (m_fBulletCreateTime<=0.f)
        {
            m_fBulletCreateTime=1.f;
            g_GameMain.CreateBullet(1,GetSpritePositionX(),GetSpritePositionY());
        }
    }
    if (m_bFloatUp)
    {
        m_fFloatTime+=fDeltaTime;
        if (m_fFloatTime>=1.f)
        {
            m_bFloatUp=false;
        }
        float fPosY=GetSpritePositionY();
        fPosY+=6.f*fDeltaTime;
        SetSpritePositionY(fPosY);
    }
    else
    {
        m_fFloatTime-=fDeltaTime;
        if (m_fFloatTime<=0.f)
        {
            m_bFloatUp=true;
        }
        float fPosY=GetSpritePositionY();
        fPosY-=6.f*fDeltaTime;
        SetSpritePositionY(fPosY);
    }
}

void CEnemyFighter::OnColOtherSprite(CGameSprite* pOther)
{
    if (NULL==pOther)
        return ;
    if (pOther->IsMyFighter()||pOther->IsMyBullet())
    {
        SetHp(GetHp()- pOther->GetDamage());
        if (IsDead())
        {
            g_GameMain.GetMyFighter()->SetScore(g_GameMain.GetMyFighter()->GetScore()+GetScore());
            g_GameMain.m_penemyExplode->PlayEffect(pOther->GetSpritePositionX(),pOther->GetSpritePositionY(),0.f);
        }
    }
}






