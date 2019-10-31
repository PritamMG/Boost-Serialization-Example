#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Abstract.hpp"

class Object
{
	protected:
		const unsigned int seed;

	public:
		std::vector<const Foo_A*> vars;

		Object(unsigned int _seed) : seed(_seed) {};
		virtual ~Object() = default;

		const unsigned int getSeed() {return this->seed;};

	private:
		friend class boost::serialization::access;

		template<class Archive> inline friend void load_construct_data(Archive &ar, Object *t, const unsigned int file_version);
		template<class Archive> inline friend void save_construct_data(Archive &ar, const Object *t, const unsigned int file_version);

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & const_cast<unsigned int&>(seed);
			ar & vars;
		};
};

class ObjectNew : public Object
{
	const Foo_A* current_var;
	const Bar_A* meta_obj;

	public:
		ObjectNew(unsigned int _seed) : Object(_seed) {};
		ObjectNew(unsigned int _seed, const Foo_A* _curr, const Bar_A* _meta) : Object(_seed), current_var(_curr), meta_obj(_meta) {};
		ObjectNew(unsigned int _seed, const Bar_A* _meta) : Object(_seed), current_var(nullptr), meta_obj(_meta) {};
		~ObjectNew() = default;

		const Foo_A* generateVarD(unsigned int);
		const Foo_A* generateVarC(std::string);
		const Foo_A* getCurrentVar() const {return current_var;};
		void setCurrentVar(const Foo_A* _var) {current_var = _var; addVar(_var);};
		void addVar(const Foo_A*);

		const Bar_A* getMetaObj() const {return this->meta_obj;};

		void printObject() const;

	private:
		friend class boost::serialization::access;

		template<class Archive> inline friend void load_construct_data(Archive &ar, ObjectNew *t, const unsigned int file_version);
		template<class Archive> inline friend void save_construct_data(Archive &ar, const ObjectNew *t, const unsigned int file_version);

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			// serialize base class information
			ar & boost::serialization::base_object<Object>(*this);

			ar & current_var;
			ar & meta_obj;
		};
};

//namespace boost { namespace serialization {

template<class Archive>
inline void save_construct_data(Archive & ar, const Object * t, const unsigned int file_version)
{
	ar << t->seed << t->vars;
}

template<class Archive>
inline void load_construct_data(Archive & ar, Object * t, const unsigned int file_version)
{
	unsigned int _seed;
	std::vector<const Foo_A*> _vars;

	ar >> _seed >> _vars;

	::new(t)Object(_seed);
}



template<class Archive>
inline void save_construct_data(Archive & ar, const ObjectNew * t, const unsigned int file_version)
{
	ar << t->seed << t->vars << t->current_var << t->meta_obj;
}

template<class Archive>
inline void load_construct_data(Archive & ar, ObjectNew * t, const unsigned int file_version)
{
	unsigned int _seed;
	std::vector<const Foo_A*> _vars;
	Foo_A* _current_var;
	Bar_A* _meta_obj;

	ar >> _seed >> _vars >> _current_var >> _meta_obj;

	::new(t)ObjectNew(_seed, _current_var, _meta_obj);
}
//}}

#endif
