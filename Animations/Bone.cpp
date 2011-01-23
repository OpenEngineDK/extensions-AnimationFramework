// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "Bone.h"
#include <utility>
#include <iostream>
#include <Geometry/Mesh.h>
#include <Geometry/GeometrySet.h>
#include <Math/Quaternion.h>
#include <Scene/TransformationNode.h>
#include <Scene/SearchTool.h>
using namespace OpenEngine::Geometry;

namespace OpenEngine {
namespace Animations {

Bone::Bone(TransformationNode* trans) : transformation(trans)  {
}

Bone::~Bone() {
}

void Bone::SetName(std::string name) {
    this->name = name;
}

void Bone::SetOffsetMatrix(Matrix<4,4,float> mat) {
    this->offsetMatrix = mat;
}

void Bone::SetTransformation(TransformationNode* trans) {
    this->transformation = trans;
}

void Bone::AddWeight(unsigned int vertexId, float weight) {
    weights.push_back( std::make_pair(vertexId, weight) );
}

void Bone::Apply(MeshPtr srcMesh, MeshPtr resMesh) {
        
    // Calculate bone-to-mesh matrix.
    Vector<3,float>   accPos;
    Quaternion<float> accRot;
    Vector<3,float>   accSca;
    transformation->GetAccumulatedTransformations(&accPos, &accRot, &accSca);

    /*
    boneMatrix = offsetMatrix;
    Scene::SearchTool search;
    TransformationNode* parent = transformation;
    while( parent ) {
        Vector<3,float>   p = parent->GetPosition();
        Matrix<4,4,float> t = parent->GetRotation().GetMatrix().GetExpanded();
        t[0][3] = p[0];
        t[1][3] = p[1];
        t[2][3] = p[2];
   
        boneMatrix = t * boneMatrix;
        parent = search.AncestorTransformationNode(parent);
   
    }
    */

    //    cout << "Offset: " << offsetMatrix << endl;
    // accRot.Normalize();
    Matrix<4,4,float> accMatrix = accRot.GetMatrix().GetExpanded();
    accMatrix(0,3) = accPos[0];
    accMatrix(1,3) = accPos[1];
    accMatrix(2,3) = accPos[2];
    accMatrix(3,3) = 1.0;
    //    cout << "AccMatrix: " << accMatrix << endl;

    // Calculate local bone matrix
    boneMatrix = accMatrix * offsetMatrix;
    //    cout << "BoneMatrix: " << boneMatrix << endl;

    Matrix<3,3,float> rotation = boneMatrix.GetReduced();
    
    IDataBlockPtr srcVert = srcMesh->GetGeometrySet()->GetVertices();
    IDataBlockPtr resVert = resMesh->GetGeometrySet()->GetVertices();

    IDataBlockPtr srcNorm = srcMesh->GetGeometrySet()->GetNormals();
    IDataBlockPtr resNorm = resMesh->GetGeometrySet()->GetNormals();

    std::vector< std::pair<unsigned int, float> >::iterator itr;
    for(itr=weights.begin(); itr!=weights.end(); itr++){
        unsigned int vertId = itr->first;
        float weight = itr->second;

//         if( vertId == 4 )
//             cout << "vertId: " << vertId << ", weight: " << weight << endl;

        Vector<3,float> srcVec;
        srcVert->GetElement(vertId, srcVec);
        Vector<4,float> srcVec4;
        srcVec4[0] = srcVec[0];
        srcVec4[1] = srcVec[1];
        srcVec4[2] = srcVec[2];
        srcVec4[3] = 1.0;
        //        if( vertId == 4 ) cout << "srcVec: " << srcVec << endl;

        Vector<3,float> resVec;
        resVert->GetElement(vertId, resVec);
        Vector<4,float> resVec4 = (boneMatrix * srcVec4) * weight;
        resVec[0] += resVec4[0];
        resVec[1] += resVec4[1];
        resVec[2] += resVec4[2];
        //        if( vertId == 4 ) cout << "resVec: " << resVec << endl;


        Vector<3,float> srcN;
        Vector<3,float> destN;

        srcNorm->GetElement(vertId, srcN);
        resNorm->GetElement(vertId, destN);


        srcN = (rotation * srcN) * weight;
        destN += srcN;


        resVert->SetElement(vertId, resVec);
        resNorm->SetElement(vertId, destN);
        
   
    }

}


} // NS Animations
} // NS OpenEngine
