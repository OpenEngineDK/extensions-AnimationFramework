// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "AnimatedMesh.h"
#include <Logging/Logger.h>
#include <Geometry/GeometrySet.h>
#include <Math/Matrix.h>

namespace OpenEngine {
namespace Animations {

AnimatedMesh::AnimatedMesh(MeshPtr sourceMesh) 
    : srcMesh(sourceMesh), animatedMesh(sourceMesh->Clone()) {
}

AnimatedMesh::~AnimatedMesh() {
}

MeshPtr AnimatedMesh::GetSourceMesh() {
    return srcMesh;
}

MeshPtr AnimatedMesh::GetAnimatedMesh() {
    return animatedMesh;
}

void AnimatedMesh::AddMeshDeformer(IMeshDeformer* deformer) {
    meshDeformers.push_back(deformer);
}

unsigned int AnimatedMesh::GetNumMeshDeformers() {
    return meshDeformers.size();
}

void AnimatedMesh::Update(){
    //logger.info << "AnimatedMesh updating mesh: " << srcMesh << logger.end;
    // Reset source mesh since mesh deformers are destructive.
    (*animatedMesh->GetGeometrySet()->GetVertices()) *= 0; 
    (*animatedMesh->GetGeometrySet()->GetNormals()) *= 0; 
    
    //IDataBlockPtr srcVert = srcMesh->GetGeometrySet()->GetVertices();
    //IDataBlockPtr resVert = animatedMesh->GetGeometrySet()->GetVertices();
      
    /*                                  
    for( unsigned int i=0; i<srcVert->GetSize(); i++ ){
        Vector<3,float> srcVec;
        srcVert->GetElement(i, srcVec);
        //srcVec = mat * srcVec;
        resVert->SetElement(i, srcVec);
    }
    */

    // Apply all mesh deformations (eg. each bone).
    std::vector<IMeshDeformer*>::iterator itr;
    for(itr=meshDeformers.begin(); itr!=meshDeformers.end(); itr++){
        (*itr)->Apply(srcMesh, animatedMesh);
    }
    
    IDataBlockPtr ptr = animatedMesh->GetGeometrySet()->GetVertices();
    IDataBlockChangedEventArg arg(ptr);
    ptr->ChangedEvent().Notify(arg);

    ptr = animatedMesh->GetGeometrySet()->GetNormals();
    arg = IDataBlockChangedEventArg(ptr);
    ptr->ChangedEvent().Notify(arg);

    /*
    int count = 0;
    Vector<3,float> srcVec;        
    Vector<3,float> resVec;
    for( unsigned int i=0; i<srcVert->GetSize(); i++ ){
        srcVert->GetElement(i, srcVec);
        resVert->GetElement(i, resVec);

        if( resVec.GetLength() < 0.01 ){
            count++;
            //resVec = srcVec;
        }

    
        resVert->SetElement(i, resVec);
    }
    if( count > 0 ){
        cout << "Vertices left untouched by bone structure" << endl;
    }
    */
}

} // NS Animation
} // NS OpenEngine
