//#include "Semaphore.h"
//
//namespace com
//{
//	namespace mixshare
//	{
//		namespace rapid_evolution
//		{
//			namespace util
//			{
//				namespace timing
//				{
//					using org::apache::log4j::Logger;
//org::apache::log4j::Logger *Semaphore::log = org::apache::log4j::Logger::getLogger(Semaphore::typeid);
//
//					Semaphore::Semaphore(int i) : java::util::concurrent::Semaphore(i, true)
//					{
//					} // fair semaphore
//
//					void Semaphore::release()
//					{
//						//if (log.isTraceEnabled())
//							//log.trace("release(): before");
//						java::util::concurrent::Semaphore::release();
//						//if (log.isTraceEnabled())
//							//log.trace("release(): after");
//					}
//
//					void Semaphore::acquire(const std::string &description) throw(InterruptedException)
//					{
//						//if (log.isTraceEnabled())
//							//log.trace("acquire(): before, description=" + description);
//						java::util::concurrent::Semaphore::acquire();
//						//if (log.isTraceEnabled())
//							//log.trace("acquire(): after, description=" + description);
//					}
//
//					void Semaphore::tryAcquire(const std::string &description, long long timeOutMillis) throw(InterruptedException)
//					{
//						//if (log.isTraceEnabled())
//							//log.trace("tryAcquire(): before, description=" + description);
//						try
//						{
//							if (!java::util::concurrent::Semaphore::tryAcquire(timeOutMillis, TimeUnit::MILLISECONDS))
//							{
//								log->warn(std::string("tryAcquire(): semaphore not acquired=") + description);
//							}
//						}
//						catch (InterruptedException ie)
//						{
//						}
//						//if (log.isTraceEnabled())
//							//log.trace("tryAcquire(): after, description=" + description);
//					}
//				}
//			}
//		}
//	}
//}
