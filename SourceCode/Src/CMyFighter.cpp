#include "CMyFighter.h"
#include "LessonX.h"
#include "CBullet.h"
#include "CGameSprite.h"
CMyFighter::CMyFighter(const char* szName): CGameSprite(szName)
{
    //ctor
    m_fVelocityLeft     =0.f;
    m_fVelocityRight    =0.f;
    m_fVelocityUp       =0.f;
    m_fVelocityDown     =0.f;
    m_fBulletCreateTime =0.3;
}

CMyFighter::~CMyFighter()
{
    //dtor
}
void CMyFighter::OnMove(bool bKeyDown,int iKey)
{
    if (bKeyDown)
    {
        switch(iKey)
        {
        case KEY_A:
            m_fVelocityLeft=30.f;
            break;
        case KEY_D:
            m_fVelocityRight=30.f;
            break;
        case KEY_W:
            m_fVelocityDown=15.f;
            break;
        case KEY_S:
            m_fVelocityUp=15.f;
            break;
        }
    }
    else
    {
        switch(iKey)
        {
            case KEY_A:
            m_fVelocityLeft=0.f;
            break;
        case KEY_D:
            m_fVelocityRight=0.f;
            break;
        case KEY_W:
            m_fVelocityDown=0.f;
            break;
        case KEY_S:
            m_fVelocityUp=0.f;
            break;
        }
    }
    float fVelX=m_fVelocityRight-m_fVelocityLeft;
    float fVelY=m_fVelocityUp-m_fVelocityDown;
    SetSpriteLinearVelocity(fVelX,fVelY);
}

void CMyFighter::OnFile(float fDeltaTime)
{
    m_fBulletCreateTime-=fDeltaTime;
    if (m_fBulletCreateTime<=0.f&&m_bCanFile)
    {
        m_fBulletCreateTime=0.3f;
        g_GameMain.CreateBullet(0,GetSpritePositionX(),GetSpritePositionY());
    }
}

void CMyFighter::OnColOtherSprite(CGameSprite* pOther)
{
    if (NULL==pOther)
        return ;
    if (pOther->IsMyBullet())
        return ;
    SetHp(GetHp()-pOther->GetDamage());
    if (GetHp()<0)
    {
        g_GameMain.m_pPlayerExplode->PlayEffect(pOther->GetSpritePositionX(),pOther->GetSpritePositionY(),0.f);
    }
    if (GetHp()<=200)
    {
        SetSpriteColorGreen(0);
        SetSpriteColorBlue(0);
    }
    else if (GetHp()<=500)
    {
        SetSpriteColorGreen(128);
        SetSpriteColorBlue(128);
    }
    else
    {
        SetSpriteColorGreen(255);
        SetSpriteColorBlue(255);
    }
    g_GameMain.GetMyFighter()->SetScore(g_GameMain.GetMyFighter()->GetScore()+pOther->GetScore());
}


