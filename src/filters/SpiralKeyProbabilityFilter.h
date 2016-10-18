//#pragma once
//
//#include "KeyProbabilityFilter.h"
//#include <vector>
//#include <limits>
//#include <stdexcept>
//
////JAVA TO C++ CONVERTER NOTE: Forward class declarations:
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
//							using com::mixshare::rapid_evolution::music::key::spiral::SpiralKey;
//							using com::mixshare::rapid_evolution::util::timing::Semaphore;
//
//							class SpiralKeyProbabilityFilter : public KeyProbabilityFilter
//							{
//
//							private:
//								Semaphore *addLock = new Semaphore(1);
//
//								std::vector<double> circle5ths_buffer(12);
//								SpiralKey *spiralKey;
//								std::vector<double> probability(12);
//
//							public:
//								SpiralKeyProbabilityFilter(SpiralKey *spiralKey);
//
//								virtual void add(std::vector<double> &values);
//
//							private:
//								void processData(std::vector<double> &circle5ths_buffer);
//
//							public:
//								virtual void add(std::vector<int> &values);
//
//								virtual KeyProbabilitySet *getNormalizedProbabilities();
//
//								virtual bool isAllZeros();
//							};
//
//						}
//					}
//				}
//			}
//		}
//	}
//}
