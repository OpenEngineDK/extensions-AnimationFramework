
# Create the extension library
ADD_LIBRARY(Extensions_AnimationFramework
  # Animations
  Animations/Animator.cpp
  Animations/Animation.cpp
  Animations/AnimatedTransformation.cpp
  Animations/AnimatedMesh.cpp
  Animations/Bone.cpp
  # Scene
  Scene/AnimatedMeshNode.cpp
  Scene/AnimatedTransformationNode.cpp
  Scene/AnimationNode.cpp
)

TARGET_LINK_LIBRARIES(Extensions_AnimationFramework
  OpenEngine_Scene
)
