#pragma once

#include <string>
#include <vector>
#include "joint.hpp"

struct Skeleton {
    friend class BVHParser;
    std::string name;
    int index;
    std::vector<Joint> joints;
    Skeleton(std::string name, int index) : name(name), index(index) {}

    protected:
        void addJoint(Joint joint) {
            joints.push_back(joint);
        }

        void moveJoint(int jointIndex, float x, float y, float z); 
        Joint createNewJoint(const std::string& name, int index, LocalTransform localOffset, std::vector<Channel> channelList, int parentIndex);
};



