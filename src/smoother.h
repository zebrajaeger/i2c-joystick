#include <Arduino.h>

#include "types.h"

class Smoother
{
public:
    Smoother(uint8_t windowSize) : values_(new u16_t[windowSize]), size_(windowSize), index_(0)
    {
        for (uint8_t i = 0; i < size_; ++i)
        {
            values_[i].uint16 = 0;
        }
    }

    void addValue(u16_t value)
    {
        values_[index_++] = value;
        index_ %= size_;
    }

    u16_t getValue()
    {
        u32_t result;
        result.uint32 = 0;
        for (uint8_t i = 0; i < size_; ++i)
        {
            result.uint32 += values_[i].uint16;
        }
        result.uint32 /= size_;

        u16_t x;
        x.uint16 = result.uint32;
        return x;
    }

private:
    u16_t *values_;
    uint8_t index_;
    uint8_t size_;
};