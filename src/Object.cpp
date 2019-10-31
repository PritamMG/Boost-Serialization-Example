#include "Object.hpp"

const Foo_A* ObjectNew::generateVarD(unsigned int x)
{
	const Foo_D* foo = new Foo_D(x);

	return foo;
}

const Foo_A* ObjectNew::generateVarC(std::string str)
{
	const Foo_C* foo = new Foo_C(str);

	return foo;
}

void ObjectNew::addVar(const Foo_A* var)
{
	this->vars.push_back(var);
}

void ObjectNew::printObject() const
{
	std::cout << "Seed: " << this->seed << std::endl;

	const Foo_D* fooD;
	const Foo_C* fooC;
	const Foo_A* foo;

	std::vector<const Foo_A*> _vars;

	_vars = this->vars;

	foo = this->getCurrentVar();

	std::cout << "Current Var: " << foo->toStr() << std::endl;

	for(std::vector<const Foo_A*>::iterator it = _vars.begin(); it != _vars.end(); it++)
	{
		foo = *it;

		std::cout << "Var: " << foo->toStr() << std::endl;
	}

	const Bar_A* barA;

	barA = getMetaObj();

	std::string str = barA->toStr();

	std::cout << "MetaObj: " << str << std::endl;
}
