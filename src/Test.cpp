#include "Object.hpp"

typedef Bar_B<int> bb_int;
typedef Bar_B<float> bb_float;

BOOST_CLASS_EXPORT(bb_int)
BOOST_CLASS_EXPORT(bb_float)
//BOOST_CLASS_EXPORT(Bar_B<int>)
//BOOST_CLASS_EXPORT(Bar_B<float>)
BOOST_CLASS_EXPORT(Bar_C)

BOOST_CLASS_EXPORT(Foo_C)
BOOST_CLASS_EXPORT(Foo_D)

//BOOST_CLASS_EXPORT(ObjectNew)

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>

static size_t i = 0;

void saveData(std::vector<const ObjectNew*> obj_vec)
{
	std::ofstream ofs("serialize-data.txt");

	// save data to archive
	boost::archive::text_oarchive oa(ofs);

	for (const ObjectNew* on : obj_vec)
	{
		oa << on;
		std::cout << i << std::endl;
		i += 1;
	}
	//oa << obj_vec;

	// write class instance to archive
	//oa << obj1 << obj2;
}

std::vector<const ObjectNew*>
loadData()
{
	// create and open an archive for input
	std::ifstream ifs("serialize-data.txt");
	boost::archive::text_iarchive ia(ifs);

	// read class state from archive
	
	std::vector<const ObjectNew*> archive_vec;
	for (; i != 0; --i)
	{
		std::cout << i << std::endl;
		ObjectNew* on;
		ia >> on;
		archive_vec.push_back(on);
	}
	//ia >> archive_vec;
	return archive_vec;
	//ia >> r_obj1 >> r_obj2;
}


int main()
{
	unsigned int seed = 42;

	const Foo_A* f1;
	const Foo_A* f2;

	f1 = new Foo_D(12);
	f2 = new Foo_C("Hi");
	const Foo_A* f_float = new Foo_D(12121);

	const Bar_A* o1 = new Bar_B<int>(1, "obj1", 3);
	const Bar_A* o2 = new Bar_C(2, "obj2", f1);
	const Bar_A* o3 = new Bar_B<float>(3, "template_float", 2.454656);

	const ObjectNew* obj1 = new ObjectNew(seed, o1);

	seed = 21;

	const ObjectNew* obj2 = new ObjectNew(seed, o2);
	const ObjectNew* obj_float = new ObjectNew(seed, o3);

	std::vector<const ObjectNew*> obj_vec = {
		obj1, obj2, obj_float,
	};

	saveData(obj_vec);

	//obj1->printObject();
	//obj2->printObject();

	std::vector<const ObjectNew*> r_obj_vec;

	r_obj_vec = loadData();

	for (const ObjectNew* on : r_obj_vec)
	{
		on->printObject();
	}

	//r_obj1->printObject();
	//r_obj2->printObject();
	
	return 0;
}
