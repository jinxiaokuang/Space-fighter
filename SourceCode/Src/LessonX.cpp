#include <Stdio.h>
#include <fstream>
#include "CommonClass.h"
#include "LessonX.h"
#include "CBullet.h"
#include "CEnemyFighter.h"
#include "CGameSprite.h"
using namespace std;
CGameMain		g_GameMain;

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。
// 构造函数
CGameMain::CGameMain()
{
	//
	m_pBeginSprite  = new CGameSprite("GameBegin");
	m_pCurScoreText = new CTextSprite("CurScoreText");
	m_pMaxScoreText = new CTextSprite("MaxScoreText");
	m_pSmallExplosion  = new CEffect("SmallExplosion","SmallExplosionPro",1.f);
	m_pPlayerExplode   = new CEffect("PlayerExplode","PlayerExplodePro",1.f);
	m_penemyExplode    = new CEffect("enemyExplode","enemyExplodePro",1.f);
    m_pMyFighter    = NULL;
    m_iMaxScore     = 0;
    m_iGameState    = 0;
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
    delete m_pMyFighter;
    m_pMyFighter=NULL;
}
//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态.
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop(float	fDeltaTime)
{
	switch(GetGameState())
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
	{
		GameInit();
		SetGameState(2); // 初始化之后，将游戏状态设置为进行中
	}
	break;

	// 游戏进行中，处理各种游戏逻辑
	case 2:
	{
		// TODO 修改此处游戏循环条件，完成正确游戏逻辑
		if (!IsGameLost())
		{
			GameRun(fDeltaTime);
		}
		else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
		{
			SetGameState(0);
			GameEnd();
		}
	}
	break;
	// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
void CGameMain::GameInit()
{
    m_pBeginSprite->SetSpriteVisible(false);
    m_pCurScoreText->SetTextValue(0);
    m_pMaxScoreText->SetTextValue(0);
    m_pMyFighter=NULL;
    if (NULL==m_pMyFighter)
    {
        m_pMyFighter=new CMyFighter("ControlSprite");
        m_pMyFighter->SetSpriteVisible(true);
        m_pMyFighter->SetSpriteColorGreen(255);
        m_pMyFighter->SetSpriteColorBlue(255);
        m_pMyFighter->SetSpritePosition(CSystem::GetScreenLeft()+5.f,0.f);
        m_pMyFighter->SetSpriteWorldLimit(WORLD_LIMIT_STICKY,CSystem::GetScreenLeft()-10.f,CSystem::GetScreenTop(),CSystem::GetScreenRight(),CSystem::GetScreenBottom());
    }
    m_pMyFighter->SetHp(500);
    m_pMyFighter->SetScore(0);
    m_pMyFighter->SetCanFile(true);
    fstream ScoreFile("Score.dat",fstream::in|fstream::binary);
    if (ScoreFile.is_open())
    {
        ScoreFile>>m_iMaxScore;
        ScoreFile.close();
    }
    m_pMaxScoreText->SetTextValue(m_iMaxScore);
}
//=============================================================================
// 每局游戏进行中
void CGameMain::GameRun(float fDeltaTime)
{
    if (m_pMyFighter)
    {
        m_pMyFighter->OnFile(fDeltaTime);
    }
    CEnemyFighter::ClassTick(fDeltaTime);
    int iListSize=m_SpriteList.GetListSize();
    for (int iLoop=0;iLoop<iListSize;iLoop++)
    {
        CGameSprite* pSprite=m_SpriteList.GetSprite(iLoop);
        if (pSprite!=NULL&&(strstr(pSprite->GetName(),"HorizontalSprite")!=NULL))
        {
            ((CEnemyFighter*)pSprite)->LoopTick(fDeltaTime);
        }
    }
    m_pCurScoreText->SetTextValue(m_pMyFighter->GetScore());
}
//=============================================================================
// 本局游戏结束
void CGameMain::GameEnd()
{
    m_pBeginSprite->SetSpriteVisible(true);
    m_SpriteList.DeleteAllSprite(true);
    m_pMyFighter->SetSpriteVisible(false);
    if (m_iMaxScore>GetMyFighter()->GetScore())
    {
        m_iMaxScore=GetMyFighter()->GetScore();
        fstream ScoreFile("Score.dat",fstream::out|fstream::binary);
        if (ScoreFile.is_open())
        {
            ScoreFile<<m_iMaxScore;
            ScoreFile.close();
        }
    }
    delete m_pMyFighter;
    m_pMyFighter=NULL;
    SetGameState(0);
}

void CGameMain::OnSpriteColWorldLimit(const char* szName, const int iColSide)
{

}

void CGameMain::CreateBullet(int iType,const float fPosX,const float fPosY)
{
    char szName[MAX_NAME_LEN];
    sprintf(szName,"Bullet1_%d",m_iCreatedSpriteCount);
    m_iCreatedSpriteCount++;
    CBullet* pBullet =new CBullet(iType,szName);
    pBullet->CloneSprite("Bullet1_Template");
    pBullet->SetSpritePosition(fPosX,fPosY);
    pBullet->SetSpriteLinearVelocityX(60);
    pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL,CSystem::GetScreenLeft()-10.f,CSystem::GetScreenTop(),CSystem::GetScreenRight()+200.f,CSystem::GetScreenBottom());
    if (1==iType)
    {
        pBullet->SetSpriteLinearVelocityX(-30);
    }
    else
    {
        pBullet->SetSpriteFlipX(true);
        pBullet->SetSpriteLinearVelocityX(60);
    }
    pBullet->SetScore(100);
    pBullet->SetHp(10);
    pBullet->SetDamage(100);
    pBullet->SetType(iType);
    pBullet->SetSpriteCollisionActive(true,true);
    AddSprite(pBullet);
}
void CGameMain::AddSprite(CGameSprite* pSprite)
{
    m_SpriteList.AddSprite(pSprite);
}

