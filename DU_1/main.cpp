#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>
#include <queue>

using namespace std;

const unsigned int ENDIAN_LITTLE   =  0x4949;
const unsigned int ENDIAN_BIG      =  0x4d4d;

#endif /* __PROGTEST__ */
#include <sstream>
#include <bitset>

ostringstream ostrm,ostrm2,ostrm3;
int width,height,NBitsPerChannel,NChannelsOfColor,nBlocks,NOfPixels,arrSize;
int width_to_nearest_eight,height_to_nearest_eight;
unsigned int ByteOrder;
bool otoc=false;

int p_arr[1000][1000][15],after_rotate[1000][1000][15],width_height[2][15];
vector<int> arr;

void Rotate(int angle)
{
    int n=0;
    int color=0;
    int tmp=height*width*NChannelsOfColor;
    while(n!=tmp)
    {
        if(angle^180)
        {
            for(int i=0;i<width_height[0][color];i++)
            {
                for (int j = 0; j < width_height[1][color]; j++) {
                    if(angle==90)
                    {
                        after_rotate[i][j][color] = p_arr[width_height[1][color]-1-j][i][color];
                        p_arr[width_height[1][color]-1-j][i][color]=0;
                    }
                    else
                    {
                        after_rotate[i][j][color] = p_arr[j][width_height[0][color]-1-i][color];
                        p_arr[j][width_height[0][color]-1-i][color]=0;
                    }
                    n++;
                }
            }
        }
        else
        {
            for(int i=0;i<width_height[1][color];i++)
            {
                for (int j = 0; j < width_height[0][color]; j++) {
                    after_rotate[width_height[1][color]-1-i][width_height[0][color]-1-j][color] = p_arr[i][j][color];
                    p_arr[i][j][color]=0;
                    n++;
                }
            }
        }
        color++;
    }
}

void LoadNumbersByBytes()
{
    int n=0,counter=0;
    int color=0;
    int posun=0;
    int posunDolu=0;
    while(counter!=NOfPixels)
    {
        if(color==NChannelsOfColor)
        {
            color=0;posun+=8;
            if(posun==width_to_nearest_eight)
            {
                posun=0;
                posunDolu+=8;
            }
        }
        width_height[0][color]=width;
        width_height[1][color]=height;
        n=0;
        for (int i = 0; n < 64; i++)
        {
            int row = 0;
            int column = i;

            do {
                if (column < 8 && row < 8)
                {
                    p_arr[row+posunDolu][column+posun][color] = arr[counter+n+8];
                    n++;
                }
                row++;
                column--;
            } while (column >= 0);
        }
        counter+=n;
        color++;
    }
}

bool checkPictureSize(int Width,int Height)
{
    if(Width==0||Height==0 || Width>1000 || Height > 1000)
    {
        return false;
    }

    nBlocks=(((Width+7)/8)*NChannelsOfColor)*((Height+7)/8);
    width_to_nearest_eight=((Width+7)/8);
    width_to_nearest_eight*=8;
    height_to_nearest_eight=(Height+7)/8;
    height_to_nearest_eight*=8;

    if(nBlocks*64!=arrSize){return false;}
    NOfPixels=nBlocks*64;
    return true;
}

void LittleWH(int a,int b,int c, int d)
{
    width+=a;
    width+=(b*256);
    height+=c;
    height+=(d*256);
}

bool Channels(int a)
{
    if(arr[0]==77)
    {
        int o,p,q;
        o=arr[2];p=arr[4];q=arr[6];
        arr[2]=arr[3];arr[4]=arr[5];arr[6]=arr[7];
        arr[3]=o;arr[5]=p;arr[7]=q;
        a=arr[6];
    }
    int n=a;
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    string s1,s2;
    int tmp = r.size();
    for(int i=0;i<tmp;i++)
    {
        if(tmp-i>4)
        {
            s1+=r[i];
        }
        else
        {
            s2+=r[i];
        }
    }
    NChannelsOfColor = stoi(s2, nullptr, 2);
    int tmp2 = stoi(s1,nullptr,2);
    NBitsPerChannel=(int)pow(2,(double)tmp2);
    if(NBitsPerChannel!=1&&NBitsPerChannel!=4&&NBitsPerChannel!=8&&NBitsPerChannel!=16){return false;}
    if(!NChannelsOfColor){return false;}

    return true;
}

