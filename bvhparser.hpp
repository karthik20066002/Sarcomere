#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "skeleton.hpp"
#include <stack>


struct PendingJoint{
    friend class BVHParser;
    std::string name{};
    int index{};
    LocalTransform offset{};
    std::vector<Channel> channels{};
    int parentIndex{0};
    PendingJoint(std::string name, int index, LocalTransform offset, std::vector<Channel> channels, int parentIndex) : name(name), index(index), offset(offset), channels(channels), parentIndex(parentIndex) {}
};
class BVHParser {
    protected:
        std::string name;

    public:
        Skeleton createNewSkeleton(const std::string& name, int index);
        int addJointToSkeleton(Skeleton& skeleton, const Joint& joint);
        MotionData parseBVHfile(const std::string& filename, Skeleton& skeleton, int parentIndex = 0);
        void PrintSkeleton(const Skeleton& skeleton, const MotionData& motionData);
};