CGameSprite* CGameMain::GetSprite(const int ilndex)
{
    return m_SpriteList.GetSprite(ilndex);
}

CGameSprite* CGameMain::GetSprite(const char* szName)
{
    return m_SpriteList.GetSprite(szName);
}

CMyFighter* CGameMain::GetMyFighter()
{
    if (NULL!=m_pMyFighter)
    {
        return m_pMyFighter;
    }
    else return NULL;
}

bool CGameMain::IsMyFighter(const char* szName)
{
    return (strcmp(m_pMyFighter->GetName(),szName)==0);
}

void CGameMain::OnSpriteColSprite(const char* szSrcName,const char* szTarName)
{
    if (2!=GetGameState())
        return ;
    CGameSprite* pSrcSprite=IsMyFighter(szSrcName)?m_pMyFighter:GetSprite(szSrcName);
    CGameSprite* pTarSprite=IsMyFighter(szTarName)?m_pMyFighter:GetSprite(szTarName);
    if (NULL==pSrcSprite||NULL==pTarSprite)
        return ;
    pSrcSprite->OnColOtherSprite(pTarSprite);
    pTarSprite->OnColOtherSprite(pSrcSprite);
    if (!pSrcSprite->IsMyFighter())
    {
        if (pSrcSprite->IsDead())
            m_SpriteList.DeleteSprite(pSrcSprite,true);
    }
    if (!pTarSprite->IsMyFighter())
    {
        if (pTarSprite->IsDead())
            m_SpriteList.DeleteSprite(pTarSprite,true);
    }
}

bool CGameMain::IsGameLost()
{
    return (m_pMyFighter?m_pMyFighter->IsDead():false);
}
void CGameMain::OnKeyDown(const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress)
{
    if (KEY_SPACE ==iKey&&0==GetGameState())
    {
        SetGameState(1);
    }
    if (2==GetGameState())
    {
        m_pMyFighter->OnMove(true,iKey);
        if (KEY_SPACE==iKey&&NULL!=m_pMyFighter)
    {
        m_pMyFighter->SetCanFile(true);
    }
    }

}
void CGameMain::OnKeyUp(const int iKey)
{
    if (2==GetGameState())
    {
        m_pMyFighter->OnMove(false,iKey);
        if (KEY_SPACE==iKey&&NULL!=m_pMyFighter)
    {
        m_pMyFighter->SetCanFile(false);
    }
    }

}

float CEnemyFighter::m_fCreateTime         = 0.f;
int   CEnemyFighter::m_iCreatedSpriteCount = 0;
