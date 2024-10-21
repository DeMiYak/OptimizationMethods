#include "NelderMeadMethod.h"
#include"algorithm"

/// � �������� �������
/// InitTrajectoryAsSimplex - ���������
/// FindMinMaxIndex - ���������
/// MassCenter - ���������
/// Reflection - ���������
/// Compression - ...
/// Stretching - ...
/// Reduction - ...

/// <summary>
/// Optimize ������ ���, ��� ����� � ������ ���� ��������� �����, � �� ����� �
/// ��������������. �������� ��, ��� �� ������ �������� �� void ������, �������, ���
/// ��������� �������� ������ ���� ������.
/// </summary>
/// <param name="ba">������� �������</param>
/// <param name="bf">������� �������</param>
/// <param name="bsc">������� �������� ���������</param>
void NelderMeadMethod::Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc)
{
	//dt.SetBaseFunction(bf);

	size_t dim = startPoint.size();
	InitTrajectoryAsSimplex(ba);
	/*InitSimplexValues(bf);*/
	/// �������� f_n_2, ��������� ��� ��������� ��� �������� �������� ���������
	double f_n_2 = 0;
	/// ����� ��������
	size_t count = 0;
	
	//dt.SetCount(count);
	//dt.SetFVal(f_n_2);
	//dt.SetSimplexIndex(simplex_index);
	//dt.SetSimplexValues(simplex_value);
	//dt.SetTrajectory(trajectory);
	do {
		++count;
		//dt.SetCount(++count);
		/// ���� ��� �������� ����� � ���������������� ��������
		pair<size_t, size_t> minmax_index = FindMinMaxIndex(bf);
		/// �������-�������� �� ���������
		
		// ��������� x_h, x_l � c_m.
		//--------------------------------------------------------------------------------------
		/// ����� �������� ���������
		vector<double> x_min = trajectory[simplex_index[minmax_index.first]];
		/// �������� � ������� ��������
		double f_min = bf(x_min);
		
		/// ����� ��������� ���������
		vector<double> x_max = trajectory[simplex_index[minmax_index.second]];
		/// �������� � ������� ���������
		double f_max = bf(x_max);

		/// 0. ���������� ������ ���� ��� ����� �����
		/// �� ������ ����� ����� ���� ����������� ��� ������������� ������������ �������.
		/// ��� ������� ������ ���������� �������� �������������� �����-������� �������.
		vector<double> x_n_2 = MassCenter(minmax_index);
		
		/// x_n_2 ������ ������� ��� ����� ����, ������� �������������� ����� �� �����
		f_n_2 = bf(x_n_2);
		//dt.SetFVal(f_n_2);
		//--------------------------------------------------------------------------------------

		// ���������: ���������
		//--------------------------------------------------------------------------------------
		/// 1. ���������. ����� ����� �� �������
		vector<double> x_n_3 = Reflection(x_n_2, x_max, ba);
		//--------------------------------------------------------------------------------------

		// ��������� f_n_3
		//--------------------------------------------------------------------------------------
		/// 2. ����� ��������� ������������� (����������� ������������,
		/// ������ �� �������� � ����� ���������)
		double f_n_3 = bf(x_n_3);
		//--------------------------------------------------------------------------------------
		
		/// 3. ��������, ���� � if-�������,
		/// ��������� �������� ����� ���������� ��� ������ ��������� ��������.
		
		// ����������� �� �����������?
		//--------------------------------------------------------------------------------------
		/// ������ ���������� (Stretching). � ���� ������ ����� ��������� �� ����� �� �������.
		if (f_n_3 < f_max) {
			// ��
			//--------------------------------------------------------------------------------------

			// ����������
			//--------------------------------------------------------------------------------------
			vector<double> x_n_4 = Stretching(x_n_2, x_n_3, ba);
			size_t size = trajectory.size();
			// ��������� f_n_4
			//--------------------------------------------------------------------------------------
			double f_n_4 = bf(x_n_4);
			
			// ����������� �� �����������
			//--------------------------------------------------------------------------------------
			/// � ���������� ����������� ����� x_n_4
			if (f_n_4 < f_min) {
				// ��
				//--------------------------------------------------------------------------------------
				/// ����� � ���� ���������� (��� ��� ����� ������������ ������������� ���,
				/// ��� ����� ���� �� ����� ������ �����
				/// ��������� ��� ������������, ��� ������������� ���������� ������ ����,
				/// ����������� ��� ������ ����� - �����, ������� ���, ����� ������ ���������� �������.
				trajectory.push_back(x_n_4);
			}
			/// � ���������� ����������� ����� x_n_3
			else {
				// ���
				//--------------------------------------------------------------------------------------
				trajectory.push_back(x_n_3);
			}

			/// ������ ������ ����� ��������� �� ������ (������ ���
			/// �������� � �����)
			simplex_index[minmax_index.second] = trajectory.size() - 1;
		}
		else {
			// ���
			//--------------------------------------------------------------------------------------
			
			// ����������� �� ����������� ��� ���� i != h?
			//--------------------------------------------------------------------------------------
			/// �������� ���������� �� ������� ������
			/// �����: �������� ������ ��� f(x_i), ��� ��������� ������ ��� �����������
			bool check = true;
			for (size_t i = 0; i < dim + 1; ++i) {
				// ���������� �� ���� x_i, ����� x_h.
				// ���� ���� �� ��� ������ i: f_n_3 >= f_i - ���
				if (i != minmax_index.second) {
					double f_i = bf(trajectory[simplex_index[i]]);
					if (f_n_3 >= f_i) {
						check = false;
						break;
					}
				}
			}

			if (!check) {
				// ��
				//--------------------------------------------------------------------------------------
				
				// ����������� �� ���������?
				//--------------------------------------------------------------------------------------
				/// �������� x_max �� x_n_3
				if (f_n_3 >= bf(trajectory[simplex_index[minmax_index.second]])) {
					// ���
					//--------------------------------------------------------------------------------------
					x_max = x_n_3;
				}

				// ������: ���������
				//--------------------------------------------------------------------------------------
				/// ������. ��� ����� ������ �� ����� �������������� �����, ��� ���
				/// ��� ���� ��������� � Reflection.
				vector<double> x_n_5 = Compression(x_n_2, x_max);
				
				// ��������� f_n_5
				//--------------------------------------------------------------------------------------
				/// ���������� f(x_n_5)
				double f_n_5 = bf(x_n_5);
				if (f_n_5 > f_max) {
					// ��
					//--------------------------------------------------------------------------------------
					
					// ��������
					//--------------------------------------------------------------------------------------
					/// ��������. ������, ������� � �������� ����� ����������
					/// (�� �������� ��������). ��� ����� ������������� ������ ���������, �������
					/// �������������� ��� ����� �� �����.
					Reduction(minmax_index, x_min);
				}
				else {
					// ���
					//--------------------------------------------------------------------------------------
					
					// ������ x_max �� x_n_5
					//--------------------------------------------------------------------------------------
					/// �������� ����� ����� ����������� ������
					trajectory.push_back(x_n_5);
					/// �������� ������ ���������, ������� �����������
					/// ����������� �����, ���������� �������������
					simplex_index[minmax_index.second] = trajectory.size() - 1;
				}
			}
			else {
				// ���
				//--------------------------------------------------------------------------------------
				/// ������ x_max �� x_n_3 
				trajectory.push_back(x_n_3);
				simplex_index[minmax_index.second] = trajectory.size() - 1;
			}
		}
	/*	dt.SetSimplexIndex(simplex_index);
		dt.SetTrajectory(trajectory);*/
	/// ��������, ����� Check ����� ��������, ������ ����� �����, ������� ������� ����������� ������
	} 
	while (!bsc.Check(trajectory, simplex_index, bf, f_n_2, count));
	/*while (!bsc.Check(dt));*/
}

