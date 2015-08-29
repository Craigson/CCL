#pragma once

#include "cinder/Json.h"
#include "CCL_MocapJoint.h"
#include "cinder/Vector.h"
#include "Jzon.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CCL_MocapData {
public:
 //   CCL_MocapData(int skip);
 //   CCL_MocapData(const string &url, int skip);
    CCL_MocapData(int skip, std::vector<CCL_MocapJoint>& mJoints);
    CCL_MocapData(string filename, vector<CCL_MocapJoint>& mJoints);
    
    void loadChannel(const string &url, int skip);
    void addUUIDtoJoint( string grp,  string title,  string uuid, int skip, std::vector<CCL_MocapJoint>& mJoints);

//    vector<CCL_MocapJoint> mJoints;
    
    
private:
    // default URL
    static constexpr const char* URL_STREAM_JSON = "http://api.piecemeta.com/channels/c51be7cc-a985-4c4a-a53b-fa034d33fff8/streams.json";
    static constexpr const char * URL_STREAM_REQ = "http://api.piecemeta.com/streams/";
};