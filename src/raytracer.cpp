#include <cmath>
#include <vector>
#include "plane.h"
#include "ray.h"
#include "sphere.h"
#include "vector3.h"
#include "unihiker_k10.h"

UNIHIKER_K10 k10;
uint8_t screen_dir = 2;

const int PIXELS_ACROSS = 240;
const int PIXELS_DOWN = 320;

const double PIXEL_WIDTH = 2.0 / PIXELS_DOWN; // 2 units over 320 rows
const double PIXEL_HALF = PIXEL_WIDTH / 2.0;
const double VIEW_WIDTH = PIXELS_ACROSS * PIXEL_WIDTH; // 1.5 units across
const double VIEW_LEFT = -VIEW_WIDTH / 2.0;            // -0.75
const int BLOCK = 8;

const double SPHERE_RADIUS = 0.25;
int fov;
double fovRadians, eyeDistance;
Vector3 eyeCoordinate, lightPos;
Plane flooring, ceiling, leftWall, rightWall, backWall;
Sphere sphere;
std::vector<Plane> scene;
double lightAngle = 0.0;

struct Hit
{
    bool didHit = true;
    Vector3 point;
    Vector3 normal;
    Vector3 color;
    double distance = 0.0;

    Hit() = default;
    Hit(bool didHit, Vector3 point, Vector3 normal, Vector3 color, double distance)
        : didHit(didHit), point(point), normal(normal), color(color), distance(distance) {}
};

uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b);
void raytracerSceneSetup();
Ray generateRayForPixel(int xPixelIndex, int yPixelIndex);
void setPixelColor(int xPixelIndex, int yPixelIndex, Vector3 color);
double clamp01(double v);
Hit traceRay(Ray ray);

void setup()
{
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.setScreenBackground(0xFFFFFF);

    raytracerSceneSetup();
}

void loop()
{
    Serial.begin(115200);
    delay(1000);
    lightAngle += 0.25; // radians per frame, ~25 frames per orbit
    lightPos.x = std::cos(lightAngle) * 0.5;
    lightPos.z = std::sin(lightAngle) * 0.5;
    lightPos.y = 0.8;

    lightAngle += 0.25; // radians per frame, ~25 frames per orbit
    lightPos.x = std::cos(lightAngle) * 0.5;
    lightPos.z = std::sin(lightAngle) * 0.5;
    lightPos.y = 0.8;

    for (int y = 0; y < PIXELS_DOWN; y += BLOCK)
    {
        for (int x = 0; x < PIXELS_ACROSS; x += BLOCK)
        {
            Hit h = traceRay(generateRayForPixel(x, y));

            Vector3 c(0.0, 0.0, 0.0);

            if (h.didHit)
            {
                Vector3 toLight = Vector3::fromTo(h.point, lightPos);
                auto shadow = sphere.raycast(Ray(h.point, toLight));
                bool blocked = std::get<0>(shadow) && std::get<3>(shadow) < toLight.length();

                double lambert = 0.0;
                if (!blocked)
                {
                    lambert = h.normal.dot(toLight.clone().normalize());
                    if (lambert < 0.0)
                        lambert = 0.0;

                    // after computing lambert, inside the render loop
                    if (x == 120 && y == 160)
                    {
                        Ray probe = generateRayForPixel(x, y);
                        Serial.print("origin: ");
                        Serial.print(probe.getOrigin().x);
                        Serial.print(",");
                        Serial.print(probe.getOrigin().y);
                        Serial.print(",");
                        Serial.println(probe.getOrigin().z);

                        Serial.print("dir: ");
                        Serial.print(probe.getDirection().x);
                        Serial.print(",");
                        Serial.print(probe.getDirection().y);
                        Serial.print(",");
                        Serial.print(probe.getDirection().z);
                        Serial.print("  len: ");
                        Serial.println(probe.getDirection().length());
                    }
                }

                c = h.color.clone().multiplyScalar(lambert);
            }

            uint32_t packed = rgbToColor(
                (uint8_t)(clamp01(c.x) * 255.0),
                (uint8_t)(clamp01(c.y) * 255.0),
                (uint8_t)(clamp01(c.z) * 255.0));

            k10.canvas->canvasRectangle(x, y, BLOCK, BLOCK, packed, packed, true);
        }
    }

    k10.canvas->updateCanvas();
}

uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b)
{
    return (uint32_t)((((uint32_t)r << 16) | ((uint32_t)g << 8)) | (uint32_t)b);
}

void raytracerSceneSetup()
{
    // fov = 45;
    // fovRadians = fov * (M_PI / 180);

    /* How far away (scalar) the eye is from the image plane
     *  -----------
     *  |         /
     *  |        /
     *  |       /
     *  | 45/2 /      <---- half angle
     *  |     /
     *  |    /
     *  |   /
     *  |  /
     *  | /
     */
    // eyeDistance = 1 / std::tan(fovRadians / 2);
    // eyeCoordinate = Vector3(0, 0, eyeDistance);
    eyeCoordinate = Vector3(0.0, 0.0, -3.0);

    // Scene objects
    sphere = Sphere(Vector3(0, 0.15, -0.3), SPHERE_RADIUS, Vector3(1, 1, 0));
    flooring = Plane(Vector3(0, 1, 0), Vector3(0, -0.25, 0));
    leftWall = Plane(Vector3(1, 0, 0), Vector3(-1, 0, 0), Vector3(0, 1, 0));
    rightWall = Plane(Vector3(-1, 0, 0), Vector3(1, 0, 0), Vector3(1, 0, 0));
    ceiling = Plane(Vector3(0, -1, 0), Vector3(0, 1, 0));
    backWall = Plane(Vector3(0, 0, -1), Vector3(0, 0, 6), Vector3(0, 0, 1));

    scene = {ceiling, flooring, leftWall, rightWall, backWall};
}

Ray generateRayForPixel(int xPixelIndex, int yPixelIndex)
{
    double pixelX = VIEW_LEFT + PIXEL_HALF + PIXEL_WIDTH * xPixelIndex;
    double pixelY = 1.0 - PIXEL_HALF - PIXEL_WIDTH * yPixelIndex;
    Vector3 pixelCoordinate(pixelX, pixelY, 0.0);

    Vector3 direction = Vector3().fromTo(eyeCoordinate, pixelCoordinate); // = vector from the eye to the pixel

    // Creates a ray from the eye toward the pixelCoordinate
    return Ray(eyeCoordinate, direction);
}

double clamp01(double v)
{
    if (v < 0.0)
        return 0.0;
    if (v > 1.0)
        return 1.0;
    return v;
}

void setPixelColor(int xPixelIndex, int yPixelIndex, Vector3 color)
{
    uint8_t r = (uint8_t)(clamp01(color.x) * 255.0);
    uint8_t g = (uint8_t)(clamp01(color.y) * 255.0);
    uint8_t b = (uint8_t)(clamp01(color.z) * 255.0);

    k10.canvas->canvasPoint(xPixelIndex, yPixelIndex, rgbToColor(r, g, b));
}

// walks every plane, keeps the closest hit
Hit traceRay(Ray ray)
{
    Vector3 background(0.0, 0.0, 0.0);
    double nearest = 1e30;
    Hit best;

    for (int i = 0; i < (int)scene.size(); i++)
    {
        auto result = scene[i].raycast(ray);

        if (std::get<0>(result) && std::get<3>(result) < nearest)
        {
            nearest = std::get<3>(result);
            best = {
                true,
                std::get<1>(result),
                std::get<2>(result),
                scene[i].getColor(),
                nearest};
        }
    }

    auto sphereHit = sphere.raycast(ray);
    if (std::get<0>(sphereHit) && std::get<3>(sphereHit) < nearest)
    {
        nearest = std::get<3>(sphereHit);
        best = {
            true,
            std::get<1>(sphereHit),
            std::get<2>(sphereHit),
            sphere.getColor(),
            nearest};
    }

    return best;
}