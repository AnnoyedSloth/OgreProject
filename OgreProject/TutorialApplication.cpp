/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
	  |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/
#include<string>
#include "stdafx.h"
#include "TutorialApplication.h"



using namespace Ogre;

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void) : mInfoLabel(0)
{
	// 종료 플래그
	mShutDown = false;

	// player 1,2 좌표설정
	player1Position = Vector3(-1000, 0, 0);
	player2Position = Vector3(1000, 0, 0);

	mP1Direction = Vector3(0, 0, 0);
	mP2Direction = Vector3(0, 0, 0);
	mBallDirection = Vector3(0, 0, 0);

	mPaddleSpeed = 1000.0f;
	mBallSpeed = 1000.0f;

	mP1Score = 0;
	mP2Score = 0;

	//
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

void TutorialApplication::createFrameListener(void) {
	BaseApplication::createFrameListener();

	mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TInfo", "Press Spacebar to start game", 350);
}

bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke) {

	if (ke.key == OIS::KC_W) {
		mP1Direction.z = -1.0f; mP1Skill = true;
	}
	if (ke.key == OIS::KC_S) {
		mP1Direction.z = 1.0f; mP1Skill = true;
	}
	if (ke.key == OIS::KC_UP) {
		mP2Direction.z = -1.0f; mP2Skill = true;
	}
	if (ke.key == OIS::KC_DOWN) {
		mP2Direction.z = 1.0f; mP2Skill = true;
	}
	if (ke.key == OIS::KC_ESCAPE) mShutDown = true;

	return true;
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke) {
	if (ke.key == OIS::KC_W && mP1Direction.z == -1.0f) {
		mP1Direction = 0;
		mP1Skill = false;
	}
	else if (ke.key == OIS::KC_S && mP1Direction.z == 1.0f) {
		mP1Direction = 0;
		mP1Skill = false;
	}
	if (ke.key == OIS::KC_UP && mP2Direction.z == -1.0f) {
		mP2Direction = 0;
		mP2Skill = false;
	}
	else if (ke.key == OIS::KC_DOWN  && mP2Direction.z == 1.0f) {
		mP2Direction = 0;
		mP2Skill = false;
	}
	return true;
}

void TutorialApplication::SetScore() {
	String score;
	score = std::to_string(mP1Score) + "        :        " + std::to_string(mP2Score);
	mInfoLabel->setCaption(score);
}

void TutorialApplication::PaddleMove(Real &move) {

	//Restricting the position of Player1
	//1st row : checking vertical axis 
	if (player1Node->getPosition().z > RESTRICT_AREA) player1Node->setPosition(Vector3(player1Node->getPosition().x, player1Node->getPosition().y, player1Node->getPosition().z - 1));
	else if (player1Node->getPosition().z < -RESTRICT_AREA) player1Node->setPosition(Vector3(player1Node->getPosition().x, player1Node->getPosition().y, player1Node->getPosition().z + 1));
	else player1Node->translate(move * mP1Direction);

	//Restricting the position of Player2
	if (player2Node->getPosition().z > RESTRICT_AREA) player2Node->setPosition(Vector3(player2Node->getPosition().x, player2Node->getPosition().y, player2Node->getPosition().z - 1));
	else if (player2Node->getPosition().z < -RESTRICT_AREA) player2Node->setPosition(Vector3(player2Node->getPosition().x, player2Node->getPosition().y, player2Node->getPosition().z + 1));
	else player2Node->translate(move * mP2Direction);
}

void TutorialApplication::BallMove(Real &move) {
	BallCollapse(move);
	ballNode->translate(move * mBallDirection);
}

void TutorialApplication::BallCollapse(Real &move) {
	// Player1 - Ball collapsing
	if ((player1Node->getPosition().x + BALL_RADIUS > ballNode->getPosition().x) &&
		(player1Node->getPosition().x - BALL_RADIUS < ballNode->getPosition().x) &&
		(ballNode->getPosition().z > player1Node->getPosition().z - PLAYER_SIZE / 2) &&
		(ballNode->getPosition().z < player1Node->getPosition().z + PLAYER_SIZE / 2))
	{
		if ((mP1Direction.z == -1.0f && mBallDirection.z < 0) ||
			(mP1Direction.z == 1.0f && mBallDirection.z > 0)) {
			mBallDirection *= Vector3(-1, 0, 0.8f);
		}
		else if ((mP1Direction.z == -1.0f && mBallDirection.z > 0) ||
			(mP1Direction.z == 1.0f && mBallDirection.z < 0)) {
			mBallDirection *= Vector3(-1.2f, 0, -1);
		}
		else mBallDirection *= Vector3(-1, 0, -1);
	}

	// Player2 - Ball collapsing
	if ((player2Node->getPosition().x - BALL_RADIUS < ballNode->getPosition().x) &&
		(player2Node->getPosition().x + BALL_RADIUS > ballNode->getPosition().x) &&
		(ballNode->getPosition().z > player2Node->getPosition().z - PLAYER_SIZE / 2) &&
		(ballNode->getPosition().z < player2Node->getPosition().z + PLAYER_SIZE / 2))
	{
		if ((mP2Direction.z == -1.0f && mBallDirection.z < 0) ||
			(mP2Direction.z == 1.0f && mBallDirection.z > 0)) {
			mBallDirection *= Vector3(-1, 0, 0.8f);
		}
		else if ((mP2Direction.z == -1.0f && mBallDirection.z > 0) ||
			(mP2Direction.z == 1.0f && mBallDirection.z < 0)) {
			mBallDirection *= Vector3(-1.2f, 0, -1);
		}
		else mBallDirection *= Vector3(-1, 0, -1);
	}

	// Ball - Upperwall collapsing
	if ((ballNode->getPosition().z < upWallNode->getPosition().z) &&
		(ballNode->getPosition().x > upWallNode->getPosition().x - WALL_WIDTH / 2) &&
		(ballNode->getPosition().x < upWallNode->getPosition().x + WALL_WIDTH / 2)) mBallDirection *= Vector3(1, 0, -1);
	// Ball - Downwall collapsing
	if ((ballNode->getPosition().z > downWallNode->getPosition().z) &&
		(ballNode->getPosition().x > downWallNode->getPosition().x - WALL_WIDTH / 2) &&
		(ballNode->getPosition().x < downWallNode->getPosition().x + WALL_WIDTH / 2))
		mBallDirection *= Vector3(1, 0, -1);

}

