// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "AnimatedMeshNode.h"
#include <Animations/Animation.h>
#include <Animations/AnimatedMesh.h>
#include <string>
#include <stdio.h>

using namespace OpenEngine::Animations;
namespace OpenEngine {
namespace Scene {

AnimatedMeshNode::AnimatedMeshNode() : animMesh(NULL) {
}

AnimatedMeshNode::AnimatedMeshNode(AnimatedMesh* animMesh) : animMesh(animMesh) {
}


AnimatedMeshNode::~AnimatedMeshNode() {
}


AnimatedMesh* AnimatedMeshNode::GetAnimatedMesh() {
    return animMesh;
}

void AnimatedMeshNode::SetAnimatedMesh(AnimatedMesh* animMesh) {
    this->animMesh = animMesh;
}


const std::string AnimatedMeshNode::ToString() const {
    std::string str = GetNodeName(); 
    str.append("\n[AnimatedMeshNode]");
    unsigned int numDeformers = 0;
    if( animMesh ){
        numDeformers = animMesh->GetNumMeshDeformers();
    }
    char buf[16];
    sprintf(buf, "\n Mesh Deformers: %i", numDeformers);
    str.append(buf);
    return str;
}

} // NS Scene
} // NS OpenEngine
