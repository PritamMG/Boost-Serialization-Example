#ifndef ABSTRACT_H
#define ABSTRACT_H

#include <iostream>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

class Foo_A
{
   public:
        virtual std::string toStr() const = 0;
        virtual ~Foo_A() = default;

   private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	};
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Foo_A)

class Foo_C : public Foo_A 
{
    protected:    
	const std::string name;

    public:
        Foo_C(std::string _name) : name(_name) {};
        virtual ~Foo_C() = default;

        const std::string getName() const { return this->name;};
//        void setElem(unsigned int x) const { this->elem = x;};

        std::string toStr() const;

    private:
	friend class boost::serialization::access;

	template<class Archive> inline friend void load_construct_data(Archive &ar, Foo_C *t, const unsigned int file_version);
	template<class Archive> inline friend void save_construct_data(Archive &ar, const Foo_C *t, const unsigned int file_version);

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Foo_A>(*this);

		ar & const_cast<std::string&>(name);
	};
};



class Foo_D : public Foo_A 
{
    protected:    
	const unsigned int elem;
	bool decl;

    public:
        Foo_D(unsigned int _elem) : elem(_elem), decl(false) {};
        virtual ~Foo_D() = default;

        const unsigned int getElem() const { return this->elem;};
//        void setElem(unsigned int x) const { this->elem = x;};

        std::string toStr() const;

    private:
	friend class boost::serialization::access;

	template<class Archive> inline friend void load_construct_data(Archive &ar, Foo_D *t, const unsigned int file_version);
	template<class Archive> inline friend void save_construct_data(Archive &ar, const Foo_D *t, const unsigned int file_version);

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Foo_A>(*this);

		ar & const_cast<unsigned int&>(elem);
		ar & decl;
	};
};

class Bar_A
{
	protected:
		const unsigned int id;
		const std::string name;

	public:
		Bar_A(unsigned int _id, std::string _name) : id(_id), name(_name) {};
		~Bar_A() = default;

		const unsigned int getID() { return this->id;};
		const std::string getName() { return this->name;};

		const Bar_A* constructBarA(unsigned int _id, std::string _name);
        	virtual std::string toStr() const;

	private:
		friend class boost::serialization::access;

		template<class Archive> inline friend void load_construct_data(Archive &ar, Bar_A *t, const unsigned int file_version);
		template<class Archive> inline friend void save_construct_data(Archive &ar, const Bar_A *t, const unsigned int file_version);

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & const_cast<unsigned int&>(id);
			ar & const_cast<std::string&>(name);
		};
};



template<typename T>
class Bar_B : public Bar_A
{
	protected:
		T data;

	public:
		Bar_B(unsigned int _id, std::string _name, T _data) : Bar_A(_id, _name), data(_data) {};
		Bar_B() : Bar_A(-1, "me"), data(0) {};
		~Bar_B() = default;

		T getData() { return this->data;};

		const Bar_A* constructBarB(unsigned int _id, std::string _name, T _data);

		std::string toStr();
	private:
		friend class boost::serialization::access;

		template<class Archive> inline friend void load_construct_data(Archive &ar, Bar_B<T> *t, const unsigned int file_version);
		template<class Archive> inline friend void save_construct_data(Archive &ar, const Bar_B<T> *t, const unsigned int file_version);

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Bar_A>(*this);

			ar & data;
		};
};

class Bar_C : public Bar_A
{
	protected:
		const Foo_A* meta_var;

	public:
		Bar_C(unsigned int _id, std::string _name, const Foo_A* _mvar) : Bar_A(_id, _name), meta_var(_mvar) {};
		~Bar_C() = default;

		const Foo_A* getID() { return this->meta_var;};

		const Bar_A* constructBarC(unsigned int _id, std::string _name, const Foo_A* mvar);
		std::string toStr();

	private:
		friend class boost::serialization::access;

		template<class Archive> inline friend void load_construct_data(Archive &ar, Bar_C *t, const unsigned int file_version);
		template<class Archive> inline friend void save_construct_data(Archive &ar, const Bar_C *t, const unsigned int file_version);

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Bar_A>(*this);

			ar & const_cast<Foo_A*&>(meta_var);
		};
};

// For non-default constructor

//namespace boost { namespace serialization {

template<class Archive>
inline void save_construct_data(Archive & ar, const Foo_C * t, const unsigned int file_version)
{
	ar << t->name;
}

template<class Archive>
inline void load_construct_data(Archive & ar, Foo_C * t, const unsigned int file_version)
{
	std::string _name;

	ar >> _name;

	::new(t)Foo_C(_name);
}

template<class Archive>
inline void save_construct_data(Archive & ar, const Foo_D * t, const unsigned int file_version)
{
	ar << t->elem << t->decl;
}

template<class Archive>
inline void load_construct_data(Archive & ar, Foo_D * t, const unsigned int file_version)
{
	unsigned int _elem;
	bool _decl;

	ar >> _elem >> _decl;

	::new(t)Foo_D(_elem);
}

template<class Archive>
inline void save_construct_data(Archive & ar, const Bar_A * t, const unsigned int file_version)
{
	ar << t->id << t->name;
}

template<class Archive>
inline void load_construct_data(Archive & ar, Bar_A * t, const unsigned int file_version)
{
	unsigned int _id;
	std::string _name;

	ar >> _id >> _name;

	::new(t)Bar_A(_id, _name);
}

/*
//template<class T, class Archive>
template<typename T>
template<class Archive>
inline void save_construct_data(Archive & ar, const Bar_B<T> * t, const unsigned int file_version)
{
	ar << t->data;
}

//template<class T, class Archive>
template<typename T>
template<class Archive>
inline void load_construct_data(Archive & ar, Bar_B<T> * t, const unsigned int file_version)
{
	unsigned int _id;
	std::string _name;
	T _data;

	ar >> _id >> _name >> _data;

	::new(t)Bar_B<T>(_id, _name, _data);
}
*/

template<class Archive>
inline void save_construct_data(Archive & ar, const Bar_C * t, const unsigned int file_version)
{
	ar << t->meta_var;
}

template<class Archive>
inline void load_construct_data(Archive & ar, Bar_C * t, const unsigned int file_version)
{
	unsigned int _id;
	std::string _name;
	Foo_A* _mvar;	

	ar >> _id >> _name >> _mvar;

	::new(t)Bar_C(_id, _name, _mvar);
}
//}}

#endif 
