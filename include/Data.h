#pragma once

#include "glm/glm.hpp"

// some data used throughout for testing purposes
static float verticies[] =
    {
         -0.5f,  -0.5f,    // 0
          0.5f,  -0.5f,  //  1
          0.5f,   0.5f, //   2
         -0.5f,   0.5f,//    3
         
    };

static float verticiesWithColor[] =
    {
         -0.5f,  -0.5f, 1.0f, 0.0f, 0.0f,  // 0
          0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, //  1
          0.5f,   0.5f, 0.0f, 0.0f, 1.0f,//   2
         -0.5f,   0.5f, .25f, .25f, .25f//    3
         
    };
// 2f = pos, 3f = colour, 2f = texcords
static float verticiesWithTexCords[] =
    {
         -0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f,  // 0
          0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, //  1
          0.5f,   0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f,//   2
         -0.5f,   0.5f, .25f, .25f, .25f, 0.0f, 1.0f//    3
         
    };
static float verticiesWithTexCords2[] =
    {
         -0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f,  // 0
          0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, //  1
          0.5f,   0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f,//   2
         -0.5f,   0.5f, .25f, .25f, .25f, 0.0f, 1.0f//    3
         
    };

static float twoTriangles[] =
    {
        // tri angle one
        1.f, -.5f, 0.0f,
        .5f, -.5f, 0.0f,
        .75f, .5f, 0.0f,
        // triangle two
        -1.f, -.5f, 0.0f,
        -.5f, -.5f, 0.0f,
        -.75f, .5f, 0.0f
    };

static float triangleOne[] =
    {
        0.f, -0.5f, 0.f,
        -.9f, -.5f, 0.f,
        -.45f, .5f, 0.f
    };
static float triangleTwo[] = 
    {
        .9f, -.5f, 0.f,
        .0f, -.5f, 0.f,
        .45f, .5f, 0.f
    };

static float cubeverticies[] =
    {// Positions            // Texture Coords

    // Front face
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 0 - Bottom-left
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 1 - Bottom-right
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 2 - Top-right
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 3 - Top-left

    // Back face
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 4 - Bottom-left
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 5 - Bottom-right
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 6 - Top-right
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 7 - Top-left

    // Left face
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 8 - Bottom-left (relative to this face)
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 9 - Bottom-right
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 10 - Top-right
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 11 - Top-left

    // Right face
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 12 - Bottom-left
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 13 - Bottom-right
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 14 - Top-right
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 15 - Top-left

    // Top face
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, // 16 - Bottom-left
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, // 17 - Bottom-right
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 18 - Top-right
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 19 - Top-left

    // Bottom face
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 20 - Bottom-left
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 21 - Bottom-right
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, // 22 - Top-right
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f  // 23 - Top-left
    
    };

static unsigned int cubeIndicies[] =
    {
    0,1,2, // bl, br, tr
    2,3,0, // tr, tl, bl
    // back face
    4,5,6,
    6,7,4,
    // left face
    8,9,10,
    10,11,8,
    // right face
    12,13,14,
    14,15,12,
    // top face
    16,17,18,
    18,19,16,
    // bottom face
    20,21,22,
    22,23,20
};

static glm::vec3 cubePositions[] =
{
    glm::vec3( 0.0f, 0.0f, 0.0f),
    glm::vec3( 2.0f, 5.0f, -15.0f),
    glm::vec3( -1.5f, -2.2f, -2.5f),
    glm::vec3( -3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3( -1.7f, 3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f, 2.0f, -2.5f),
    glm::vec3( 1.5f, 0.2f, -1.5f),
    glm::vec3( -1.3f, 1.0f, -1.5f),
};

static unsigned int indicies[]
{
    0,1,2,
    2,3,0
};
