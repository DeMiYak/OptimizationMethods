#pragma once
#include"BaseArea.h"

/// <summary>
/// ����� ��������������� ��� ���������� 
/// ������� ������ ����������.
/// ������ pair<vector<double>, vector<double>> ��� �����.
/// �� ������ �����, ��� vector<pair<double,double>>, ��� ���
/// ��������������� ��� �����, � �� ����� ����� ����������� ���
/// </summary>
class Rectangle : public BaseArea {
public:
	/// <summary>
	/// ����������� ��� ���������������. �������������� 
	/// bound ������ ����� fpt, spt ������������� � ��������������.
	/// ��������� �� ������������ �������� (�������� ��������) �
	/// �� �������������� ���������� ��������� (���������� ���������������) 
	/// </summary>
	/// <param name="fpt">������ �����</param>
	/// <param name="spt">������ �����</param>
	Rectangle(vector<double> fpt, vector<double> spt) : BaseArea() {
		/// �������� �� ������������ ������
		CheckValidity(fpt, spt);
		
		/// ������ ������� ��� ������ ���������������
		for (size_t i = 0; i < fpt.size(); ++i) {
			bound.push_back(make_pair(fpt[i], spt[i]));
		}
	};
	
	/// <summary>
	/// ����������� ����������� 
	/// </summary>
	/// <param name="rectangle">���������� ������</param>
	Rectangle(const Rectangle& rectangle) : BaseArea(), bound(rectangle.bound) {};

	/// <summary>
	/// ����������� �����������
	/// </summary>
	/// <param name="rectangle">������������ ������</param>
	Rectangle(Rectangle&& rectangle) noexcept : BaseArea(), bound(move(rectangle.bound)) {};

	Rectangle& operator=(const Rectangle& rectangle){
		if (this != &rectangle) {
			this->bound = rectangle.bound;
		}
		return *this;
	}
	virtual vector<pair<double, double>> GetBounds() const { return bound; };

	virtual bool IsInside(const vector<double>& point) const;
private:
	/// <summary>
	/// �������, �������������� ������
	/// </summary>
	vector<pair<double, double>> bound;

	/// <summary>
	/// ��������� ����� ��� �������� �����-���������� �� ������������:
	/// ��� �� ���������� ��������������� � ������������ ������������ �����.
	/// ��� ����������� ����� ����� ���������� ������� "����������� ������������" ��
	/// �������� � ��������  
	/// </summary>
	/// <param name="fpt">������ �����</param>
	/// <param name="spt">������ �����</param>
	void CheckValidity(const vector<double>& fpt, const vector<double>& spt);
};

///// <summary>
///// @brief ������� ��������� �������
///// </summary>
//class BaseSampleGenerator
//{
//public:
//	/// <summary>
//	/// ���������� ������
//	/// </summary>
//	/// <param name="_samVol">����� �������</param>
//	BaseSampleGenerator(int _samVol) :
//		samVol(_samVol),
//		sample(new int[_samVol]) {
//	};
//	/// <summary>
//	/// ����������� �����������
//	/// </summary>
//	/// <param name="bsg">��������� �������</param>
//	BaseSampleGenerator(const BaseSampleGenerator& bsg) :
//		samVol(bsg.samVol)
//	{
//		sample = new int[samVol];
//		for (int i = 0; i < samVol; i++) {
//			sample[i] = bsg.sample[i];
//		}
//	};
//	/// <summary>
//	/// ����������� �����������
//	/// </summary>
//	/// <param name="bsg">��������� �������</param>
//	BaseSampleGenerator(BaseSampleGenerator&& bsg) noexcept :
//		samVol(std::exchange(bsg.samVol, 0)),
//		sample(std::move(bsg.sample))
//	{
//		bsg.sample = nullptr;
//	}
//	/// <summary>
//	/// �������� ������������ � ������������
//	/// </summary>
//	/// <param name="bsg">��������� �������</param>
//	/// <returns>��������� �������</returns>
//	BaseSampleGenerator& operator=(const BaseSampleGenerator& bsg) {
//		if (this != &bsg) {
//			samVol = bsg.samVol;
//			delete[] sample;
//			sample = new int[samVol];
//			for (int i = 0; i < samVol; i++) {
//				sample[i] = bsg.sample[i];
//			}
//		}
//		return *this;
//	}
//	/// <summary>
//	/// �������� ������������ � ������������
//	/// </summary>
//	/// <param name="bsg">��������� �������</param>
//	/// <returns>��������� �������</returns>
//	BaseSampleGenerator& operator=(BaseSampleGenerator&& bsg) noexcept {
//		if (this != &bsg) {
//			sample = std::move(bsg.sample);
//			samVol = std::exchange(bsg.samVol, 0);
//			bsg.sample = nullptr;
//		}
//		return *this;
//	}
//	/// <summary>
//	/// ����� ������ � �������
//	/// </summary>
//	friend std::ostream& operator<<(std::ostream& os, const BaseSampleGenerator& bsg) {
//		os << std::endl << "����� ������� = " << bsg.samVol;
//		os << "\n�������: [" << bsg.sample[0];
//		for (int i = 1; i < bsg.samVol; i++) {
//			os << ", " << bsg.sample[i];
//		}
//		os << "]" << std::endl;
//		return os;
//	}
//	/// <summary>
//	/// ����������� ����� ��������� �������
//	/// </summary>
//	/// <param name="dis">�������������</param>
//	/// <param name="_samVol">����� �������</param>
//	virtual void Simulate(const Distribution& dis, int _samVol) = 0;
//	/// <summary>
//	/// ����������� ���������� ������
//	/// </summary>
//	virtual ~BaseSampleGenerator() { delete[] sample; samVol = 0; };
//	/// <summary>
//	/// ��������� �������
//	/// </summary>
//	/// <returns>��������� �� �������</returns>
//	int* GetSample() const { return sample; };
//	/// <summary>
//	/// ��������� ������ �������
//	/// </summary>
//	/// <returns>����� �������</returns>
//	int GetSamVol() const { return samVol; };
//protected:
//	/// <summary>
//	/// ������ ���������� ��������
//	/// </summary>
//	int* sample;
//	/// <summary>
//	/// ����� �������
//	/// </summary>
//	int samVol;
//};