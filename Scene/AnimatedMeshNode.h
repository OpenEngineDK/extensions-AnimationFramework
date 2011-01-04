// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _ANIMATION_MESH_NODE_H_
#define _ANIMATION_MESH_NODE_H_

#include <Scene/ISceneNode.h>

namespace OpenEngine {
    namespace Animations {
        class AnimatedMesh;
    }

namespace Scene {

    using OpenEngine::Animations::AnimatedMesh;
    
    class AnimatedMeshNode : public Scene::ISceneNode {
        OE_SCENE_NODE(AnimatedMeshNode, ISceneNode)

    public:
        AnimatedMeshNode();
        AnimatedMeshNode(AnimatedMesh* animMesh);
        virtual ~AnimatedMeshNode();

        AnimatedMesh* GetAnimatedMesh();
        void SetAnimatedMesh(AnimatedMesh* animMesh);

        const std::string ToString() const;

    private:
        AnimatedMesh* animMesh;
    };


} // NS Scene
} // NS OpenEngine

#endif
