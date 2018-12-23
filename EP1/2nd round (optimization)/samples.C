#include <bits/stdc++.h>
#define ll long long int
using namespace std;
//time,value
vector<pair<ll,ll>> samples;
ll n,l;
string gtOrlt = "";
string avgminmax = "";
ll howLong;
ll minIndex,currentTime;
ll currentAvgMinMaxValue;

int main() {
    ios::sync_with_stdio(0);
    while(cin>>n){
        int time = 0,value = 0;
        for(int i=0;i<n;i++){
            cin>> time >> value;
            samples.push_back(make_pair(time,value));
        }
        cin >> l;
        for(int i=0;i<l;i++){
            cin>>gtOrlt>>avgminmax>>howLong;
            //value, time
            priority_queue<pair<ll,ll>> biggestFirstQ;
            priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> smallestFirstQ;
            if(samples.size() == 0){
                cout << 0 << endl;
                continue;
            }
            ll result = 0;
            minIndex = 0;
            currentAvgMinMaxValue = samples[0].second;
            ll currentAvgSize = 1;
            if(avgminmax == "min")
            {
                smallestFirstQ.push(make_pair(samples[0].second,samples[0].first));
            }
            if(avgminmax == "max"){
                biggestFirstQ.push(make_pair(samples[0].second,samples[0].first));
            }

            for(int j = 1;j<samples.size();j++){
                while(samples[minIndex].first+howLong < samples[j].first){
                    if(avgminmax == "avg"){
                        currentAvgMinMaxValue -= samples[minIndex].second;
                        currentAvgSize -= 1;
                    }
                    minIndex++;
                }

                if(avgminmax == "min"){

                    while(!smallestFirstQ.empty() && smallestFirstQ.top().second + howLong < samples[j].first)
                    {
                        smallestFirstQ.pop();
                    }
                    if(!smallestFirstQ.empty()){
                        if(gtOrlt == "gt"){
                            if(samples[j].second > smallestFirstQ.top().first)
                            {
                                result += 1;
                            }
                        }
                        else{
                            if(samples[j].second < smallestFirstQ.top().first)
                            {
                                result += 1;
                            }
                        }
                    }
                    smallestFirstQ.push(make_pair(samples[j].second,samples[j].first));
                }
                else if (avgminmax == "max"){

                    while(!biggestFirstQ.empty() && biggestFirstQ.top().second + howLong < samples[j].first)
                    {
                        biggestFirstQ.pop();
                    }

                    if(!biggestFirstQ.empty()){
                        if(gtOrlt == "gt"){
                            if(samples[j].second > biggestFirstQ.top().first)
                            {
                                result += 1;
                            }
                        }
                        else{
                            if(samples[j].second < biggestFirstQ.top().first)
                            {
                                result += 1;
                            }
                        }
                    }
                    biggestFirstQ.push(make_pair(samples[j].second,samples[j].first));
                }
                else{
                    if(currentAvgSize != 0){
                        if(gtOrlt == "gt"){
                            if((double)samples[j].second > (currentAvgMinMaxValue/(double)currentAvgSize))
                            {
                                result += 1;
                            }
                        }
                        else{
                            if((double)samples[j].second < (currentAvgMinMaxValue/(double)currentAvgSize))
                            {
                                result += 1;
                            }
                        }
                    }
                    currentAvgSize += 1;
                    currentAvgMinMaxValue += samples[j].second;
                }
            }
            cout << result << endl;
        }


        samples.clear();
    }
    return 0;
}