void TutorialApplication::Reset() {
	mIsStarted = false;
	player1Node->setPosition(-1000, 0, 0);
	player2Node->setPosition(1000, 0, 0);
	ballNode->setPosition(Vector3(0, 0, 0));
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	bool ret = BaseApplication::frameRenderingQueued(evt);

	//mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
	//mInfoLabel->show();
	//mInfoLabel->setCaption("Hello World!");

	mPaddleMove = mPaddleSpeed * evt.timeSinceLastFrame;
	mBallMove = mBallSpeed * evt.timeSinceLastEvent;

	if (mKeyboard->isKeyDown(OIS::KC_SPACE)) {
		srand(time(NULL));
		float randNum = std::sin(rand() % 60);
		float startDirection = ((rand() % 2) - 0.5f) * 2;
		mIsStarted = true;
		SetScore();
		mBallDirection = Vector3(1-randNum, 0, randNum);
		mBallDirection.normalise();
		mBallDirection *= startDirection;
	}
	if (mKeyboard->isKeyDown(OIS::KC_R)) {
		mP1Score = 0;
		mP2Score = 0;
		Reset();
		SetScore();
	}

	if (!processUnbufferedInput(evt)) return false;
	if (mShutDown) return false;

	mMouse->capture();
	mKeyboard->capture();

	if (mP1Score > 2 || mP2Score > 2) {
		Reset();
		mInfoLabel->setCaption("GameOver press R to reset game");
	}
	else
	{
		if (mIsStarted == true) {
			PaddleMove(mPaddleMove);
			BallMove(mBallMove);
			if (ballNode->getPosition().x > WALL_WIDTH / 2) {
				Reset();
				mP1Score++;
				SetScore();
			}
			else if (ballNode->getPosition().x < -WALL_WIDTH / 2) {
				Reset();
				mP2Score++;
				SetScore();
			}

			mCamera->lookAt(Vector3(0, 0, 0));
		}
	}


	return ret;
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& evt) {
	static bool mMouseDown = false;
	static Ogre::Real mToggle = 0.0;
	static Ogre::Real mRotate = 0.13;
	static Ogre::Real mPaddleMove = 250;

	//bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);

	//mMouseDown = currMouse;
	mToggle -= evt.timeSinceLastFrame;

	//mSceneMgr->getSceneNode("Player1Node")->translate(player1Position * evt.timeSinceLastFrame, Node::TS_LOCAL);

	return true;
}


//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	//Create a sphere from OGRE PrefabType 
	// A material must be assigned for each object 
	// Create a sphere 

	//Set ambient light 
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
	ParticleSystem* sunParticle = mSceneMgr->createParticleSystem("Sun", "Space/Sun");
	SceneNode* particleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Particle");
	particleNode->attachObject(sunParticle);
	particleNode->setPosition(-800, 600, -800);

	//Create a light 	 
	Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(300, 300, 300);

	//Change a camera's position 
	mCamera->setPosition(-800, 1400, 2400);
	mCamera->lookAt(Vector3(0, 0, -20));

	//Ball Creating
	ballEnt = mSceneMgr->createEntity("MyBall", "ogrehead.mesh");
	ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ballNode->setScale(1, 1, 1);
	ballNode->setPosition(0, 0, 0);
	ballNode->attachObject(ballEnt);

	//Player1 Creating
	player1 = mSceneMgr->createEntity("Player1", SceneManager::PT_CUBE);
	player1->setMaterialName("BaseWhiteLighting");
	player1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Player1Node");
	player1Node->scale(0.5f, 1.0f, 2.0f);
	player1Node->setPosition(player1Position);
	player1Node->attachObject(player1);

	//Player2 Creating
	player2 = mSceneMgr->createEntity("Player2", SceneManager::PT_CUBE);
	player2->setMaterialName("BaseWhiteLighting");
	player2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Player2Node");
	player2Node->scale(0.5f, 1.0f, 2.0f);
	player2Node->setPosition(player2Position);
	player2Node->attachObject(player2);

	downWall = mSceneMgr->createEntity("downWall", SceneManager::PT_CUBE);
	downWall->setMaterialName("BaseWhiteLighting");
	downWallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	downWallNode->scale(25.0f, 1.0f, 0.2f);
	downWallNode->setPosition(0, 0, 800);
	downWallNode->attachObject(downWall);

	upWall = mSceneMgr->createEntity("upWall", SceneManager::PT_CUBE);
	upWall->setMaterialName("BaseWhiteLighting");
	upWallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	upWallNode->scale(25.0f, 1.0f, 0.2f);
	upWallNode->setPosition(0, 0, -800);
	upWallNode->attachObject(upWall);
	//Ogre::Mesh* mMesh = Ogre::MeshManager::getSingleton().createManual()

}
//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		TutorialApplication app;

		try {
			app.go();
		}
		catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			//MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occurred: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
