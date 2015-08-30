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

    
    
    head = jointPos[0];
    r_shoulder = jointPos[6];
    r_elbow = jointPos[8];
    r_hand = jointPos[9];
    l_shoulder = jointPos[13];
    l_elbow = jointPos[16];
    l_hand = jointPos[17];
    spine_base = jointPos[27];
    spine_top = jointPos[21];
    r_hip = jointPos[30];
    r_knee = jointPos[34];
    r_foot = jointPos[35];
    l_hip = jointPos[31];
    l_knee = jointPos[43];
    l_foot = jointPos[44];
    
//    mSkeletonVbo = ci::gl::Vbo::create( GL_ARRAY_BUFFER, boneJoints.size() * sizeof(glm::vec3), boneJoints.data(), GL_DYNAMIC_DRAW );
    
    
//    const ci::ColorA skeletonColour( 0.9f, 0.9f, 0.9f,0.3f);
//
//    mSkeletonMesh->color(skeletonColour);
//    
    
    /*
    //HEAD
    mSkeletonMesh->vertex(head);
    mSkeletonMesh->vertex(spine_top);
    
    //TORSO
    mSkeletonMesh->vertex(r_shoulder);
    mSkeletonMesh->vertex(l_shoulder);
    mSkeletonMesh->vertex(spine_top);
    mSkeletonMesh->vertex(spine_base);
    mSkeletonMesh->vertex(spine_base);
    mSkeletonMesh->vertex(r_hip);
    mSkeletonMesh->vertex(spine_base);
    mSkeletonMesh->vertex(l_hip);
    
    //RIGHT ARM
    
    //RIGHT LEG
    
    //LEFT ARM
    
    //LEFT LEG

     */
    
    
    
     }

void Skeleton::render()
    {
        ci::gl::color(1.,1.,1.);
        ci::gl::lineWidth(5);
        ci::gl::drawLine(head,spine_top);
        std::cout << "should be drawing" << std::endl;
    }

void Skeleton::update(const std::vector<glm::vec3>& pos){
    
    
    //REPLACE VBOMESH
    
   // glm::vec3 *boneJoints = (glm::vec3*)mInstanceDataVbo->mapReplace();

    /*
    boneJoints[0] = positions[0];
    boneJoints[1] = positions[6];
    boneJoints[2] = positions[8];
    boneJoints[3] = positions[9];
    boneJoints[4] = positions[13];
    boneJoints[5] = positions[16];
    boneJoints[6] = positions[17];
    boneJoints[7] = positions[27];
    boneJoints[8] = positions[21];
    boneJoints[9] = positions[30];
    boneJoints[10] = positions[34];
    boneJoints[11] = positions[35];
    boneJoints[12] = positions[31];
    boneJoints[13] = positions[43];
    boneJoints[14] = positions[44];
    */
    
    head = pos[0];
    spine_top = pos[21];
    
    std::cout << head << " " << spine_top << std::endl;

    
   // mInstanceDataVbo->unmap();
}

