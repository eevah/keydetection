//#pragma once
//
//#include "KeyProbabilityFilter.h"
//#include <vector>
//
////JAVA TO C++ CONVERTER NOTE: Forward class declarations:
//namespace com { namespace mixshare { namespace rapid_evolution { namespace audio { namespace detection { namespace key { namespace filters { class KeyProbabilityFilter; } } } } } } }
//namespace com { namespace mixshare { namespace rapid_evolution { namespace audio { namespace detection { namespace key { namespace filters { class KeyProbabilitySet; } } } } } } }
//
//namespace com
//{
//	namespace mixshare
//	{
//		namespace rapid_evolution
//		{
//			namespace audio
//			{
//				namespace detection
//				{
//					namespace key
//					{
//						namespace filters
//						{
//
//							class CompositeKeyProbabilityFilter : public KeyProbabilityFilter
//							{
//
//							private:
//								KeyProbabilityFilter *filter1;
//								KeyProbabilityFilter *filter2;
//								double weight1 = 0;
//								double weight2 = 0;
//
//							public:
//								CompositeKeyProbabilityFilter(KeyProbabilityFilter *filter1, KeyProbabilityFilter *filter2, double weight1, double weight2);
//
//								virtual void add(std::vector<double> &values);
//
//								virtual void add(std::vector<int> &values);
//
//								virtual KeyProbabilitySet *getNormalizedProbabilities();
//
//								virtual bool isAllZeros();
//
//							};
//
//						}
//					}
//				}
//			}
//		}
//	}
//}
