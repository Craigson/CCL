//
//  Joint.h
//  CCL
//
//  Created by Craig Pickard on 8/28/15.
//
//

#pragma once

#include <stdio.h>


class Joint {
    
    glm::vec3 pos;
    
    Joint();
    Joint(const std::list<glm::vec3>& jsonData, const ci::gl::GlslProgRef& mShader);
    
    std::list<glm::vec3>    mPositions;
    
    ci::gl::BatchRef        mSphereBatch;
    
    void render();
    void update();
    
    
};

