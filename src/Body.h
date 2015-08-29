//
//  Body.h
//  CCL
//
//  Created by Craig Pickard on 8/28/15.
//
//

#pragma once

#include <stdio.h>
#include "CCL_MocapJoint.h"

class Body {
    
    Body(const std::vector<CCL_MocapJoint>& jointList);
    
    void render();
    void update();
    
};