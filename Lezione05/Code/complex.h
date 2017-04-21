class complex
{
public:
	//default ctor
	complex();
	//ctor re im
	complex(const double& Re, const double& Im);
	//ctor rho theta
	complex(const double& Rho, const double& Theta, bool flag);
	//dtor
	~complex(){};

	//operator =()
	complex& operator=(const complex& original);

	//operator +()
	complex& operator+(const complex& addendum);

	//methods
	double Re();
	double Im();
	double Mod();
	double Rho();
	double Theta();
	void Print() const;



private:

	double re_p;
	double im_p;
};