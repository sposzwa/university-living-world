#pragma once

class ISubject;
class IObserver{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {};
public:
    virtual ~IObserver() {};
    virtual void Update(ISubject* subject) = 0;
};