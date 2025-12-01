#pragma once

#include "../external/glm/glm/glm.hpp"
#include "../external/glm/glm/gtc/constants.hpp"
using namespace glm;

// random number generator - Marsaglia's xor32
// This is a high-quality RNG that uses a single 32-bit seed. More info:
// https://www.researchgate.net/publication/5142825_Xorshift_RNGs

// main credits to Jacco Bikker
// some of the helper functions using the main functions are added by Hesam Ghadimi

/// <summary>
/// generates detirministic random numbers efficiently. the user is responsible for keeping an unsinged int "seed".
/// NOTE: in a multithreaded application, don't use a single seed.
/// </summary>
class RNG
{
public:
    // WangHash: calculates a high-quality seed based on an arbitrary non-zero
    // integer. Use this to create your own seed based on e.g. thread index.
    static uint WangHash(uint s)
    {
        s = (s ^ 61) ^ (s >> 16);
        s *= 9, s = s ^ (s >> 4);
        s *= 0x27d4eb2d;
        s = s ^ (s >> 15);
        return s;
    }

    /// <summary>
    /// initalize your seed with this function to make it a high quality seed base. uses WangHash
    /// </summary>
    /// <param name="seedBase">can be any uint</param>
    /// <returns>a high quality seed base</returns>
    static uint InitSeed(uint seedBase) { return WangHash((seedBase + 1) * 17); }

    static uint RandomUInt(uint& customSeed)
    {
        customSeed ^= customSeed << 13;
        customSeed ^= customSeed >> 17;
        customSeed ^= customSeed << 5;
        return customSeed;
    }

    static float RandomFloat(uint& customSeed) { return static_cast<float>(RandomUInt(customSeed)) * 2.3283064365387e-10f; }

    static float RandomFloat(uint& customSeed, float min, float max) { return min + (RandomFloat(customSeed) * (max - min)); }

    static uint RandomUInt(uint& customSeed, int inclusive_min, int exclusive_max)
    {
        return inclusive_min + (RandomUInt(customSeed) % (exclusive_max - inclusive_min));
    }

    static vec2 RandomPointOnCircle(uint& customSeed)
    {
        // from Sebastian Lague https://youtu.be/Qz0KTGYJtUk?si=YTTg56J1Yi21FZYJ&t=1979
        const float angle = RandomFloat(customSeed) * glm::two_pi<float>();
        const vec2 point_on_circle = vec2(cos(angle), sin(angle));
        return point_on_circle * sqrt(RandomFloat(customSeed));
    }

    static vec3 RandomPointOnSphere(uint& customSeed)
    {
        vec3 rand_point(0);
        while (true)
        {
            rand_point = {
                RandomFloat(customSeed, -1.0f, 1.0f),
                RandomFloat(customSeed, -1.0f, 1.0f),
                RandomFloat(customSeed, -1.0f, 1.0f),
            };
            const float len = length(rand_point);
            if (len > 1e-160 && len <= 1.0f)
            {
                return normalize(rand_point);
            }
        }
    }

    static vec3 RandomPointOnHemisphere(uint& customSeed, const vec3& normal)
    {
        const vec3 dir = RandomPointOnSphere(customSeed);
        return dot(dir, normal) > 0.0f ? dir : -dir;
    }

    static vec3 CosineWeightedDiffuseReflection(const vec3 N, uint& seed)
    {
        // blog.demofox.org/2020/06/06/casual-shadertoy-path-tracing-2-image-improvement-and-glossy-reflections
        vec3 R;
        do
        {
            R = vec3(RandomFloat(seed) * 2 - 1, RandomFloat(seed) * 2 - 1, RandomFloat(seed) * 2 - 1);
        } while (dot(R, R) > 1);
        return normalize(N + normalize(R));
    }
};
