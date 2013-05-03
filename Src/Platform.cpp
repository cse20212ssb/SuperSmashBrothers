/* Platform class

This is the platform class, which is used to create platforms for the program. It derives from the entity
class and utilizes a few simple functions from entity to draw the platforms and determine if an object
collided with the platform. Since platforms don't move, they don't shift during collisions.

*/

#include "Platform.h"

using namespace std;

Platform::Platform(int x, int y, int h, int w) : Entity(x,y,h,w) {
}
