#ifndef _MORPHER_INTERFACE_
#define _MORPHER_INTERFACE_

namespace OpenEngine {
namespace Animation {

template <class T>
class IMorpher {
 public:
  /** scaling between 0 and 1 */
  virtual void Morph(T* from, T* to, float scaling) = 0;
  virtual T* GetObject() = 0;
  virtual ~IMorpher() {}
};

} // NS Animation
} // NS OpenEngine

#endif // _MORPHER_INTERFACE_
