// Lab 1 ver.4 Shafran Volodymyr
#include <iostream>
using namespace std;

double getCont(double& a);
bool getPoint(double& x, double& y);
int wherePoint(double a, double x, double y);
double distPointCont(double a, double x, double y, int location_point);
void outPoint(double x, double y);
void outCont(double a);
void outResult(double x, double y, double a, int location_point, double dist);
bool processCont(double a);

int main()
{
	double a = 1; // parameter

	processCont(a);
	cout << "<<<END OF WORK>>>";
	return 0;
}

double getCont(double& a)
{
	cout << "Enter a parameter for the contour(parameter > 0): ";
	cin >> a;
	if (cin.eof()) // User entered CRTL-Z
	{
		cout << "<<<CONTOUR IS ABSENT>>>\n";
		cin.clear();
		return 2;
	}
	cin.clear();
	if (cin.get() != '\n' || a <= 0) //Checking the correctness of the entered data.
	{
		cout << "<<<WRONG PARAMETER>>>\n";
		cin.clear();
		return 1;
	}
	return 0;
}

bool getPoint(double& x, double& y)
{
	cout << "Enter coordinate point \"x\": ";
	cin >> x;
	if (cin.eof())  // User entered CRTL-Z
	{
		cin.clear();
		return false;
	}
	cin.clear();
	if (cin.get() != '\n') //Checking the correctness of the entered data.
	{
		cin.clear();
		return false;
	}

	cout << "Enter coordinate point \"y\": ";
	cin >> y;
	if (cin.eof()) // User entered CRTL-Z
	{
		cin.clear();
		return false;
	}
	cin.clear();
	if (cin.get() != '\n') //Checking the correctness of the entered data.
	{
		cin.clear();
		return false;
	}

	return true;
}

int wherePoint(double a, double x, double y)
{
	if ((x < 0 || x > 2 * a) && (y < 0 || y > 2 * a)) return 1;
	// Our hexagon is squared. To begin with, a point is outside this square, and therefore outside our figure. We return 1.
	else
	{
		if ((x - y - a > 0) || (x - y + a < 0)) return 1;
		/*The next step is to calculate whether the point is in two triangles that do not belong to our figure.
		If the point is in the lower triangle then the equations x-y-a>0
		If the point is in the upper triangle then the equations x-y+a<0
		Let's make the equation of the straight lines:
		1. The first is a straight line beyond two points A(0,0) and F(2a,a):
		(x-a)/(2a-a)=(y-0)/(a-0)
		(x-a)/a=y/a
		x-y-a=0
		2. The second is a straight line behind two points B(0,a) and C(a,2a):
		(x-0)/(a-0)=(y-a)/(2a-a)
		x/a=(y-a)/a
		x-y+a=0 */
		else
		{
			if ((x - y - a == 0) || (x - y + a == 0) || ((x >= 0 && x < a) && y == 0) || ((x > a && x <= 2 * a) && y == 2 * a) || ((y >= 0 && y < a) && x == 0) || ((y > a && y < 2 * a) && x == 2 * a))
				return 0; // Check if the point lies on the contour. If so, we return 0.
			else return -1; // If all these conditions are not met then it is obvious that the point is inside our figure.
		}
	}
}

