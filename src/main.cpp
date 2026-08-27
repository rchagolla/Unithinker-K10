#include "unihiker_k10.h"
#include "vector3.h"

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

// Renamed from 'near' to avoid compiler keyword conflicts
bool isNearlyEqual(double val, double expected)
{
  return std::abs(val - expected) < 0.0001;
}

void setup()
{
  k10.begin();
  k10.initScreen(screen_dir);
  k10.creatCanvas();
  k10.setScreenBackground(0xFFFFFF); // White Background

  // Inform user that checks are starting on screen
  k10.canvas->canvasText("Running standard assertions...", 1, 0x000000);
  k10.canvas->updateCanvas();

  // ---------------------------------------------------------
  // Execution Matrix (Will instantly halt program if any fail)
  // ---------------------------------------------------------

  // 1. Constructor
  Vector3 v1;
  Vector3 v2(3.0, 4.0, 0.0);
  assert(isNearlyEqual(v1.x, 0.0) && isNearlyEqual(v1.y, 0.0) && isNearlyEqual(v1.z, 0.0));
  assert(isNearlyEqual(v2.x, 3.0) && isNearlyEqual(v2.y, 4.0) && isNearlyEqual(v2.z, 0.0));

  // 2. Set
  v1.set(1.0, 2.0, 3.0);
  assert(isNearlyEqual(v1.x, 1.0) && isNearlyEqual(v1.y, 2.0) && isNearlyEqual(v1.z, 3.0));

  // 3. Clone
  Vector3 vClone = v1.clone();
  assert(isNearlyEqual(vClone.x, 1.0) && isNearlyEqual(vClone.y, 2.0) && isNearlyEqual(vClone.z, 3.0));

  // 4. Copy
  Vector3 vCopy;
  vCopy.copy(v2);
  assert(isNearlyEqual(vCopy.x, 3.0) && isNearlyEqual(vCopy.y, 4.0) && isNearlyEqual(vCopy.z, 0.0));

  // 5. Negate
  Vector3 vNegate(5.0, -2.0, 3.0);
  vNegate.negate();
  assert(isNearlyEqual(vNegate.x, -5.0) && isNearlyEqual(vNegate.y, 2.0) && isNearlyEqual(vNegate.z, -3.0));

  // 6. Add
  Vector3 vAdd1(1.0, 2.0, 3.0);
  Vector3 vAdd2(4.0, 5.0, 6.0);
  vAdd1.add(vAdd2);
  assert(isNearlyEqual(vAdd1.x, 5.0) && isNearlyEqual(vAdd1.y, 7.0) && isNearlyEqual(vAdd1.z, 9.0));

  // 7. Subtract
  Vector3 vSub1(10.0, 10.0, 10.0);
  Vector3 vSub2(3.0, 4.0, 5.0);
  vSub1.subtract(vSub2);
  assert(isNearlyEqual(vSub1.x, 7.0) && isNearlyEqual(vSub1.y, 6.0) && isNearlyEqual(vSub1.z, 5.0));

  // 8. Multiply Scalar
  Vector3 vMult(2.0, 3.0, 4.0);
  vMult.multiplyScalar(3.0);
  assert(isNearlyEqual(vMult.x, 6.0) && isNearlyEqual(vMult.y, 9.0) && isNearlyEqual(vMult.z, 12.0));

  // 9. Length & 10. LengthSqr
  Vector3 vLengthTest(3.0, 4.0, 0.0);
  assert(isNearlyEqual(vLengthTest.length(), 5.0));
  assert(isNearlyEqual(vLengthTest.lengthSqr(), 25.0));

  // 11. Normalize
  Vector3 vNorm(3.0, 4.0, 0.0);
  vNorm.normalize();
  assert(isNearlyEqual(vNorm.length(), 1.0));
  assert(isNearlyEqual(vNorm.x, 0.6) && isNearlyEqual(vNorm.y, 0.8) && isNearlyEqual(vNorm.z, 0.0));

  // 12. Dot Product
  Vector3 vDot1(1.0, 2.0, 3.0);
  Vector3 vDot2(4.0, 5.0, 6.0);
  assert(isNearlyEqual(vDot1.dot(vDot2), 32.0));

  // 13. FromTo
  Vector3 pointA(1.0, 1.0, 1.0);
  Vector3 pointB(4.0, 6.0, 8.0);
  Vector3 directionVec = v1.fromTo(pointA, pointB);
  assert(isNearlyEqual(directionVec.x, 3.0) && isNearlyEqual(directionVec.y, 5.0) && isNearlyEqual(directionVec.z, 7.0));

  // 14. Rescale
  Vector3 vRescale(3.0, 4.0, 0.0);
  vRescale.rescale(10.0);
  assert(isNearlyEqual(vRescale.length(), 10.0));

  // 15. Angle
  Vector3 vAng1(1.0, 0.0, 0.0);
  Vector3 vAng2(0.0, 1.0, 0.0);
  assert(isNearlyEqual(v1.angle(vAng1, vAng2), 90.0));

  // 16. Project
  Vector3 vecToProject(2.0, 3.0, 0.0);
  Vector3 targetAxis(5.0, 0.0, 0.0);
  Vector3 projected = v1.project(vecToProject, targetAxis);
  assert(isNearlyEqual(projected.x, 2.0) && isNearlyEqual(projected.y, 0.0) && isNearlyEqual(projected.z, 0.0));

  // If execution reaches here, every single test passed cleanly!
  k10.canvas->canvasClear();
  k10.canvas->canvasText("ALL ASSERTS PASSED!", 1, 0x00FF00); // Prints Green message
  k10.canvas->updateCanvas();

  while (true)
  {
    delay(100);
  }
}

void loop()
{
}