void NelderMeadMethod::InitSimplexValues(const BaseFunction& bf)
{
	simplex_value.clear();
	/// ����� ��������������, ��� trajectory.size() = startPoint.size() + 1.
	for (size_t i = 0; i < trajectory.size(); ++i) {
		simplex_value.push_back(bf(trajectory[i]));
	}
}

/// <summary>
/// ���������� ���������� ���������. ������ ����� ���������� � ���,
/// ��� ���������, ��� �������� ����� ������ ���������������.
/// 
/// �������� ��������� ���� �� �����������.
/// </summary>
void NelderMeadMethod::InitTrajectoryAsSimplex(const BaseArea& ba)
{
	/// ������� ���������� � ��������� ��������� �����
	trajectory.clear();
	trajectory.push_back(startPoint);
	size_t size = startPoint.size();
	double d1 = t / (size * sqrt(2)) * (sqrt(size + 1) + size - 1);
	double d2 = t / (size * sqrt(2)) * (sqrt(size + 1)  - 1);
	/// ������ ����� ��� ���������� ���������
	vector<double> copy(startPoint);
	

	/// �������� ����� �� ������� (��� � ���������)
	copy[0] += d1;
	for (size_t i = 1; i < size; ++i) {
		copy[i] += d2;
	}

	/// �������� ��������� - ���������� ���������� ������� �������
	for (size_t i = 1; i < size; ++i) {
		trajectory.push_back(copy);
		/// �������� d1 �� d2 � d2 �� d1
		copy[i] = startPoint[i] + d1;
		copy[i - 1] = startPoint[i - 1] + d2;
	}
	trajectory.push_back(copy);

	/// ���������� ������� �������� ���������. �� ����� �������� ��
	/// ������� ��������� �� ������ ��������. ��� ����� ��������
	/// ���������� ���������� ���������
	simplex_index.clear();
	for (size_t i = 0; i < size+1; ++i) {
		simplex_index.push_back(i);
	}

	/// ������������ �����
	for (size_t i = 1; i < trajectory.size(); ++i) {
		CorrectPointPlacement(startPoint, trajectory[i], ba);
	}
}

