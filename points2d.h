// Ceren Serpin
// This class holds a bunch of 2D points with pair values
// Can Add two groups of points together, print them out, copy them, move them, and read them from input

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

#include <cstdlib>
#include <utility>

namespace teaching_project
{

    // Points 2D is a class that stores a list of 2D points
    // Ability to create, copy, move, add, or print
    template <typename Object>
    class Points2D
    {
    public:
        // Default "big five" -- you have to alter them for your assignment.
        // That means that you will remove the "= default" statement.
        //  and you will provide an implementation.

        // Zero-parameter constructor.
        // Set size to 0.

        // Default constructor
        //  Starts with no points
        Points2D() : sequence_(nullptr),
                     size_(0) {}

        // Copy-constructor.
        // Makes a copy of another Points 2D object with its own memeory
        Points2D(const Points2D &rhs) : sequence_(nullptr), size_(rhs.size_)
        {
            if (size_ > 0)
            {
                // allocate space for new  points
                sequence_ = new std::array<Object, 2>[size_];

                // copy each point
                for (size_t i = 0; i < size_; i++)
                {
                    sequence_[i] = rhs.sequence_[i];
                }
            }
        }

        // Copy-assignment. If you have already written
        // the copy-constructor and the move-constructor
        // you can just use:
        // {
        // Points2D copy = rhs;
        // std::swap(*this, copy);
        // return *this;
        // }

        // replaces current obj wwith copy
        Points2D &operator=(const Points2D &rhs)
        {
            // if self assignment - do nothing
            if (this == &rhs)
            {
                return *this;
            }
            // deep copy
            Points2D copy(rhs);
            // swap the data
            std::swap(sequence_, copy.sequence_);
            std::swap(size_, copy.size_);
            return *this;
        }

        // Move-constructor.
        // // take the memory from another object
        // no copy
        Points2D(Points2D &&rhs) : sequence_(rhs.sequence_),
                                   size_(rhs.size_)
        {
            // clear old object
            rhs.sequence_ = nullptr;
            rhs.size_ = 0;
        }

        // Move-assignment.
        // Just use std::swap() for all variables.
        Points2D &operator=(Points2D &&rhs)
        {
            if (this != &rhs)
            {
                std::swap(sequence_, rhs.sequence_);
                std::swap(size_, rhs.size_);
            }

            return *this;
        }

        // Destructor
        // Clean memory when obj is destroyed
        ~Points2D()
        {
            delete[] sequence_;
        }

        // End of big-five.

        // One parameter constructor.
        // Creates a points2D obj with one point
        Points2D(const std::array<Object, 2> &item) : sequence_(new std::array<Object, 2>[1]),
                                                      size_(1)
        {
            sequence_[0] = item;
        }

        // Returns size
        size_t size() const
        {
            return size_;
        }

        // @location: an index to a location in the sequence.
        // @returns the point at @location.
        // const version.
        // abort() if out-of-range.

        // Access a point using index
        const std::array<Object, 2> &operator[](size_t location) const
        {
            // abort if its out of range
            if (location >= size_)
            {
                std::abort();
            }
            return sequence_[location];
        }

        //  @c1: A sequence.
        //  @c2: A second sequence.
        //  @return their sum. If the sequences are not of the same size, append the
        //    result with the remaining part of the larger sequence.

        // Add two objects together
        friend Points2D operator+(const Points2D &c1, const Points2D &c2)
        {
            Points2D results;

            size_t p_1 = c1.size();
            size_t p_2 = c2.size();
            size_t p_min = (p_1 < p_2) ? p_1 : p_2;
            size_t p_max = (p_1 > p_2) ? p_1 : p_2;

            // if both are empty
            if (p_max == 0)
            {
                return results;
            }

            results.size_ = p_max;
            results.sequence_ = new std::array<Object, 2>[p_max];

            // add overlapping points
            for (size_t i = 0; i < p_min; ++i)
            {
                results.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                results.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            }

            // copy the leftover points
            if (p_1 > p_2)
            {
                for (size_t i = p_min; i < p_max; ++i)
                {
                    results.sequence_[i] = c1.sequence_[i];
                }
            }
            else
            {
                for (size_t i = p_min; i < p_max; ++i)
                {
                    results.sequence_[i] = c2.sequence_[i];
                }
            }
            return results;
        }

        // new constructor to allow operator to only read
        explicit Points2D(size_t n) : sequence_(nullptr), size_(n)
        {
            if (n > 0)
            {
                sequence_ = new std::array<Object, 2>[n];
            }
        }

        // Overloading the << operator.
        // Print the points

        friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points)
        {
            if (some_points.size_ == 0)
            {
                out << "()\n";
                return out;
            }

            for (size_t i = 0; i < some_points.size_; ++i)
            {
                out << "(" << some_points.sequence_[i][0] << ", " << some_points.sequence_[i][1] << ")";
                if (i + 1 < some_points.size_)
                {
                    out << " ";
                }
            }
            out << "\n";
            return out;
        }

        // Overloading the >> operator.
        // Read a chain from an input stream (e.g., standard input).
        friend std::istream &operator>>(std::istream &in, Points2D &some_points)
        {

            if (some_points.size_ > 0 && some_points.sequence_ == nullptr)
            {
                some_points.sequence_ = new std::array<Object, 2>[some_points.size_];
            }

            for (size_t i = 0; i < some_points.size_; ++i)
            {
                Object x, y;
                if (!(in >> x >> y))
                    return in;

                some_points.sequence_[i] = {x, y};
            }
            return in;

            // size_t n;
            // if (!(in >> n))
            // {
            //     return in;
            // }
            // std::array<Object, 2> *new_sequence = nullptr;
            // if (n > 0)
            // {
            //     new_sequence = new std::array<Object, 2>[n];
            // }
            // // reaad each point
            // for (size_t i = 0; i < n; ++i)
            // {
            //     Object x, y;
            //     if (!(in >> x >> y)){
            //         delete[] new_sequence; // stop if the input is failing
            //         return in;
            //     }

            //     new_sequence[i] = {x, y};
            // }
            // // delete old data, then replace
            // delete[] some_points.sequence_;
            // some_points.sequence_ = new_sequence;
            // some_points.size_ = n;

            // return in;
        }

    private:
        // Sequence of points.
        std::array<Object, 2> *sequence_;
        // Size of sequence.
        size_t size_;
    };

} // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