double distPointCont(double a, double x, double y, int location_point)
{/*Distance calculation algorithm. If the point lies on the contour, then the distance is zero.
 Then for each side we check the distances using the scalar product, the angle, if the cosine is negative,
 then the perpendicular cannot be projected, and the shortest distance will be to the nearest vertex of the figure.
 To find the distance when the perpendicular is possible,
 use the formula to find the area given three points (two vertices and an input point) in coordinates.
 Then all measured lengths are compared and the shortest is selected.
 Vector scalar product formula: (FM, FE) = (x - a) * (2 * a - a) + (y - 0) * (a - 0)
 If the scalar product is less than zero then the angle is obtuse.
 The formula for finding the distance to the top of the shape: |FM| = sqrt(pow(x - a, 2) + pow(y - 0, 2))
 The formula for finding the distance at a perpendicular: h = abs((x - a) * (a - 0) - (2 * a - a) * (y - 0)) / (sqrt(pow(2 * a - a, 2) + pow(a - 0, 2)))
 Points of our figure: M (x, y), F(a, 0), E(2a, a), B(0, a), A(0, 0), C(a, 2a), D(2a, 2a).
 */
	double dist = 0, distFE, distBC, distAF, distAB, distCD, distDE;
	if (location_point == 0)
		return location_point;

	if ((x - a) * (2 * a - a) + (y - 0) * (a - 0) < 0) // Side distance check FE
	{// Scalar product of vectors: (FM, FE). If the angle is obtuse, then the closest distance is the distance to the top of the hexagon. 
		distFE = sqrt(pow(x - a, 2) + pow(y - 0, 2));
	}// If the angle is sharp then check the angle from the next vertex.
	else if ((x - 2 * a) * (a - 2 * a) + (y - a) * (0 - a) < 0)
	{// Scalar product of vectors: (EM, EF). If the angle from the second vertex is obtuse, then there will be the desired distance to this very point.
		distFE = sqrt(pow(x - 2 * a, 2) + pow(y - a, 2));
	}
	else
	{	/*If the angle from the second vertex is also sharp, it is obvious that the perpendicular can be dropped from the point.
	And this is the desired distance.*/
		distFE = abs((x - a) * (a - 0) - (2 * a - a) * (y - 0)) / (sqrt(pow(2 * a - a, 2) + pow(a - 0, 2)));
	}


	if ((x - 0) * (a - 0) + (y - a) * (2 * a - a) < 0) // Side distance check BC
	{// Scalar product of vectors: (BM, BC). If the angle is obtuse, then the closest distance is the distance to the top of the hexagon. 
		distBC = sqrt(pow(x - 0, 2) + pow(y - a, 2));
	}// If the angle is sharp then check the angle from the next vertex.
	else if ((x - a) * (0 - a) + (y - 2 * a) * (a - 2 * a) < 0)
	{// Scalar product of vectors: (CM, CB). If the angle from the second vertex is obtuse, then there will be the desired distance to this very point.
		distBC = sqrt(pow(x - a, 2) + pow(y - 2 * a, 2));
	}
	else
	{	/*If the angle from the second vertex is also sharp, it is obvious that the perpendicular can be dropped from the point.
	And this is the desired distance.*/
		distBC = abs((x - 0) * (2 * a - a) - (a - 0) * (y - a)) / (sqrt(pow(a - 0, 2) + pow(2 * a - a, 2)));
	}


	if ((x - 0) * (a - 0) + (y - 0) * (0 - 0) < 0) // Side distance check AF
	{// Scalar product of vectors: (AM, AF). If the angle is obtuse, then the closest distance is the distance to the top of the hexagon. 
		distAF = sqrt(pow(x - 0, 2) + pow(y - 0, 2));
	}// If the angle is sharp then check the angle from the next vertex.
	else if ((x - a) * (0 - a) + (y - 0) * (0 - 0) < 0)
	{// Scalar product of vectors: (FM, FA). If the angle from the second vertex is obtuse, then there will be the desired distance to this very point.
		distAF = sqrt(pow(x - a, 2) + pow(y - 0, 2));
	}
	else
	{	/*If the angle from the second vertex is also sharp, it is obvious that the perpendicular can be dropped from the point.
	And this is the desired distance.*/
		distAF = abs((x - a) * (0 - 0) - (0 - a) * (y - 0)) / (sqrt(pow(a - 0, 2) + pow(0 - 0, 2)));
	}


	if ((x - 0) * (0 - 0) + (y - 0) * (a - 0) < 0) // Side distance check AB
	{// Scalar product of vectors: (AM, AB). If the angle is obtuse, then the closest distance is the distance to the top of the hexagon. 
		distAB = sqrt(pow(x - 0, 2) + pow(y - 0, 2));
	}// Scalar product of vectors: (BM, BA). If the angle is sharp then check the angle from the next vertex.
	else if ((x - 0) * (0 - 0) + (y - a) * (0 - a) < 0)
	{// If the angle from the second vertex is obtuse, then there will be the desired distance to this very point.
		distAB = sqrt(pow(x - 0, 2) + pow(y - a, 2));
	}
	else
	{	/*If the angle from the second vertex is also sharp, it is obvious that the perpendicular can be dropped from the point.
	And this is the desired distance.*/
		distAB = abs((x - 0) * (0 - a) - (0 - 0) * (y - a)) / (sqrt(pow(0 - 0, 2) + pow(a - 0, 2)));
	}


	if ((x - a) * (2 * a - a) + (y - 2 * a) * (2 * a - 2 * a) < 0) // Side distance check CD
	{// Scalar product of vectors: (CM, CD). If the angle is obtuse, then the closest distance is the distance to the top of the hexagon. 
		distCD = sqrt(pow(x - a, 2) + pow(y - 2 * a, 2));
	}// If the angle is sharp then check the angle from the next vertex.
	else if ((x - 2 * a) * (a - 2 * a) + (y - 2 * a) * (2 * a - 2 * a) < 0)
	{// Scalar product of vectors: (DM, DC). If the angle from the second vertex is obtuse, then there will be the desired distance to this very point.
		distCD = sqrt(pow(x - 2 * a, 2) + pow(y - 2 * a, 2));
	}
	else
	{	/*If the angle from the second vertex is also sharp, it is obvious that the perpendicular can be dropped from the point.
	And this is the desired distance.*/
		distCD = abs((x - 2 * a) * (2 * a - 2 * a) - (a - 2 * a) * (y - 2 * a)) / (sqrt(pow(2 * a - a, 2) + pow(2 * a - 2 * a, 2)));
	}


	if ((x - 2 * a) * (2 * a - 2 * a) + (y - a) * (2 * a - a) < 0) // Side distance check DE
	{// Scalar product of vectors: (DM, DE).If the angle is obtuse, then the closest distance is the distance to the top of the hexagon. 
		distDE = sqrt(pow(x - 2 * a, 2) + pow(y - a, 2));
	}// If the angle is sharp then check the angle from the next vertex.
	else if ((x - 2 * a) * (2 * a - 2 * a) + (y - 2 * a) * (a - 2 * a) < 0)
	{// Scalar product of vectors: (EM, ED). If the angle from the second vertex is obtuse, then there will be the desired distance to this very point.
		distDE = sqrt(pow(x - 2 * a, 2) + pow(y - 2 * a, 2));
	}
	else
	{	/*If the angle from the second vertex is also sharp, it is obvious that the perpendicular can be dropped from the point.
	And this is the desired distance.*/
		distDE = abs((x - 2 * a) * (a - 2 * a) - (2 * a - 2 * a) * (y - 2 * a)) / (sqrt(pow(2 * a - 2 * a, 2) + pow(a - 2 * a, 2)));
	}


	if (distBC <= distFE && distBC <= distAF && distBC <= distAB && distBC <= distCD && distBC <= distDE)
		dist = distBC;
	else if (distFE <= distBC && distFE <= distAF && distFE <= distAB && distFE <= distCD && distFE <= distDE)
		dist = distFE;
	else if (distAF <= distBC && distAF <= distFE && distAF <= distAB && distAF <= distCD && distAF <= distDE)
		dist = distAF;
	else if (distAB <= distBC && distAB <= distFE && distAB <= distAF && distAB <= distCD && distAB <= distDE)
		dist = distAB;
	else if (distCD <= distBC && distCD <= distFE && distCD <= distAF && distCD <= distAB && distCD <= distDE)
		dist = distCD;
	else if (distDE <= distBC && distDE <= distFE && distDE <= distAF && distDE <= distAB && distDE <= distCD)
		dist = distDE;
	return dist;
}

void outPoint(double x, double y)
{
	cout << "(" << x << ";" << " " << y << ")\n";
}

void outCont(double a)
{
	cout << "[" << a << "]\n";
}

void outResult(double x, double y, double a, int location_point, double dist)
{
	outPoint(x, y);
	switch (location_point)
	{
	case -1: cout << "IN_C\n"; break;
	case 0: cout << "ON_C\n"; break;
	case 1: cout << "OUT_C\n"; break;
	}
	outCont(a);
	cout << "DISTANCE = " << dist << endl;
}

bool processCont(double a)
{
	double x, y, dist;
	int location_point, q;

	while (1) {
	tryAgain:
		switch (q = getCont(a))
		{
		case 0: break;
		case 1: goto tryAgain;
		case 2: return 0;
		}
		if (!getPoint(x, y))
		{
			cout << "<<<POINT IS ABSENT>>>\n";
			goto tryAgain;
		}
		location_point = wherePoint(a, x, y);
		dist = distPointCont(a, x, y, location_point);
		outResult(x, y, a, location_point, dist);
	}
}