#include <cstdio>

#include "RangeSearch.h"

#define EPSILON 1

typedef RangeSearch<int, int, EPSILON> IntRangeSearch;

int main(int argc, char* argv[])
{
	if (argc > 1)
		if (!freopen(argv[1], "r", stdin))
			return 1;
	int t;
	scanf("%d", &t);
	IntRangeSearch range_search;
	while (t--)
	{
		int n;
		scanf("%d", &n);
		while (n--)
		{
			int min, max, data;
			scanf("%d %d %d", &min, &max, &data);
			range_search.add_range(IntRangeSearch::Range(min, max), data);
		}

		range_search.compile();
		fprintf(stderr, "----------\n");
		for (IntRangeSearch::RangeMap::iterator it = range_search.ranges.begin(); it != range_search.ranges.end(); ++it)
		{
			fprintf(stderr, "[%d,%d) ->", it->first.min, it->first.max);
			for (IntRangeSearch::DataSet::iterator iter = it->second.begin(); iter != it->second.end(); ++iter)
				fprintf(stderr, " %d", *iter);
			fprintf(stderr, "\n");
		}

		fprintf(stderr, "----------\n");
		scanf("%d", &n);
		while (n--)
		{
			int value;
			scanf("%d", &value);
			IntRangeSearch::DataSet data_set;
			range_search.find(value, data_set);
			printf("%ld", data_set.size());
			for (IntRangeSearch::DataSet::iterator it = data_set.begin(); it != data_set.end(); ++it)
				printf(" %d", *it);
			printf("\n");
		}

		range_search.clear();
	}

	return 0;
}
