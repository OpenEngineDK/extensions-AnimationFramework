// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _ANIMATED_MESH_H_ 
#define _ANIMATED_MESH_H_ 

#include <vector>
#include <Geometry/Mesh.h>
#include "IMeshDeformer.h"


namespace OpenEngine {
namespace Animations {
        
    using namespace OpenEngine::Geometry;
    
    class AnimatedMesh {
    public:
        AnimatedMesh(MeshPtr sourceMesh);
        virtual ~AnimatedMesh();
        
        MeshPtr GetSourceMesh();
        MeshPtr GetAnimatedMesh();

        void AddMeshDeformer(IMeshDeformer* deformer);
        unsigned int GetNumMeshDeformers();

        void Update();

    private:
        MeshPtr srcMesh;       // The undeformed mesh in bind pose.
        MeshPtr animatedMesh;  // The mesh on which the IMeshDeformers are applied.
        std::vector<IMeshDeformer*> meshDeformers;
    };
    
} // NS Animation
} // NS OpenEngine

#endif
