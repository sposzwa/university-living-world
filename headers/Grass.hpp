#pragma once
#include "Plant.hpp"

class Grass : public Plant {
protected:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version){
        ar& boost::serialization::base_object<Plant>(*this);
    }
public: 
    Grass();
    Grass(Position pos);
    Grass(Grass const& grass);
    ~Grass();
    Organism* createOffspring(Position pos) override;
};