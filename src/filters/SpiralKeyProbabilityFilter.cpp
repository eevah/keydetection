//#include "SpiralKeyProbabilityFilter.h"
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
//							using com::mixshare::rapid_evolution::music::key::spiral::Point;
//							using com::mixshare::rapid_evolution::music::key::spiral::SpiralArray;
//							using com::mixshare::rapid_evolution::music::key::spiral::SpiralKey;
//							using com::mixshare::rapid_evolution::util::timing::Semaphore;
//
//							SpiralKeyProbabilityFilter::SpiralKeyProbabilityFilter(SpiralKey *spiralKey)
//							{
//								this->spiralKey = spiralKey;
//							}
//
//							void SpiralKeyProbabilityFilter::add(std::vector<double> &values)
//							{
//								try
//								{
//									addLock->acquire();
//									for (int i = 0; i < 12; ++i)
//									{
//										circle5ths_buffer[i] = 0.0;
//									}
//									int index = 0;
//									for (int i = 0; i < 12; ++i)
//									{
//										circle5ths_buffer[i] = values[index];
//										index += 7;
//										if (index >= 12)
//										{
//											index -= 12;
//										}
//									}
//									processData(circle5ths_buffer);
//								}
//								catch (std::exception &e)
//								{
//								}
////JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
//								finally
//								{
//									addLock->release();
//								}
//							}
//
//							void SpiralKeyProbabilityFilter::processData(std::vector<double> &circle5ths_buffer)
//							{
//								Point *centerEffect = SpiralArray::getCenterPoint(circle5ths_buffer);
//								if (centerEffect != nullptr)
//								{
//									spiralKey->getKeyProbabilities(centerEffect, probability);
//								}
//							}
//
//							void SpiralKeyProbabilityFilter::add(std::vector<int> &values)
//							{
//								try
//								{
//									addLock->acquire();
//									for (int i = 0; i < 12; ++i)
//									{
//										circle5ths_buffer[i] = 0.0;
//									}
//									int index = 0;
//									for (int i = 0; i < 12; ++i)
//									{
//										circle5ths_buffer[i] = values[index];
//										index += 7;
//										if (index >= 12)
//										{
//											index -= 12;
//										}
//									}
//									processData(circle5ths_buffer);
//								}
//								catch (std::exception &e)
//								{
//								}
////JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
//								finally
//								{
//									addLock->release();
//								}
//							}
//
//							KeyProbabilitySet *SpiralKeyProbabilityFilter::getNormalizedProbabilities()
//							{
//								std::vector<double> normalizedProbabilities(12);
//								double minimum = std::numeric_limits<double>::max();
//								for (int i = 0; i < 12; ++i)
//								{
//									if (probability[i] < minimum)
//									{
//										minimum = probability[i];
//									}
//								}
//								int index = 0;
//								for (int i = 0; i < 12; ++i)
//								{
//									normalizedProbabilities[index] = probability[i] - minimum;
//									index += 7;
//									if (index >= 12)
//									{
//										index -= 12;
//									}
//								}
//								double total = 0;
//								for (int i = 0; i < 12; ++i)
//								{
//									total += normalizedProbabilities[i];
//								}
//								for (int i = 0; i < 12; ++i)
//								{
//									normalizedProbabilities[i] = normalizedProbabilities[i] / total;
//								}
//								return new KeyProbabilitySet(normalizedProbabilities, spiralKey->isMajor(), spiralKey->getType());
//							}
//
//							bool SpiralKeyProbabilityFilter::isAllZeros()
//							{
//								for (int i = 0; i < 12; ++i)
//								{
//									if (probability[i] > 0.0)
//									{
//										return false;
//									}
//								}
//								return true;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}
