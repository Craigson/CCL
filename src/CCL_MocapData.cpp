//
//  CCL_MocapData.cpp
//  CCL_JSON
//
//  Created by Gene Han on 8/28/15.
//
//

#include "CCL_MocapData.h"

using namespace ci;
using namespace std;
/*
CCL_MocapData::CCL_MocapData(int skip){
    CCL_MocapData(URL_STREAM_JSON, skip);
};

CCL_MocapData::CCL_MocapData(const string &url, int skip = 1, std::vector<CCL_MocapJoint>& mJoints){
    try{
        const JsonTree json( loadUrl(url) ); //LOAD JSON FILE CONTAINING UUIDs

        //CHECK EACH UUID AND SORT INTO JOINTS
        
        //LOOP THROUGH STREAMS
        for( auto &stream : json.getChildren() ){

            const string &uuid = stream["uuid"].getValue();
            string title = stream["title"].getValue();
            if( stream.hasChild("group")){
                string group = stream["group"].getValue();
          //      std::cout << "group:"<< group << " title:" << title << " uuid[" << i << "] = " << uuid << std::endl;
                addUUIDtoJoint(group, title, uuid, skip, mJoints);
            }
        }
    }
    catch( ci::Exception &exc ) {
        std::cout << "Failed to parse json, what: " << exc.what() << std::endl;
    }
    

};
*/
CCL_MocapData::CCL_MocapData(int skip, std::vector<CCL_MocapJoint>& mJoints)
{
    try{
        const JsonTree json( loadUrl(URL_STREAM_JSON) ); //LOAD JSON FILE CONTAINING UUIDs
        
        //CHECK EACH UUID AND SORT INTO JOINTS
        
        //LOOP THROUGH STREAMS
        
        int counter = 0;
        for( auto &stream : json.getChildren() ){
        
        //for( int i =0; i < 3; i++){
            
            const string &uuid = stream["uuid"].getValue();
            string title = stream["title"].getValue();
            if( stream.hasChild("group")){
                string group = stream["group"].getValue();
                //      std::cout << "group:"<< group << " title:" << title << " uuid[" << i << "] = " << uuid << std::endl;
                if (counter < 9){
                    
                    addUUIDtoJoint(group, title, uuid, skip, mJoints);
                    counter++;
                }
                
            }
        
        }
    }

    catch( ci::Exception &exc ) {
        std::cout << "Failed to parse json, what: " << exc.what() << std::endl;
    }
    
    
};



void CCL_MocapData::addUUIDtoJoint(string grp, string title, const string uuid, int skip, std::vector<CCL_MocapJoint>& mJoints){
 //   std::cout << "add - grp:"<<grp<< " title:"<<title<<" uuid:"<<uuid<<std::endl;

    bool hasFound = false;
    for(int i = 0; i < mJoints.size(); i++) {
        CCL_MocapJoint joint = mJoints[i];
        if( joint.jointName == grp  ){
            hasFound = true;
            mJoints[i].addUUID(title, uuid);
            i = mJoints.size();
        }
    }
    
    if( !hasFound ){
        CCL_MocapJoint joint = CCL_MocapJoint(grp, skip);
        std::cout << "total joints: " << mJoints.size() + 1 << std::endl;
        joint.addUUID(title, uuid);
        mJoints.push_back(joint);
//        cout<<"[JOINT NUM]"<<mJoints.size()<<endl <<endl;
        
    }
    
};



