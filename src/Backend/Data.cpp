//
// Created by pjahoda on 4/21/17.
//

#include "Data.h"
#include <iostream>

Data::Data() {

}

/**
   copy food ingredients into map, key is its name and values is its category - name of a category is a name of column in recipes table
   careful, vegetables has two columns vegetable and vegetable2, so does spices - spice and spice2
   integer parameter is used to show progressBar progress
 * @param select
 */
void Data::GetDataFromDatabase(const int select) {

    result r;
    switch(select)
    {
        case 1:
            r = query("SELECT * FROM \"public\".\"alcoholicBeverages\"");
            CopyIntoMap(r,".alcB",beveragesAndCategory);
            break;
        case 2:

            break;
        case 3:
            r = query("SELECT * FROM \"public\".\"beverages\"");
            CopyIntoMap(r,".bev",beveragesAndCategory);
            break;
        case 4:

            break;
        case 5:
            r = query("SELECT * FROM \"public\".\"cheese\"");
            CopyIntoMap(r,"cheese",foodNameAndCategory);
            break;
        case 6:

            break;
        case 7:
            r = query("SELECT * FROM \"public\".\"fruit\"");
            CopyIntoMap(r,"fruit",foodNameAndCategory);
            break;
        case 8:

            break;
        case 9:
            r = query("SELECT * FROM \"public\".\"meat\"");
            CopyIntoMap(r,"meat",foodNameAndCategory);
        case 10:

            break;
        case 11:
            r = query("SELECT * FROM \"public\".\"nuts\"");
            CopyIntoMap(r,"nuts",foodNameAndCategory);
            break;
        case 12:

            break;
        case 13:
            r = query("SELECT * FROM \"public\".\"sides\"");
            CopyIntoMap(r,"side",foodNameAndCategory);
            break;
        case 14:

            break;
        case 15:
            r = query("SELECT * FROM \"public\".\"spices\"");
            CopyIntoMap(r,"spice2",foodNameAndCategory);
            break;
        case 16:

            break;
        case 17:
            r = query("SELECT * FROM \"public\".\"vegetables\"");
            CopyIntoMap(r,"vegetable",foodNameAndCategory);
            break;
        case 18:

            break;
        default:
            /* Blok default */
            break;
    }
}

///copies ingredient name from pqxx::result as a key and ingredient category as value into the map
void Data::CopyIntoMap(const result &R,const string category, map<string,string> & myMap) {
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        myMap.insert(make_pair(c[1].as<string>(),category));
    }
}

/**
 * \return map foodNameAndCategory
 */
map<string, string> &Data::GetMapOfIngridients(){
    return foodNameAndCategory;
}
