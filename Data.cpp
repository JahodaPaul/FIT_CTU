//
// Created by pjahoda on 4/21/17.
//

#include "Data.h"
#include <iostream>

Data::Data() {

}

void Data::GetDataFromDatabase() {
    //copy food ingredients into map, key is its name and values is its category - name of a category is a name of column in recipes table
    //careful, vegetables has two columns vegetable and vegetable2, so does spices - spice and spice2
    result r;
    //r = query("SELECT * FROM \"public\".\"alcoholicBeverages\"");
    //cout << r.size() << endl;
    //CopyIntoMap(r,"#alcB");
    //r = query("SELECT * FROM \"public\".\"beverages\"");
    //cout << r.size() << endl;
    //CopyIntoMap(r,"#bev");

    printWaitDownloading(1);

    r = query("SELECT * FROM \"public\".\"cheese\"");
    CopyIntoMap(r,"cheese");
    printWaitDownloading(2);

    r = query("SELECT * FROM \"public\".\"fruit\"");
    CopyIntoMap(r,"fruit");
    printWaitDownloading(3);

    r = query("SELECT * FROM \"public\".\"meat\"");
    CopyIntoMap(r,"meat");
    printWaitDownloading(1);

    r = query("SELECT * FROM \"public\".\"nuts\"");
    CopyIntoMap(r,"nuts");
    printWaitDownloading(2);

    r = query("SELECT * FROM \"public\".\"sides\"");
    CopyIntoMap(r,"side");
    printWaitDownloading(3);

    r = query("SELECT * FROM \"public\".\"spices\"");
    CopyIntoMap(r,"spice2");
    printWaitDownloading(1);

    r = query("SELECT * FROM \"public\".\"vegetables\"");
    CopyIntoMap(r,"vegetable");
    printWaitDownloading(2);

    //just for testing purposes
    //cout << foodNameAndCategory.begin()->first << endl;
    //auto it = foodNameAndCategory.find("Salt");
    //cout << it->first << endl;
    //cout << foodNameAndCategory.size() << endl;
}

void Data::CopyIntoMap(result R,string category) {
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        foodNameAndCategory.insert(make_pair(c[1].as<string>(),category));
    }
}

void Data::printWaitDownloading(int dots) {
    string s = "Successful login.\nDownloading data ";
    for(int i=0;i<dots;i++)
    {
        s += ".";
    }
    system("clear");
    cout << s << endl;
}
