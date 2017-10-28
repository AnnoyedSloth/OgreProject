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

#include "TutorialApplication.h"

using namespace Ogre;

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke) {
//
//	switch (ke.key) {
//	case OIS::KC_UP:
//	case OIS::KC_W:
//		mDirection.z = -mMove;
//		break;
//	case OIS::KC_DOWN:
//	case OIS::KC_S:
//		mDirection.z = mMove;
//		break;
//	case OIS::KC_LEFT:
//	case OIS::KC_A:
//		mDirection.x = -mMove;
//		break;
//	case OIS::KC_RIGHT:
//	case OIS::KC_D:
//		mDirection.x = mMove;
//		break;
//	case OIS::KC_PGDOWN:
//	case OIS::KC_E:
//		mDirection.y = -mMove;
//		break;
//	case OIS::KC_PGUP:
//	case OIS::KC_Q:
//		mDirection.y = mMove;
//		break;
//	default:
//		break;
//
//	}
//
//	return true;
//}
//bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke) {
//	switch (ke.key) {
//	case OIS::KC_UP: case OIS::KC_W:
//		mDirection.z = 0;
//		break;
//	case OIS::KC_DOWN: case OIS::KC_S:
//		mDirection.z = 0;
//		break;
//	case OIS::KC_LEFT: case OIS::KC_A:
//		mDirection.x = 0;
//		break;
//	case OIS::KC_RIGHT: case OIS::KC_D:
//		mDirection.x = 0;
//		break;
//	case OIS::KC_PGDOWN: case OIS::KC_E:
//		mDirection.y = 0;
//		break;
//	case OIS::KC_PGUP: case OIS::KC_Q:
//		mDirection.y = 0;
//		break;
//	default:
//		break;
//	}
//
//	return true;
//}

//bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt) {
//
//	bool ret = BaseApplication::frameRenderingQueued(evt);
//
//	mCamNode->translate(mDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
//
//	if (!processUnbufferedInput(evt)) return false;
//
//	mMouse->getMouseState().buttonDown(OIS::MB_Left);
//	mKeyboard->isKeyDown(OIS::KC_SPACE);
//
//	return ret;
//
//}

//bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& evt) {
//	static bool mMouseDown = false;
//	static Ogre::Real mToggle = 0.0;
//	static Ogre::Real mRotate = 0.13;
//	static Ogre::Real mMove = 250;
//
//	bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);
//
//	if (currMouse && !mMouseDown) {
//		Ogre::Light* light = mSceneMgr->getLight("Light1");
//		light->setVisible(!light->isVisible());
//	}
//
//	mMouseDown = currMouse;
//	mToggle -= evt.timeSinceLastFrame;
//
//	if ((mToggle < 0.0f) && mMouse->getMouseState().buttonDown(OIS::MB_Right)) {
//		mToggle = 0.5;
//		Ogre::Light* light = mSceneMgr->getLight("Light1");
//		light->setVisible(!light->isVisible());
//	}
//
//	return true;
//}


void TutorialApplication::createColourCube() {
	MeshPtr msh = MeshManager::getSingleton().createManual("ColourCube", "General");

	SubMesh* sub = msh->createSubMesh();

	const float sqrt13 = 0.577350269f;

	const size_t nVertices = 8;
	const size_t vbufCount = 3 * 2 * nVertices;
	float vertices[vbufCount] =
	{ -100.0,100.0,-100.0,        // 0 position 
	  -sqrt13,sqrt13,-sqrt13,     // 0 normal
	  100.0,100.0,-100.0,         // 1 position
		sqrt13,sqrt13,-sqrt13,    // 1 normal
		100.0,-100.0,-100.0,      // 2 position
		sqrt13,-sqrt13,-sqrt13,   // 2 normal
		-100.0,-100.0,-100.0,     // 3 position
		-sqrt13,-sqrt13,-sqrt13,  // 3 normal
		-100.0,100.0,100.0,       // 4 position
		-sqrt13,sqrt13,sqrt13,    // 4 normal
		100.0,100.0,100.0,        // 5 position
		sqrt13,sqrt13,sqrt13,     // 5 normal
		100.0,-100.0,100.0,       // 6 position
		sqrt13,-sqrt13,sqrt13,    // 6 normal
		-100.0,-100.0,100.0,      // 7 position
		-sqrt13,-sqrt13,sqrt13,   // 7 normal
	};

	const size_t ibufCount = 36;
	unsigned short faces[ibufCount] = {
		0,2,3,
		0,1,2,
		1,6,2,
		1,5,6,
		4,5,6,
		4,7,6,
		0,7,4,
		0,3,7,
		0,5,1,
		0,4,5,
		2,7,3,
		2,6,7 };

	msh->sharedVertexData = new VertexData();
	msh->sharedVertexData->vertexCount = nVertices;

	VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	//Create a sphere from OGRE PrefabType 
	// A material must be assigned for each object 
	// Create a sphere 

	//Set ambient light 
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	//Create a light 	 
	Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(300, 300, 300);

	//Change a camera's position 
	mCamera->setPosition(0, 0, 500);
	//Create a colored cube
	createColourCube();

	//Ogre::Entity* sphereEnt = mSceneMgr->createEntity("MySphere", Ogre::SceneManager::PT_SPHERE);
	//sphereEnt->setMaterialName("BaseWhiteLighting");
	//Ogre::SceneNode *sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//sphereNode->setScale(0.5f, 0.5f, 0.5f);
	//sphereNode->attachObject(sphereEnt);

	////Create a plane 
	//Ogre::Entity* planeEnt = mSceneMgr->createEntity("MyPlane", Ogre::SceneManager::PT_CUBE);
	//planeEnt->setMaterialName("BaseWhiteLighting");
	//Ogre::SceneNode *planeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	////planeNode->pitch(Ogre::Degree(-70));
	//planeNode->setPosition(-200, 0, -500); planeNode->attachObject(planeEnt);
	////Create a cube 
	//Ogre::Entity* cubeEnt = mSceneMgr->createEntity("MyCube", Ogre::SceneManager::PT_CUBE);
	//cubeEnt->setMaterialName("BaseWhiteLighting");
	//Ogre::SceneNode* cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//cubeNode->setPosition(200, 0, -500);
	//cubeNode->setScale(1.0f, 1.0f, 1.0f);
	//cubeNode->attachObject(cubeEnt);

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
