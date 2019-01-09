#include <bits/stdc++.h>

using namespace std;

int t;

struct Line{
    double x1,y1,x2,y2;
    Line(double X1,double Y1, double X2, double Y2){
        x1 = X1; y1 = Y1; x2 = X2; y2 = Y2;
    }
};

bool InBetweenTwoValues(double value, double v1, double v2){
    return ((value>=v1 && value<=v2) || (value>=v2 && value<=v1));
}

double GetAngle(Line line){
    double angle = atan2(0 - line.y2, 0 - line.x2); //in radians
    return angle * 180 / 3.14159265358979323846; //in degrees
}

bool PointIsOnLine(Line line, double x, double y){
    double a = abs((line.y2-line.y1)*x-(line.x2-line.x1)*y+line.x2*line.y1-line.y2*line.x1);
    double b = sqrt((line.x2 - line.x1) * (line.x2 - line.x1) + (line.y2 - line.y1) * (line.y2 - line.y1));
    return (abs(a/b) < 0.000001);
}

bool DoTwoLinesIntersect(Line first, Line second){
    if((first.x1-first.x2)*(second.y1-second.y2)-(first.y1-first.y2)*(second.x1-second.x2) == 0){//they are parallel
        //first check if they are vertical
        if(first.x1 == first.x2){
            if(first.x1 != second.x1){
                return false;
            }
            else{
                return (InBetweenTwoValues(first.y1,second.y1,second.y2) || InBetweenTwoValues(first.y2,second.y1,second.y2));
            }
        }
        return ( (PointIsOnLine(first,second.x1,second.y1) && InBetweenTwoValues(second.x1,first.x1,first.x2))
                || (PointIsOnLine(first,second.x2,second.y2) && InBetweenTwoValues(second.x2,first.x1,first.x2))
                || (PointIsOnLine(second,first.x1,first.y1) && InBetweenTwoValues(first.x1,second.x1,second.x2))
                || (PointIsOnLine(second,first.x2,first.y2) && InBetweenTwoValues(first.x2,second.x1,second.x2)) );
    }
    else{
        double a = (first.x1-first.x2)*(second.y1-second.y2)-(first.y1-first.y2)*(second.x1-second.x2);
        double b = (first.x1-second.x1)*(second.y1-second.y2)-(first.y1-second.y1)*(second.x1-second.x2);
        double c = (first.x1-first.x2)*(first.y1-second.y1)-(first.y1-first.y2)*(first.x1-second.x1);
        double t = b/a;
        double u = -1*(c/a);
        return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
    }
}
double xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;

bool IsLineInsideOfRectangle(Line line){ //at least one point
    return (line.x1 >= xleft && line.x1 <= xright && line.y1 >= ybottom && line.y1 <= ytop) ||
            (line.x2 >= xleft && line.x2 <= xright && line.y2 >= ybottom && line.y2 <= ytop);
}

int main() {
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>xstart>>ystart>>xend>>yend>>xleft>>ytop>>xright>>ybottom;
        if(xleft > xright){
            double tmp = xleft;
            xleft = xright;
            xright = tmp;
        }
        if(ytop < ybottom){
            double tmp = ytop;
            ytop = ybottom;
            ybottom = tmp;
        }
        Line givenLine = Line(xstart,ystart,xend,yend);
        Line rectLine1 = Line(xleft,ytop,xright,ytop);
        Line rectLine2 = Line(xright,ytop,xright,ybottom);
        Line rectLine3 = Line(xright,ybottom,xleft,ybottom);
        Line rectLine4 = Line(xleft,ybottom,xleft,ytop);
        if(DoTwoLinesIntersect(givenLine,rectLine1) || DoTwoLinesIntersect(givenLine,rectLine2) ||
                DoTwoLinesIntersect(givenLine,rectLine3) || DoTwoLinesIntersect(givenLine,rectLine4) || IsLineInsideOfRectangle(givenLine)){
            cout << "T" << endl;
        }
        else{
            cout << "F" << endl;
        }
    }
    return 0;
}