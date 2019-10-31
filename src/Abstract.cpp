#include "Abstract.hpp"

std::string Foo_C::toStr() const
{
	std::string res;

	res = "Foo_C_" + name;

	return res;
}

std::string Foo_D::toStr() const
{
	std::string res;

	res = "Foo_D_" + std::to_string(elem);

	return res;
}

const Bar_A* Bar_A::constructBarA(unsigned int _id, std::string _name)
{
	const Bar_A* bar = new Bar_A(_id, _name);

	return bar;	
}

template<typename T>
const Bar_A* Bar_B<T>::constructBarB(unsigned int _id, std::string _name, T _data)
{
	const Bar_B* bar = new Bar_B<T>(_id, _name, _data);

	return bar;	
}

const Bar_A* Bar_C::constructBarC(unsigned int _id, std::string _name, const Foo_A* mvar)
{
	const Bar_C* bar = new Bar_C(_id, _name, mvar);

	return bar;	
}

std::string Bar_A::toStr() const
{
	std::string res = "Id: " + std::to_string(id) + " Name: " + name;

	return res;
}

template<typename T>
std::string Bar_B<T>::toStr()
{
	std::string res = "Id: " + std::to_string(id) + " Name: " + name + " Data: " + std::to_string(data);

	return res;
}

std::string Bar_C::toStr()
{
	std::string res = "Id: " + std::to_string(id) + " Name: " + name + " Foo: " + meta_var->toStr();

	return res;
}
