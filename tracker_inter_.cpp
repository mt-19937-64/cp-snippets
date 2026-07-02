class tracker_inter
{
	public:
		set<pair<int, int>> forbidden;
		
		int clear()
		{
			forbidden.clear();
			return 0;
		}
	
	        bool inter_check(int st, int endi)
		{
			auto itr = forbidden.upper_bound({st, st});
			if(itr==forbidden.end() || itr->first>endi)
			{
				if(itr==forbidden.begin() || prev(itr)->second<st)
				{
					return 0;
				}
			}
			return 1;
		}

		int pt_remove(int stuff)
		{
			if(!this->inter_check(stuff, stuff))
			{
				return 0;
			}
			pair<int, int> previ = *prev(forbidden.upper_bound({stuff, 1e9}));
			forbidden.erase(previ);
			
			if(previ.first<=stuff && previ.second>=stuff)
			{
				pair<int, int> insi1 = {previ.first, stuff-1}, insi2 = {stuff+1, previ.second};
				if(insi1.first<=insi1.second)
				{
					forbidden.insert(insi1);
				}	
				if(insi2.first<=insi2.second)
				{
					forbidden.insert(insi2);
				}
			}
			return 1;	
		}
		
		int pt_add(int stuff)
		{
			if(this->inter_check(stuff, stuff))
			{
				return 0;
			}
			pair<int, int> previn = {stuff, stuff};
			if(!forbidden.empty() && forbidden.upper_bound({stuff, 2e9})!=forbidden.begin())
			{
				previn = *prev(forbidden.upper_bound({stuff, 2e9}));
			}
			if(previn.second==stuff-1)
			{
				forbidden.erase(previn);
				previn.second++;	
			}
			else
			{
				previn = {stuff, stuff};
			}	
			forbidden.insert(previn);	
			if(next(forbidden.find(previn))!=forbidden.end())
			{
				auto thing = *next(forbidden.find(previn));
				if(thing.first==previn.second+1)
				{
					forbidden.erase(thing); forbidden.erase(previn);
					previn.second = thing.second;
					forbidden.insert(previn);
				}
			}
			return 1;		
		} 	
};