bool rotateImage ( const char  * srcFileName,const char  * dstFileName,int angle,unsigned int byteOrder )
{
    ifstream fin(srcFileName,ios::binary);
    ofstream fout(dstFileName, ios::binary);
    ostrm.str("");width=0;height=0;NBitsPerChannel=0;NChannelsOfColor=0;nBlocks=0;NOfPixels=0;arrSize=0,otoc=false;
    ByteOrder=byteOrder;
    bool b=false;
    for(int i=0;i<15;i++)
    {
        width_height[0][i]=0;
        width_height[1][i]=0;
    }
    if(!arr.empty())
    {
        arr.clear();
    }
    unsigned char tmp;
    int cnt=0;
    int tmpInt=0;
    while(fin >> noskipws >> tmp)
    {
        cnt++;
        if(cnt>8 && !b)
        {
            if(!Channels(arr[6]))
            {
                return false;
            }
            else{ b=true; }
        }
        else if(!b)
        {
            arr.push_back((int)tmp);
        }

        if(b && NBitsPerChannel==16)
        {
            if(cnt%2==1)
            {
                tmpInt += (1000*(int)tmp);
            }
            else
            {
                tmpInt += (int)tmp;
                arr.push_back(tmpInt);
                tmpInt=0;
            }
        }
        else if(b && NBitsPerChannel==4)
        {
            int n=(int)tmp;
            string r;
            while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
            string s1,s2;
            int tmp = r.size();
            for(int i=0;i<tmp;i++)
            {
                if(tmp-i>4)
                {
                    s1+=r[i];
                }
                else
                {
                    s2+=r[i];
                }
            }
            int tmp2,tmp1;
            if(s2.size()>0){
                tmp2 = stoi(s2, nullptr, 2);
            }
            else{tmp2=0;}
            if(s1.size()>0){
                tmp1 = stoi(s1,nullptr,2);}
            else{tmp1=0;}
            arr.push_back(tmp1);
            arr.push_back(tmp2);
        }
        else if(b && NBitsPerChannel==1)
        {

        }
        else if(b)
        {
            arr.push_back((int)tmp);
        }
        if(cnt>1000000){return false;}
    }
    if(!cnt){return false;}
    arrSize=arr.size()-8;
    if(arrSize<=0){return false;}
    if((arr[2]==0&&arr[3]==0)||(arr[4]==0&&arr[5]==0)){return false;}
    if(arr[2]<0||arr[3]<0||arr[4]<0||arr[5]<0||arr[2]>255||arr[3]>255||arr[4]>255||arr[5]>255){return false;}
    LittleWH(arr[2],arr[3],arr[4],arr[5]);
    if((arr[0]!=77||arr[1]!=77) && (arr[0]!=73||arr[1]!=73))
    {
        return false;
    }

    if(!checkPictureSize(width,height)){return false;}

    if(angle<0)
    {
        angle *= -1;
        angle = angle % 360;
        angle = 360-angle;
        if(angle==360)angle=0;
    }
    else
    {
        angle = angle % 360;
    }
    if(angle!=0&&angle!=90&&angle!=180&&angle!=270)return false;
    LoadNumbersByBytes();

    if(angle)
    {
        Rotate(angle);
    }

    if(angle==90||angle==270)
    {
        int tmp = width_to_nearest_eight;
        width_to_nearest_eight=height_to_nearest_eight;
        height_to_nearest_eight=tmp;
        int tmp1=arr[2];
        int tmp2=arr[3];
        arr[2]=arr[4];
        arr[3]=arr[5];
        arr[4]=tmp1;
        arr[5]=tmp2;
    }
    if(ByteOrder==ENDIAN_BIG)
    {
        int o,p,q;
        o=arr[2];p=arr[4];q=arr[6];
        arr[2]=arr[3];arr[4]=arr[5];arr[6]=arr[7];
        arr[3]=o;arr[5]=p;arr[7]=q;
    }
    if(ByteOrder==ENDIAN_LITTLE && arr[0]==77)
    {
        arr[0]=73;
        arr[1]=73;
        ByteOrder=ENDIAN_BIG;
        otoc=true;
    }
    else if(ByteOrder==ENDIAN_BIG && arr[0]==73)
    {
        arr[0]=77;
        arr[1]=77;
        ByteOrder=ENDIAN_LITTLE;
        otoc=true;
    }

    for(int i=0;i<8;i++)
    {
        if(!(fout << (char)arr[i]))
        {
            return false;
        }
    }
    int n=0,counter=0;
    int color=0;
    int posun=0;
    int posunDolu=0;
    int tmp2=0;
    int cnt4=0;
    int tmp4=0;
    string s4="";
    while(counter!=NOfPixels)
    {
        if(color==NChannelsOfColor)
        {
            color=0;posun+=8;
            if(posun==width_to_nearest_eight)
            {
                posun=0;
                posunDolu+=8;
            }
        }
        n=0;
        for (int i = 0; n < 64; i++)
        {
            int column = i;
            int row = 0;
            do {
                if (column < 8 && row < 8)
                {
                    if(angle)
                    {
                        if(NBitsPerChannel==8)
                        {
                            fout << (char)after_rotate[row+posunDolu][column+posun][color];
                            after_rotate[row+posunDolu][column+posun][color]=0;
                        }
                        else if(NBitsPerChannel==16)
                        {
                            if(otoc)
                            {
                                tmp2=after_rotate[row + posunDolu][column + posun][color]%1000;
                                after_rotate[row + posunDolu][column + posun][color] /= 1000;
                                fout << (char) tmp2;
                                fout << (char) after_rotate[row + posunDolu][column + posun][color];
                            }
                            else
                            {
                                tmp2=after_rotate[row + posunDolu][column + posun][color]%1000;
                                after_rotate[row + posunDolu][column + posun][color] /= 1000;
                                fout << (char) after_rotate[row + posunDolu][column + posun][color];
                                fout << (char) tmp2;
                            }
                        }
                        else
                        {
                            cnt4++;
                            if(otoc)
                            {
                                if(cnt4%2==1)
                                {
                                    tmp4=after_rotate[row + posunDolu][column + posun][color];
                                    s4 = std::bitset< 4 >( 12345 ).to_string();
                                }
                                else
                                {
                                    s4 += std::bitset< 4 >( 12345 ).to_string();
                                    tmp4+= after_rotate[row + posunDolu][column + posun][color]*16;
                                    fout << (char) tmp4;
                                }
                            }
                            else
                            {
                                if(cnt4%2==1)
                                {
                                    tmp4=after_rotate[row + posunDolu][column + posun][color]*16;
                                }
                                else
                                {
                                    tmp4+= after_rotate[row + posunDolu][column + posun][color];
                                    fout << (char) tmp4;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(NBitsPerChannel==8) {
                            fout << (char) p_arr[row + posunDolu][column + posun][color];
                            p_arr[row + posunDolu][column + posun][color] = 0;
                        }
                        else if(NBitsPerChannel==16)
                        {
                            if(otoc)
                            {
                                tmp2=p_arr[row + posunDolu][column + posun][color]%1000;
                                p_arr[row + posunDolu][column + posun][color] /= 1000;
                                fout << (char) tmp2;
                                fout << (char) p_arr[row + posunDolu][column + posun][color];
                            }
                            else
                            {
                                tmp2=p_arr[row + posunDolu][column + posun][color]%1000;
                                p_arr[row + posunDolu][column + posun][color] /= 1000;
                                fout << (char) p_arr[row + posunDolu][column + posun][color];
                                fout << (char) tmp2;
                            }
                        }
                        else
                        {
                            cnt4++;
                            if(otoc)
                            {
                                if(cnt4%2==1)
                                {
                                    tmp4=p_arr[row + posunDolu][column + posun][color];
                                }
                                else
                                {
                                    tmp4+= p_arr[row + posunDolu][column + posun][color]*16;
                                    fout << (char) tmp4;
                                }
                            }
                            else
                            {
                                if(cnt4%2==1)
                                {
                                    tmp4=p_arr[row + posunDolu][column + posun][color]*16;
                                }
                                else
                                {
                                    tmp4+= p_arr[row + posunDolu][column + posun][color];
                                    fout << (char) tmp4;
                                }
                            }
                        }
                    }
                    n++;
                }
                row++;
                column--;
            } while (column >= 0);
        }
        counter+=n;
        color++;
    }

    int tmp3;
    if(width_height[1][0]>width_height[0][0]){tmp3=width_height[1][0];}
    else{tmp3=width_height[0][0];}
    for(int o=0;o<NChannelsOfColor;o++)
    {
        for(int i=0;i<tmp3;i++)
        {
            for (int j = 0; j < tmp3; j++) {
                after_rotate[i][j][o]=0;
                p_arr[i][j][o]=0;
            }
        }
    }
    if(!arr.empty())
    {
        arr.clear();
    }
    fout.close();
    fin.close();
    return true;
}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1, const char * fileName2 )
{
    ifstream fin(fileName1, ios::binary);
    ifstream fin2(fileName2, ios::binary);
    ostrm3.str("");
    ostrm2.str("");
    if(!(ostrm3 << fin.rdbuf()) || !(ostrm2 << fin2.rdbuf()))
    {
        return false;
    }
    fin.close();
    fin2.close();
    string image1(ostrm3.str());
    string image2(ostrm2.str());
    return (image1==image2);
}

int main ( void )
{


    // extra inputs (optional & bonus tests)
    assert (  rotateImage ( "input_00.img", "output_00.img", 0, ENDIAN_LITTLE )
              && identicalFiles ( "output_00.img", "ref_00.img" ) );

    assert (  rotateImage ( "input_01.img", "output_01.img", 90, ENDIAN_LITTLE )
              && identicalFiles ( "output_01.img", "ref_01.img" ) );

    assert (  rotateImage ( "input_02.img", "output_02.img", 540, ENDIAN_LITTLE )
              && identicalFiles ( "output_02.img", "ref_02.img" ) );

    assert (  rotateImage ( "input_03.img", "output_03.img", -900450, ENDIAN_LITTLE )
              && identicalFiles ( "output_03.img", "ref_03.img" ) );

    assert (  rotateImage ( "input_04.img", "output_04.img", 90, ENDIAN_LITTLE )
              && identicalFiles ( "output_04.img", "ref_04.img" ) );

    assert (  rotateImage ( "input_05.img", "output_05.img", 270, ENDIAN_LITTLE )
              && identicalFiles ( "output_05.img", "ref_05.img" ) );

    assert (  rotateImage ( "input_06.img", "output_06.img", 90, ENDIAN_LITTLE )
              && identicalFiles ( "output_06.img", "ref_06.img" ) );

    assert (  rotateImage ( "input_07.img", "output_07.img", 270, ENDIAN_LITTLE )
              && identicalFiles ( "output_07.img", "ref_07.img" ) );

    assert ( ! rotateImage ( "input_08.img", "output_08.img", 270, ENDIAN_LITTLE ) );

    assert ( ! rotateImage ( "input_09.img", "output_09.img", -275, ENDIAN_LITTLE ) );

    assert ( ! rotateImage ( "in_000.bin", "output_10.img", 0, ENDIAN_LITTLE ) );

    // extra inputs (optional & bonus tests)
    assert ( rotateImage ( "extra_input_03.img", "extra_out_03.img", 270, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
    assert ( rotateImage ( "extra_input_00.img", "extra_out_00.img", 90, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );

    assert ( rotateImage ( "extra_input_02.img", "extra_out_02.img", 180, ENDIAN_BIG )
             && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
    assert ( rotateImage ( "extra_input_01.img", "extra_out_01.img", 90, ENDIAN_BIG )
             && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );

    assert ( rotateImage ( "extra_input_04.img", "extra_out_04.img", 90, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
//    assert ( rotateImage ( "extra_input_05.img", "extra_out_05.img", 270, ENDIAN_LITTLE )
//             && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
//    assert ( rotateImage ( "extra_input_08.img", "extra_out_08.img", 90, ENDIAN_LITTLE )
//             && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
//    assert ( rotateImage ( "extra_input_09.img", "extra_out_09.img", 270, ENDIAN_LITTLE )
//             && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );




//    assert ( rotateImage ( "extra_input_06.img", "extra_out_06.img", 180, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
//    assert ( rotateImage ( "extra_input_07.img", "extra_out_07.img", 0, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );

//    assert ( rotateImage ( "extra_input_02.img", "extra_out_02.img", 180, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
//    assert ( rotateImage ( "extra_input_10.img", "extra_out_10.img", 180, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
//    assert ( rotateImage ( "extra_input_11.img", "extra_out_11.img", 0, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
//
//
//
//
//
//    assert ( rotateImage ( "extra_input_07.img", "extra_out_07.img", 0, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );





//    assert ( rotateImage ( "extra_input_06.img", "extra_out_06.img", 180, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
//
//    assert ( rotateImage ( "extra_input_10.img", "extra_out_10.img", 180, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
//    assert ( rotateImage ( "extra_input_11.img", "extra_out_11.img", 0, ENDIAN_BIG )
//             && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );


    return 0;
    /*Pavel Jahoda*/
}
#endif /* __PROGTEST__ */
