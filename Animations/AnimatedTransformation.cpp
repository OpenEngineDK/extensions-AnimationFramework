// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "AnimatedTransformation.h"
#include <utility>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Animations {


AnimatedTransformation::AnimatedTransformation(TransformationNode* target) {
    this->target = target;
}

AnimatedTransformation::~AnimatedTransformation() {
}

void AnimatedTransformation::SetName(std::string name) {
    this->name = name;
}

std::string AnimatedTransformation::GetName() {
    return name;
}
        
void AnimatedTransformation::SetAnimatedNode(TransformationNode* target) {
    this->target = target;
}

TransformationNode* AnimatedTransformation::GetAnimatedNode() {
    return target;
}
        
void AnimatedTransformation::AddRotationKey(unsigned int time, Math::Quaternion<float> key) {
    rotationKeys.push_back(std::make_pair(time, key));
}

void AnimatedTransformation::UpdateAndApply(unsigned int time) {
    std::pair<double, Math::Quaternion<float> > elm, kStart, kEnd;

    kStart.first = -1;
    kEnd.first = -1;

    std::vector< std::pair<double, Math::Quaternion<float> > >::iterator itr;
    for(itr=rotationKeys.begin(); itr!=rotationKeys.end(); itr++){
        elm = *itr;
        if( time >= elm.first ) {
            kStart = elm;
        }else{
            kEnd = elm;
            break;
        }
    }

    elm = kStart;
    // Interpolation between kStart.second and kEnd.second.
    if( kStart.first != -1 && kEnd.first != -1 ){
        double delta = kEnd.first - kStart.first;
        double iTime = time - kStart.first;
        double progr = 0;
        
        if( delta > 0 )
            progr = iTime / delta;
        
        elm.second = Quaternion<float>(kStart.second, kEnd.second, progr);
    }

    // Apply rotation to affected transformation node.
    target->SetRotation(elm.second);
}


} // NS Animations
} // NS OpenEngine
