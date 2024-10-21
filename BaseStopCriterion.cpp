#include"BaseStopCriterion.h"

bool BaseStopCriterion::Check(const size_t& count) const
{
	if (count > iter_num) {
		return true;
	}
	return false;
}
