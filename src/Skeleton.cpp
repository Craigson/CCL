//
//  Skeleton.cpp
//  CCL
//
//  Created by Craig Pickard on 8/29/15.
//
//

#include "Skeleton.h"

Skeleton::Skeleton(){}

Skeleton::Skeleton(const std::vector<glm::vec3>& jointPos)
{
    boneJoints = jointPos;
  //  cinder::gl::Batch::create(cinder::geom::LINES, mGlsl);
    
 //   mSkeletonMesh = ci::gl::VertBatch::create( GL_LINES );
    
   // blahblah = ci::gl::VboMesh::create(cinder::geom::LINES, solidShader);

    
    
    head = boneJoints[0];
    r_shoulder = boneJoints[6];
    r_elbow = boneJoints[8];
    r_hand = boneJoints[9];
    l_shoulder = boneJoints[13];
    l_elbow = boneJoints[16];
    l_hand = boneJoints[17];
    spine_base = boneJoints[27];
    spine_top = boneJoints[21];
//  r_hip = boneJoints[30];
    r_hip = boneJoints[28];
    r_knee = boneJoints[34];
    r_foot = boneJoints[35];
//  l_hip = boneJoints[31];
    l_hip = boneJoints[29];
    l_knee = boneJoints[43];
    l_foot = boneJoints[44];
    
    
    
     }

void Skeleton::render()
    {
        ci::gl::color(1.,1.,1.);
        ci::gl::lineWidth(5);
        
        //NECK
        //ci::gl::drawLine(head,spine_top);
        
        //TORSO
        ci::gl::drawLine(r_shoulder, l_shoulder);
        ci::gl::drawLine(spine_top, spine_base);
        ci::gl::drawLine(spine_base, r_hip);
        ci::gl::drawLine(spine_base, l_hip);
        
        //RIGHT ARM
        ci::gl::drawLine(r_shoulder, r_elbow);
        ci::gl::drawLine(r_elbow, r_hand);
        
        //LEFT ARM
        ci::gl::drawLine(l_shoulder, l_elbow);
        ci::gl::drawLine(l_elbow, l_hand);
        
        //RIGHT LEG
        ci::gl::drawLine(r_hip, r_knee);
        ci::gl::drawLine(r_knee, r_foot);
        
        //LEFT LEG
        ci::gl::drawLine(l_hip, l_knee);
        ci::gl::drawLine(l_knee, l_foot);

    }

void Skeleton::update(const std::vector<glm::vec3>& pos){

    boneJoints = pos;

    head = boneJoints[0];
    r_shoulder = boneJoints[6];
    r_elbow = boneJoints[8];
    r_hand = boneJoints[9];
    l_shoulder = boneJoints[13];
    l_elbow = boneJoints[16];
    l_hand = boneJoints[17];
    spine_base = boneJoints[27];
    spine_top = boneJoints[21];
    r_hip = boneJoints[28];
    r_knee = boneJoints[34];
    r_foot = boneJoints[35];
    l_hip = boneJoints[29];
    l_knee = boneJoints[43];
    l_foot = boneJoints[44];
    
    std::cout << l_foot << std::endl;
    
}

