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
    : animRoot(animNode)
    , animatedScene(animNode)
    , curAnim(NULL)
    , curAnimMesh(NULL)
    , speedFactor(1.0)
    , isPlaying(false)
    , loopAnimation(true) {

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
        if( !loopAnimation && GetElapsedTime() > curAnim->GetDuration() ){
            Reset();
        }

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
    UpdateAnimation();
}

void Animator::LoopAnimation(bool loop) {
    this->loopAnimation = loop;
}


void Animator::SetSpeed(float speed) {
    speedFactor = speed;
}

float Animator::GetSpeed() {
    return speedFactor;
}


bool Animator::IsPlaying() {
    return isPlaying;
}


ISceneNode* Animator::GetSceneNode() {
    return animatedScene;
}

void Animator::Handle(Core::InitializeEventArg arg) {
}

void Animator::Handle(Core::ProcessEventArg arg) {
    // Update both transformations and meshes.
    UpdateAnimation();
}

void Animator::Handle(Core::DeinitializeEventArg arg) {
}

void Animator::UpdateAnimation() {
    // Update transformations.
    if( curAnim ) {        
        UpdateAnimatedTransformations();
    }
    // Update mesh deformations.
    if( curAnimMesh ){
        UpdateAnimatedMeshes();        
    }
}

void Animator::UpdateAnimatedTransformations() {
    // Check time limits.
    double usecElapsed = GetElapsedTime();
    if( usecElapsed > curAnim->GetDuration() ){
        loopAnimation ? Reset() : Pause();
    }
    curAnim->UpdateTransformations(usecElapsed);
}

void Animator::UpdateAnimatedMeshes() {
    // Update animated meshes if any (aka. skinning)
    if( curAnimMesh ){
        curAnimMesh->Update();
    }
}

double Animator::GetElapsedTime() {
    return ((timer.GetElapsedTime().sec * 1000000) + 
            timer.GetElapsedTime().usec) * speedFactor;

}


} // NS Animation
} // NS OpenEngine
