#pragma once

#include <string>
#include <vector>
#include "joint.hpp"


struct MotionData {
    int frameCount;
    float frameTime;
    std::vector<std::vector<float>> motionValues;
    MotionData() : frameCount(0), frameTime(0.0f), motionValues({}) {}
    MotionData(int frameCount, float frameTime, std::vector<std::vector<float>> motionValues) : frameCount(frameCount), frameTime(frameTime), motionValues(motionValues) {}
};

struct Skeleton {
    friend class BVHParser;
    std::string name;
    int index;
    MotionData motion;
    std::vector<Joint> joints;
    Skeleton(std::string name, int index) : name(name), index(index) {}

    protected:
        void addJoint(Joint joint) {
            joints.push_back(joint);
        }

        Joint createNewJoint(const std::string& name, int index, LocalTransform localOffset, std::vector<Channel> channelList, int parentIndex);
};



