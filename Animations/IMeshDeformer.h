// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _MESH_DEFORMER_H_
#define _MESH_DEFORMER_H_

#include <Geometry/Mesh.h>

namespace OpenEngine {
namespace Animations {

    class IMeshDeformer {
    public:
        IMeshDeformer() {}
        virtual ~IMeshDeformer() {}

        virtual void Apply(OpenEngine::Geometry::MeshPtr srcMesh,
                           OpenEngine::Geometry::MeshPtr resMesh) = 0;
    };

} // NS Animations
} // NS OpenEngine

#endif
