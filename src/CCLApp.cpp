#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CameraUi.h"
#include "cinder/Json.h"

#include "CCL_MocapData.h"
#include "Skeleton.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/*----------------------- NOTES FOR IMPROVEMENTS ---------------------------
 
 CHANGE ALL vectors TO lists TO IMPROVE EFFICIENCY (AS NO RANDOM INDEX ACCESS IS
 REQUIRED - USE ITERS.
 
 
 
 
 
 --------------------------------------------------------------------------*/

//GLOBAL VARIABLES
//const float DRAW_SCALE = 200;       //SCALE FOR DRAWING THE POINTS
int FRAME_COUNT;
int TOTAL_FRAMES;

class CCLApp : public App {
  public:
   // static void prepareSettings( Settings *settings );
    
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseDrag (MouseEvent event) override;
	void update() override;
	void draw() override;
    
    void setupEnviron( int xSize, int zSize, int spacing );     //METHOD FOR SETTING UP THE 3D ENVIRONMENT
    void renderScene();                                         //METHOD FOR RENDERING THE 3D ENVIRONMENT
    void initData();                                            //METHOD FOR IMPORTING JSON DATA
    void setupShader();
    
    std::vector<vec3> distortLimbs(const std::vector<vec3>& normalLimbs, float scaleFactor);
    
    //CREATE A VERTEX BATCH FOR THE FLOOR MESH
    gl::VertBatchRef	mGridMesh;
    
    CameraPersp			mCamera;
    CameraUi			mCamUi;
    
    std::vector<CCL_MocapJoint> jointList;  //GLOBAL CONTAINER TO HOLD THE JOINT POSITIONS
    
    //TEST SPHERES
    gl::BatchRef        mSphereBatch;
    gl::VboRef			mInstanceDataVbo;
    
    gl::GlslProgRef		mGlsl;
    gl::GlslProgRef     solidShader;
    
    int numJoints;
    
    // create an array of initial per-instance positions laid out in a 2D grid
    //std::vector<glm::vec3> jointPositions;
    
    //CREATE A CONTAINER TO STORE THE POSITION OF EACH JOINT FOR A SINGLE FRAME
    std::vector<glm::vec3> framePositions;
    
    
    typedef vector<glm::vec3>::size_type bodySize;
    // bodySize sizeOfBody = jointPositions.size();
    
    Skeleton skeleton;
    
    std::vector<glm::vec3> distortedJoints;
    
    bool limbsDistorted;
    
};


//--------------------- SETUP ----------------------------------

void CCLApp::setup()
{
    
    setFrameRate(12);
    
    //SETUP THE 3D ENVIRONMENT
    setupEnviron( 5000, 5000, 100 );
    
    //SETUP THE CAMERA
    mCamera.lookAt( vec3( 100, 100, 10 ), vec3( 0 ) );
    
    mCamera.setFarClip(20000);
    
    //mCamera.setEyePoint(vec3(0,200,650));
    mCamUi = CameraUi( &mCamera, getWindow() );
    
    setupShader();
    
    initData(); //IMPORT THE JSON DATA AND SORT IT INTO A LIST
    
    limbsDistorted = true;
    
    /* THIS JUST PRINTS OUT THE POSITIONS OF THE FIRST JOINT TO CHECK THAT IT'S LOADED CORRECTLY
    for (int i = 0; i < 1; i++){
        for (int j = 0; j < jointList[i].jointPositions.size(); j++){
            std::cout << j << ": " << jointList[i].jointPositions[j] << std::endl;
        }
    }
    */
    
    
    FRAME_COUNT = 0;
    TOTAL_FRAMES = jointList[0].jointPositions.size(); //SHOULD PROBABLY PUT A TRY/CATCH HERE
    
    std::cout << "total frames: " << TOTAL_FRAMES << std::endl;
    
    gl::VboMeshRef body = gl::VboMesh::create( geom::Sphere().subdivisions( 16 ).radius(2) );
    
    
    // CREATE THE SPHERES AT THE INITIAL JOINT LOCATIONS
    for ( int i = 0; i < jointList.size(); ++i ) {
        float instanceX = jointList[i].jointPositions[0].x;
        float instanceY = jointList[i].jointPositions[0].y;
        float instanceZ = jointList[i].jointPositions[0].z;
       // float instanceZ = 0;

        framePositions.push_back( vec3( instanceX, instanceY, instanceZ));
    }
    
    skeleton = Skeleton(framePositions);
    
    //std::cout << "positions: " << positions[0] << std::endl;
    
    
    
    // create the VBO which will contain per-instance (rather than per-vertex) data
    mInstanceDataVbo = gl::Vbo::create( GL_ARRAY_BUFFER, framePositions.size() * sizeof(vec3), framePositions.data(), GL_DYNAMIC_DRAW );
    
    // we need a geom::BufferLayout to describe this data as mapping to the CUSTOM_0 semantic, and the 1 (rather than 0) as the last param indicates per-instance (rather than per-vertex)
    geom::BufferLayout instanceDataLayout;
    
    instanceDataLayout.append( geom::Attrib::CUSTOM_0, 3, 0, 0, 1 /* per instance */ );
    
    //NOW ADD IT TO THE VBO MESH THAT WE INITIAL CREATED FOR THE BODY / SKELETON
    body->appendVbo( instanceDataLayout, mInstanceDataVbo );
    
    //FINALLY, BUILD THE BATCH, AND MAP THE CUSTOM_0 ATTRIBUTE TO THE "vInstancePosition" GLSL VERTEX ATTRIBUTE
    mSphereBatch = gl::Batch::create( body, mGlsl, { { geom::Attrib::CUSTOM_0, "vInstancePosition" } } );
    
    gl::enableDepthWrite();
    gl::enableDepthRead();
    
    //PRINT OUT JOINT INDEX AND NAME OF JOINT
    
    for (int i = 0; i < jointList.size(); i++)
    {
        std::cout << "index: " << i << ", Joint name: " << jointList[i].jointName << std::endl;
    }
    
    
    
}

//--------------------- MOUSEDOWN ------------------------------

void CCLApp::mouseDown( MouseEvent event )
{
}


//----------------------- UPDATE -------------------------------

void CCLApp::update()
{
  //  std::cout << mCamera.getEyePoint() << std::endl;
    
    //UPDATE POSITIONS
    //MAP INSTANCE DATA TO VBO
    //WRITE NEW POSITIONS
    //UNMAP
    
    glm::vec3 *newPositions = (glm::vec3*)mInstanceDataVbo->mapReplace();
    
    for( int i = 0; i < jointList.size(); ++i ) {

        float instanceX = jointList[i].jointPositions[FRAME_COUNT].x;
        float instanceY = jointList[i].jointPositions[FRAME_COUNT].y;
        float instanceZ = jointList[i].jointPositions[FRAME_COUNT].z;

        vec3 newPos(vec3(instanceX,instanceY, instanceZ)); //CREATE A NEW VEC3 FOR UPDATING THE VBO
        
        framePositions[i] = newPos;
        
        //distortedJoints.push_back(newPos);
        
    }
    
    //REPLACE VEC3s IN VBO BY INCREMENTING THE POINTER
    for (int i = 0; i < framePositions.size(); i++){
        *newPositions++ = framePositions[i];
    }
    
    //CHECK WHETHER THE LIMBS ARE DISTORED
    if (limbsDistorted){
    skeleton.update(distortLimbs(framePositions,5));
    } else {
        skeleton.update(framePositions);
    }
    

    mInstanceDataVbo->unmap();
   // std::cout << "position: " << positions[0] << std::endl;

    
    
    //MANUALLY INCREMENT THE FRAME, IF THE FRAME_COUNT EXCEEDS TOTAL FRAMES, RESET THE COUNTER
    if (FRAME_COUNT < TOTAL_FRAMES)
    {
    FRAME_COUNT += 1;
    } else {
        FRAME_COUNT = 0;
    }
    
   // std::cout << "frame rate: " << getAverageFps() << ", frame count: " << FRAME_COUNT << std::endl;
}

//--------------------------- DRAW -----------------------------

void CCLApp::draw()
{
    
    gl::clear(Color(0.1f,0.1f,0.1f) );
    
    gl::setMatrices( mCamera );
    
   
    
    renderScene();
    
    gl::color( 1, 0, 0 );
    //gl::ScopedModelMatrix modelScope;
    //mSphereBatch->drawInstanced( sizeOfBody );
    
    mSphereBatch->drawInstanced( jointList.size() );
     skeleton.render();


}

//------------------- MOUSE DRAGGED ------------------------------

void CCLApp::mouseDrag( MouseEvent event )
{
    mCamUi.mouseDrag( event );
}

//------------------- SETUP THE ENVIRONMENT / GRID -----------------------

void CCLApp::setupEnviron( int xSize, int zSize, int spacing )
{
    CI_ASSERT( ( spacing <= xSize ) && ( spacing <= zSize ) );
    
    // Cut in half and adjust for spacing.
    xSize = ( ( xSize / 2 ) / spacing ) * spacing;
    zSize = ( ( zSize / 2 ) / spacing ) * spacing;
    
    const int xMax = xSize + spacing;
    const int zMax = zSize + spacing;
    const ColorA defaultColor( 0.9f, 0.9f, 0.9f,0.1f);
    const ColorA black( 0, 0, 0, 1 );
    
    mGridMesh = gl::VertBatch::create( GL_LINES );
    
    // Add x lines.
    for( int xVal = -xSize; xVal < xMax; xVal += spacing ) {
        mGridMesh->color( defaultColor );
        mGridMesh->vertex( (float)xVal, 0, (float)-zSize );
        mGridMesh->vertex( (float)xVal, 0, (float)zSize );
    }// end for each x dir line
    
    // Add z lines.
    for( int zVal = -zSize; zVal < zMax; zVal += spacing ) {
        mGridMesh->color( defaultColor );
        mGridMesh->vertex( (float)xSize, 0, (float)zVal );
        mGridMesh->vertex( (float)-xSize, 0, (float)zVal );
    }// end for each z dir line
}


//------------------ RENDER THE SCENE ------------------------

void CCLApp::renderScene()
{
    
    gl::pushMatrices();
    mGridMesh->draw();
    gl::popMatrices();
}

//-------------------- IMPORT DATA -------------------------

void CCLApp::initData()
{
    //CREATE AND INITIALISE A CCL_MOCAPDATA OBJECT, PASSING IN THE GLOBAL "jointList" AS A REFERENCE
     CCL_MocapData("CLL_JOINT.json",jointList);
 //    CCL_MocapData(1, jointList); //UNCOMMENT THIS LINE TO CAPTURE NEW JSON DATA
     std::cout << jointList.size()<< endl;
     std::cout << endl;
     std::cout << endl;
     std::cout << endl;
    
    
}
                            
//--------------------- SETUP SHADERS -----------------------

void CCLApp::setupShader(){

    //CHOOSE BETWEEN solidShader AND mGlsl AS SHADERS FOR THE SPHERES
    solidShader = gl::getStockShader( gl::ShaderDef().color() );
    mGlsl = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );
    mSphereBatch = gl::Batch::create( geom::Sphere(), solidShader );
}

//----------------------- DISTORT LIMBS -----------------------
std::vector<glm::vec3> CCLApp::distortLimbs(const std::vector<vec3>& normalLimbs, float scaleFactor){
    
    //[8] r_elbow
    //[9] r_upper_wrist
    //[10] r_lower_wrist
    //[12]r_thumb
    //[13]r_pinky
    
    std::vector<vec3> distortedVectors = normalLimbs;
    
    glm::vec3 forearmDirection =  normalLimbs[8] - normalLimbs[9];
    float forearmLength = distance(normalLimbs[9],normalLimbs[8]);
    glm::vec3 newArm = normalize(forearmDirection);
    glm::vec3 newWrist = normalLimbs[8] + newArm;
    
    distortedVectors[8] = newWrist*2.0f;
    
    return distortedVectors;
    
}

//-------------------------------------------------------------

CINDER_APP( CCLApp, RendererGl, [&]( App::Settings *settings ) {
    settings->setWindowSize( 1280, 720 );
} )