vector<double> NelderMeadMethod::MassCenter(const pair<size_t, size_t>& minmax_index)
{
	/// ����������� ����� 
	size_t size = startPoint.size();
	size_t index_max = simplex_index[minmax_index.second];
	vector<double> x_n_2(size, 0);

	/// ����������� �� ������ ���������, ���������
	/// ���, ����� �����, �� ������� ����������� ��������
	for (size_t i = 0; i < size + 1; ++i) {
		if (index_max != simplex_index[i]) {
			/// ����������� �������������� ��������
			//transform(x_n_2.begin(), x_n_2.end(), trajectory[simplex_index[i]].begin(), x_n_2.begin(), plus<double>());
			for (size_t k = 0; k < size; ++k) {
				x_n_2[k] += trajectory[simplex_index[i]][k];
			}
		}
	}

	/// ���������� �����
	for (size_t i = 0; i < size; ++i) {
		x_n_2[i] /= size;
	}
	return x_n_2;
}

vector<double> NelderMeadMethod::Reflection(const vector<double>& x_n_2, const vector<double>& x_max, const BaseArea& ba)
{
	size_t size = startPoint.size();
	vector<double> x_n_3(x_n_2);
	/// ���������� ���������
	for (size_t i = 0; i < size; ++i) {
		x_n_3[i] += alpha * (x_n_2[i] - x_max[i]);
	}
	CorrectPointPlacement(x_n_2, x_n_3, ba);
	return x_n_3;
}

void NelderMeadMethod::Reduction(const pair<size_t, size_t>& minmax_index, const vector<double>& x_min)
{
	size_t size = simplex_index.size();
	size_t min_index = minmax_index.first;
	/// ��������� �� ����� �������� �������� ���� ��������,
	/// ������� ��������� ��� ����� � ����������
	for (size_t i = 0; i < size; ++i) {
		size_t curr_index = simplex_index[i];
		if (min_index != curr_index) {
			/// �������� ��� x_i �� x_l + 0.5*(x_i-x_l)
			vector<double> x_i(x_min);
			const vector<double>& x_curr(trajectory[curr_index]);
			for (size_t k = 0; k < x_i.size(); ++k) {
				x_i[k] += 0.5 * (x_curr[k] - x_min[k]);
			}
			/// ����� ���������, ��������� � ���������� � ������ ������
			trajectory.push_back(x_i);
			simplex_index[i] = trajectory.size() - 1;
		}
	}
}

vector<double> NelderMeadMethod::Compression(const vector<double>& x_n_2, const vector<double>& x_max)
{
	vector<double> x_n_5(x_n_2);
	for (size_t i = 0; i < x_n_2.size(); ++i) {
		x_n_5[i] += beta * (x_max[i] - x_n_2[i]);
	}
	return x_n_5;
}

vector<double> NelderMeadMethod::Stretching(const vector<double>& x_n_2, const vector<double>& x_n_3, const BaseArea& ba)
{
	size_t size = startPoint.size();
	vector<double> x_n_4(x_n_2);
	for (size_t i = 0; i < size; ++i) {
		x_n_4[i] += gamma * (x_n_3[i] - x_n_2[i]);
	}
	CorrectPointPlacement(x_n_2, x_n_4, ba);
	return x_n_4;
}

void NelderMeadMethod::CheckInput()
{
	bool check = true;
	if (alpha <= 0) {
		cout << endl << "Error: Alpha must be > 0." << endl;
		check = false;
	}
	if (gamma <= 1) {
		cout << endl << "Error: Gamma must be > 1." << endl;
		check = false;
	}
	if (!(0 < beta && beta < 1)) {
		cout << endl << "Error: Beta must be between 0 and 1." << endl;
		check = false;
	}
	if (!check) {
		exit(1);
	}
}

pair<size_t, size_t> NelderMeadMethod::FindMinMaxIndex(const BaseFunction& bf) const
{
	/// ��������� ������ ��� k-�� ��������
	size_t size = simplex_index.size();

	/// ������ �������, �������� � ���� �� �������
	double min = bf(trajectory[simplex_index[0]]);
	double max = min;
	size_t min_index = 0, max_index = 0;
	for (size_t i = 1; i < size; ++i) {
		double f = bf(trajectory[simplex_index[i]]);
		if (min > f) {
			min = f;
			min_index = i;
		}
		if (max < f) {
			max = f;
			max_index = i;
		}
	}
	return pair<size_t, size_t>(min_index, max_index);
}