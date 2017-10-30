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
using namespace Ogre;

//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication();
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);


	//void createColourCube();
	//Players Entities, Nodes
	Entity* ballEnt;
	SceneNode *ballNode;
	Entity* player1;
	SceneNode *player1Node;
	Entity* player2;
	SceneNode *player2Node;

	//Objects Entities, Nodes
	Entity* downWall;
	SceneNode* downWallNode;
	Entity* upWall;
	SceneNode* upWallNode;

	Real mRotate;
	Real mPaddleMove;
	Real mPaddleSpeed;
	Real mBallMove;
	Real mBallSpeed;
	SceneNode* mCamNode;
	Vector3 mP1Direction;
	Vector3 mP2Direction;
	Vector3 mBallDirection;

	Vector3 player1Position;						   
	Vector3 player2Position;

	void BallMove(Real &move);
	void PaddleMove(Real &move);
	void BallCollapse(Real &move);
private:
	bool processUnbufferedInput(const Ogre::FrameEvent& evt);
	bool mIsStarted;
	bool mShutDown;
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
