// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <Core/IModule.h>
#include <vector>

namespace OpenEngine { 
    namespace Utils {
        class Timer;
    }
    namespace Animations {
        class Animation;
        class AnimatedMesh;
    }
    namespace Scene { 
        class ISceneNode;
        class AnimationNode; 
    } 
}

namespace OpenEngine {
namespace Animations {

    using OpenEngine::Core::IModule;
    using OpenEngine::Scene::ISceneNode;
    using OpenEngine::Scene::AnimationNode;
    using OpenEngine::Utils::Timer;

    class Animator : public IModule {
    public:
        Animator(AnimationNode* animNode);
        virtual ~Animator();

        unsigned int GetNumAnimations();
        Animation* GetAnimation(unsigned int idx);
                
        void SetActiveAnimation(unsigned int idx);
        void Play();
        void Stop();
        void Pause();
        void Reset();
        void LoopAnimation(bool loop);

        void SetSpeed(float speed);
        float GetSpeed();
        bool IsPlaying();

        ISceneNode* GetSceneNode();

        // Engine call backs.
        void Handle(Core::InitializeEventArg arg);
        void Handle(Core::ProcessEventArg arg);
        void Handle(Core::DeinitializeEventArg arg);

    private:
        AnimationNode* animRoot;    // Input scene;
        ISceneNode* animatedScene;  // The resulting scene;
        std::vector<AnimationNode*> animList; // List of animation sequences.
        Animation* curAnim;         // Current animation sequence.
        AnimatedMesh* curAnimMesh;  // Current animated mesh (aka skinning).
        Timer timer;                // Sequence timer.
        float speedFactor;          // Speed multiplier.
        bool isPlaying;
        bool loopAnimation;

        void UpdateAnimatedTransformations();
        void UpdateAnimatedMeshes();
        double GetElapsedTime();
    };
    

} // NS Animation
} // NS OpenEngine

#endif
