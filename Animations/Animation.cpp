// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "Animation.h"
#include <Animations/AnimatedTransformation.h>
#include <Animations/AnimatedMesh.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Animations {

Animation::Animation() : name(""), duration(0.0), ticksPerSecond(1.0) {
}

Animation::~Animation() {
}

void Animation::SetDuration(double ticks) {
    duration = ticks;
}

double Animation::GetDuration() {
    return duration;
}
    
void Animation::SetTicksPerSecond(double ticks) {
    ticksPerSecond = ticks;
}

double Animation::GetTicksPerSecond() {
    return ticksPerSecond;
}

void Animation::SetName(std::string name) {
    this->name = name;
}

std::string Animation::GetName() {
    return name;
}

bool Animation::HasAnimatedTransformations() {
    return animTrans.size() > 0;
}
    
unsigned int Animation::GetNumAnimatedTransformations() {
    return animTrans.size();
}

void Animation::AddAnimatedTransformation(AnimatedTransformation* anim) {
    animTrans.push_back(anim);
}
    
bool Animation::HasAnimatedMesh() {
    return animMesh.size() > 0;
}

unsigned int Animation::GetNumAnimatedMesh() {
    return animMesh.size();
}

void Animation::AddAnimatedMesh(AnimatedMesh* am) {
    animMesh.push_back(am);
}
    
void Animation::UpdateTransformations(unsigned int time) {
    // For each animated transformation, update and apply according to time.
    std::vector<AnimatedTransformation*>::iterator itr;
    for(itr=animTrans.begin(); itr!=animTrans.end(); itr++) {
        (*itr)->UpdateAndApply(time);
    }
}

void Animation::UpdateMeshes(){
    // For each animated mesh do...

    // 1. Calculate accumulated transformation (bone-to-mesh matrix)
    
    // 2.  

}

} // NS Animations
} // NS OpenEngine
