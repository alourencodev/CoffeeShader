#ifndef COFFEE_SHAPES_HPP
#define COFFEE_SHAPES_HPP

#include <vector>

namespace coffee::shapes
{

static const std::vector<float> k_cube = {
    1.0f,1.0f,1.0f,    -1.0f,1.0f,1.0f,   -1.0f,-1.0f,1.0f,   1.0f,-1.0f,1.0f,    
    1.0f,1.0f,1.0f,     1.0f,-1.0f,1.0f,   1.0f,-1.0f,-1.0f,  1.0f,1.0f,-1.0f,    
    1.0f,1.0f,1.0f,     1.0f,1.0f,-1.0f,  -1.0f,1.0f,-1.0f,  -1.0f,1.0f,1.0f,     
    -1.0f,-1.0f,-1.0f, -1.0f,1.0f,-1.0f,   1.0f,1.0f,-1.0f,   1.0f,-1.0f,-1.0f,   
    -1.0f,-1.0f,-1.0f, -1.0f,-1.0f,1.0f,  -1.0f,1.0f,1.0f,   -1.0f,1.0f,-1.0f,    
    -1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f,  1.0f,-1.0f,1.0f,   -1.0f,-1.0f,1.0f  
};

static const std::vector<float> k_cubeFaceColors = {
    1.0f,0.0f,0.0f,  1.0f,0.0f,0.0f,  1.0f,0.0f,0.0f,  1.0f,0.0f,0.0f,    
    0.0f,1.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,1.0f,0.0f,     
    0.0f,0.0f,1.0f,  0.0f,0.0f,1.0f,  0.0f,0.0f,1.0f,  0.0f,0.0f,1.0f,     
    1.0f,1.0f,0.0f,  1.0f,1.0f,0.0f,  1.0f,1.0f,0.0f,  1.0f,1.0f,0.0f,     
    0.0f,1.0f,1.0f,  0.0f,1.0f,1.0f,  0.0f,1.0f,1.0f,  0.0f,1.0f,1.0f,     
    1.0f,0.0f,1.0f,  1.0f,0.0f,1.0f,  1.0f,0.0f,1.0f,  1.0f,0.0f,1.0f
};

}

#endif