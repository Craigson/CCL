//
//  Joint.cpp
//  CCL
//
//  Created by Craig Pickard on 8/28/15.
//
//

#include "Joint.h"

using namespace ci;

Joint::Joint()
{
    
    
};

Joint::Joint(const std::list<glm::vec3>& jsonData, const ci::gl::GlslProgRef& mShader){

    mPositions = jsonData; //STORE THE X,Y,Z POSITION VALUES IN A LIST
    mSphereBatch = gl::Batch::create( geom::Sphere(), mShader );  //CREATE A BATCH FOR THE SPHERE
    jointName = "";
    
    //SIFT THROUGH THE POSITION DATA AND EXTRACT THE JOINT NAME AND X,Y,Z COMPONENTS
    float tempX, tempY, tempZ;
    
    
}

void Joint::update(){
    
}


void Joint::render()
{
    gl::color( 1, 0, 0 );
    gl::ScopedModelMatrix modelScope;
    mSphereBatch->draw();
}