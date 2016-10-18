//#include "CompositeKeyProbabilityFilter.h"
//#include "KeyProbabilitySet.h"
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
//							CompositeKeyProbabilityFilter::CompositeKeyProbabilityFilter(KeyProbabilityFilter *filter1, KeyProbabilityFilter *filter2, double weight1, double weight2)
//							{
//								this->filter1 = filter1;
//								this->filter2 = filter2;
//								this->weight1 = weight1;
//								this->weight2 = weight2;
//							}
//
//							void CompositeKeyProbabilityFilter::add(std::vector<double> &values)
//							{
//								filter1->add(values);
//								filter2->add(values);
//							}
//
//							void CompositeKeyProbabilityFilter::add(std::vector<int> &values)
//							{
//								filter1->add(values);
//								filter2->add(values);
//							}
//
//							KeyProbabilitySet *CompositeKeyProbabilityFilter::getNormalizedProbabilities()
//							{
//								KeyProbabilitySet *set1 = filter1->getNormalizedProbabilities();
//								KeyProbabilitySet *set2 = filter2->getNormalizedProbabilities();
//								std::vector<double> set3(12);
//								for (int i = 0; i < 12; ++i)
//								{
//									set3[i] = set1->getProbability(i) * weight1 + set2->getProbability(i) * weight2;
//								}
//								return new KeyProbabilitySet(set3, set1->isMajor(), set1->getType());
//							}
//
//							bool CompositeKeyProbabilityFilter::isAllZeros()
//							{
//								return (filter1->isAllZeros() && filter2->isAllZeros());
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}
