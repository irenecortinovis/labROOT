class istogramma
{
public:

	//default ctor
	istogramma();
	//ctor
	istogramma(const int& nBin, const float& min, const float& max);
	//copy ctor
	istogramma(const istogramma& original);
	//dtor
	~istogramma();
	//operator =()
	istogramma& operator=(const istogramma& original);

	//methods
	int Fill(const float& value);
	void Print() const;
	float GetMean() const;

private:

	int nBin_p;
	float min_p;
	float max_p;
	float invStep_p;
	int* binContent_p;
	int entries_p;
	float sum_p;
	float sum2_p;

};