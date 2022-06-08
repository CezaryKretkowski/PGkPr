//
// Created by Lothar on 24.03.2022.
//

#ifndef PGKPR_DIRECTIONSTRATEGY_H
#define PGKPR_DIRECTIONSTRATEGY_H
#include <glm/glm.hpp>
class DirectionStrategy{
public:
    virtual ~DirectionStrategy(){}
    virtual glm::vec3 calculateDirection(){
        return glm::vec3 (0.0f,-10.0f,0.0f);
    }
};
#endif //PGKPR_DIRECTIONSTRATEGY_H
