/**
 * @file AverageCounter.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Class for containing info and count average
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

 /**
  * @brief Class for containing info and count average
  *
  */
template<typename SumType>
class AverageCounter {
public:
    AverageCounter() : sum(0), count(0) {};

    void operator+=(const SumType& value) { sum += value; ++count; };

    operator SumType() const { return sum / count; }

    void clear() { sum = 0; count = 0; }

private:
    SumType sum;
    int count;
};
