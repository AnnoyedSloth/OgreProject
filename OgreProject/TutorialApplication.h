/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
public:
	//TutorialApplication(void) : mRotate(13), mMove(250), mCamNode(0), mDirection(Ogre::Vector3::ZERO) {};
	TutorialApplication();
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
	//virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	//virtual bool keyPressed(const OIS::KeyEvent& ke);
	//virtual bool keyReleased(const OIS::KeyEvent& ke);

	void createColourCube();

	Ogre::Real mRotate;
	Ogre::Real mMove;
	Ogre::SceneNode* mCamNode;
	Ogre::Vector3 mDirection;


private:
	//bool processUnbufferedInput(const Ogre::FrameEvent& evt);
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------