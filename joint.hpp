#pragma once

#include <string>
#include <vector>
struct LocalTransform {
    float x;
    float y;
    float z;
    LocalTransform() : x(0.0f), y(0.0f), z(0.0f) {}
    LocalTransform(float x, float y, float z) : x(x), y(y), z(z) {}
    };
        enum class Channel {
            PosX,
            PosY,
            PosZ,
            RotX,
            RotY,
            RotZ
        };
class Joint {
    friend struct Skeleton;
    friend class BVHParser;
    private:
        std::string name;
        int index;
        LocalTransform offset;
        std::vector<Channel> channels;
        int parentIndex;

    protected:
        LocalTransform moveLocalTransform(LocalTransform offset, float x, float y, float z) {
            //how do i implement a transform, Fourier? matrix multiplication?
            // For now, just return the current LocalTransform
            return {offset.x + x, offset.y + y, offset.z + z};
        };
        Joint(std::string name, int index, LocalTransform localOffset, std::vector<Channel> channelList, int parentIndex) : name(name), index(index), offset(localOffset), channels(channelList), parentIndex(parentIndex) {}

        public:
        
};