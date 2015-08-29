//
//  Body.h
//  CCL
//
//  Created by Craig Pickard on 8/28/15.
//
//

#pragma once

#include <stdio.h>
#include "Joint.h"

class Body {
    
    std::vector<Joint> joints;
    
    Body();
    
    void render();
    void update();
    
};