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

#include "stdafx.h"
#include "TutorialApplication.h"

using namespace Ogre;

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
	// 종료 플래그
	mShutDown = false;

	// player 1,2 좌표설정
	player1Position = Vector3(-1000, 0, 0);
	player2Position = Vector3(1000, 0, 0);

	mP1Direction = Vector3(0, 0, 0);
	mP2Direction = Vector3(0, 0, 0);

	mSpeed = 400.0f;
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke) {
	
	if (ke.key == OIS::KC_W) mP1Direction.z = -1.0f;
	if (ke.key == OIS::KC_S) mP1Direction.z = 1.0f;
	if (ke.key == OIS::KC_UP) mP2Direction.z = -1.0f;
	if (ke.key == OIS::KC_DOWN) mP2Direction.z = 1.0f;
	if (ke.key == OIS::KC_ESCAPE) mShutDown = true;

	return true;
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke) {
	if(ke.key == OIS::KC_W && mP1Direction.z == -1.0f) mP1Direction = 0;
	else if(ke.key == OIS::KC_S && mP1Direction.z == 1.0f) mP1Direction = 0;
	if (ke.key == OIS::KC_UP && mP2Direction.z == -1.0f) mP2Direction = 0;
	else if (ke.key == OIS::KC_DOWN  && mP2Direction.z == 1.0f) mP2Direction = 0;
	return true;
}

void TutorialApplication::CollisionDetect(Real &move) {

	//
	if (player1Node->getPosition().z > 700) player1Node->setPosition(Vector3(player1Node->getPosition().x, player1Node->getPosition().y, player1Node->getPosition().z - 1));
	else if (player1Node->getPosition().z < -700) player1Node->setPosition(Vector3(player1Node->getPosition().x, player1Node->getPosition().y, player1Node->getPosition().z + 1));
	else player1Node->translate(mMove * mP1Direction);

	if (player2Node->getPosition().z > 700) player2Node->setPosition(Vector3(player2Node->getPosition().x, player2Node->getPosition().y, player2Node->getPosition().z - 1));
	else if (player2Node->getPosition().z < -700) player2Node->setPosition(Vector3(player2Node->getPosition().x, player2Node->getPosition().y, player2Node->getPosition().z + 1));
	else player2Node->translate(mMove * mP2Direction);
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	bool ret = BaseApplication::frameRenderingQueued(evt);

	mMove = mSpeed * evt.timeSinceLastFrame;

	if (mKeyboard->isKeyDown(OIS::KC_SPACE)) mIsStarted = true;

	if (!mIsStarted) return ret;

	if (!processUnbufferedInput(evt)) return false;
	if (mShutDown) return false;

	mMouse->capture();
	mKeyboard->capture();

	CollisionDetect(mMove);
	
	//mSceneMgr->getSceneNode("Player1Node")->translate(player1Move * evt.timeSinceLastFrame, Node::TS_LOCAL);
	//mSceneMgr->getSceneNode("Player2Node")->translate(player2Move * evt.timeSinceLastFrame, Node::TS_LOCAL);

	return ret;
}

bool TutorialApplication::Moving(){
	return true;
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& evt) {
	static bool mMouseDown = false;
	static Ogre::Real mToggle = 0.0;
	static Ogre::Real mRotate = 0.13;
	static Ogre::Real mMove = 250;

	
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

	//Create a light 	 
	Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(300, 300, 300);

	//Change a camera's position 
	mCamera->setPosition(-800, 1400, 2400);
	mCamera->lookAt(Vector3(0, 0, -20));

	//Ball Creating
	sphereEnt = mSceneMgr->createEntity("MySphere", Ogre::SceneManager::PT_SPHERE);
	sphereEnt->setMaterialName("BaseBlueLighting");
	sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	sphereNode->setScale(0.5f, 0.5f, 0.5f);
	sphereNode->setPosition(0, 0, 0);
	sphereNode->attachObject(sphereEnt);

	//Player1 Creating
	player1 = mSceneMgr->createEntity("Player1", SceneManager::PT_CUBE);
	player1->setMaterialName("BaseWhiteLighting");
	player1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Player1Node");
	player1Node->scale(0.5f, 1.0f, 2.0f);
	player1Node->setPosition(player1Position.x, player1Position.y, player1Position.z);
	player1Node->attachObject(player1);

	//Player2 Creating
	player2 = mSceneMgr->createEntity("Player2", SceneManager::PT_CUBE);
	player2->setMaterialName("BaseWhiteLighting");
	player2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Player2Node");
	player2Node->scale(0.5f, 1.0f, 2.0f);
	player2Node->setPosition(player2Position.x, player2Position.y, player2Position.z);
	player2Node->attachObject(player2);

	Entity* downWall = mSceneMgr->createEntity("downWall", SceneManager::PT_CUBE);
	downWall->setMaterialName("BaseWhiteLighting");
	SceneNode* downWallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	downWallNode->scale(25.0f, 1.0f, 0.2f);
	downWallNode->setPosition(0, 0, 800);
	downWallNode->attachObject(downWall);

	Entity* upWall = mSceneMgr->createEntity("upWall", SceneManager::PT_CUBE);
	upWall->setMaterialName("BaseWhiteLighting");
	SceneNode* upWallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
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
