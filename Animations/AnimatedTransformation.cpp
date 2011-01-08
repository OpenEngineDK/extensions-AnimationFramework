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

void AnimatedTransformation::AddPositionKey(unsigned int time, Math::Vector<3,float> key) {
    positionKeys.push_back(std::make_pair(time, key));
}

void AnimatedTransformation::AddScalingKey( unsigned int time, Math::Vector<3,float> key) {
    scalingKeys.push_back(std::make_pair(time, key));
}

void AnimatedTransformation::UpdateAndApply(unsigned int time) {
    // Find rotation key frame interval and interpolate in between.
    std::pair<double, Math::Quaternion<float> > rotElm, rotStart, rotEnd;
    rotStart.first = -1;
    rotEnd.first = -1;
    std::vector< std::pair<double, Math::Quaternion<float> > >::iterator itr;
    for(itr=rotationKeys.begin(); itr!=rotationKeys.end(); itr++){
        rotElm = *itr;
        if( time >= rotElm.first ) {
            rotStart = rotElm;
        }else{
            rotEnd = rotElm;
            break;
        }
    }
    rotElm = rotStart;
    // Interpolation between rotStart.second and rotEnd.second.
    if( rotStart.first != -1 && rotEnd.first != -1 ){
        double delta = rotEnd.first - rotStart.first;
        double iTime = time - rotStart.first;
        double progr = 0;
        
        if( delta > 0 )
            progr = iTime / delta;

        rotElm.second = Quaternion<float>(rotStart.second, rotEnd.second, progr);
    }

    // Apply rotation to affected transformation node.
    target->SetRotation(rotElm.second);

    // Find position key frame interval and interpolate in between.
    std::pair<double, Math::Vector<3,float> > posElm, posStart, posEnd;
    posStart.first = -1;
    posEnd.first = -1;
    std::vector< std::pair<double, Math::Vector<3,float> > >::iterator posItr;
    for(posItr=positionKeys.begin(); posItr!=positionKeys.end(); posItr++) {
        posElm = *posItr;
        if( time >= posElm.first ) {
            posStart = posElm;
        } else {
            posEnd = posElm;
            break;
        }
    }
    posElm = posStart;
    if( posStart.first != -1 && posEnd.first != -1 ){
        double delta = posEnd.first - posStart.first;
        double iTime = time - posStart.first;
        double progr = 0;
        
        if( delta > 0 )
            progr = iTime / delta;

        // Interpolate vector: deltaVec * scale + startVec
        posElm.second = ((posEnd.second - posStart.second) * progr) + posStart.second;
    }
    // Apply position to affected transformation node.
    target->SetPosition(posElm.second);
}


} // NS Animations
} // NS OpenEngine
