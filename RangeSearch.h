#ifndef RANGE_SEARCH_H_
#define RANGE_SEARCH_H_

#include <set>
#include <map>
#include <list>
#include <algorithm>

using std::set;
using std::map;
using std::list;

/**
 * In its most general form, the range searching problem consists of preprocessing a set S of objects, in order to
 * determine which objects from S intersect with a query object, called a range. For example, S may be a set of points 
 * corresponding to the coordinates of several cities, and we want to find the cities within a certain latitude and 
 * longitude range.
 */

/**
 * Range of [min, max)
 * It supposed to be illegal if max <= min
 */
template <typename Boundary>
class RangeTemplate
{
public:
	RangeTemplate()
	{
	}
	explicit RangeTemplate(const Boundary& value)
	: min(value)
	, max(value)
	{
	}
	RangeTemplate(const Boundary& min_, const Boundary& max_)
	: min(min_)
	, max(max_)
	{
	}

	/// No two intersecting ranges are possible in a RangeTemplateSearch
	bool operator<(const RangeTemplate& range) const
	{
		return max <= range.min;
	}

	Boundary min, max;
};

template <typename Boundary, typename Data, Boundary EPSILON>
class RangeSearch
{
public:
	class BoundaryEvent
	{
	public:
		Data data;
		bool add;		// True if data must be added, false if it must be removed
	};
	typedef RangeTemplate<Boundary> Range;
	typedef set<Data> DataSet;
	typedef list<BoundaryEvent> EventList;
	typedef map<Boundary, EventList> EventMap;
	typedef map<Range, DataSet> RangeMap;

	int add_range(Range range, Data data)
	{
		range.max += EPSILON;
		if (range.max <= range.min)
			return -1;
		BoundaryEvent event;
		event.data = data;

		// Inserts add event
		event.add = true;
		typename EventMap::iterator iter = events.find(range.min);
		if (iter == events.end())
			iter = events.insert(typename EventMap::value_type(range.min, EventList())).first;
		iter->second.push_front(event);

		// Inserts remove event
		event.add = false;
		iter = events.find(range.max);
		if (iter == events.end())
			iter = events.insert(typename EventMap::value_type(range.max, EventList())).first;
		iter->second.push_front(event);
		return 0;
	}

	void compile()
	{
		DataSet data_set;
		Range range;
		for (typename EventMap::const_iterator it = events.begin(); it != events.end(); ++it)
		{
			const Boundary& boundary = it->first;
			range.min = range.max;
			range.max = boundary;
			if (!data_set.empty())
				ranges.insert(typename RangeMap::value_type(range, data_set));
			const EventList& event_list = it->second;
			for (typename EventList::const_iterator event_iter = event_list.begin(); event_iter != event_list.end();
					++event_iter)
				if (event_iter->add)
					data_set.insert(event_iter->data);
				else
					data_set.erase(event_iter->data);
		}
	}

	void clear()
	{
		events.clear();
		ranges.clear();
	}

	void find(const Boundary& value, DataSet& data_set) const
	{
		typename RangeMap::const_iterator it = ranges.find(Range(value, value + EPSILON));
		if (it != ranges.end())
			data_set = it->second;
		else
			data_set.clear();
	}

	EventMap events;
	RangeMap ranges;
};

#endif
