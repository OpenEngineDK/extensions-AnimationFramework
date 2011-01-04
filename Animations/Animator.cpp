// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "Animator.h"
#include <Logging/Logger.h>
#include <Scene/SearchTool.h>
#include <Scene/AnimationNode.h>
#include <Scene/AnimatedMeshNode.h>
#include <Scene/MeshNode.h>
#include <Animations/Animation.h>
#include <Animations/AnimatedMesh.h>
#include <list>

namespace OpenEngine {
namespace Animations {

using OpenEngine::Logging::Logger;
using OpenEngine::Animations::Animation;
using namespace OpenEngine::Scene;

Animator::Animator(AnimationNode* animNode) 
    : animRoot(animNode), animatedScene(animNode), curAnim(NULL), curAnimMesh(NULL), isPlaying(false) {
    // Search the animation tree for sequences
    SearchTool search;
    std::list<AnimationNode*> animNodeRes;
    animNodeRes = search.DescendantAnimationNodes(animNode);
    // Throw results in vector list for convenience.
    std::list<AnimationNode*>::iterator itr;
    for(itr=animNodeRes.begin(); itr!=animNodeRes.end(); itr++){
        animList.push_back(*itr);
    }

    // Search the animation tree for animated meshes.
    std::list<AnimatedMeshNode*> animMeshNodeRes;
    animMeshNodeRes = search.DescendantAnimatedMeshNodes(animNode);
    if( animMeshNodeRes.size() > 0 ){
        curAnimMesh = animMeshNodeRes.front()->GetAnimatedMesh();
        animatedScene = new MeshNode(curAnimMesh->GetAnimatedMesh());
    }

    // TODO: Some kind of Animation Library Node should be parent for all animations.
    // The Animator should keep a list of animations not animation nodes.
}

Animator::~Animator() {
}
    
unsigned int Animator::GetNumAnimations() {
    return animList.size();
}

Animation* Animator::GetAnimation(unsigned int idx) {
    if( idx < animList.size() )
        return animList[idx]->GetAnimation();
    else
        return NULL;
}
           
void Animator::SetActiveAnimation(unsigned int idx) {
    if( idx < animList.size() ){
        if( (curAnim = animList[idx]->GetAnimation()) != NULL ){
            logger.info << "Active Animation: " << curAnim->GetName() << " with duration " << curAnim->GetDuration() << logger.end;
            logger.info << "Active Animation num animated transformations: " << curAnim->GetNumAnimatedTransformations() << logger.end;
        }else{
            logger.warning << "Animation invalid, " << curAnim->GetName() << " sequence num " << idx << logger.end;
        }
    }
    else{
        logger.warning << "Animation out of range, " << curAnim->GetName() << " sequence num " << idx << logger.end;
    }
}

void Animator::Play(){
    if( curAnim ){
        timer.Start();
        isPlaying = true;
    }
}

void Animator::Stop() {
    timer.Stop();
    timer.Reset();
    isPlaying = false;
}

void Animator::Pause() {
    timer.Stop();
    isPlaying = false;
}

void Animator::Reset() {
    timer.Reset();
}

bool Animator::IsPlaying() {
    return isPlaying;
}


ISceneNode* Animator::GetSceneNode() {
    return animatedScene;
}

void Animator::Handle(Core::InitializeEventArg arg) {
    logger.info << "init" << logger.end;
}

void Animator::Handle(Core::ProcessEventArg arg) {
    if( curAnim ) {        
        UpdateAnimatedTransformations();
    }

    if( curAnimMesh ){
        UpdateAnimatedMeshes();        
    }
}

void Animator::Handle(Core::DeinitializeEventArg arg) {
    logger.info << "deinit" << logger.end;
}

void Animator::UpdateAnimatedTransformations() {
    // Check time limits.
    double speedFactor = 0.05f;

    double usecElapsed = ((timer.GetElapsedTime().sec * 1000000) + timer.GetElapsedTime().usec) * speedFactor;
    //std::cout << "Duration: " << curAnim->GetDuration() << " Elapsed: " << usecElapsed << std::endl;

    if( usecElapsed > curAnim->GetDuration() ){
        //logger.info << "resetting animation time" << logger.end;
        timer.Reset();
    }
    curAnim->UpdateTransformations(usecElapsed);
    /*
    // Set fixed time
    static double count = 0;
    count += 100;
    if( count > 800000 ) count = 0;
    curAnim->UpdateTransformations(count);
    */
}

void Animator::UpdateAnimatedMeshes() {
    // Update animated meshes if any (aka. skinning)
    if( curAnimMesh ){
        curAnimMesh->Update();
    }
}

} // NS Animation
} // NS OpenEngine
