#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CameraUi.h"
#include "cinder/Json.h"

#include "CCL_MocapData.h"

using namespace ci;
using namespace ci::app;
using namespace std;

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
    void initData();                                           //METHOD FOR IMPORTING JSON DATA
    
    //CREATE A BATCH VERTEX FOR THE FLOOR MESH
    gl::VertBatchRef	mGridMesh;
    
    //TEST SPHERE
    gl::BatchRef        mSphereBatch;
    
    gl::GlslProgRef		mGlsl;
    
    CameraPersp			mCamera;
    CameraUi			mCamUi;
    
    std::vector<CCL_MocapJoint> jointList;  //GLOBAL CONTAINER TO HOLD THE JOINT POSITIONS
    
private:
   
    
   
    
};

//--------------------- SETUP ----------------------------------

void CCLApp::setup()
{
    //SETUP THE 3D ENVIRONMENT
    setupEnviron( 500, 500, 10 );
    
    //SETUP THE CAMERA
    mCamera.lookAt( vec3( 100, 100, 10 ), vec3( 0 ) );
    
    //mCamera.setEyePoint(vec3(0,200,650));
    mCamUi = CameraUi( &mCamera, getWindow() );
    
    
        // SHADER TEST CODE ------------------
        
        gl::GlslProgRef solidShader = gl::getStockShader( gl::ShaderDef().color() );
        
        mGlsl = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );
        
        mSphereBatch = gl::Batch::create( geom::Sphere(), solidShader );
        
        gl::enableDepthWrite();
        gl::enableDepthRead();
        
        // -----------------------------------------
    
   /*
    initData(); //IMPORT THE JSON DATA AND SORT IT INTO A LIST
    
    for (int i = 0; i < 1; i++){
        for (int j = 0; j < jointList[i].jointPositions.size(); j++){
            std::cout << j << ": " << jointList[i].jointPositions[j] << std::endl;
        }
    }
    */
    
}

//--------------------- MOUSEDOWN ------------------------------

void CCLApp::mouseDown( MouseEvent event )
{
}


//----------------------- UPDATE -------------------------------

void CCLApp::update()
{
  //  std::cout << mCamera.getEyePoint() << std::endl;
}

//--------------------------- DRAW -----------------------------

void CCLApp::draw()
{
    gl::clear();
    renderScene();
    

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
    const Colorf defaultColor( 0.2f, 0.2f, 0.2f);
    const Colorf black( 0, 0, 0 );
    
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
    gl::setMatrices( mCamera );
    mGridMesh->draw();
    
    gl::color( 1, 0, 0 );
    gl::ScopedModelMatrix modelScope;
    mSphereBatch->draw();
    gl::popMatrices();

}

//-------------------- IMPORT DATA -------------------------

void CCLApp::initData()
{
  
    CCL_MocapData jsonData  = CCL_MocapData(1, jointList);
    
     std::cout << jointList.size()<< endl;
     std::cout << endl;
     std::cout << endl;
     std::cout << endl;
    
    
}

//-------------------------------------------------------------

CINDER_APP( CCLApp, RendererGl, [&]( App::Settings *settings ) {
    settings->setWindowSize( 1280, 720 );
} )
