// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _BONE_H_
#define _BONE_H_

#include "IMeshDeformer.h"
#include <Math/Matrix.h>
#include <string>
#include <vector>

namespace OpenEngine {
    namespace Scene {
        class TransformationNode;
    }
    namespace Animations {

    using OpenEngine::Math::Matrix;
    using OpenEngine::Scene::TransformationNode;
    using OpenEngine::Geometry::MeshPtr;

    class Bone : public IMeshDeformer {
    public:
        Bone(TransformationNode* trans);
        ~Bone();

        void SetName(std::string name);
        void SetOffsetMatrix(Matrix<4,4,float> mat);
        void SetTransformation(TransformationNode* trans);

        void AddWeight(unsigned int vertexId, float weight);
        void Apply(MeshPtr srcMesh, MeshPtr resMesh);

    private:
        std::string name;
        TransformationNode* transformation;
        Matrix<4,4,float> offsetMatrix;
        Matrix<4,4,float> boneMatrix;
        std::vector< std::pair<unsigned int, float> > weights;
    };

} // NS Animations
} // NS OpenEngine

#endif
