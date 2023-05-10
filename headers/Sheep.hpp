#pragma once
#include "Animal.hpp"

class Sheep : public Animal {
protected:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& boost::serialization::base_object<Animal>(*this);
    }
public: 
    Sheep();
    Sheep(Position pos);
    Sheep(Sheep const& sheep);
    ~Sheep();
    Organism* createOffspring(Position pos) override;
};