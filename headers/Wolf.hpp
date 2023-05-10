#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include "Animal.hpp"

class Wolf : public Animal {
protected:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& boost::serialization::base_object<Animal>(*this);
    }
public: 
    Wolf();
    Wolf(Position pos);
    Wolf(Wolf const& wolf);
    ~Wolf();
    Organism* createOffspring(Position pos) override;
};