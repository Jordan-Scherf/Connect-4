/*
Name: Jordan Scherf (Scherf@unlv.nevada.edu)
Program Description:This is the header for the bank system which is a self made hashmap
*/
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

template <class t1, class t2>
class hashMap
{
public:
	hashMap(std::size_t = 5);
	t2& operator[](t1);
private:
	struct keyVal
	{
		keyVal()
		{
			key = t1();
			value = t2();
		}

		t1 key;
		t2 value;
	};

	void resize(std::size_t);

	std::size_t hash1(std::string);
	std::size_t hash2(std::string);

	std::vector<keyVal> table1;
	std::vector<keyVal> table2;

	std::size_t items1;
	std::size_t items2;
};



/* This is the contrusctor the tables starting them at 0 then resizing them based on size
 * Return :: Void;
 */
template <class t1, class t2>
hashMap<t1, t2>::hashMap(std::size_t size)
{
	items1 = 0;
  items2 = 0;
  table1.resize(size);
  table2.resize(size);
}

/*
 * The function overloads the bracket operator in order to support our find and insert operation
 * Return :: Void
 */
template <class t1, class t2>
t2& hashMap<t1, t2>::operator[](t1 key)
{
// Initialize the probing variables
    int k1 = 0;
    int k2 = 0;

// Check if table1 or table2 needs to be resized
    if(double(items1) / table1.size() >= 0.2)
        this->resize(table1.size());
    if(double(items2) / table2.size() >= 0.2)
        this->resize(table2.size());

// Compute the indices for both tables
    std::size_t i1 = hash1(key) % table1.size();
    std::size_t i2 = hash2(key) % table2.size();

// Initialize the iteration counter
    int it = 1;

// Probe through the tables until the key is found or an empty slot is encountered
    do{
// If an empty slot is encountered in table1
        if(table1[i1].key == t1()){
            items1++;
            table1[i1].key = key;
            table1[i1].value = t2();
            return table1[i1].value;
        }
// If the key is found in table1
         if(table1[i1].key == key){
            return table1[i1].value;
        }
// If an empty slot is encountered in table2
         if(table2[i2].key == t1()){
            items2++;
            table2[i2].key = key;
            table2[i2].value = t2();
            return table2[i2].value;
        }
// If the key is found in table2
         if(table2[i2].key == key){
            return table2[i2].value;
        }
// If the slot is already occupied, probe further
        else{
            k1++;
            k2++;
// Alternate between hash1 and hash2 for probing
            if(it % 2 == 0){
                i1 = (i1 + k1 * hash2(key)) % table1.size();
                i2 = (i2 + k2 * hash1(key)) % table2.size();
            }else{
                i1 = (i1 + k1 * hash1(key)) % table1.size();
                i2 = (i2 + k2 * hash2(key)) % table2.size();
            }
        }
// Increment the iteration counter
        it++;
    }while(true);


}



/*
 *  This function resizes the tables in order to override collisions
 * Return :: Void
 */
template <class t1, class t2>
void hashMap<t1, t2>::resize(std::size_t amount)
{
    //Lets make a couple of temporary vectors equal to the table
    std::vector<keyVal> tmp = table1;
    std::vector<keyVal> tmp2 = table2;
    /* I dont wanna write alot of comments so Im gonna summarize in this block. We are going to clear out our original
     * vectors then resize them with a new amouunt that multiplies it by 2. Thus giving us double the space. Then after
     * we will use our new overloaded [] operator to place the contents back into the table.
     */
    table1.clear();
    table2.clear();
    items1 = 0;
    items2 = 0;
    int n = amount * 2;
    table1.resize(n);
    table2.resize(n);
    for(auto &c: tmp){
        if(c.key != t1()) {
            (*this)[c.key] = c.value;
        }
    }
    for(auto &b: tmp2){
        if(b.key != t1()) {
            (*this)[b.key] = b.value;
        }
    }
}
/*
 * This Function provides the summation of the key multiplied by 10 to the power of the indext
 * from the left most to the right most
 * Return :: size_t (Which is a summation)
 */
template <class t1, class t2>
std::size_t hashMap<t1, t2>::hash1(std::string key)
{
    auto indexKey = 0;
    std::size_t product = 0;
    for(int i = 0; i < key.size(); i++){
        indexKey = key[i];
        product  += (indexKey * pow(10, i));
    }
    return product;
}



/*
 * This Function provides the summation of the key multiplied by 10 to the power of the indext
 * from the right most to the left most
 * Return :: size_t (Which is a summation)
 */
template <class t1, class t2>
std::size_t hashMap<t1, t2>::hash2(std::string key)
{
    auto indexKey = 0;
    std::size_t product = 0;
    int a = 0;
    for (int i = key.size(); i >= 0; i--) {
        indexKey = key[i];
        product += (indexKey * pow(10, a));
        a++;
    }
    return product;
}
