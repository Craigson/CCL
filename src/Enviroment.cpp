//
//  Enviroment.cpp
//  CCL
//
//  Created by Craig Pickard on 8/28/15.
//
//

#include "Enviroment.h"

Environment::Environment()
{

    sizeX, sizeY;
    glm::vec3 origin;
    
    CI_ASSERT( ( spacing <= xSize ) && ( spacing <= zSize ) );
    
    // Cut in half and adjust for spacing.
    xSize = ( ( xSize / 2 ) / spacing ) * spacing;
    zSize = ( ( zSize / 2 ) / spacing ) * spacing;
    
    const int xMax = xSize + spacing;
    const int zMax = zSize + spacing;
    const Colorf defaultColor( 0.75f, 0.75f, 0.75f );
    const Colorf black( 0, 0, 0 );
    
    mGridMesh = gl::VertBatch::create( GL_LINES );
    
    // Add x lines.
    for( int xVal = -xSize; xVal < xMax; xVal += spacing ) {
        if( xVal == 0 ) // Center line.
            mGridMesh->color( black );
        else
            mGridMesh->color( defaultColor );
        mGridMesh->vertex( (float)xVal, 0, (float)-zSize );
        mGridMesh->vertex( (float)xVal, 0, (float)zSize );
    }// end for each x dir line
    
    // Add z lines.
    for( int zVal = -zSize; zVal < zMax; zVal += spacing ) {
        if( zVal == 0 ) // Center line.
            mGridMesh->color( black );
        else
            mGridMesh->color( defaultColor );
        
        mGridMesh->vertex( (float)xSize, 0, (float)zVal );
        mGridMesh->vertex( (float)-xSize, 0, (float)zVal );
    }// end for each z dir line
    
}

    
    
void Environment::setupGrid()
{
    

}
    
void Environment::render()
{
    
    
}

