extern float x, y, angle, diff;
extern bool trackenabled;

void track();
void stopTracking();

const float sideDistance = 0.0,  // Distance in inches from tracking center to center of side tracker
              backDistance = 6.7675, // Distance in inches from tracking center to center of back tracker
              sideDiameter = 3.25,   // Side tracker diameter in inches
              backDiameter = 2.75;   // Back tracker diameter in inches

extern pros::Task *tracking;